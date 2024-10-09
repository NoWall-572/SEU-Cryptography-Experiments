#pragma once
#ifndef DIFFIE_HELLMAN_HPP
#define DIFFIE_HELLMAN_HPP

#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include "HugeInt.hpp"
#include <random>
#include <chrono>
using namespace std;

class DH
{
public:
	DH() {};
	~DH() {};

	bool isPrime(Hugeint) const;


	Hugeint MaxPrime(Hugeint) const;


	Hugeint Gcd(Hugeint, Hugeint) const;


	bool Bezout(Hugeint, Hugeint, Hugeint&, Hugeint&) const;
	

	Hugeint DeMo2(Hugeint B, Hugeint N, Hugeint M) const;


	Hugeint ChooseNumber() const;

	static Hugeint HugePrimeTable[10];

private:
};
#endif // !DIFFIE-HELLMAN_HPP
