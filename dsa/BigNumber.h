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
	BigNumber(std::string);
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
	BigNumber bigNumMod(BigNumber ,BigNumber);
}; 

