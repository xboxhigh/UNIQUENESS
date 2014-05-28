#include "globalFunc.h"

string itoa(int _num)	{
	char strBuf[128];
	
	sprintf(strBuf, "%d", _num);
	
	return strBuf;
}