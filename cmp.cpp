#include <iostream>
#include <vector>
#include <fstream>
#include <string.h>

using namespace std;

void LinksStorer(string _filePath, vector<string> _link)	{
	FILE* LinkFile;
	LinkFile = fopen (_filePath.c_str(), "w+");
	
	for (vector<string>::iterator it = _link.begin() ;it != _link.end(); ++it)	{		
		//std::cout << ' ' << *it;		
		fputs(&*it->c_str(), LinkFile);
		fputs("\n", LinkFile);
	}
	
	fclose(LinkFile);
}

int main(int argc, char **argv)	{

	fstream fin, fin2;
	
	char buffer1[128*1024];
	char buffer2[128*1024];
	vector<string> UrlList;
	int i =0;
	fin.open("FalsePostive_Other_Sorted", ios::in);	
	fin2.open("Postive_Sorted", ios::in);
	
	while(fin.getline(buffer1, sizeof(buffer1), '\n'))	{
		while(fin2.getline(buffer2, sizeof(buffer2), '\n'))	{
		
			if(strcmp(buffer1, buffer2) == 0)	{
				UrlList.push_back(buffer1);
			}		
		}
		i++;
	}
	cout << "total compare : " << i << endl;
	LinksStorer("ErrorRate", UrlList);
	
	fin.close();
	fin2.close();
}