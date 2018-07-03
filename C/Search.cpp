#include "Search.h"

int Search::findID(const char* ID)
{
	Body* body = Body::getInst();
	for (int i = 0; i < body->getsize(); ++i)
	{
		if ((*body)[i].getID() && !strcmp((*body)[i].getID(), ID))
		{
			return i;
		}
	}
	return -1;
}
int Search::findEnd(const char* tag, int from_row)
{
	Body* body = Body::getInst();
	if (from_row < 0 || from_row >= body->getsize())
	{
		std::cout << "Wrong Index \n";
		return -1;
	}
	return findTag(tag, from_row, false);
}
int Search::findBeg(const char* tag, int from_row)
{
	Body* body = Body::getInst();
	if (from_row < 0 || from_row >= body->getsize())
	{
		std::cout << "Wrong Index \n";
		return -1;
	}
	return findTag(tag, from_row, true);
}
int Search::findTag(const char* tag, int from_row,bool isbeg)
{
	Body* body = Body::getInst();
	if (from_row < 0 || from_row >= body->getsize())
	{
		std::cout << "Wrong Index \n";
		return -1;
	}
	int len = strlen(tag) + 3;
	char* closetag = new (std::nothrow) char[len + 1];
	closetag[0] = '\0';
	if (!isbeg)
	{
		strcat(closetag, "</");
	}
	else
	{
		strcat(closetag, "<");
	}
	strcat(closetag, tag);
	strcat(closetag, ">");
	for (int i = from_row; i < body->getsize(); ++i)
	{
		if (Search::findWord(closetag, i,true) != -1)
		{
			return i;
		}
	}
	return -1;
}
int Search::findWord(const char* word, int row,bool beg)
{
	Body* body = Body::getInst();
	if (row < 0 || row >= body->getsize())
	{
		std::cout << "Wrong Index \n";
		return -1;
	}
	return (*body)[row].findWord(word,beg);
}
const char* Search::getOutsideTag(int line, int position)
{
	Body* body = Body::getInst();
	if (line < 0 || line >= body->getsize())
	{
		std::cout << "Wrong Index \n";
		return NULL;
	}
	int beg = -1;
	int end = -1;

	for (int i = position-2; i >= 0; --i)
	{
		if ((*body)[line].getcontent()[i] == '>')
			end = i;
		if ((*body)[line].getcontent()[i] == '<')
		{
			beg = i;
			break;
		}
	}
	if (beg == -1 || end == -1) return NULL;
	char* outsidetag = new (std::nothrow) char[end - beg];
	int counter = 0;
	for (int i = beg + 1; i < end; ++i)
	{
		outsidetag[counter++] = (*body)[line].getcontent()[i];
	}
	return outsidetag;
}
bool Search::isPath(char** path, int taginPath, int line)
{
	Body* body = Body::getInst();
	if (line < 0 || line >= body->getsize())
	{
		std::cout << "Wrong Index \n";
		return false;
	}
	taginPath--;
	int current_indentation = 0;
	int previous_indentation = 0;
	while (true)
	{
		current_indentation = (*body)[line].getindentation();
		previous_indentation = (*body)[line - 1].getindentation();
		if (current_indentation - previous_indentation == 1)
		{
			int i = 1;
			while ((*body)[line-1].getcontent()[i] != ' ' || (*body)[line-1].getcontent()[i] != '>')
			{
				i++;
			}
			const char* tagname = substring(1, i - 1, (*body)[line-1]);
			if (tagname != path[taginPath] )
			{
				delete[] tagname;
				return false;
			}
			delete[] tagname;
			--taginPath;
		}
		if (!strcmp(path[taginPath], "body"))
		{
			
			return true;
		}
		if (line == 1) return false;
		--line;
	}
}
int Search::findEndinLine(const char* tag, int line,bool beg)
{
	Body* body = Body::getInst();
	if (line < 0 || line >= body->getsize())
	{
		std::cout << "Wrong Index \n";
		return -1;
	}
	int len = strlen(tag) + 3;
	char* closertag = new (std::nothrow) char[len + 1];
	closertag[0] = '\0';
	strcat(closertag, "</");
	strcat(closertag, tag);
	strcat(closertag, ">" );
	int index = (*body)[line].findWord(closertag,beg);
	if (index != -1) return index - 1;
	return -1;
}
const char* Search::getTagbyID(const Line& line, const char* target_id)
{
	int beg = line.findWord(target_id,true);
	int i = beg;
	int j = -1;
	while (line.getcontent()[i] != '<')
	{
		if (line.getcontent()[i] == ' ')
		{
			j = i;
		}
		if (i == 0)
		{
			std::cout << "Error no Tag with that ID \n";
			return NULL;
		}
		--i;
	}
	int taglen = j - i;
	char* tag = new(std::nothrow) char[taglen + 1];
	if (!tag)
	{
		std::cout << "Memory problem \n";
		return NULL;
	}
	int counter = 0;
	for (int k = i + 1; k < j; ++k)
	{
		tag[counter++] = line.getcontent()[k];
	}
	tag[counter] = '\0';
	return tag;
}
const char* Search::substring(int beg,int end,const Line& line)
{
	int len = strlen(line.getcontent());
	if (((beg < 0 || beg >= len) || (end < 0 || end >= len)) && beg < end)
	{
	std::cout << "Invalid index ;( \n";
	return NULL;
	}
	int stringlen = end - beg + 1;
	char* string = new (std::nothrow) char[stringlen + 1];
	int counter = 0;
	for (int i = beg; i <= end; ++i)
	{
		string[counter++] = line.getcontent()[i];
	}
	return string;
}