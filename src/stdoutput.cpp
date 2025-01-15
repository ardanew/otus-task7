#include "stdoutput.h"
#include <iostream>
using namespace std;

void StdOutput::writeBlock(const std::deque<std::unique_ptr<Command>>& block)
{
	if (block.empty())
		return;

	cout << "bulk: ";
	for (size_t i = 0; i < block.size(); i++)
	{
		cout << block[i]->m_name;
		if (i != block.size() - 1)
			cout << ", ";
	}
	cout << "\n";
}
