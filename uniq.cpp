#include "UniqueNorm.h"

static string itoa(int _num)	{
	char strBuf[128];
	
	sprintf(strBuf, "%d", _num);
	
	return strBuf;
}

void Usage(char *czAName)	{
	cerr << czAName << " [OPTIONS] Directories\n";
	cerr << "\t-o Output file name.\n";
	cerr << "\t-i Input file name.\n";
	cerr << "\t-h Current page.\n";
	exit(1);
}

void SimulationOfSaveUniqURL()	{
	
	system("./msort .newURLList.tmp* -o existedURL");	
	system("./msort .maybeFalsePositive.tmp* -o URLForCheck");
	
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
	int nC = 0, oC = 0;
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
			
			nC++;
			string tmpPath = newUrlPath;
			tmpPath += itoa(nC);			
			BFFC.LinksStorer(tmpPath.c_str(), BFFC.newUrlList);			
			//cout << "NEW : [" << BFFC.newUrlList.size() << "]" << endl;
			BFFC.ResetNewURLListBuffs();
		}
		else if (resl == 2)	{
			cout << "Start write URL for false positive check." << endl;
			
			oC++;
			string tmpPath = mayFalPosPath;
			tmpPath += itoa(oC);
			
			BFFC.LinksStorer(tmpPath.c_str(), BFFC.oldUrlList);
			//BFFC.MergeSort(tmpPath.c_str(), 'c');
			//cout << endl << "False Positive : [" << BFFC.FalsePositiveCheck() << "]" << endl << endl;
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
	
	
	SimulationOfSaveUniqURL();
	cout << "Start to check false positive" << endl;
	cout << endl << "False Positive : [" << BFFC.FalsePositiveCheck() << "]" << endl << endl;
}