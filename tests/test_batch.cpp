#include <gtest/gtest.h>
#include <fstream>
#include "stdinput.h"
#include "stdoutput.h"
#include "logoutput.h"
#include "cmdprocessor.h"
using namespace std;

class MocInput : public StdInput
{
public:
	void setLines(const std::deque<std::string>& lines) { m_lines = lines;}

protected:
	std::deque<std::string> m_lines;
	bool getLine(std::string& line) override
	{
		if (m_lines.empty())
			return false;
		line = m_lines.front();
		m_lines.pop_front();
		return true;
	}
};

struct MocProcessor : public CmdProcessor
{
	MocProcessor(size_t maxCmds) : CmdProcessor(maxCmds) {}
	void startBlock() override { m_starts++; }
	void endBlock() override { m_ends++; }
	void eof() override {}
	void process(std::unique_ptr<Command>&& cmd) override { m_cmds.push_back(cmd->m_name); }
	int m_starts = 0;
	int m_ends = 0;
	std::deque<std::string> m_cmds;
};

TEST(Batch, StandardInput)
{
	MocInput input;
	MocProcessor proc{3};
 	input.setCmdProcessor(&proc);

 	input.setLines( { "cmd1", "cmd2", "{", "cmd3", "}", "cmd4"});
	while (true)
	{
		if (!input.read() )
			break;
	}
	EXPECT_EQ(1, proc.m_starts);
	EXPECT_EQ(1, proc.m_ends);
	EXPECT_EQ(4, proc.m_cmds.size());
}

TEST(Batch, StandardOutput)
{
	std::deque<std::unique_ptr<Command>> cmds;
	auto cmd1 = std::make_unique<Command>();
	cmd1->m_name = "cmd1";
	cmds.push_back(std::move(cmd1));

	testing::internal::CaptureStdout();

	StdOutput output;
	output.writeBlock(std::move(cmds));

	std::string outStr = testing::internal::GetCapturedStdout();
	EXPECT_EQ("bulk: cmd1\n", outStr);
}

TEST(Batch, LogOutput)
{
	std::deque<std::unique_ptr<Command>> cmds;
	auto cmd1 = std::make_unique<Command>();
	const std::time_t t = 42;
	cmd1->m_time = t;
	cmd1->m_name = "cmd1";
	cmds.push_back(std::move(cmd1));

	LogOutput output;
	std::string fname = output.makeFileName(t);
	output.writeBlock(std::move(cmds));

	std::ifstream ifs(fname);
	std::string line;
	std::getline(ifs, line, '\t');

	EXPECT_EQ("bulk: cmd1\n", line);
}

TEST(Batch, LimitedStateOnly)
{
	MocInput input;
	CmdProcessor proc{ 3 };
	StdOutput output;
	input.setCmdProcessor(&proc);
	proc.addOutput(&output);

	testing::internal::CaptureStdout();

	input.setLines({ "cmd1", "cmd2", "cmd3", "cmd4", "cmd5" });
	while (true)
	{
		if (!input.read())
			break;
	}

	std::string outStr = testing::internal::GetCapturedStdout();
	EXPECT_EQ("bulk: cmd1, cmd2, cmd3\nbulk: cmd4, cmd5\n", outStr);
}

TEST(Batch, MixedStates)
{
	MocInput input;
	CmdProcessor proc{ 3 };
	StdOutput output;
	input.setCmdProcessor(&proc);
	proc.addOutput(&output);

	testing::internal::CaptureStdout();

	input.setLines({ "cmd1", "cmd2", "{", "cmd3", "cmd4", "}", "{", "cmd5", "cmd6", 
		"{", "cmd7", "cmd8", "}", "cmd9", "}", "{", "cmd10", "cmd11"});
	while (true)
	{
		if (!input.read())
			break;
	}

	std::string outStr = testing::internal::GetCapturedStdout();
	EXPECT_EQ("bulk: cmd1, cmd2\nbulk: cmd3, cmd4\nbulk: cmd5, cmd6, cmd7, cmd8, cmd9\n", outStr);
}
