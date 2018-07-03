#include "XHTMLConverter.h"

void XHTMLConverter::start()
{
	char command[200];
	while (true)
	{
		std::cout << "> ";
		std::cin >> command;
		if (!strcmp(command, "open"))
		{
			char filename[200];
			std::cin >> filename;
			filecommands.open(filename);
		}
		if (!strcmp(command, "save"))
		{
			filecommands.save_saveas(filecommands.getfilename());
		}
		if (!strcmp(command, "saveas"))
		{
			char filename[200];
			std::cin >> filename;
			filecommands.save_saveas(filename);
		}
		if (!strcmp(command, "close"))
		{
			filecommands.close();
		}
		if (!strcmp(command, "exit"))
		{
			break;
		}
		if (!strcmp(command, "print"))
		{
			filecommands.print();
		}
		if (!strcmp(command, "create"))
		{ 
			char content[1000];
		
			std::cin.getline(content,1000);
			basecommands.Create(content);
		}
		if (!strcmp(command, "add"))
		{
			char target_id[200];
			char content[1000];
			std::cin >> target_id;
			std::cin.getline(content, 1000);
			basecommands.Add(target_id, content);
		}
		if (!strcmp(command, "erase"))
		{
			char path[200];
			std::cin >> path;//path go transformvame v dvumeren masiv !!!!!!!!!!!!!!!
			char** result = NULL;
			int len = stringtoPath(path,result);
			basecommands.Erase(result,len);
			for (int i = 0; i < len; ++i)
			{
				delete[] result[i];
			}
			delete[] result;
		}
		if (!strcmp(command, "find"))
		{
			char tag_name[200];
			std::cin >> tag_name;
			basecommands.Find(tag_name);
		}
		if (!strcmp(command, "within"))
		{
			char path[200];
			std::cin >> path;
			char** result = NULL;
			int len = stringtoPath(path, result);
			basecommands.Within(result, len);
			for (int i = 0; i < len; ++i)
			{
				delete[] result[i];
			}
			delete[] result;
		}
	}
}

int XHTMLConverter::stringtoPath(const char* str,char** result)
{
	int count = 0;
	int len = strlen(str);
	for (int i = 0; i < len; ++i)
	{
		if (str[i] == '/')
			count++;
	}
	char** path = new (std::nothrow) char*[count + 1];
	int counter = 0;
	int counter2 = 0;
	path[0] = new (std::nothrow) char[100];
	for (int i = 0; i < len; ++i)
	{
		if (str[i] == '/')
		{
			path[counter2][counter] = '\0';
			counter2++;
			counter = 0;
			path[counter2] = new (std::nothrow) char[100];
		}
		else
		{ 
			path[counter2][counter++] = str[i];
		}
	}
	result = path;
	return count+1;
}
