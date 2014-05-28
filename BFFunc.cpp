#include "BFFunc.h"

/*Definition :
  _des : Encoded 2 dimension string, the row size must less than 41 include '\0' character.
  _src : Input string.
*/
int BF_Encode(ENCODEURLINFO *_URL)
{
	/*Init*/
	int res[3] = {0, 0, 0};
	char tmpEncodeStr[3][41];  
	unsigned int tmpIndex[14];
	
	tmpIndex[13] = '\0';
	
	/*Encoding*/
  res[0] = MD4_Encode(tmpEncodeStr[0], _URL->urlName, tmpIndex);
  res[1] = MD5_Encode(tmpEncodeStr[1], _URL->urlName, tmpIndex);  
	res[2] = SHA1_Encode(tmpEncodeStr[2], _URL->urlName, tmpIndex);
  
  //cout << "TMP : (" << strlen(tmpEncodeStr[0]) << ") " << tmpEncodeStr[0] << endl;
  //cout << "TMP : (" << strlen(tmpEncodeStr[1]) << ") " << tmpEncodeStr[1] << endl;
  //cout << "TMP : (" << strlen(tmpEncodeStr[2]) << ") " << tmpEncodeStr[2] << endl;
  
  if(res[0] == 1 && res[1] == 1 && res[2] == 1 )
  {
  	memcpy( _URL->bfIndexList, &tmpIndex, 14 * sizeof(int)); 
  	 	
  	return 1;
  }
  else
  {
  	if(res[0] != 1)
  	{
  		cout << "SHA1 encoding error ! " << endl;
  		return 0;
  	}
  	else if(res[1] != 1)
  	{
  		cout << "MD4 encoding error ! " << endl;
  		return 0;
  	}
  	else if(res[2] != 1)
  	{
  		cout << "MD5 encoding error ! " << endl;
  		return 0;
  	}
  	else
  	{
  		cout << "Unknow error ! " << endl;
  		return 0;
  	}
  }
  
	return 1;
}

int BF_Decode(char *_des, char *_src, unsigned int *_bfIndexList)
{
	return 1;
}
int BFTable_Init(char *_BFTable, int _colNum, int _colSize)
{
	int MaxTableSize;
	
	MaxTableSize = _colNum * _colSize + 1;
	_BFTable = (char*)malloc(sizeof(char) * MaxTableSize);	
	
	memset(_BFTable, '0', MaxTableSize);
		
	return 1;
}
int BFUniqueness(char *_BFTable, struct ENCODEURLINFO *_URL)
{
	_URL->bfIndexList[12] = 10101010;
	
	cout << _URL->bfIndexList[12] << endl;
	return 1;
}

int MergeSort()
{
	return 1;
}

/*Definition :
  _des : Encoded string, the buffer size must be 33 include '\0' character.
  _src : Input string.
*/
int MD4_Encode(char *_des, char *_src, unsigned int *_bfIndexList)
{
	unsigned int index[4];
	
	MD4Data(_src, strlen(_src), _des);
	_des[32] = '\0';
	IndexCalculation(index, _des, 4);
  
  for(int i = 0; i < 4; i++)
  	_bfIndexList[i] = index[i];
  
	return 1;
}

/*Definition :
  _des : Encoded string, the buffer size must be 33 include '\0' character.
  _src : Input string.
*/
int MD5_Encode(char *_des, char *_src, unsigned int *_bfIndexList)
{
	unsigned int index[4];
	
	MD5Data(_src, strlen(_src), _des);
	_des[32] = '\0'; 	
	
	for(int i = 0; i < 4; i++)
  	_bfIndexList[i + 4] = index[i];
  	
	return 1;
}

/*Definition :
  _des : Encoded string, the buffer size must be 41 include '\0' character.
  _src : Input string.
*/
int SHA1_Encode(char *_des, char *_src, unsigned int *_bfIndexList)
{
	SHA_CTX s;	
  int size, flag;
	unsigned char hash[20];
	unsigned int index[5];
	
	size = strlen(_src);
	flag = 0;
		
	SHA1_Init(&s);
	SHA1_Update(&s, _src, size);
	SHA1_Final(hash, &s);
	
	/*
	for (i=0; i < 20; i++)
  {
    //printf("%.2x", (int)hash[i]);
    sprintf(&_des[flag], "%.2x", (int)hash[i]);
    
    cout << i << "] " << (int)hash[i] << endl;
    flag += 2;
  }
  _des[40] = '\0';
  */
  
 	for(int i = 0; i < 5; i++)
 	{
 		_bfIndexList[i + 8] = (int)hash[i * 4]
 												+	(int)hash[i * 4 + 1] * 256
 												+	(int)hash[i * 4 + 2] * 256 * 256
 												+	(int)hash[i * 4 + 3] * 256 * 256 * 256;
  }
  
	return 1;
}

int IndexCalculation(unsigned int *_tar, char *_src, int _byteNum)
{
	int count = 0;

	while(count < _byteNum)
	{
		_tar[count] = HexToDec(_src[count * 8])
								+ (HexToDec(_src[count * 8 + 1]) * 16)
	  						+ (HexToDec(_src[count * 8 + 2]) * 16 * 16)
	  						+ (HexToDec(_src[count * 8 + 3]) * 16 * 16 * 16)
	  						+ (HexToDec(_src[count * 8 + 4]) * 16 * 16 * 16 * 16) 
	  						+ (HexToDec(_src[count * 8 + 5]) * 16 * 16 * 16 * 16 * 16)
	  						+ (HexToDec(_src[count * 8 + 6]) * 16 * 16 * 16 * 16 * 16 * 16) 
	  						+ (HexToDec(_src[count * 8 + 7]) * 16 * 16 * 16 * 16 * 16 * 16 * 16);
		count++;
	}

	
	return 0;
}
