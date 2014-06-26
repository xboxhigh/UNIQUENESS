#include <iostream>
#include <stdio.h>      // printf, fopen
#include <stdlib.h>     // exit, EXIT_FAILURE
#include <time.h>       // time_t, struct tm, difftime, time, mktime
#include <fstream>
#include <unistd.h>			// For getopt()
#include <string>

using namespace std;

struct BUFFER	{
	string* newCache;
	string* oldCache;
	string* uniqCache;
};

void Usage(char *czAName)	{
	cerr << czAName << " [OPTIONS] Directories\n";
	cerr << "\t-o Output file name.\n";
	cerr << "\t-i New URL file name.\n";
	cerr << "\t-c Old URL file name.\n";
	cerr << "\t-h Current page.\n";
	exit(1);
}

int main(int argc, char **argv)	{

	char opt;
	string outPath = "", inPath = "", cPath = "";
	
	while((opt = getopt(argc, argv, "hi:c:o:")) != -1 )	{
		switch( opt )	{
			case 'o':
				outPath = optarg;
				break;
			case 'i':
				inPath = optarg;
				break;
			case 'c':
				cPath = optarg;
				break;
			case 'h':				
				Usage(argv[0]);
				break;
			default:
				Usage(argv[0]);
				break;
		}
	}
	
	fstream existURLFile, forCheckURLFile, oFile, tmpFile;
	char buffer[128*1024];
	bool newFlag = false, oldFlag = false;

	clock_t BegTime, EndTime;			// Initial Clock Variable
	
	forCheckURLFile.open(inPath.c_str(), ios::in);
	existURLFile.open(cPath.c_str(), ios::in);
	tmpFile.open(outPath.c_str(), ios::out);
	oFile.open("MERCATOR-B_RECORD", ios::out);
	
	BUFFER CACHE;
	CACHE.newCache = new string[600];
	CACHE.oldCache = new string[600];
	CACHE.uniqCache = new string[600];
	
	
	while(true)	{
		
		if(oldFlag)	{
		
			existURLFile.seekg(0, existURLFile.beg);
			oldFlag = false;
				
		}	else	{
		
			for(int countNew = 0; countNew < 600; countNew++)	{
				forCheckURLFile.getline(buffer, sizeof(buffer), '\n');
				CACHE.newCache->append(buffer);
				
				if (forCheckURLFile.eof())	{
					newFlag = true;
					break;
				}
			}
			
			for(int countOld = 0; countOld < 600; countOld++)	{
				existURLFile.getline(buffer, sizeof(buffer), '\n');
				CACHE.oldCache->append(buffer);
				
				if (existURLFile.eof())	{
					oldFlag = true;
					break;
				}
			}
		}
		
		if (forCheckURLFile.eof())
			break;
	}
	
	
	
	return 0;
}