#include "UniqueNorm.h"

static string itoa(int _num)	{
	char strBuf[128];
	
	sprintf(strBuf, "%d", _num);
	
	return strBuf;
}

int main(int argc, char **argv)	{

	BFF BFFC;
	
	/*
	string input1, input2, input3;
	input1 = "http://yahoo.com.tw";
	input2 = "http://yahoo.com.tw";
	input3 = "http://yahoo.com.tw/new";
	cout << "NEW : [" << BFFC.newUrlList.size() << "] V.S OLD : [" << BFFC.oldUrlList.size() << "]" << endl;
	*/
	
	string path = argv[argc - 1];
	char buffer[128*1024];	
	fstream fin;
	int nC = 0, oC = 0, tC = 0;
	
	fin.open(path.c_str(), ios::in);	
	cout << "Start URL uniqueness..." << endl;
	
	//BFFC.UniquenessURLs(input3);

	while(fin.getline(buffer, sizeof(buffer), '\n'))	{
	
		int resl = BFFC.UniquenessURLs(buffer);
		
		if (resl == 1)	{
			nC++;
			string tmpPath = "NewURLsLists_";
			tmpPath += itoa(nC);
			BFFC.LinksStorer(tmpPath.c_str(), BFFC.newUrlList);
			//cout << "NEW : [" << BFFC.newUrlList.size() << "]" << endl;
			BFFC.ResetNewURLListBuffs();
		}
		else if (resl == 2)	{
			oC++;
			string tmpPath = "OldURLsLists_";
			tmpPath += itoa(oC);
			BFFC.LinksStorer(tmpPath.c_str(), BFFC.oldUrlList);
			//cout << "OLD : [" << BFFC.oldUrlList.size() << "]" << endl;
			BFFC.ResetOldURLListBuffs();
		}
		
		tC++;
	}
	fin.close();
	
	
	cout << "Finish URL uniqueness..." << endl;
	cout << "Total urls : " << tC << endl;	
	cout << "Start write other URLs..." << endl;
	BFFC.LinksStorer("NewURLsLists_Other", BFFC.newUrlList);
	BFFC.LinksStorer("OldURLsLists_Other", BFFC.oldUrlList);
	cout << "Finish write other URLs..." << endl;
	
	cout << "NEW times: [" << nC << "] V.S OLD times: [" << oC << "]" << endl;
	//cout << "NEW : [" << BFFC.newUrlList.size() << "] V.S OLD : [" << BFFC.oldUrlList.size() << "]" << endl;
	
	
}