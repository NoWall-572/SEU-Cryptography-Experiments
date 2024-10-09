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
    long long int exgcd(long long int, long long int, long long int*, long long int*);//拓展欧几里得算法

    long long int isprime(long long int); //素数判断

    void primegenerator(long long int*);//生成素数表

    void distributekey();//生成密钥

    void rsa_encryption();//加密函数

    void rsa_decryption();//解密函数

   
};

#endif