#include <iostream>
#include "Body.h"
#include "Filecommands.h"
#include "Basecommands.h"
class XHTMLConverter
{
public:
	void start();
private:
	int stringtoPath(const char*,char**);
private:
	Filecommands filecommands;
	Basecommands basecommands;
};
