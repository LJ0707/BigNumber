#include<iostream>
#include<stack>
#include<string>
#include<cmath>
#include<ctime>
#include"BigNumber.h"

#define TEXTTIME 10

BigNumber zero(0);
BigNumber one(1);
BigNumber ten(10);

BigNumber NUMS[11] = {BigNumber(unsigned int(0)),BigNumber(unsigned int(1)),BigNumber(2),BigNumber(3),BigNumber(4),BigNumber(5),BigNumber(6),
					BigNumber(7),BigNumber(8),BigNumber(9),BigNumber(unsigned int(10))};


BigNumber BigNumber::operator=(BigNumber a) {
	this->length = a.length;
	this->sign = a.sign;
	for (int i = 0; i < MAXLENGTH; i++) {
		this->number[i] = a.number[i];
	}
	return *this;
}

BigNumber BigNumber::operator+(BigNumber a) {
	BigNumber c(0);
	BigNumber::unsignedaddBigNumber(*this, a, c);
	return c;
}

BigNumber BigNumber::operator-(BigNumber a) {
	BigNumber c(0);
	BigNumber::unsignedsubBigNumber(*this, a, c);
	return c;
}

BigNumber BigNumber::operator*(BigNumber a) {
	BigNumber c(0);
	BigNumber::unsignedmulBigNumber(*this, a, c);
	return c;
}

BigNumber BigNumber::operator/(BigNumber a) {
	BigNumber c(0);
	BigNumber d(0);
	BigNumber::unsigneddivBigNumber(*this, a, c, d);
	return c;
}

BigNumber BigNumber::operator%(BigNumber a) {
	BigNumber c(0);
	BigNumber d(0);
	BigNumber::unsigneddivBigNumber(*this, a, c, d);
	return d;
}

/*向屏幕输出无符号大整数*/
void BigNumber::unsignedprintBigNumber() {
	std::stack<unsigned int> s;
	BigNumber remainder;
	BigNumber tmp = *this;
	if (BigNumber::unsignedisEqual(tmp,zero)) {
		std::cout << 0 << std::endl;
	}
	while (!BigNumber::unsignedisEqual(tmp, zero)) {
		remainder = tmp % ten;
		tmp = tmp / ten;
		s.push(unsigned int(remainder.number[0]));
	}
	while (!s.empty()) {
		std::cout << s.top();
		s.pop();
	}
	std::cout << std::endl;
}

/*根据string构建无符号大整数对象，n代表进制数*/
BigNumber::BigNumber(std::string s,int n) {
	memset(BigNumber::number, 0, MAXLENGTH*sizeof(uint32_t));
	int len = s.length();
	BigNumber result,tmp;
	result = zero;
	if (n == 10) {								//十进制
		for (int i = 0; i < len; i++) {
			if (i != 0) {
				result = result * ten;
			}
			result = result + NUMS[int(s[i] - '0')];
		}
		*this = result;
	}
	else if (n==2) {						//二进制
		for (int i = 0; i < len; i++) {
			if (i != 0) {
				*this = *this*NUMS[2];
			}
			*this = *this + NUMS[int(s[i] - '0')];
		}
	}
	else {

	}
}

BigNumber::BigNumber(uint64_t num) {
	memset(BigNumber::number, 0, MAXLENGTH * sizeof(uint32_t));
	if (num >> 32) {							//num为64位
		this->length = 2;
		this->number[0] = uint32_t(num&0x00000000ffffffff);
		this->number[1] = uint32_t((num >> 32)&0x00000000ffffffff);
	}
	else {										//num为32位
		this->length = 1;
		this->number[0] = uint32_t(num&0x00000000ffffffff);
	}
}

BigNumber::BigNumber() {
	memset(BigNumber::number, 0, MAXLENGTH * sizeof(uint32_t));
	BigNumber::length = 1;
	BigNumber::number[0] = 0;
}

//void BigNumber::addBigNumber(BigNumber&, BigNumber&, BigNumber&) {
//
//}

