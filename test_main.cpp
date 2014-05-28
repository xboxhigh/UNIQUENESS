#include "BFFunc.h"

static char *BFTable;
  
#define MAX_COLUMN_SIZE 512 * 1024 * 1024 	// (4 * 1024 * 1024 * 1024 / 8)
#define MAX_COLUMN_NUM 10

int main(int argc, char **argv)
{  
	if(argc < 1 || argc > 2)
  {
    printf("%s[Input File]\n", argv[0]);
    exit(1);
  }
  
  
  /*Initialize Variables*/
  ENCODEURLINFO URL;
  
  char c[512];
  if(argc > 1)
  {
  	memcpy(URL.urlName, argv[argc - 1], strlen(argv[argc - 1]) + 1);  
  }
  else
  {  	
  	strcpy(c, "https://www.cgu.edu.tw\0");
  	memcpy(URL.urlName, c, strlen(c) + 1);  
  }
  
	/*Initialize BF Table*/  
  BFTable_Init(BFTable, MAX_COLUMN_NUM, MAX_COLUMN_SIZE);	
	/*Encoding URL to BFIndex*/
	
  cout << "URL for test : " << URL.urlName << endl;
    
  BF_Encode(&URL);
  /*The First Filter Phase*/
  BFUniqueness(BFTable, &URL);
  
   
  for(int i = 0; i < 13; i++)
  	cout << i << "] " << URL.bfIndexList[i] << endl;
  
  
  /*URLs Uniquence*/
  
  
  return 0;
}
