unique : tmpUni.cpp filter.cpp
	g++ -g tmpUni.cpp filter.cpp -lmd -o unique

test : test_main.cpp BFFunc.cpp globalFunc.cpp
	g++ -g test_main.cpp BFFunc.cpp globalFunc.cpp -lmd -o test		
uniq : UniqueNorm.cpp uniq.cpp
	g++ uniq.cpp UniqueNorm.cpp -lcrypto -o uniq
		