/*无符号大整数加法*/
void BigNumber::unsignedaddBigNumber(BigNumber&a, BigNumber&b, BigNumber&result) {
	uint32_t carry = 0;
	result = a;
	if (a.length<b.length) {
		result.length = b.length;
	}
	else {
		result.length = a.length;
	}
	for (int i = 0; i < result.length; i++) {
		uint64_t sum = b.number[i];
		sum = sum + carry + a.number[i];
		carry = (sum >> 32);
		result.number[i] = (sum & 0x00000000ffffffff);
	}
	result.number[result.length] = carry;
	result.length += carry;

}

/*无符号大整数减法*/
void BigNumber::unsignedsubBigNumber(BigNumber&a, BigNumber&b, BigNumber&result) {
	uint32_t borrow = 0;
	result = a;
	for (int i = 0; i < a.length; i++) {
		if ((a.number[i]>b.number[i]) || (a.number[i] == b.number[i] && borrow == 0)) {
			result.number[i] = a.number[i] - b.number[i] - borrow;
			borrow = 0;
		}
		else {
			uint64_t sum = 0x100000000 + a.number[i];
			result.number[i] = uint32_t(sum - b.number[i] - borrow);
			borrow = 1;
		}
	}
	while ((result.number[result.length - 1] == 0)&&result.length>1)result.length--;
}

/*无符号大整数乘法*/
void BigNumber::unsignedmulBigNumber(BigNumber&a, BigNumber&b, BigNumber&result) {
	uint64_t carry = 0;
	result.length = a.length + b.length - 1;
	for (int i = 0; i < result.length; i++) {
		uint64_t sum = carry;
		carry = 0;
		for (int j = 0; j < b.length; j++) {
			if (((i - j) >= 0) && ((i - j)<a.length)) {
				uint64_t mul = a.number[i - j];
				mul =mul* (uint64_t)b.number[j];
				carry = carry + (mul >> 32);
				mul = mul & 0x00000000ffffffff;
				sum = sum + mul;
			}
		}
		carry = carry + (sum >> 32);
		result.number[i] = uint32_t(sum);
	}
	/*处理最高位*/
	if (carry!=0) {
		result.length++;
		result.number[result.length - 1] = uint32_t(carry);
	}
}

/*无符号大整数除法*/
void BigNumber::unsigneddivBigNumber(BigNumber&value1, BigNumber&value2, BigNumber&result, BigNumber&remainder) {
	BigNumber r = zero;
	BigNumber a = value1;
	BigNumber tmp = zero;
	if (BigNumber::compareBigNumber(value1, value2) == 0) {
		result = one;
		remainder = zero;
	}
	else if (BigNumber::compareBigNumber(value1, value2) == -1) {
		result = zero;
		remainder = value1;
	}
	else {
		while (BigNumber::compareBigNumber(a, value2) == 1 || BigNumber::compareBigNumber(a, value2) == 0) {
			uint64_t div = a.number[a.length - 1];
			uint64_t num = value2.number[value2.length - 1];
			uint32_t len = a.length - value2.length;
			if ((div == num) && (len == 0)) {
				r = r + one;
				a = a - value2;
				break;
			}
			if ((div <= num) && (len > 0)) {
				len--;
				div = ((div << 32) + a.number[a.length - 2]);
			}
			div = div / (num + 1);					//试商
			BigNumber multi(div);
			if (len > 0) {
				multi.length = multi.length + len;
				uint32_t i;
				for (i = multi.length - 1; i >= len; i--) {
					multi.number[i] = multi.number[i - len];
				}
				for (i = 0; i < len; i++) {
					multi.number[i] = 0;
				}
			}
			r = r + multi;
			tmp = value2 * multi;
			a = a - tmp;
		}
		result = r;
		remainder = a;
	}
}

