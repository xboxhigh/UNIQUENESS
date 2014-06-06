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
	string path = argv[argc - 1];
	
	while((opt = getopt(argc, argv, "ho:")) != -1 )	{
		switch( opt )	{
			case 'o':
				path = optarg;
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
	string iputPath[argc - 1];
	string newUrlPath = ".newURLList.tmp";
	string mayFalPosPath = ".maybeFalsePositive.tmp";
	
	fstream fin;
	char buffer[128*1024];
	int nC = 0, oC = 0;
	
	//	Get all input file path
	for (int i = optind; i < argc; i++)	
		iputPath[i - 1] = argv[i];
		

	//fin.open(path.c_str(), ios::in);
	
	for (int iTimes = 0; iTimes < (argc - 1); iTimes++)	{	
		cout << "URL uniqueness #" << iTimes << " times start..."<< endl;
		
		fin.open(iputPath[iTimes].c_str(), ios::in);
		memset(buffer, ' ', 128*1024);
		
		while(fin.getline(buffer, sizeof(buffer), '\n'))	{
	
			int resl = BFFC.UniquenessURLs(buffer);
			
			if (resl == 1)	{
				nC++;
				string tmpPath = newUrlPath;
				tmpPath += itoa(nC);
				BFFC.LinksStorer(tmpPath.c_str(), BFFC.newUrlList);
				//cout << "NEW : [" << BFFC.newUrlList.size() << "]" << endl;
				BFFC.ResetNewURLListBuffs();
			}
			else if (resl == 2)	{
				oC++;
				string tmpPath = mayFalPosPath;
				tmpPath += itoa(oC);
				BFFC.LinksStorer(tmpPath.c_str(), BFFC.oldUrlList);
				//cout << "OLD : [" << BFFC.oldUrlList.size() << "]" << endl;
				BFFC.ResetOldURLListBuffs();
			}
		}
		fin.close();
		
		cout << "URL uniqueness #" << iTimes << " times finish..." << endl;		
		cout << "Start write URLs..." << endl;
		
		// Merge sort the NewURLList File
		string tmp1 = newUrlPath;
		tmp1 += itoa(nC);
		BFFC.LinksStorer(tmp1.c_str(), BFFC.newUrlList);
		nC++;
		// Merge sort the mayFalsePositive URLs
		string tmp2 = mayFalPosPath;
		tmp2 += itoa(oC);
		BFFC.LinksStorer(tmp2.c_str(), BFFC.oldUrlList);
		oC++;
		
		cout << "Finish write URLs..." << endl;
		
		BFFC.Reset();
	}
	
	// Start Merge Files
	string commandForNewURLs = "./msort ", commandForCheckFP = "./msort ";
	cout << "Start merge URL files..." << endl;
		
	// Merge sort the NewURLList File	
	for (int count = 0; count < nC; count++)	{
		string combineCommand = newUrlPath;
		combineCommand += itoa(count);
		commandForNewURLs = commandForNewURLs + combineCommand + " ";
	}
	commandForNewURLs += "-o URLPools";
	//cout << commandForNewURLs << endl;
	
	system(commandForNewURLs.c_str());
	//system("rm -rf .newURLList.tmp*");
	
	// Merge sort the mayFalsePositive URLs		
	for (int count = 0; count < nC; count++)	{
		string combineCommand = mayFalPosPath;
		combineCommand += itoa(count);
		commandForCheckFP = commandForCheckFP + combineCommand + " ";
	}
	commandForCheckFP += "-o URLForCheck";
	//cout << commandForCheckFP << endl;
	system(commandForCheckFP.c_str());
	//system("rm -rf .maybeFalsePositive.tmp*");
	
	cout << "Finish merge URL files..." << endl;
	
	
	
	
	cout << "NEW times: [" << nC << "] V.S OLD times: [" << oC << "]" << endl;
	//cout << "NEW : [" << BFFC.newUrlList.size() << "] V.S OLD : [" << BFFC.oldUrlList.size() << "]" << endl;
	
}