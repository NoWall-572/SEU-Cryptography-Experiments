#pragma once
#pragma warning(disable:4996)
#include <iostream>
using namespace std;
#include<iomanip>
#include<string.h>

#ifndef AES_HPP
#define AES_HPP


class AES
{
public:

	AES() {};
	~AES() 
	{
		cout << "Thank you for your support of using!!! ";
	};

	//定义有限域*2乘法
	unsigned char x2time(unsigned char);

	//定义有限域*3乘法
	unsigned char x3time(unsigned char);

	//定义有限域*4乘法
	unsigned char x4time(unsigned char);

	//定义有限域*8乘法
	unsigned char x8time(unsigned char);

	//定义有限域*9乘法
	unsigned char x9time(unsigned char);

	//定义有限域*B乘法
	unsigned char xBtime(unsigned char);

	//定义有限域*D乘法
	unsigned char xDtime(unsigned char);

	//定义有限域*E乘法
	unsigned char xEtime(unsigned char);

	//定义列混合操作
	void MixColumns(unsigned char*);

	//定义逆向列混淆
	void Contrary_MixColumns(unsigned char*);

	//定义行移位操作：行左循环移位
	void ShiftRows(unsigned char*);

	//逆向行移位
	void Contrary_ShiftRows(unsigned char*);

	//定义s盒字节代换替换操作
	void SubBytes(unsigned char*);

	//逆向字节代换
	void Contrary_SubBytes(unsigned char*);

	//密钥编排，16字节--->44列32bit密钥生成--> 11组16字节:分别用于11轮 轮密钥加运算
	void ScheduleKey(unsigned char*, unsigned char*, int, int);

	//定义轮密钥加操作
	void AddRoundKey(unsigned char*, unsigned char*, int);

	//AES加密函数
	void AesEncryplaintext(unsigned char*, unsigned char*, int);

	//AES 解密函数
	void Contrary_AesEncryplaintext(unsigned char*, unsigned char*, int);

private:
	//定义轮常量表
	const static unsigned char Rcon[10];

	//s盒矩阵 Substitution Table
    const static unsigned char sbox[256];

	//逆向S盒矩阵
	const static unsigned char contrary_sbox[256];


};
#endif