/*无符号大整数比较，相等返回0，value1>value2返回1，value1<value2返回-1，感觉这里得改一改*/
int BigNumber::compareBigNumber(BigNumber value1, BigNumber value2) {
	if (value1.sign == 0 && value2.sign == 1) {		//value1>value2
		return 1;
	}
	else if (value1.sign == 1 && value2.sign == 0) {		//value1<value2
		return -1;
	}
	else if (value1.sign == 0 && value2.sign == 0) {
		if (value1.length>value2.length) {
			return 1;
		}
		else if (value1.length<value2.length) {
			return -1;
		}
		else {
			for (int i = 0; i < value1.length; i++) {
				if ((unsigned int)value1.number[value1.length - 1 - i] >(unsigned int) value2.number[value1.length - 1 - i]) {
					return 1;
					break;
				}
				else if ((unsigned int)value1.number[value1.length - 1 - i] == (unsigned int)value2.number[value1.length - 1 - i]) {

				}
				else {
					return -1;
					break;
				}
			}
			return 0;			//value1==value2
		}
	}
	else {
		if (value1.length>value2.length) {
			return -1;
		}
		else if (value1.length<value2.length) {
			return 1;
		}
		else {
			for (int i = 0; i < value1.length; i++) {
				if (value1.number[value1.length - 1 - i] > value2.number[value1.length - 1 - i]) {
					return -1;
				}
				else if (value1.number[value1.length - 1 - i] == value2.number[value1.length - 1 - i]) {

				}
				else {
					return 1;
				}
			}
			return 0;			//value1==value2
		}
	}
}

/*判读无符号大整数是否相等*/
bool BigNumber::unsignedisEqual(BigNumber a, BigNumber b) {
	if (a.length == b.length) {
		for (int i = 0; i < a.length; i++) {
			if (a.number[i] != b.number[i]) {
				return false;
			}
		}
		return true;
	}
	else {
		return false;
	}
}

int BigNumber::isBig(BigNumber a,BigNumber b) {
	int flag = BigNumber::compareBigNumber(a, b);
	if (flag==1) {
		return 1;
	}
	else {
		return 0;
	}
}

BigNumber BigNumber::gcd(BigNumber b) {
	BigNumber y = isBig(*this, b) ? *this : b;
	BigNumber x = isBig(b, *this) ? *this : b;
	BigNumber r = y % x;
	while (!BigNumber::unsignedisEqual(zero,r)) {
		y = x;
		x = r;
		r = y % x;
	}
	return x;
}

BigNumber BigNumber::inverseBigNumber(BigNumber n) {
	BigNumber I, J;
	int x, y;
	BigNumber m = n;
	BigNumber e = *this;
	BigNumber X = 0;
	BigNumber Y = 1;
	x = y = 1;
	while (!BigNumber::unsignedisEqual(e,zero))
	{
		I = m / e;
		J = m % e;
		m = e;
		e = J;
		J = Y;
		Y = Y * I;
		if (x == y)
		{
			if ((BigNumber::compareBigNumber(X,Y)==1)||(BigNumber::compareBigNumber(X,Y)==0))
				Y = X - Y;
			else
			{
				Y = Y - X;
				y = 0;
			}
		}
		else
		{
			Y = X + Y;
			x = 1 - x;
			y = 1 - y;
		}
		X = J;
	}

	if (x == 0)
		X = n - X;

	return X;
}

int BigNumber::Jacobi(BigNumber n) {
	BigNumber x = *this;
	BigNumber y = n;
	BigNumber tmp,tmp1;
	int J = 1;
	while (isBig(y, one)) {
		x = x % y;
		tmp = y / NUMS[2];
		if (isBig(x, tmp)) {
			x = y - x;
			tmp = y % NUMS[4];
			if (BigNumber::unsignedisEqual(tmp, NUMS[3])) {
				J = -J;
			}
		}
		if (BigNumber::unsignedisEqual(x, zero)) {
			x = one;
			y = zero;
			J = 0;
		}
		tmp = x % 4;
		while (BigNumber::unsignedisEqual(tmp, zero)) {
			x = x / NUMS[4];
			tmp = x % 4;
		}
		tmp = x % 2;
		if (BigNumber::unsignedisEqual(tmp, zero)) {
			x = x / 2;
			tmp = y % NUMS[8];
			if (BigNumber::unsignedisEqual(tmp, NUMS[3]) || BigNumber::unsignedisEqual(tmp, NUMS[5])) {
				J = -J;
			}
		}
		tmp = x % 4;
		tmp1 = y % 4;
		if (BigNumber::unsignedisEqual(tmp, NUMS[3]) && BigNumber::unsignedisEqual(tmp1, NUMS[3])) {
			J = -J;
		}
		tmp = x;
		x = y;
		y = tmp;
	}
	return J;
}

