#include "Basecommands.h"

void Basecommands::Add(const char* target_id, const char* content)
{
	Body* body = Body::getInst();
	
	int begining=Search::findID(target_id);
	const char* tagname = Search::getTagbyID((*body)[begining], target_id);
	int end = Search::findEnd(tagname, begining);
	delete[] tagname;
	body->InsertLine(Transform::convert(content), end );//da se vnimava
	body->setlineindantation(end, (*body)[end + 1].getindentation() + 1);
}
void Basecommands::Create(const char* content)
{
	Body* body = Body::getInst();
	body->InsertLine(Transform::convert(content), body->getsize()-2);
	body->setlineindantation(body->getsize() - 3, 2);
}
void Basecommands::Erase(char** path,int size)
{
	Body* body = Body::getInst();
	if (size <= 2 || (!strcmp(path[0], "html") && !strcmp(path[1],"body")))
	{
		std::cout << "Erased 0 element(s) \n";
		return;
	}
	int count = 0;
	int i = 0;
	int j = 0;
	int positionInLine = 0;
	bool hasOutside = true;
	while (true)
	{
		i = Search::findBeg(path[size-1], i );
		if (i == -1) break;
		hasOutside = true;
		while (hasOutside)
		{
			positionInLine = Search::findWord(path[size - j - 1], i,true);
			const char* outsidetag = Search::getOutsideTag(i, positionInLine - 1);
			if (!outsidetag || strcmp(outsidetag, path[size - j - 2]))
			{
				hasOutside = false;
			}
			else j++;
			delete[] outsidetag;
		}
		
		if (Search::isPath(path, size - j - 1, i))
		{
			int endposition = Search::findEndinLine(path[size - 1], i,false);
			if (endposition == -1)
			{
				int endtag = Search::findEnd(path[size - 1], i);
				for (int k = i; k <= endtag; ++k)
				{
					body->DeleteLine(k);
					
				}
				count++;
			}
			else
			{
				int len = strlen((*body)[i].getcontent());
				if (j == 0 && positionInLine == 1 && endposition == len - 1)
				{
					body->DeleteLine(i);
					count++;
				}
				else
				{
					body->DeleteinLine(path[size - 1], i);
					count++;
				}
			}
		}
	}
	std::cout << "Erased " << count << " element(s). \n";
}

void Basecommands::Find(const char* tag)
{
	Body* body = Body::getInst();

	int i = 0;
	int beg = 0;
	int end = 0;
	while (true)
	{
		i = Search::findBeg(tag,i+1);
		if (i == -1) break;
		beg = Search::findWord(tag, i, true);
		end = Search::findEndinLine(tag, i, false) + 1;
		if (end != -1)
		{
			(*body)[i].print(beg-1, end, 0);
		}
		else
		{
			end = Search::findEnd(tag, i);
			int indentation = (*body)[i].getindentation();
			for (; i < end; ++i)
			{
				(*body)[i].print(0, strlen((*body)[i].getcontent()) - 1, (*body)[i].getindentation() - indentation);
			}
		}
	}
}

void Basecommands::Within(char** path,int size)
{
	Body* body = Body::getInst();
	if (size <= 2 || (!strcmp(path[0], "html") && !strcmp(path[1], "body")))
	{
		return;
	}
	int i = 0;
	int j = 0;
	int positionInLine = 0;
	bool hasOutside = true;
	while (true)
	{
		i = Search::findBeg(path[size - 1], i);
		if (i == -1) break;
		hasOutside = true;
		while (hasOutside)
		{
			positionInLine = Search::findWord(path[size - j - 1], i, false);
			const char* outsidetag = Search::getOutsideTag(i, positionInLine);
			if (!outsidetag || strcmp(outsidetag, path[size - j - 2]))
			{
				hasOutside = false;
			}
			else j++;
			delete[] outsidetag;
		}

		if (Search::isPath(path, size - j - 1, i))
		{
			int endposition = Search::findEndinLine(path[size - 1], i,true);
			if (endposition == -1)
			{
				int endtag = Search::findEnd(path[size - 1], i);
				for (int k = i + 1; k < endtag; ++k)
				{
					(*body)[k].print(0, strlen((*body)[k].getcontent()) - 1, (*body)[k].getindentation());
				}
			}
			else
			{
				(*body)[i].print(positionInLine + 1, endposition - 1, 0);
			}
		}
	}
}