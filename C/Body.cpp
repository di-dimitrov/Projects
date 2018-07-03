#include "Body.h"

Body* Body::instance = NULL;

Body* Body::getInst()
{
	if (!instance)
	{
		instance = new (std::nothrow) Body;
		if (!instance)
		{
			std::cout << "Memory problem ;( \n";
		}
	}
	return instance;
}

Body::~Body()
{
	DeleteLines();
	delete instance;
}

int Body::getsize() const
{
	return size;
}
void Body::DeleteLine(int row_index)
{
	if (!lines)
	{
		std::cout << "There are no lines ... why delete ?!?";
		return;
	}
	Line* lines2 = new (std::nothrow) Line[size];
	for (int i = 0; i < size; ++i)
	{
		lines2[i] = lines[i];
	}
	int counter = 0;
	for (int i = 0; i < size;++i)
	{
		if (i = row_index) continue;
		lines[counter++] = lines2[i];
	}
	ReSize(false);
	delete[] lines2;
}
void Body::DeleteLines()
{
	delete[] lines;
	lines = NULL;
	size = 0;
}
void Body::ReSize(bool add)
{
	Line* lines2;
	if (add)
	{
		
		lines2 = new (std::nothrow) Line[size + 1];
		if (!lines2)
		{
			std::cout << "Memory problem ;( \n";
			return;
		}
		for (int i = 0; i < size; ++i)
		{
			lines2[i] = lines[i];
		}
		delete[] lines;
		lines = lines2;
		size++;
	}
	else
	{
		lines2 = new (std::nothrow) Line[size - 1];
		if (!lines2)
		{
			std::cout << "Memory problem ;( \n";
			return;
		}
		for (int i = 0; i < size; ++i)
		{
			lines2[i] = lines[i];
		}
		delete[] lines;
		lines = lines2;
		size--;
	}
	
}
void Body::InsertLine(const Line& line,int index)
{
	if (index < 0 || index >= size)
	{
		std::cout << "Wrong Index \n";
		return;
	}

	Line* lines2 = new (std::nothrow) Line[size];
	for (int i = 0; i < size; ++i)
	{
		lines2[i] = lines[i];
	}
	ReSize(true);
	int counter = 0;
	for (int i = 0; i < size; ++i)
	{
		if (i == index)
		{
			counter++;
			lines[i] = line;
		}
		else
		{
			lines[i] = lines2[i - counter];
		}
	}
	delete[] lines2;
}
const Line& Body::operator[](int index)
{
	if (index < 0 || index >= size)
	{
		std::cout << "Wrong Index \n";
		Line a;
		return a;
	}
	return lines[index];
}
void Body::setlineindantation(int line,int indentation)
{
	if (line < 0 || line >= size)
	{
		std::cout << "Wrong Index \n";
		return;
	}
	lines[line].setindentation(indentation);
}
void Body::AddLine(const Line& line)
{
	if (!lines)
	{
		size = 1;
		lines = new (std::nothrow) Line[size];
		if (!lines)
		{
			std::cout << "Memory problem ;( \n";
			return;
		}
		else
		{
			lines[0] = line;
		}
	}
	else
	{
		ReSize(true);
		lines[size-1] = line;
	}
}
void Body::DeleteinLine(const char* tag, int line)
{
	if (line < 0 || line >= size)
	{
		std::cout << "Wrong Index \n";
		return;
	}
	lines[line].DeleteTag(tag);
}