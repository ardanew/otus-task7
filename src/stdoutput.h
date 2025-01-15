#pragma once
#include "ioutput.h"

/// \brief Outputs a batch to the console
class StdOutput : public IOutput
{
public:
	void writeBlock(const std::deque<std::unique_ptr<Command>>& block) override;
};

