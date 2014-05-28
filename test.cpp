#include <iostream>
#include "unistd.h"

int main(void){
	using namespace std;
	cout << sizeof(long long int) << endl;
	cout << sizeof(off_t) << endl;
	cout << sizeof(int*) << endl;
	return 0;
}

