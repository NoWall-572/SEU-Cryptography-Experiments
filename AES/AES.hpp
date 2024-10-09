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

	//����������*2�˷�
	unsigned char x2time(unsigned char);

	//����������*3�˷�
	unsigned char x3time(unsigned char);

	//����������*4�˷�
	unsigned char x4time(unsigned char);

	//����������*8�˷�
	unsigned char x8time(unsigned char);

	//����������*9�˷�
	unsigned char x9time(unsigned char);

	//����������*B�˷�
	unsigned char xBtime(unsigned char);

	//����������*D�˷�
	unsigned char xDtime(unsigned char);

	//����������*E�˷�
	unsigned char xEtime(unsigned char);

	//�����л�ϲ���
	void MixColumns(unsigned char*);

	//���������л���
	void Contrary_MixColumns(unsigned char*);

	//��������λ����������ѭ����λ
	void ShiftRows(unsigned char*);

	//��������λ
	void Contrary_ShiftRows(unsigned char*);

	//����s���ֽڴ����滻����
	void SubBytes(unsigned char*);

	//�����ֽڴ���
	void Contrary_SubBytes(unsigned char*);

	//��Կ���ţ�16�ֽ�--->44��32bit��Կ����--> 11��16�ֽ�:�ֱ�����11�� ����Կ������
	void ScheduleKey(unsigned char*, unsigned char*, int, int);

	//��������Կ�Ӳ���
	void AddRoundKey(unsigned char*, unsigned char*, int);

	//AES���ܺ���
	void AesEncryplaintext(unsigned char*, unsigned char*, int);

	//AES ���ܺ���
	void Contrary_AesEncryplaintext(unsigned char*, unsigned char*, int);

private:
	//�����ֳ�����
	const static unsigned char Rcon[10];

	//s�о��� Substitution Table
    const static unsigned char sbox[256];

	//����S�о���
	const static unsigned char contrary_sbox[256];


};
#endif