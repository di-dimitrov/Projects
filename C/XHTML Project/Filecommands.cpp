#include "Filecommands.h"

Filecommands::~Filecommands()
{
	delete[] filename;
}

void Filecommands::open(const char* filename)
{
	setfilename(filename);
	std::fstream myfile(filename,std::ios::in);
	if (myfile.is_open())
	{
		Body* body = Body::getInst();
		char c='a';
		int filesize = 0;
		myfile.seekg(0,std::ios::end);
		filesize = myfile.tellg();
		myfile.seekg(0,std::ios::beg);
		char* filecontent = new(std::nothrow) char[filesize + 1];
		int fill = 0;
		while (myfile.get(c))
		{
			filecontent[fill++] = c;
		}
		filecontent[fill] = '\0';
		int counter=0;
		int lastpos = 0;
		int index = 0;
		bool read = false;
		char* line = NULL;
		int contentcounter = 0;
		while (true)
		{
			if ((filecontent[contentcounter] == '\n' || filecontent[contentcounter] == '\0') && !read)
			{
				if (line) delete[] line;
				line = new (std::nothrow) char[counter - lastpos + 1];
				contentcounter = lastpos;
				if (lastpos != 0) contentcounter++;
				index = 0;
				lastpos = counter;
				read = true;
				continue;
			}
			if ((filecontent[contentcounter] == '\n' || filecontent[contentcounter] == '\0') && read)
			{
				line[index] = '\0';
				body->AddLine(Transform::convert(line));
				read = false;
				if (filecontent[contentcounter] == '\0') break;
			}
			if (read)
			{
				line[index++] = filecontent[contentcounter];
			}
			else counter++;
			contentcounter++;
		}
		std::cout << "Successfully opened "<< filename << "\n";
		delete[] line;
		myfile.close();
	}
	else
	{
		myfile.open(filename, std::ios::out);
		myfile.close();
		std::cout << "Successfully opened" << filename << "\n";
	}
}
void Filecommands::save_saveas(const char* filename)
{
	std::fstream myfile;
	//save
	if (this->filename == filename)
	{
		myfile.open(filename, std::ios::out);
	}
	//saveas
	else
	{
		myfile.open(filename, std::ios::out);
	}
	if (!myfile.is_open())
	{
		std::cout << "Fail open failed \n";
		return;
	}
	Body* body = Body::getInst();
	for (int i = 0; i < body->getsize(); ++i)
	{
		const char* p = Transform::revert((*body)[i]);
		if (i != body->getsize() - 1) myfile << p << "\n";
		else
			myfile << p;
		
		delete[] p;
	}
	myfile.close();
}
void Filecommands::close()
{
	Body* body = Body::getInst();
	body->DeleteLines();
	delete[] filename;
	filename = NULL;
}

void Filecommands::print()
{
	Body* body = Body::getInst();
	
	for (int i = 0; i < body->getsize(); ++i)
	{
		(*body)[i].print(0, strlen((*body)[i].getcontent()) - 1, (*body)[i].getindentation());
	}
}
void Filecommands::setfilename(const char* filename)
{
	int len = strlen(filename);
	if (this->filename) delete[] this->filename;
	this->filename = new (std::nothrow) char[len + 1];
	if (!this->filename)
	{
		std::cout << "Memory problem ;( \n";
		return;
	}
	strcpy(this->filename, filename);
} 

const char* Filecommands::getfilename() const
{
	return filename;
}
