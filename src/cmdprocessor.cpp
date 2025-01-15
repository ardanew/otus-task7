#include "cmdprocessor.h"
#include "limitedstate.h"
#include "unlimitedstate.h"

CmdProcessor::CmdProcessor(size_t maxCommands)
{
	m_currentState = std::make_unique<LimitedState>(m_outputs, maxCommands);
	m_otherState = std::make_unique<UnlimitedState>(m_outputs);
}

void CmdProcessor::addOutput(IOutput* output)
{
	m_outputs.push_back(output);
}

void CmdProcessor::startBlock()
{
	if (m_currentState->startBlock())
		std::swap(m_currentState, m_otherState);
}

void CmdProcessor::endBlock()
{
	if (m_currentState->endBlock())
		std::swap(m_currentState, m_otherState);
}

void CmdProcessor::eof()
{
	m_currentState->eof();
}

void CmdProcessor::process(std::unique_ptr<Command>&& cmd)
{
	m_currentState->process(std::move(cmd));
}