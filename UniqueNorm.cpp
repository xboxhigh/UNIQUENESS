#include "UniqueNorm.h"

static char* BFTable = (char*)malloc(sizeof(char) * BFTABLE_NUM * EACH_TABLE_SIZE);

BFF::BFF()	{
	Init();
}

void BFF::InitBFTable()	{
	long long int index = 0;
	
	for (int i = 0; i < BFTABLE_NUM; i++)	{
		memset(&BFTable[index], 0, EACH_TABLE_SIZE);
		//cout << i << " round setup finish." << endl;
		index += EACH_TABLE_SIZE;
	}
}

void BFF::InitBFIndex()	{
	if (BFTABLE_NUM <= 4)	
		BFIndex = new unsigned int[4];
	else if (BFTABLE_NUM > 4 && BFTABLE_NUM <= 8)		
		BFIndex = new unsigned int[8];
	else if (BFTABLE_NUM > 8 && BFTABLE_NUM <= 13)
		BFIndex = new unsigned int[13];
}

void BFF::Init()	{
	cout << "Start initialization..." << endl;
	
	InitBFIndex();
	newUrlList = vector<string>();
	oldUrlList = vector<string>();
	InitBFTable();
	SetWriteFilePath();
	
	cout << "Finish initialization..." << endl;		
}

void BFF::Reset()	{
	ResetNewURLListBuffs();
	ResetOldURLListBuffs();
	ResetBFIndexBuffs();
}

void BFF::ResetOldURLListBuffs()	{	oldUrlList.clear();}
void BFF::ResetNewURLListBuffs()	{	newUrlList.clear();}
void BFF::ResetBFIndexBuffs()	{	memset(BFIndex, 0, BFTABLE_NUM);}
	
int BFF::FalsePositiveCheck()	{
	int falsePositive = 0;
	
	fstream existURLFile, forCheckURLFile, falsePositiveFile;
	existURLFile.open(existedURL.c_str(), ios::in);
	
	if (!existURLFile.is_open())	{
	
		cout << "The first time do the uniqueness !" << endl;
		
		system(("mv " + URLPools + " " + existedURL).c_str());
		
		existURLFile.close();
		return 0;
		
	}	else {
	
		forCheckURLFile.open(URLForCheck.c_str(), ios::in);
		falsePositiveFile.open(fPositive.c_str(), ios::out);
		char lineOfExist[128*1024], lineOfCheck[128*1024];
		bool flag = false;
		int count = 0;	
		memset(lineOfCheck, ' ', 128*1024);
		memset(lineOfExist, ' ', 128*1024);
		while(forCheckURLFile.getline(lineOfCheck, sizeof(lineOfCheck), '\n'))	{

				
			existURLFile.clear();
			existURLFile.seekg(0, existURLFile.beg);
			
			while(existURLFile.getline(lineOfExist, sizeof(lineOfExist), '\n'))	{
				
				if(strcmp(lineOfCheck, lineOfExist) == 0)	{
					flag = true;
					
					break;
				}
			}
			
			if(!flag)	{
				falsePositive++;
				falsePositiveFile << lineOfCheck << endl;
				flag = false;
				//cout << "False Postive : [" << lineOfCheck << "]" << endl;
			}
			
		}
				
		forCheckURLFile.close();
		existURLFile.close();
		falsePositiveFile.close();
	}
	
	return falsePositive;
}

void BFF::MergeSort(string _src, char _type)	{

	string combineCommand = "./msort ";
	
	combineCommand = combineCommand + _src + " ";

	if(_type == 'n')	{
		combineCommand += ("-o " + URLPools);
		system(combineCommand.c_str());
	}
	else if (_type == 'c')	{
		combineCommand  += ("-o " + URLForCheck);
		system(combineCommand.c_str());
	}
	else
		exit(1);
	
	//system(("rm " + _src).c_str());
}

void BFF::LinksStorer(string _filePath, vector<string> _link)	{
	FILE* LinkFile;
	LinkFile = fopen (_filePath.c_str(), "w+");
	
	for (vector<string>::iterator it = _link.begin() ;it != _link.end(); ++it)	{		
		//std::cout << ' ' << *it;		
		fputs(&*it->c_str(), LinkFile);
		fputs("\n", LinkFile);
	}
	
	fclose(LinkFile);
}

/// _str : Input URL str
/// _length : The length of "_str"
void BFF::StrToMD4(const char* _str, int _length)	{
	int n;
    MD4_CTX c;			//int [32]
    unsigned char digest[16];
 
    MD4_Init(&c);

    while (_length > 0) {
        if (_length > 512) {
            MD4_Update(&c, _str, 512);
        } else {
            MD4_Update(&c, _str, _length);
        }
        _length -= 512;
        _str += 512;
    }

    MD4_Final(digest, &c);
	
	int index = 0;
	for (int i = 0; i < BFTABLE_NUM; i++)	{
		memcpy(&BFIndex[i], &digest[index], 4);
		index = index + 4;
	}
}