/*计算a^bmodc*/
BigNumber BigNumber::bigNumMod(BigNumber b,BigNumber c) {
	BigNumber value = *this;
	BigNumber result = 1;
	BigNumber tmp;
	uint32_t num;
	int count;
	int len = int(log10(b.number[b.length - 1]) / log10(2))+1;
	for (int i = 0; i < b.length;i++) {
		num = b.number[i];
		if (i != (b.length - 1))count = 32;
		else count = len;
		if (num & 0x00000001) {
			result = result * value;
			result = result % c;
		}
		for (int j = 0; j < count - 1; j++) {
			num = (num >> 1);
			value = value * value;
			value = value % c;
			if (num&0x00000001) {
				result = result * value;
				result = result % c;
			}
		}
		if (i != (b.length - 1)) {
			value = value * value;
			value = value % c;
		}
	}
	return result;
}

/*大整数转换位字符串，十进制的形式的字符串*/
std::string BigNumber::BigNumberToString() {
	BigNumber value = *this;
	BigNumber tmp;
	char ch;
	std::string s;
	std::stack<char> tk;
	tmp = value % NUMS[10];
	ch = char(tmp.number[0])+'0';
	tk.push(ch);
	value = value / NUMS[10];
	while (!BigNumber::unsignedisEqual(value,zero)) {
		tmp = value % NUMS[10];
		ch = char(tmp.number[0]) + '0';
		tk.push(ch);
		value = value / NUMS[10];
	}
	while (!tk.empty()) {
		s.push_back(tk.top());
		tk.pop();
	}
	return s;
}

/*随机返回一个n位大素数(二进制位)*/
BigNumber BigNumber::generatePrimeNumber(int n) {
	std::string s;
	std::string s1;
	BigNumber result;
	srand((unsigned)time(0));
	s.resize(n);
	s1.resize(n);
	s[0] = '1';
	s[n - 1] = '1';
	for (int i = 0; i < n; i++)s1[i] = '1';
	BigNumber stand(s1,2);
	for (int i = 1; i < n - 1; i++) {
		s[i] = char(rand() % 2) + '0';
	}
	result = BigNumber::BigNumber(s, 2);
	while (1) {
		if (!(BigNumber::compareBigNumber(result, stand) == -1)) {
			srand((unsigned)time(0));
			for (int i = 1; i < n - 1; i++) {
				s[i] = char(rand() % 2) + '0';
			}
			result = BigNumber::BigNumber(s, 2);
		}
		else {
			result = result + NUMS[2];
		}
		result.unsignedprintBigNumber();
		if (result.Miller_Rabin())break;
	}
	return result;
}

/*Miller-Rabin素性测试*/
int BigNumber::Miller_Rabin() {
	BigNumber value = *this - one;
	BigNumber m = value;
	BigNumber obj = *this;
	int s = 1;
	int r;
	BigNumber tmp(one);
	BigNumber remainder = m % NUMS[2];
	while (BigNumber::unsignedisEqual(remainder, zero)) {
		m = m / 2;
		s++;
		remainder = m % NUMS[2];
	}
	for (int i = 0; i < TEXTTIME;i++) {
		tmp = tmp + 1;
		r = 0;
		BigNumber z = tmp.bigNumMod(m, *this);
		if (BigNumber::unsignedisEqual(z, one) || BigNumber::unsignedisEqual(z, value))continue;
		else {
			while (1) {
				if (r == (s - 1)) {
					return 0;
				}
				z = z.bigNumMod(NUMS[2],*this);
				if (BigNumber::unsignedisEqual(z, value))break;
				r = r + 1;
			}
		}
	}
	return 1;
}