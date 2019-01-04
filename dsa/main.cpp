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
	a.unsignedprintBigNumber();
	a = a * d;
	cout <<"liangji"<< a.unsignedisEqual(a,b) << endl;
	/*a.unsignedprintBigNumber();
	s1 = a.BigNumberToString();
	cout << s1 << endl;*/
	/*c = a * d;
	c.unsignedprintBigNumber();*/
	/*d = a - c;
	d.unsignedprintBigNumber();
	d = b.bigNumMod(d,a);
	d.unsignedprintBigNumber();*/
	//cout << a.Miller_Rabin() << endl;
	/*d = d.generatePrimeNumber(30);
	d.unsignedprintBigNumber();*/
	getchar();
	return 0;
}