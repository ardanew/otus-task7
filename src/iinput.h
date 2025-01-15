#pragma once
#include "command.h"
#include <icmdprocessor.h>

/// \brief Interface for input
class IInput
{
public:
	virtual ~IInput() = default;
	virtual void setCmdProcessor(ICmdProcessor *cmdProcessor) = 0;
	virtual bool read() = 0;
};