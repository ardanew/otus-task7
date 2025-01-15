#include <iostream>
#include <string>
#include "cmdprocessor.h"
#include "stdinput.h"
#include "stdoutput.h"
#include "logoutput.h"
using namespace std;

void printHelp() { cout << "Usage: batch <numCmds>" << endl; }

int main(int argc, char **argv)
{
	if (argc <= 1)
	{
		printHelp();
		return -1;
	}

	int maxCmds = static_cast<size_t>( stoi(argv[1]) );

	auto input = make_unique<StdInput>();
	auto processor = make_unique<CmdProcessor>(maxCmds);
	auto stdOutput = make_unique<StdOutput>();
	auto logOutput = make_unique<LogOutput>();

	input->setCmdProcessor(processor.get());
	processor->addOutput(stdOutput.get());
	processor->addOutput(logOutput.get());

	while (true)
	{
		if (!input->read())
			break;
	}
    return 0;
}