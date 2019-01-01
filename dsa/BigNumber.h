#pragma once
#include<iostream>
#include<string>
#include<stack>
#define MAXLENGTH 64     //二进制的大整数最大长度


class BigNumber {
private:
	bool sign = 0;			//
	int length;
	uint32_t number[MAXLENGTH] ;
	void addBigNumber(BigNumber&, BigNumber&, BigNumber&);
	void unsignedaddBigNumber(BigNumber&, BigNumber&, BigNumber&);
	void unsignedsubBigNumber(BigNumber&, BigNumber&, BigNumber&);
	void unsignedmulBigNumber(BigNumber&, BigNumber&, BigNumber&);
	void unsigneddivBigNumber(BigNumber&, BigNumber&, BigNumber&, BigNumber&);
public:
	bool unsignedisEqual(BigNumber&, BigNumber&);
	BigNumber(uint64_t);
	BigNumber();
	/*n表示string的进制*/
	BigNumber(std::string,int n);
	void unsignedprintBigNumber();
	int compareBigNumber(BigNumber, BigNumber);
	BigNumber operator+(BigNumber);
	BigNumber operator-(BigNumber);
	BigNumber operator*(BigNumber);
	BigNumber operator/(BigNumber);
	BigNumber operator%(BigNumber);
	BigNumber operator=(BigNumber);
	int isBig(BigNumber ,BigNumber);
	BigNumber gcd(BigNumber);
	BigNumber inverseBigNumber(BigNumber);
	int Jacobi(BigNumber);

	/*计算a^bmodc*/
	BigNumber bigNumMod(BigNumber b,BigNumber c);

	/*大整数转换位字符串，十进制的形式的字符串*/
	std::string BigNumberToString();

	/*随机返回一个n位大素数(二进制位)*/
	BigNumber generatePrimeNumber(int n);

	/*Miller-Rabin素性测试*/
	int Miller_Rabin();
}; 

