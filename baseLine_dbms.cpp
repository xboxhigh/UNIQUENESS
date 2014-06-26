#include <mysql/mysql.h>
#include <iostream>
#include <stdio.h>      // printf, fopen
#include <stdlib.h>     // exit, EXIT_FAILURE
#include <time.h>       // time_t, struct tm, difftime, time, mktime
#include <fstream>
#include <unistd.h>			// For getopt()
#include <string>

using namespace std;

unsigned int overlappingURLCount = 0;

void finish_with_error(MYSQL *con)	{
	fprintf(stderr, "%s\n", mysql_error(con));
	mysql_close(con);
	exit(1);        
}

// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
const string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}

void Usage(char *czAName)	{
	cerr << czAName << " [OPTIONS] Directories\n";
	cerr << "\t-o Output file name.\n";
	cerr << "\t-i Input file name.\n";
	cerr << "\t-h Current page.\n";
	exit(1);
}

string InsertURLCommand(string _url)	{
	 
	string sqlCom = "";
	
	sqlCom.append("INSERT INTO urlList VALUES(NULL, '");
	sqlCom.append(currentDateTime());
	sqlCom.append("', '");
	sqlCom.append(_url.c_str());
	sqlCom.append("')");
	
	return sqlCom;
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
	
	//cout << "currentDateTime()=" << currentDateTime() << endl;
	
	fstream srcURL, oFile;
	char buffer[128*1024];
	clock_t BegTime, EndTime;			// Initial Clock Variable
	
	srcURL.open(inPath.c_str(), ios::in);
	oFile.open("DBMS_RECORD", ios::out);
	
	// Establish SQL Connection
	MYSQL *con = mysql_init(NULL);
	if (con == NULL)	{
		fprintf(stderr, "%s\n", mysql_error(con));
		exit(1);
	}
	if (mysql_real_connect(con, "120.126.17.115", "dbms", "dbms", "dbms", 0, NULL, 0) == NULL)	{
		finish_with_error(con);
	}
	
	BegTime = clock();		// Set the begining time
	
	// Start insert URLs
	cout << "Start insert URLs into DBMS" << endl;
	while(srcURL.getline(buffer, sizeof(buffer), '\n'))	{
		int relCode = 0;
		relCode = mysql_query(con, InsertURLCommand(buffer).c_str());
		
		if (relCode)	{
			overlappingURLCount++;
		}	else{
		
			MYSQL_RES* result = mysql_store_result(con);
		
			mysql_free_result(result);
		}
	}
	
	EndTime = clock();		// Set the begining time
	
	cout << "Finish insert URLs..." << endl;
	cout << "Overlaping Count : " << overlappingURLCount << endl;
	
	oFile << "Number of Overlapping : " << overlappingURLCount << endl;
	oFile << "Cost of total time : " << ((EndTime - BegTime) / (double)(CLOCKS_PER_SEC)) << endl;
	
	srcURL.close();
	oFile.close();
	mysql_close(con);
	
	return 0;
}