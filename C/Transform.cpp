#include "Transform.h"

int Transform::getindentation(const char* str)
{
	int spaces = 0;
	int i = 0;
	int indentation = 0;
	while (str[i] == ' ' || str[i] == '\t')
	{
		if (str[i] == ' ') spaces++;
		if (str[i] == '\t') indentation++;
		if (spaces == 4)
		{
			indentation++;
			spaces = 0;
		}
		i++;
	}
	if (spaces) indentation++;
	return indentation;
}

const char* Transform::getcontent(const char* str)
{
	int k = 0;
	while (str[k] == '\t' || str[k] == ' ')
		k++;
	int len = strlen(str)-k;
	char* content = new (std::nothrow) char[len + 1];
	if (!content)
	{
		std::cout << "Memory problem ;( \n";
		return NULL;
	}
	for (int i = 0; i < len; ++i,++k)
	{
		content[i] = str[k];
	}
	content[len] = '\0';
	return content;
}

const char* Transform::getID(const char* str)
{
	int len = strlen(str);
	for (int i = 0; i < len; ++i)
	{
		if (str[i] == 'i' && str[i + 1] == 'd')
		{
			i += 4;
			char* temp = new (std::nothrow) char[100];
			int j = 0;
			while (str[i] != '"')
			{ 
				temp[j] = str[i];
				j++;
				i++;
			}
			temp[j] = '\0';
			return temp;
		}
	}
	return NULL;
}

Line Transform::convert(const char* str)
{
	const char* id = getID(str);
	const char* content = getcontent(str);
	int indentation = getindentation(str);
	Line a(id, indentation, content);
	delete[] id;
	delete[] content;
 	return a;
}
const char* Transform::revert(const Line& line)
{
	int len = strlen(line.getcontent()) + line.getindentation();
	char* reverted = new (std::nothrow) char[len + 1];
	reverted[0] = '\0';
	for (int i = 0; i < line.getindentation(); ++i)
	{
		strcat(reverted, "\t");
	}
	strcat(reverted, line.getcontent());
	const char* result = reverted;
	return result;
}



//int spaces = 0;
//int i = 0;
//while (str[i] == ' ' || str[i] == '\t')
//{
//	if (str[i] == ' ') ++spaces;
//	if (str[i] == '\t') ++indentation;
//	if (spaces == 4)
//	{
//		indentation++;
//		spaces = 0;
//	}
//	i++;
//}
//if (!spaces) indentation++;
//int len = strlen(str) - i;
//content = new (std::nothrow) char[len + 1];
//if (!content)
//{
//	std::cout << "Memory problem \n";
//	return;
//}
//for (int k = 0; k < len; ++k, ++i)
//{
//	content[k] = str[i];
//}
//if (content[0] == '<')
//{
//	if (content[1] == '/')
//	{
//		beg = false;
//	}
//}
//for (int k = 0; k < len; ++k)
//{
//	if (content[k] == 'i' && content[k + 1] == 'd')
//	{
//		k += 4;
//		char* temp = new (std::nothrow) char[100];
//		int j = 0;
//		while (content[k] != '"')
//		{
//			temp[j] = content[k];
//			j++;
//			k++;
//		}
//		setID(temp);
//		break;
//	}
//}
