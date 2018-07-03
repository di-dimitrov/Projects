#pragma once
#include <iostream>
#include "Line.h"
class Body
{
public:
	~Body();
public:
	static Body* getInst();
public:
	int getsize()const;
	void AddLine(const Line&);
	void DeleteinLine(const char*, int);//da se napishe
	void DeleteLine(int);
	void DeleteLines();
	void ReSize(bool);
	void InsertLine(const Line&,int);//da vnimavame dali 6te izbutva reda nadoly ili nagore!!!!!!!!!!!!!!!!!!!!!!!!!!!
	const Line& operator[](int);
	void setlineindantation(int, int);//da se napishe
private:
	Body() : lines(NULL),size(0){};
	Body(const Body&);
	Body& operator=(const Body&);
private:
	static Body* instance;
	Line* lines;
	 int size;
};// kato podavam index da pravq proverka