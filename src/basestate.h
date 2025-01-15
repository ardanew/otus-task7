#pragma once
#include <memory>
#include <deque>
#include "command.h"
#include "ioutput.h"

/// \brief Base state class
/// \details Used instead of interface class for state pattern
class BaseState
{
public:
	BaseState(std::deque<IOutput*>& outputs);

	/// \brief Return true if state must be changed
	virtual bool startBlock() = 0;
	/// \brief Return true if state must be changed
	virtual bool endBlock() = 0;
	virtual void eof() = 0;
	virtual void process(std::unique_ptr<Command>&& cmd) = 0;

protected:
	/// \brief Pass the batch of commands to outputs
	void flush();

	std::deque<std::unique_ptr<Command>> m_commands;
	std::deque<IOutput*>& m_outputs;
};