#pragma once
#pragma warning(disable:4996)
#include<iostream>
#include<stdio.h>
using namespace std;
#include<ctime>
#include<string.h>

#ifndef DES_HPP
#define DES_HPP

//����DES��
class DES
{

public:
	~DES() {} //������������ 
	void set_key(const unsigned char*); //��Կ��չ
	void en_transform(const unsigned char*, unsigned char*); //���ܱ任
	void de_transform(const unsigned char*, unsigned char*); //���ܱ任
private:
	bool enkey[16][48]; //��ż��ܵ�����Կ 
	bool dekey[16][48]; //��Ž��ܵ�����Կ

	const static unsigned char IP_Table[64];
	//���û� 

	const static unsigned char IPR_Table[64];
	//���û� 

	const static unsigned char E_Table[48];
	//E�� 

	const static unsigned char P_Table[32];
	//�û�ѡ�� 

	const static unsigned char PC1_Table[56];
	//�û�ѡ��1

	const static unsigned char PC2_Table[48];
	//�û�ѡ��2

	const static unsigned char LOOP_Table[16];
	//��Կλ�ƣ����ƴ����� 

	const static unsigned char S_Box[8][4][16];
	// S�� 
};


#endif