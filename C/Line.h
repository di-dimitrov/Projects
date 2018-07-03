#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

class Line 
{
public:
	Line() : id(NULL), indentation(0), content(NULL) {}
	Line(const char*, int, const char*);
	~Line();
	Line(const Line&);
	Line& operator=(const Line&);
public:
	const char* getID() const;
	void setID(const char*);
	void setcontent(const char*);
	const char* getcontent() const;
	void print(int,int,int) const;
	void setindentation(int);
	int getindentation() const;
	void DeleteTag(const char*);
	int findWord(const char*,bool) const;
private:
	char* id;
	int indentation;
	char* content;
};