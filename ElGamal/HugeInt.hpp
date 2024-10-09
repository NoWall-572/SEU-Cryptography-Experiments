#pragma once
#define _CRT_SECURE_NO_WARNINGS
#ifndef HUGEINT_HPP
#define HUGEINT_HPP

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iosfwd>
#include <cstring>
#include <stdio.h>
#define MAX_L 1024
using namespace std;


class Hugeint
{
	friend istream& operator>>(istream&, Hugeint&);//����������
	friend ostream& operator<<(ostream&, Hugeint&);//���������
public:
	int len, s[MAX_L];//���ĳ��ȣ���¼����

	//���캯��
	Hugeint();
	Hugeint(const char*);
	Hugeint(const std::string&);
	Hugeint(int);
	//��������
	~Hugeint();

	bool sign = 1;//���� 1���� 0����
	string toStr() const;//ת��Ϊ�ַ�������Ҫ�Ǳ������

	//���ظ�ֵ
	Hugeint operator=(const char*);
	Hugeint operator=(int);
	Hugeint operator=(string);

	//���ظ��ֱȽ�
	bool operator>(const Hugeint&) const;
	bool operator>=(const Hugeint&) const;
	bool operator<(const Hugeint&) const;
	bool operator<=(const Hugeint&) const;
	bool operator==(const Hugeint&) const;
	bool operator!=(const Hugeint&) const;

	//������������
	Hugeint operator+(const Hugeint&) const;
	Hugeint operator++();
	Hugeint operator++(int);
	Hugeint operator+=(const Hugeint&);

	Hugeint operator-(const Hugeint&) const;
	Hugeint operator*(const Hugeint&)const;

	Hugeint operator*(const int num)const;
	Hugeint operator*=(const Hugeint&);

	Hugeint operator/(const Hugeint&)const;
	Hugeint operator/=(const Hugeint&);

	//�����������������
	Hugeint operator%(const Hugeint&)const;//ȡģ��������
	Hugeint factorial()const;//�׳�
	Hugeint Sqrt()const;//��������������ȡ����
	Hugeint pow(const Hugeint&)const;//������

	

	long long toLongLong() const;
	//�����ĺ���
	void clean();//ȥ�������0
};


#endif