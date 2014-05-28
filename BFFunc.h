/**/
#ifndef BFFUNC_H
#define BFFUNC_H

#include "globalFunc.h"
#include <md5.h>
#include <md4.h>
#include <openssl/sha.h>

#define BFTABLE_NUM 10
#define EACH_TABLE_SIZE 536870912	/* (32 bits / 8 bits) => (2^32 / 2^3) */

using namespace std;

struct ENCODEURLINFO
{
	char urlName[512];
	unsigned int bfIndexList[14];
};

int BF_Encode(ENCODEURLINFO *_URL);
int BF_Decode(char *_des, char* _src);
int BFTable_Init(char *_BFTable, int _colNum, int _colSize);
int BFUniqueness(char *_BFTable, struct ENCODEURLINFO *_URL);
int MergeSort();
int SHA1_Encode(char *_des, char *_src, unsigned int *_bfIndexList);
int MD4_Encode(char *_des, char *_src, unsigned int *_bfIndexList);
int MD5_Encode(char *_des, char *_src, unsigned int *_bfIndexList);
int IndexCalculation(unsigned int *_tar, char *_src, int _byteNum);

#endif  /* #ifndef BFFUNC_H */ 
