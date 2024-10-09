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

    // �������һ�� g �������Ƿ��� p ��ԭ��
	Hugeint generatePrimitiveRoot(const Hugeint&);

	// ��չŷ������㷨����˷���Ԫ
	Hugeint modInverse(Hugeint, Hugeint);
private:
};



#endif