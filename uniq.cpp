#include "UniqueNorm.h"

static string itoa(int _num)	{
	char strBuf[128];
	
	sprintf(strBuf, "%d", _num);
	
	return strBuf;
}

void Usage(char *czAName)
{
	cerr << czAName << " [OPTIONS] Directories\n";
	cerr << "\t-o Output file name.\n";
	exit(1);
}



int main(int argc, char **argv)	{

	char opt;
	string outPath = "", inPath = "";
	
	while((opt = getopt(argc, argv, "hi:o:")) != -1 )	{
		switch( opt )	{
			case 'o':
				outPath = optarg;
				break;
			case 'i':
				inPath = optarg;
				break;
			case 'h':				
				Usage(argv[0]);
				break;
			default:
				Usage(argv[0]);
				break;
		}
	}
	
	BFF BFFC;
	const string newUrlPath = ".newURLList.tmp";
	const string mayFalPosPath = ".maybeFalsePositive.tmp";
	
	fstream fin;
	char buffer[128*1024];
		
	cout << "URL uniqueness start..." << endl;
	
	fin.open(inPath.c_str(), ios::in);
	if (!fin.is_open())	{
		cerr << "Error open file " << inPath << ", no such file found !" << endl;
		exit(1);
	}
	
	memset(buffer, ' ', 128*1024);
		
	while(fin.getline(buffer, sizeof(buffer), '\n'))	{
		
		int resl = BFFC.UniquenessURLs(buffer);
		
		if (resl == 1)	{		
			cout << "Start write URL for new URL pool." << endl;
			BFFC.LinksStorer(newUrlPath.c_str(), BFFC.newUrlList);
			BFFC.MergeSort(newUrlPath.c_str(), 'n');

			//cout << "NEW : [" << BFFC.newUrlList.size() << "]" << endl;
			BFFC.ResetNewURLListBuffs();
		}
		else if (resl == 2)	{
			cout << "Start write URL for false positive check." << endl;
			BFFC.LinksStorer(mayFalPosPath.c_str(), BFFC.oldUrlList);
			BFFC.MergeSort(mayFalPosPath.c_str(), 'c');
			cout << endl << "False Positive : [" << BFFC.FalsePositiveCheck() << "]" << endl << endl;
			//cout << "OLD : [" << BFFC.oldUrlList.size() << "]" << endl;
			BFFC.ResetOldURLListBuffs();
		}
	}
	fin.close();
	
	cout << "URL uniqueness finish..." << endl;		
	cout << "Waiting for another job..." << endl;
	
	// Merge sort the NewURLList File
	BFFC.LinksStorer(newUrlPath.c_str(), BFFC.newUrlList);
	

	// Merge sort the mayFalsePositive URLs		
	BFFC.LinksStorer(mayFalPosPath.c_str(), BFFC.oldUrlList);

}