#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include "Body.h"
#include "Transform.h"
class Filecommands
{
public:
	Filecommands() : filename(NULL) {}
	~Filecommands();

public:
	void open(const char*);
	void save_saveas(const char*);
	void close();
	void print();
	void setfilename(const char*);
	const char* getfilename() const;
private:
	char* filename;
};
