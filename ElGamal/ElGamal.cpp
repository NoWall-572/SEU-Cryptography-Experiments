#include "HugeInt.hpp"
#include "ElGamal.hpp"

// �ж��Ƿ�Ϊ����
bool ElGamal::isPrime(Hugeint number) const
{
	for (Hugeint i(2); i < number.Sqrt() + 1; i++)
	{
		if (number % i == 0)
			return false;
	}
	return true;
}

// ����С�ڸ�������������
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

// �����������
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

// ģ�ظ�ƽ�����㷨
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
	vector<bool> seen(p, false); // ׷�������ݽ��
	long long current = g;
	for (int i = 1; i < p; ++i)
	{
		current = (current * g) % p;
		if (seen[current]) return false; // �������ظ����� g ����ԭ��
		seen[current] = true;
	}
	return true;
}

bool ElGamal::isPrimitiveRoot(const Hugeint& g, const Hugeint& p) 
{
	std::vector<bool> seen(p.toLongLong(), false); // ׷�������ݽ�������� p ����ת��Ϊ��С������
	Hugeint current = g;
	Hugeint one("1");

	for (Hugeint i = one; i < p; i += one)
	{
		current = (current * g) % p;
		long long index = current.toLongLong() - 1; // �� Hugeint ת��Ϊ long long ��������
		if (seen[index]) return false; // �������ظ����� g ����ԭ��
		seen[index] = true;
	}
	return true;
}

// �������һ�� g �������Ƿ��� p ��ԭ��
Hugeint ElGamal::generatePrimitiveRoot(const Hugeint& p)
{
	random_device rd;
	mt19937_64 gen(rd());
	uniform_int_distribution<long long> dis(2, p.toLongLong() - 1); // ���ɵķ�Χ
	

	while (true) 
	{
		Hugeint g(std::to_string(dis(gen)%10+1)); // ����һ������� g
		if (isPrimitiveRoot(g, p))
		{
			return g; // ��� g ��ԭ�������� g
		}
	}
}

// ��չŷ������㷨����˷���Ԫ
Hugeint ElGamal::modInverse(Hugeint k, Hugeint p) 
{
	k = k % p;
	for (Hugeint x = 1; x < p; x++)
		if ((k * x) % p == 1)
			return x;
	return -1; // ��������ڳ˷���Ԫ���򷵻� -1
}