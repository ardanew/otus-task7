#include "stdinput.h"
#include <iostream>
#include <string>
#include <chrono>

void StdInput::setCmdProcessor(ICmdProcessor* cmdProcessor)
{
	m_cmdProcessor = cmdProcessor;
}

bool StdInput::read()
{
	std::string line;
	if (!getLine(line))
	{
		m_cmdProcessor->eof();
		return false;
	}
	
	if (line == "{")
		m_cmdProcessor->startBlock();
	else if (line == "}")
		m_cmdProcessor->endBlock();
	else
	{
		auto now = std::chrono::system_clock::now();

		auto cmd = std::make_unique<Command>();
		cmd->m_name = line;
		cmd->m_time = std::chrono::system_clock::to_time_t(now);

		m_cmdProcessor->process(std::move(cmd));
	}
	return true;
}

bool StdInput::getLine(std::string& line)
{
	if (!std::getline(std::cin, line))
		return false;
	return true;
}