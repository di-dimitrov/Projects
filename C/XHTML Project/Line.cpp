#include "Line.h"

Line::Line(const char* id, int indentation, const char* content)
:id(NULL), indentation(0), content(NULL)
{
	setID(id);
	this->indentation = indentation;
	setcontent(content);
}


void Line::print(int begining,int end,int indentation) const
{
	int len = strlen(content);
	if ((begining < 0 || begining >= len) || (end < 0 || end >= len))
	{
		std::cout << "Wrong index";
		return;
	}
	for (int i = 0; i < indentation; ++i)
	{
		std::cout << '\t';
	}
	for (int i = begining; i <= end; ++i)
	{
		std::cout << content[i];
	}
	std::cout << '\n';
}
void Line::setindentation(int indentation)
{
	this->indentation = indentation;
}
int Line::getindentation() const
{
	return indentation;
}

Line::Line(const Line& other)
:id(NULL), indentation(0), content(NULL)
{
	setcontent(other.content);
	setID(other.id);
	this->indentation = other.indentation;
}

Line& Line::operator=(const Line& other)
{
	if (this != &other)
	{
		setcontent(other.content);
		setID(other.id);
		this->indentation = other.indentation;
	}
	return *this;
}
Line::~Line()
{
	delete[] id;
	delete[] content;
}

const char* Line::getID() const
{
	return id;
}

void Line::setID(const char* str)
{
	if (str == NULL) return;
	int len = strlen(str);
	if (id) delete[] id;
	id = new (std::nothrow) char[len + 1];
	if (!id)
	{
		std::cout << "Memory problem ;( \n";
		return;
	}
	strcpy(id, str);
}
void Line::setcontent(const char* str)
{
	int len = strlen(str);
	if (content) delete[] content;
	content = new (std::nothrow) char[len + 1];
	if (!content)
	{
		std::cout << "Memory problem ;( \n";
		return;
	}
	strcpy(content, str);
}
const char* Line::getcontent() const
{
	return content;
}
void Line::DeleteTag(const char* tag)
{
	int len = strlen(tag) + 3;
	int beg = findWord(tag,true)-1;
	char* help = new (std::nothrow) char[len + 1];
	strcat(help, "</");
	strcat(help, tag);
	strcat(help, ">");
	int end = findWord(tag, false);
	int contentlen = strlen(content);
	char* newcontent = new (std::nothrow) char[contentlen - (end - beg) + 1];
	int counter = 0;
	for (int i = 0; i < contentlen; ++i)
	{
		if (i >= beg && i <= end) continue;
		newcontent[counter++] = content[i];
	}
	newcontent[counter] = '\0';
	setcontent(newcontent);
	delete[] newcontent;
}
int Line::findWord(const char* word,bool beg) const
{
	if (!content) return -1;
	char* helper = content;
	int len = strlen(content);
	int wordlen = strlen(word);
	
	for (int i = 0; i < len - wordlen + 1; ++i)
	{
		if (!strncmp(helper, word, wordlen))
		{
			if (beg) return i;
			return i + wordlen - 1;
		}
		helper++;
	}
	return -1;
}
