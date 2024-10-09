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
	friend istream& operator>>(istream&, Hugeint&);//重载输入流
	friend ostream& operator<<(ostream&, Hugeint&);//重载输出流
public:
	int len, s[MAX_L];//数的长度，记录数组

	//构造函数
	Hugeint();
	Hugeint(const char*);
	Hugeint(const std::string&);
	Hugeint(int);
	//析构函数
	~Hugeint();

	bool sign = 1;//符号 1正数 0负数
	string toStr() const;//转化为字符串，主要是便于输出

	//重载赋值
	Hugeint operator=(const char*);
	Hugeint operator=(int);
	Hugeint operator=(string);

	//重载各种比较
	bool operator>(const Hugeint&) const;
	bool operator>=(const Hugeint&) const;
	bool operator<(const Hugeint&) const;
	bool operator<=(const Hugeint&) const;
	bool operator==(const Hugeint&) const;
	bool operator!=(const Hugeint&) const;

	//重载四则运算
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

	//四则运算的衍生运算
	Hugeint operator%(const Hugeint&)const;//取模（余数）
	Hugeint factorial()const;//阶乘
	Hugeint Sqrt()const;//整数开根（向下取整）
	Hugeint pow(const Hugeint&)const;//幂运算

	

	long long toLongLong() const;
	//辅助的函数
	void clean();//去掉多余的0
};


#endif