/// _str : Input URL str
/// _length : The length of "_str"
void BFF::StrToMD5(const char* _str, int _length)	{	
	int n;
    MD5_CTX c;
    unsigned char digest[16];
	
    MD5_Init(&c);

    while (_length > 0) {
        if (_length > 512) {
            MD5_Update(&c, _str, 512);
        } else {
            MD5_Update(&c, _str, _length);
        }
        _length -= 512;
        _str += 512;
    }

    MD5_Final(digest, &c);
	
	int index = 0;
	for (int i = 4; i < BFTABLE_NUM; i++)	{
		memcpy(&BFIndex[i], &digest[index], 4);
		index = index + 4;
	}
}

/// _str : Input URL str
/// _length : The length of "_str"
void BFF::StrToSHA1(const char* _str, int _length)	{
	int n;
    SHA_CTX c;
    unsigned char digest[20];
    unsigned char *resl = digest;

    SHA1_Init(&c);

    while (_length > 0) {
        if (_length > 640) {
            SHA1_Update(&c, _str, 640);
        } else {
            SHA1_Update(&c, _str, _length);
        }
        _length -= 640;
        _str += 640;
    }

    SHA1_Final(digest, &c);
	
	int index = 0;
	for (int i = 8; i < BFTABLE_NUM; i++)	{
		memcpy(&BFIndex[i], &digest[index], 4);
		index = index + 4;
	}
}

int BFF::HexToDec(char _des)	{
	int resul = 0;
		
	if( _des >= '0' && _des <= '9' )
		return _des - '0';
	else
		return 10 + (int)(_des - 'a');
}

int BFF::CheckBFTable()	{
	int byteIndex = 0, bitIndex = 0, checkListCount = 0;
	
	for (int flag = 0; flag < BFTABLE_NUM; flag++)	{	//Check index in the tables sequentially.
		byteIndex = BFIndex[flag] / BFTABLE_NUM;
		bitIndex = BFIndex[flag] % 8;
		
//cout << "flag : " << flag << " byteIndex : " << byteIndex << "  bitIndex : " << bitIndex << endl; 
//cout << "Table : " <<  (BFTable[byteIndex] & (0x01 << bitIndex)) << " plus : "<< (0x01 << bitIndex) << endl;
		
		if((BFTable[byteIndex] & (0x01 << bitIndex)) == (0x01 << bitIndex))	{
			checkListCount++;	
		}	else	{	
			BFTable[byteIndex] = (BFTable[byteIndex] | (0x01 << bitIndex));
		}
	}
	
	
	if	(checkListCount == BFTABLE_NUM)		//URL is found in the BFTable.
		return 1;
	else	{			//URL is not found in the BFTable.
		BFTable[byteIndex] = (BFTable[byteIndex] | (0x01 << bitIndex));		
		return 0;
	}
	return 0;
}

int BFF::SetBFTabelFlag(string _url)	{
	
	if (BFTABLE_NUM <= 4)	{	// BFTABLE_NUM = 1, 2, 3, 4
		StrToMD4(_url.c_str(), strlen(_url.c_str()));	//Calculate md4 hash value.	

	}	else if (BFTABLE_NUM > 4 && BFTABLE_NUM <= 8)	{	// BFTABLE_NUM = 5, 6, 7, 8
		StrToMD4(_url.c_str(), strlen(_url.c_str()));	//Calculate md4 hash value.	
		StrToMD5(_url.c_str(), strlen(_url.c_str()));	//Calculate md5 hash value.	
		
	}	else if (BFTABLE_NUM > 8 && BFTABLE_NUM <= 13)	{	// BFTABLE_NUM = 9, 10 , 11, 12, 13
		StrToMD4(_url.c_str(), strlen(_url.c_str()));	//Calculate md4 hash value.	
		StrToMD5(_url.c_str(), strlen(_url.c_str()));	//Calculate md5 hash value.	
		StrToSHA1(_url.c_str(), strlen(_url.c_str()));	//Calculate sha1 hash value.	
	}
	
	//for (int o= 0; o < BFTABLE_NUM; o++)
	//	cout << o << " # " << BFIndex[o] << endl;
		
	return CheckBFTable();			//Check the BFTable whether the URL is already exist.
}

///Return value : 
///		'0' default, means either newUrlList buffer nor oldUrlList buffer exceed the threshold
///		'1' means that newUrlList buffer exceeds the threshold
///		'2' means that oldUrlList buffer exceeds the threshold
int BFF::UniquenessURLs(string _url)	{
		
	int resl = SetBFTabelFlag(_url);
	//cout << _url << " is processing..." << endl;
	if(resl == 0)	{		//The url not be found in the BFTable. 
		newUrlList.push_back(_url);		
	}	else if (resl == 1)	{
		oldUrlList.push_back(_url);
	}	else	{
		newUrlList.push_back(_url);
	}
	//cout << _url << " is finish..." << endl;

	if (newUrlList.size() == URLLIST_THRESHOLD)	{
		//cout << "new URL write" << endl;
		return 1;
	}
	if (oldUrlList.size() == URLLIST_THRESHOLD)	{
		//cout << "old URL write" << endl;
		return 2;
	}
	
	return 0;
}