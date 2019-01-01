#include<iostream>
#include<string>
#include<stack>
#include"BigNumber.h"

using namespace std;


int main(int argc,char**argv) {
	string s = "1000000000000000000000000000000000000000000000000000000001";
	BigNumber a(s,10);
	a.unsignedprintBigNumber();
	BigNumber b(1321313123);
	BigNumber c(1);
	BigNumber d(0);
	string s1;
	s1 = a.BigNumberToString();
	cout << s1 << endl;
	d = a - c;
	d.unsignedprintBigNumber();
	d = b.bigNumMod(d,a);
	d.unsignedprintBigNumber();
	//cout << a.Miller_Rabin() << endl;
	/*d = d.generatePrimeNumber(30);
	d.unsignedprintBigNumber();*/
	getchar();
	return 0;
}