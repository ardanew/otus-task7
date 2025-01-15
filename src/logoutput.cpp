#include "logoutput.h"
#include <fstream>
using namespace std;

void LogOutput::writeBlock(const std::deque<std::unique_ptr<Command>>& block)
{
	if (block.empty())
		return;

	std::time_t first = block[0]->m_time;
	std::string fname = makeFileName(first);

	std::ofstream ofs(fname);

	ofs << "bulk: ";
	for (size_t i = 0; i < block.size(); i++)
	{
		ofs << block[i]->m_name;
		if (i != block.size() - 1)
			ofs << ", ";
	}
	ofs << "\n";
}

std::string LogOutput::makeFileName(std::time_t t) const
{
	return std::string("bulk") + std::to_string(t) + ".log";
}