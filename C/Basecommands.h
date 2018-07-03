#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Search.h"
#include "Body.h"
#include "Transform.h"

class Basecommands
{
public:
	void Add(const char*, const char*);
	void Create(const char*);
	void Find(const char*);
	void Erase(char**,int);
	void Within(char**,int);
private:

};