#include "ioutput.h"

/// \brief Outputs commands batch to a log file
class LogOutput : public IOutput
{
public:
	void writeBlock(const std::deque<std::unique_ptr<Command>>& block) override;

protected:
	std::string makeFileName(std::time_t t) const;

	friend class Batch_LogOutput_Test;
};