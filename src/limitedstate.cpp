#include "limitedstate.h"

LimitedState::LimitedState(std::deque<IOutput*>& outputs, size_t maxCmds) : BaseState(outputs), m_maxCmds(maxCmds)
{}

bool LimitedState::startBlock()
{
	flush();
	return true;
}

bool LimitedState::endBlock()
{
	flush();
	return false;
}

void LimitedState::eof()
{
	flush();
}

void LimitedState::process(std::unique_ptr<Command>&& cmd)
{
	m_commands.push_back(std::move(cmd));
	if (m_commands.size() >= m_maxCmds) // TODO
		flush();
}
