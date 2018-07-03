# Project Description

The goal of the project is to edit xhtml files. The main operations are: tag addition, deleting tags, search for tag scope.
In this project the goal was to implement it for only a small number of tags not all existing, since it was a one person project.

The main idea is that all tags are contained within a singleton Body class(only 1 can exist). Each line of code in the xhtml file is a instance
of the object Line. From there on you have a static Transfromation class which navigates you to the tag content,ID etc.
Search class is used to determine where a tag starts,ends,depth and more. 
Basecommands class is just a class which uses all the above to execute user-input.
XHTML Converter class intitializes the program and waits for user input.
