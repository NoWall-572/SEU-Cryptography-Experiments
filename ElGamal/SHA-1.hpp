#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <string>
#include <bitset>
#include <math.h>
#include <iomanip>
#include "HugeInt.hpp"
using namespace std;

#ifndef SHA_1_HPP
#define SHA_1_HPP

class SHA1
{
private:
	long long pad[75] = { 0 };
	int lenth_pad = 0;
public:
	bitset<32> Kt[4] = { 0x5A827999,0x6ED9EBA1,0x8F1BBCDC,0xCA62C1D6 };
	bitset<32> Ht[5] = { 0x67452301,0xEFCDAB89,0x98BADCFE,0x10325476,0xC3D2E1F0 };

	//Ft函数
	bitset<32> Ft(int, bitset<32>, bitset<32>, bitset<32>);

	//字符串的拓展函数
	void SHA_PAD(string);
	//循环左移函数
	bitset<32> ROTL(int, bitset<32>);

	//模2^32加函数
	bitset<32> ADD(bitset<32>, bitset<32>);

	//循环体
	void DO(bitset<512> M);

	string hash(string);

	Hugeint hextoHugeint(const string&);
};

#endif // !SHA_1_HPP