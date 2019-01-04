#include<iostream>
#include<string>
#include<stack>
#include"BigNumber.h"

using namespace std;


int main(int argc,char**argv) {
	string s = "1000000000000000000000000000000000000000000000000000000000000000000000000000000000";
	string s1 = "111111111111111111111111111111111111111111111111111111111110";
	BigNumber a(s,10);
	BigNumber b(s1,10);
	BigNumber c(1);
	BigNumber d(10);
	
	d = d.generatePrimeNumber(100);
	d.unsignedprintBigNumber();
	getchar();
	return 0;
}