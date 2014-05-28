#include <iostream>
#include <openssl/sha.h>

using namespace std;

int main()
{
  SHA_CTX s;
  int i, size;
  char c[512];
  char sha1[41];
  unsigned char hash[20];
  strcpy(c, "http://www.cplusplus.com/reference/cstring/strcpy/\n");
  int indexOfMDFS = 0;
  
  cout << c << endl;
  
  size = strlen(c);
        
  SHA1_Init(&s);
  
  
  //while((size = read(0, c, 512)) > 0)
  SHA1_Update(&s, c, size);
  
  cout << "Update finish" << endl;
  SHA1_Final(hash, &s);
                  
  for (i=0; i < 20; i++)
  {
    printf("%.2x", (int)hash[i]);
    sprintf(&sha1[indexOfMDFS], "%.2x", (int)hash[i]);
    
    indexOfMDFS += 2;
  }
  printf ("\n");
  memcpy(&sha1[40], "\0", 1);
  
  cout << strlen(sha1) << ")__" << sha1;
  return 0;
}

