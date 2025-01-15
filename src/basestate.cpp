#include "basestate.h"

BaseState::BaseState(std::deque<IOutput*>& outputs) : m_outputs(outputs) 
{}

void BaseState::flush()
{
	for (const auto& output : m_outputs)
		output->writeBlock(m_commands);

	m_commands.clear();
}