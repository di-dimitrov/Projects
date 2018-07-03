#include<iostream>
#include <fstream>
#include "Huffman.h"


int main()
{
	//char* a =  "this is an example of a huffman tree";
	//std::fstream myfile;
	//int len = strlen(a);
	//myfile.open(a, std::ios::out | std::ios::binary);
	//if (myfile.is_open())
	//{
	//	myfile.write(a, len);
	//}
	//return 0;
	/*Huffman huff;
	huff.FillLeaves(a);
	huff.BuildTree();
	const char* archived = huff.CodeString();
	std::cout << archived;
	int arch_len = strlen(archived);
	std::fstream arch_file;
	arch_file.open("Archived", std::ios::out, std::ios::binary);
	if (arch_file.is_open())
	{
		arch_file.write(archived, arch_len);
	}
	arch_file.close();
	std::cout << huff.Decode(archived);
	delete[] archived;*/
	char input[100];
	char command[100];
	char archive[100];
	char file[100];
	int i = 0;
	int counter = 0;
	Huffman hufftree;
	while (true)
	{
		std::cout << "EnterCommand:>";
		std::cin.getline(input, 202);
		i = 0;
		counter = 0;
		while (input[i] != ' ')
		{
			command[counter++] = input[i++];
		}
		command[counter] = '\0';
		counter = 0;
		i++;
		while (input[i] != ' ')
		{
			archive[counter++] = input[i++];
		}
		archive[counter] = '\0';
		counter = 0;
		i++;
		while (input[i] != '\0')
		{
			file[counter++] = input[i++];
		}
		file[counter] = '\0';
		if (!strcmp(command, "-Pack"))
		{
			hufftree.FillLeaves(file);
			hufftree.BuildTree();
			const char* coded = hufftree.CodeString();
			int len = strlen(coded);
			std::fstream arch_file;
			arch_file.open(archive, std::ios::out, std::ios::binary);
			if (arch_file.is_open())
			{
				arch_file.write(archive, len);
			}
			arch_file.close();
			delete[] coded;
		}
		if (!strcmp(command, "-Unpack"))
		{
			char* string_01;
			std::fstream arch_file;
			arch_file.open(archive, std::ios::in | std::ios::binary);
			if (arch_file.is_open())
			{
				arch_file.seekg(0, std::ios::end);
				int size = arch_file.tellg();
				arch_file.seekg(0, std::ios::beg);
				string_01 = new char[size+1];
				arch_file.read(string_01, size);
				string_01 = '\0';
			}
			arch_file.close();
			const char* decoded = hufftree.Decode(string_01);
			std::fstream decoded_file;
			decoded_file.open(file, std::ios::out | std::ios::binary);
			if (decoded_file.is_open())
			{
				int decoded_size = strlen(decoded);
				decoded_file.write(decoded, decoded_size);
			}
			decoded_file.close();
			delete[] decoded;
		}
	}
	return 0;
}