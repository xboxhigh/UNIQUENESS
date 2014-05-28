/**/
#include "filter.h"

int MDEncode(char *_srcStr, char *_tarStr)
{
	char MD4Str[33];
	char MD5Str[33];
	char MDFinalStr[73];
	int indexOfMDFS = 0, indexOfEachMDS = 0, flag = 0; 
	
	if(strlen(_srcStr) > 0)
	{
		MD4Data(_srcStr, strlen(_srcStr), MD4Str);
		MD5Data(_srcStr, strlen(_srcStr), MD5Str);
	}
	cout << MD4Str << endl;
	cout << MD5Str << endl;
	
	while(indexOfMDFS < 72)
	{
		if(flag == 0)
		{
			memcpy(&MDFinalStr[indexOfMDFS], &MD4Str[indexOfEachMDS], 8);
			indexOfMDFS += 8;
			indexOfEachMDS += 8;
			memcpy(&MDFinalStr[indexOfMDFS], "\t", 1);
			indexOfMDFS += 1;
			
			if(indexOfEachMDS > 31)
			{
				flag++;				
				indexOfEachMDS = 0;
			}
		}
		else if (flag == 1)
		{
			memcpy(&MDFinalStr[indexOfMDFS], &MD5Str[indexOfEachMDS], 8);
			indexOfMDFS += 8;
			indexOfEachMDS += 8;
			memcpy(&MDFinalStr[indexOfMDFS], "\t", 1);
			indexOfMDFS += 1;
		}		
	}
	memcpy(&MDFinalStr[indexOfMDFS], "\0", 1);
	
	memcpy(_tarStr, MDFinalStr, 73);
	
	
	return 1;
}

