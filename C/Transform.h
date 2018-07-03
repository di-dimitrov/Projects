#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include "Line.h"

class Transform
{
public:
	static Line convert(const char*);
	static const char* revert(const Line&);
private:
	static int getindentation(const char*);
	static const char* getID(const char*);
	static const char* getcontent(const char*);
private:
	Transform();
	~Transform();
	Transform(const Transform&);
	Transform& operator=(const Transform&);
};