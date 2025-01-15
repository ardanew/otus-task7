#include "unlimitedstate.h"

UnlimitedState::UnlimitedState(std::deque<IOutput*>& outputs) : BaseState(outputs) {}

bool UnlimitedState::startBlock()
{
	m_starts++;
	return false;
}

bool UnlimitedState::endBlock()
{
	m_starts--;
	if (m_starts == 0)
	{
		m_starts = 1; // for next time
		flush();
		return true;
	}
	return false;
}

void UnlimitedState::eof()
{
}

void UnlimitedState::process(std::unique_ptr<Command>&& cmd)
{
	m_commands.push_back(std::move(cmd));
}
