#include "filter.h"

int main(int argc, char **argv)
{
	if(argc < 4 || argc > 5)
  {
    printf("%s <Table Size> <Hash Func Num> [Input File] [Old URL File]\n", argv[0]);
    exit(1);
  }
  
  //cout << argv[1] << ", " << argv[2] << ", " << argv[3] << ", " << argv[4] << endl;
  
  char strTest[8];
  char catchStr[73];
  char str[8];
  int index = 0;
  
  strcat(strTest, "WORLDALL");
  
  MDEncode(strTest, catchStr);
  
  //cout << catchStr << endl;
  
  
  return 1;
	
}
