test : test_main.cpp BFFunc.cpp globalFunc.cpp
	g++ -g test_main.cpp BFFunc.cpp globalFunc.cpp -lmd -o test		
uniq : UniqueNorm.cpp uniq.cpp
	g++ uniq.cpp UniqueNorm.cpp -lcrypto -o uniq
dbms : baseLine_dbms.cpp
	g++ baseLine_dbms.cpp -lmysqlclient -o dbms
cleanbak :
	rm -rf *~
			