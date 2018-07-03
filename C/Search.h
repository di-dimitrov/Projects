#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Body.h"

class Search
{
public:
	static int findID(const char*);//vru6ta reda s dadenoto ID 
	static int findEnd(const char*,int);//vru6ta reda v koito se zatvarq taga
	static int findBeg(const char*, int);//reda v koito zapo4va tag
	static int findWord(const char*,int,bool);//int - v koi red tursim dumata,namira na4alniq indeks na podadenata duma
	static const char* getOutsideTag(int,int);//kazva ni dali imame i koi e outside tag //ne moje da imame <a></a><b></b>!!!
	static bool isPath(char**, int, int);//proverqva dali daden tag ot dvumerniqt masiv i dadena posiciq
	static int findEndinLine(const char*, int,bool);
	static const char* getTagbyID(const Line&, const char*);
private:
	static int findTag(const char*, int,bool);//namira reda v koito zapo4va taga
	static const char* substring(int, int,const Line&);
};