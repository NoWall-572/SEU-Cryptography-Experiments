#include"Diffie_Hellman.hpp"

// 判断是否为素数
bool DH::isPrime(Hugeint number) const
{
	for (Hugeint i(2); i < number.Sqrt()+1; i++)
	{
		if (number % i == 0)
			return false;
	}
	return true;
}

// 返回小于该数的最大的素数
Hugeint DH::MaxPrime(Hugeint number) const
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
Hugeint DH::Gcd(Hugeint number1, Hugeint number2) const
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

// 贝祖等式s*a+t*b=(a,b)
bool DH::Bezout(Hugeint a, Hugeint b, Hugeint& s, Hugeint& t) const
{
	if (a <= 0 || b <= 0)
		return false;
	else
	{
		Hugeint r1 = a;
		Hugeint s1 = 1;
		Hugeint t1 = 0;
		Hugeint r2 = b;
		Hugeint s2 = 0;
		Hugeint t2 = 1;
		Hugeint q = r1 / r2;
		Hugeint temp = r2;
		r2 = r1 - q * temp;
		r1 = temp;
		while (r2 != 0)
		{
			temp = s2;
			s2 = (Hugeint)-1 * s2 * q + s1;
			s1 = temp;
			temp = t2;
			t2 = (Hugeint)-1 * t2 * q + t1;
			t1 = temp;
			q = r1 / r2;
			temp = r2;
			r2 = r1 - q * temp;
			r1 = temp;
		}
		s = s2;
		t = t2;
		return true;
	}
}

// 模重复平方计算法
Hugeint DH::DeMo2(Hugeint B, Hugeint N, Hugeint M) const
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

Hugeint DH::ChooseNumber() const 
{
	
	mt19937 mt(static_cast<long unsigned int>(chrono::high_resolution_clock::now().time_since_epoch().count()));
	uniform_int_distribution<> dist(0, 9);

	int Len = 128;
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
  
	//cout << Prime.toStr() << endl;
	return Prime;
}

Hugeint DH::HugePrimeTable[10] = 
{
	"497151313288639003227658433467309821468692144596567406520186926733820779193144294052783645318605335696527",
	"358068954085315338270699558358324836901341207773066047318065857045629186190164121762873683547665862896598699",
	"5988082198236780683082893827684264698762606460332539303922798132995708051391132878509327408011716470343",
	"268105628270399416288547455987812689352175151115400330113996985091634500525229006108539397710889353420168489",
	"824460813361240123013518483798454425042429337092865559871887066550955746533447340752336898480020838589",
	"32588586719486820055271992698243047335178395930819226444231799750551760432498025552439868703705179383129",
	"20061805489337975089366513481627142376214865186853502324246556808406491400870364388804344647630184376757340431",
	"59776127961569310204182560029797542433822505404471363280471554086883350741230554752820879220957639269",
	"158699563836635190445110465634141782376204320616748682659217921059900390147895824690047186572974655707",
	"57446557924084911000409025038589556977504244852870978514621820391541768841099692415836992555412292429"
};//根据ChooseNumber生成的大素数表