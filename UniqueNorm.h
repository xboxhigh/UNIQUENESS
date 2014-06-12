#ifndef UNIQUENORM_H
#define UNIQUENORM_H

#include <iostream>
#include <stdio.h>
#include <unistd.h>			// For getopt()
#include <stdlib.h>			// For atoi()
#include <string.h>			// For strtok()
#include <openssl/md5.h>
#include <openssl/md4.h>
#include <openssl/sha.h>
#include <vector>
#include <fstream>

#define URLLIST_THRESHOLD 1024*1024	//	1 GB
#define BFTABLE_NUM 13
#define EACH_TABLE_SIZE 536870911	// (32 bits / 8 bits) => (2^32 / 2^3) 


using namespace std;

class BFF	{
private:
	void Init();
	void InitBFTable();
	void InitBFIndex();
	void SetWriteFilePath()	{URLPools = "URLPools"; URLForCheck = "URLForCheck"; existedURL = "existedURL"; fPositive = "falsePositive";}
	void FlagCalculation();
	void StrToMD4(const char* _str, int _length);
	void StrToMD5(const char* _str, int _length);
	void StrToSHA1(const char* _str, int _length);
	int CheckBFTable();
	int SetBFTabelFlag(string _url);
	
	unsigned int* BFIndex; 
	string URLForCheck;
	string URLPools;
	string existedURL;
	string fPositive;
public:
	BFF();
	~BFF()	{}
	
	void Reset();
	void ResetNewURLListBuffs();
	void ResetOldURLListBuffs();
	void ResetBFIndexBuffs();
	void LinksStorer(string _filePath, vector<string> _link);
	void MergeSort(string _src, char _type);
	int FalsePositiveCheck();
	int HexToDec(char _des);
	int UniquenessURLs(string _url);
	
	vector<string> newUrlList;
	vector<string> oldUrlList;
};


#endif  // #ifndef UNIQUENORM_H 