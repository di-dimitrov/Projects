#pragma once
#include<iostream>
struct node
{
	int freq;
	char symb;
	node* left;
	node* right;
	node() :freq(0), left(NULL), right(NULL),symb('\0'){}
	node(char symb, int freq)
	{
		left = NULL;
		right = NULL;
		this->symb = symb;
		this->freq = freq;
	}
};


class Huffman
{
public:
	Huffman() :trees(NULL), curr_size(0), capacity(2),original_str(NULL){}
	~Huffman();

	
	void FillLeaves(const char* filename);//
	void BuildTree();
	const char* CodeString();
	const char* Decode(const char* string_01);
private:
	bool helpCode(node* root,int level,char* result,char _0_1,char symb);
	void clean();
	void minFreq(int&,int&);//ne mi se pravi struktura za 2 inta...
	int getHeight(node* root);
	void RemovePair(int, int);
	void ReSize();
	bool isLeaf(node* node);
	int minFreq();
	void RemoveMin(int);
private:
	int curr_size;
	int capacity;
	char* original_str;
	node** trees;
};