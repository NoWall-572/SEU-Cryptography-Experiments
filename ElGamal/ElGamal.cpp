#include "HugeInt.hpp"
#include "ElGamal.hpp"

// 判断是否为素数
bool ElGamal::isPrime(Hugeint number) const
{
	for (Hugeint i(2); i < number.Sqrt() + 1; i++)
	{
		if (number % i == 0)
			return false;
	}
	return true;
}

// 返回小于该数的最大的素数
Hugeint ElGamal::MaxPrime(Hugeint number) const
{
	while (number > 0)
	{
		number = number - 1;
		if (isPrime(number))
			return number;
	}
	return 1;
}

// 返回最大公因数
Hugeint ElGamal::Gcd(Hugeint number1, Hugeint number2) const
{
	if (number1 < number2)
	{
		Hugeint temp = number1;
		number1 = number2;
		number2 = temp;
	}
	while (number2 != 0)
	{
		Hugeint temp2 = number2;
		number2 = number1 % number2;
		number1 = temp2;
	}
	return number1;
}

// 模重复平方计算法
Hugeint ElGamal::DeMo2(Hugeint B, Hugeint N, Hugeint M) const
{
	Hugeint a = 1;
	Hugeint b = B;
	while (N != 0)
	{
		if (N % 2 == 0)
		{
			N = N / 2;
			b = (b * b) % M;
		}
		else
		{
			N = N / 2;
			a = (a * b) % M;
			b = (b * b) % M;
		}
	}
	return a;
}

Hugeint ElGamal::ChooseNumber() const
{
	Labchoose:
	mt19937 mt(static_cast<long unsigned int>(chrono::high_resolution_clock::now().time_since_epoch().count()));
	uniform_int_distribution<> dist(0, 9);

	int Len = 5;
	string pri;
	pri.reserve(Len);

	pri.push_back(dist(mt) % 9 + 1 + '0');

	for (int j = 1; j < Len; j++)
	{
		pri.push_back(dist(mt) % 10 + '0');
	}

	Hugeint Prime(pri);
	Prime = Prime * 6;
	Prime = Prime - 1;
	if (!isPrime(Prime))
	{
		goto Labchoose;
	}
	//cout << Prime.toStr() << endl;
	return Prime;
}

bool ElGamal::isPrimitiveRoot(int g, long long p)
{
	vector<bool> seen(p, false); // 追踪所有幂结果
	long long current = g;
	for (int i = 1; i < p; ++i)
	{
		current = (current * g) % p;
		if (seen[current]) return false; // 如果结果重复，则 g 不是原根
		seen[current] = true;
	}
	return true;
}

bool ElGamal::isPrimitiveRoot(const Hugeint& g, const Hugeint& p) 
{
	std::vector<bool> seen(p.toLongLong(), false); // 追踪所有幂结果，假设 p 可以转换为较小的整数
	Hugeint current = g;
	Hugeint one("1");

	for (Hugeint i = one; i < p; i += one)
	{
		current = (current * g) % p;
		long long index = current.toLongLong() - 1; // 将 Hugeint 转换为 long long 用于索引
		if (seen[index]) return false; // 如果结果重复，则 g 不是原根
		seen[index] = true;
	}
	return true;
}

// 随机生成一个 g 并检验是否是 p 的原根
Hugeint ElGamal::generatePrimitiveRoot(const Hugeint& p)
{
	random_device rd;
	mt19937_64 gen(rd());
	uniform_int_distribution<long long> dis(2, p.toLongLong() - 1); // 生成的范围
	

	while (true) 
	{
		Hugeint g(std::to_string(dis(gen)%10+1)); // 生成一个随机数 g
		if (isPrimitiveRoot(g, p))
		{
			return g; // 如果 g 是原根，返回 g
		}
	}
}

// 扩展欧几里得算法计算乘法逆元
Hugeint ElGamal::modInverse(Hugeint k, Hugeint p) 
{
	k = k % p;
	for (Hugeint x = 1; x < p; x++)
		if ((k * x) % p == 1)
			return x;
	return -1; // 如果不存在乘法逆元，则返回 -1
}