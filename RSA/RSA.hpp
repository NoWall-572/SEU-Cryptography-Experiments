#pragma once
#include <iostream>
using namespace std;
#include <vector>
#include <cmath>
#include <string.h>
#include <stdio.h>
#include <cstdlib>
#include <random>
#include <chrono>
#include <sstream>


#ifndef RSA_HPP
#define RSA_HPP

class RSA
{
public:
    long long int exgcd(long long int, long long int, long long int*, long long int*);//��չŷ������㷨

    long long int isprime(long long int); //�����ж�

    void primegenerator(long long int*);//����������

    void distributekey();//������Կ

    void rsa_encryption();//���ܺ���

    void rsa_decryption();//���ܺ���

   
};

#endif