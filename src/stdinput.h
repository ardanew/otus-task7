#pragma once
#include "iinput.h"

/// \brief Handles console input
class StdInput : public IInput
{
public:
	bool read() override;
	void setCmdProcessor(ICmdProcessor* cmdProcessor) override;

protected:
	virtual bool getLine(std::string& line);

	ICmdProcessor* m_cmdProcessor = nullptr;
};
