#include "Huffman.h"
#include <fstream>
#include <algorithm>


Huffman::~Huffman()
{

}

void Huffman::minFreq(int& min_index, int&min_ish_index)
{
	int min, min_ish;
	min = trees[0]->freq;
	min_index = 0;
	min_ish = trees[0]->freq;
	min_ish_index = 0;
	for (int i = 0; i < curr_size; i++)
	{
		if (trees[i]->freq < min)
		{
			min = trees[i]->freq;
			min_index = i;
		}
		else
		{
			if (trees[i]->freq < min_ish)
			{
				min_ish = trees[i]->freq;
				min_ish_index = i;
			}
		}
	}
}

void  Huffman::RemovePair(int min, int min_ish)
{
	node** temp = new node*[curr_size-1];
	int counter = 0;
	for (int i = 0; i < curr_size; i++)
	{
		if (i != min && i != min_ish)
		{
			temp[counter++] = trees[i];
		}
	}
	delete[] trees;
	trees = temp;
	curr_size--;
}

void  Huffman::FillLeaves(const char* filename)
{
	int ascii[256] = { 0 };
	std::fstream myfile;
	myfile.open(filename, std::ios::in | std::ios::binary);
	if (myfile.is_open())
	{
		myfile.seekg(0, std::ios::end);
		int size = myfile.tellg();
		myfile.seekg(0,std::ios::beg);
		char* temp = new char[size];
		myfile.read(temp, size);
		temp[size] = '\0';
		original_str = new char[size + 1];
		strcpy(original_str, temp);
		for (int i = 0; i < size;i++)
		{
			ascii[temp[i]]++;
		}
	}
	myfile.close();
	if (!trees)
	{
		trees = new node*[capacity];
	}
	for (int i = 0; i < 256; i++)
	{
		if (ascii[i])
		{
			if (curr_size == capacity) ReSize();
			trees[curr_size++] = new node(i,ascii[i]);
		}
	}
}

void  Huffman::ReSize()
{
	node** temp = new node*[capacity*2];
	capacity *= 2;
	for (int i = 0; i < curr_size; i++)
	{
		temp[i] = trees[i];
	}
	delete[] trees;
	trees = temp;
}
void  Huffman::BuildTree()
{
	int min_index = 0;//index
	//int min_ish = 0;//index
	while (curr_size != 1)
	{
		// vseki put da namiram mina - sled tova da slagam pointer kum nego sled tova go maham s funciq i sled tova pak vikam mina i su6toto
		node* top = new node;
		min_index = minFreq();
		top->freq = trees[min_index]->freq;
		top->left = trees[min_index];
		RemoveMin(min_index);//problemm pri remove na 2roto obhojdane
		curr_size--;
		min_index = minFreq();
		top->freq += trees[min_index]->freq;
		top->right = trees[min_index];
		curr_size++;
		RemoveMin(min_index);
		curr_size--;
		trees[curr_size - 1] = top;
		/*node* top = new node;
		minFreq(min, min_ish);
		top->freq = trees[min]->freq + trees[min_ish]->freq;
		top->left = trees[min];
		top->right = trees[min_ish];
		RemovePair(min, min_ish);
		trees[curr_size - 1] = top;*/
	}
}

int Huffman::getHeight(node* root)
{
	if (!root) return -1;
	return 1 + std::max(getHeight(root->left), getHeight(root->right));
}

const char* Huffman::CodeString()
{
	int len = strlen(original_str);
	int height = getHeight(trees[0]);
	int res_size = len*height;
	char* result = new char[res_size+1];
	//int counter = 0;
	int size_res = 0;
	char* temp = new char[height + 1];
	result[0] = '\0';
	for (int i = 0; i < len; ++i)
	{
		/*counter++;
		if (!helpCode(trees[0]->left, counter, result, '0', original_str[i]))
		helpCode(trees[0]->right, counter, result, '1', original_str[i]);*/
		//tuka ne e nared za6toto v result se zapisva put koito dori da e gre6en si ostava ... i posle si vliza v else
		if (!helpCode(trees[0]->left, 1, temp, '0', original_str[i]))
		{
			temp[0] = '\0';
			helpCode(trees[0]->right, 1, temp, '1', original_str[i]);
		}
		size_res += strlen(temp);
		strcat(result, temp);
	}
	result[size_res] = '\0';
	return result;
}

bool Huffman::helpCode(node* root,int counter, char* result, char code, char symb)
{
	if (isLeaf(root) && symb == root->symb)
	{
		result[counter-1] = code;
		result[counter] = '\0';
		//std::cout << code;
		return true;
	}
	if (isLeaf(root) && symb != root->symb)
	{
		return false;
	}
	result[counter - 1] = code;
	//std::cout << code;
	if (!helpCode(root->left, ++counter, result, '0', symb))
	{
		counter--;
		helpCode(root->right, ++counter, result, '1', symb);
	}
}
bool Huffman::isLeaf(node* node)
{
	if ((!node->left && !node->right))
		return true;
	return false;
}

const char* Huffman::Decode(const char* string_01)
{
	node* root = trees[0];
	
	int len = strlen(string_01);
	char* temp = new char[len + 1];
	int counter = 0;
	for (int i = 0; i < len; i++)
	{
		if (string_01[i] == '0')
		{
			root = root->left;
		}
		else
		{
			root = root->right;
		}
		if (isLeaf(root))
		{
			temp[counter++] = root->symb;
			root = trees[0];
		}
	}
	temp[counter] = '\0';
	return temp;
}

int Huffman::minFreq()
{
	int min = trees[0]->freq;
	int min_index = 0;
	for (int i = 0; i < curr_size; i++)
	{
		if (trees[i]->freq < min)
		{
			min = trees[i]->freq;
			min_index = i;
		}
	}
	return min_index;
}

void Huffman::RemoveMin(int min_index)
{
	node** temp = new node*[curr_size - 1];
	int counter = 0;
	for (int i = 0; i < curr_size; i++)
	{
		if (i != min_index)
		{
			temp[counter++] = trees[i];
		}
	}
	delete[] trees;
	trees = temp;
}