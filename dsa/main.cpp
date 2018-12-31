#include<iostream>
#include<string>
#include<stack>
#include"BigNumber.h"

using namespace std;


int main(int argc,char**argv) {
	string s = "9";
	BigNumber a(s);
	BigNumber b(2);
	BigNumber c(0);
	BigNumber d(0);
	a.unsignedprintBigNumber();
	c = b.inverseBigNumber(a);
	c.unsignedprintBigNumber();
	getchar();
	return 0;
}