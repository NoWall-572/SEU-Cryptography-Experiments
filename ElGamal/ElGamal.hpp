#pragma once
#define _CRT_SECURE_NO_WARNINGS
#ifndef ELGAMAL_HPP
#define ELGAMAL_HPP
#include "HugeInt.hpp"
#include "SHA-1.hpp"

#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include "HugeInt.hpp"
#include <random>
#include <chrono>
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

class ElGamal
{
public:
	ElGamal() {};
	~ElGamal() {};

	bool isPrime(Hugeint) const;


	Hugeint MaxPrime(Hugeint) const;


	Hugeint Gcd(Hugeint, Hugeint) const;


	bool Bezout(Hugeint, Hugeint, Hugeint&, Hugeint&) const;


	Hugeint DeMo2(Hugeint B, Hugeint N, Hugeint M) const;


	Hugeint ChooseNumber() const;

	bool isPrimitiveRoot(int, long long);

    bool isPrimitiveRoot(const Hugeint& , const Hugeint& );

    // 随机生成一个 g 并检验是否是 p 的原根
	Hugeint generatePrimitiveRoot(const Hugeint&);

	// 扩展欧几里得算法计算乘法逆元
	Hugeint modInverse(Hugeint, Hugeint);
private:
};



#endif