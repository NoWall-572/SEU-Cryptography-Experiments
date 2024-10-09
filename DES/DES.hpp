#pragma once
#pragma warning(disable:4996)
#include<iostream>
#include<stdio.h>
using namespace std;
#include<ctime>
#include<string.h>

#ifndef DES_HPP
#define DES_HPP

//构造DES类
class DES
{

public:
	~DES() {} //定义析构函数 
	void set_key(const unsigned char*); //密钥扩展
	void en_transform(const unsigned char*, unsigned char*); //加密变换
	void de_transform(const unsigned char*, unsigned char*); //解密变换
private:
	bool enkey[16][48]; //存放加密的子密钥 
	bool dekey[16][48]; //存放解密的子密钥

	const static unsigned char IP_Table[64];
	//初置换 

	const static unsigned char IPR_Table[64];
	//逆置换 

	const static unsigned char E_Table[48];
	//E表 

	const static unsigned char P_Table[32];
	//置换选择 

	const static unsigned char PC1_Table[56];
	//置换选择1

	const static unsigned char PC2_Table[48];
	//置换选择2

	const static unsigned char LOOP_Table[16];
	//密钥位移（左移次数） 

	const static unsigned char S_Box[8][4][16];
	// S盒 
};


#endif