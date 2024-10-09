#include"HugeInt.hpp"

auto max(int a, int b)
{
	return a > b ? a : b;
}
auto min(int a, int b)
{
	return a < b ? a : b;
}


Hugeint::Hugeint()
{
	memset(s, 0, sizeof(s));
	len = 1;
	sign = 1;
}

Hugeint::Hugeint(const char* num)
{
	*this = num;
}

Hugeint::Hugeint(const string& number)
{
	*this = number.c_str();
} 

Hugeint::Hugeint(int num)
{
	*this = num;
}

string Hugeint::toStr() const
{
	string res;
	res = "";
	for (int i = 0; i < len; i++)
		res = (char)(s[i] + '0') + res;
	if (res == "")
		res = "0";
	if (!sign && res != "0")
		res = "-" + res;
	return res;
}

istream& operator>>(istream& in, Hugeint& num)
{
	string str;
	in >> str;
	num = str;
	return in;
}

ostream& operator<<(ostream& out, Hugeint& num)
{
	out << num.toStr();
	return out;
}

Hugeint Hugeint::operator=(const char* num)
{
	memset(s, 0, sizeof(s));
	char a[MAX_L] = "";
	if (num[0] != '-')
		strcpy(a, num);
	else
		for (int i = 1; i < strlen(num); i++)
			a[i - 1] = num[i];
	sign = !(num[0] == '-');
	len = strlen(a);
	for (int i = 0; i < strlen(a); i++)
		s[i] = a[len - i - 1] - 48;
	return *this;
}

Hugeint Hugeint::operator=(int num)
{
	if (num < 0)
		sign = 0, num = -num;
	else
		sign = 1;
	char temp[MAX_L];
	sprintf(temp, "%d", num);
	*this = temp;
	return *this;
}

Hugeint Hugeint::operator=(const string num)
{
	const char* tmp;
	tmp = num.c_str();
	*this = tmp;
	return *this;
}

bool Hugeint::operator<(const Hugeint& num) const
{
	if (sign ^ num.sign)
		return num.sign;
	if (len != num.len)
		return len < num.len;
	for (int i = len - 1; i >= 0; i--)
		if (s[i] != num.s[i])
			return sign ? (s[i] < num.s[i]) : (!(s[i] < num.s[i]));
	return !sign;
}

bool Hugeint::operator>(const Hugeint& num)const
{
	return num < *this;
}

bool Hugeint::operator<=(const Hugeint& num)const
{
	return !(*this > num);
}

bool Hugeint::operator>=(const Hugeint& num)const
{
	return !(*this < num);
}

bool Hugeint::operator!=(const Hugeint& num)const
{
	return *this > num || *this < num;
}

bool Hugeint::operator==(const Hugeint& num)const
{
	return !(num != *this);
}

Hugeint Hugeint::operator+(const Hugeint& num) const
{
	if (sign ^ num.sign)
	{
		Hugeint tmp = sign ? num : *this;
		tmp.sign = 1;
		return sign ? *this - tmp : num - tmp;
	}
	Hugeint result;
	result.len = 0;
	int temp = 0;
	for (int i = 0; temp || i < (max(len, num.len)); i++)
	{
		int t = s[i] + num.s[i] + temp;
		result.s[result.len++] = t % 10;
		temp = t / 10;
	}
	result.sign = sign;
	return result;
}

Hugeint Hugeint::operator++()
{
	*this = *this + 1;
	return *this;
}

Hugeint Hugeint::operator++(int)
{
	Hugeint old = *this;
	++(*this);
	return old;
}

Hugeint Hugeint::operator+=(const Hugeint& num)
{
	*this = *this + num;
	return *this;
}

Hugeint Hugeint::operator-(const Hugeint& num) const
{
	Hugeint b = num, a = *this;
	if (!num.sign && !sign)
	{
		b.sign = 1;
		a.sign = 1;
		return b - a;
	}
	if (!b.sign)
	{
		b.sign = 1;
		return a + b;
	}
	if (!a.sign)
	{
		a.sign = 1;
		b = Hugeint(0) - (a + b);
		return b;
	}
	if (a < b)
	{
		Hugeint c = (b - a);
		c.sign = false;
		return c;
	}
	Hugeint result;
	result.len = 0;
	for (int i = 0, g = 0; i < a.len; i++)
	{
		int x = a.s[i] - g;
		if (i < b.len) x -= b.s[i];
		if (x >= 0) g = 0;
		else
		{
			g = 1;
			x += 10;
		}
		result.s[result.len++] = x;
	}
	result.clean();
	return result;
}

Hugeint Hugeint::operator * (const Hugeint& num)const
{
	Hugeint result;
	result.len = len + num.len;

	for (int i = 0; i < len; i++)
		for (int j = 0; j < num.len; j++)
			result.s[i + j] += s[i] * num.s[j];

	for (int i = 0; i < result.len; i++)
	{
		result.s[i + 1] += result.s[i] / 10;
		result.s[i] %= 10;
	}
	result.clean();
	result.sign = !(sign ^ num.sign);
	return result;
}

Hugeint Hugeint::operator*(const int num)const
{
	Hugeint x = num;
	Hugeint z = *this;
	return x * z;
}
Hugeint Hugeint::operator*=(const Hugeint& num)
{
	*this = *this * num;
	return *this;
}

Hugeint Hugeint::operator /(const Hugeint& num)const
{
	Hugeint ans;
	ans.len = len - num.len + 1;
	if (ans.len < 0)
	{
		ans.len = 1;
		return ans;
	}

	Hugeint divisor = *this, divid = num;
	divisor.sign = divid.sign = 1;
	int k = ans.len - 1;
	int j = len - 1;
	while (k >= 0)
	{
		while (divisor.s[j] == 0) j--;
		if (k > j) k = j;
		char z[MAX_L];
		memset(z, 0, sizeof(z));
		for (int i = j; i >= k; i--)
			z[j - i] = divisor.s[i] + '0';
		Hugeint dividend = z;
		if (dividend < divid) { k--; continue; }
		int key = 0;
		while (divid * key <= dividend) key++;
		key--;
		ans.s[k] = key;
		Hugeint temp = divid * key;
		for (int i = 0; i < k; i++)
			temp = temp * 10;
		divisor = divisor - temp;
		k--;
	}
	ans.clean();
	ans.sign = !(sign ^ num.sign);
	return ans;
}

Hugeint Hugeint::operator/=(const Hugeint& num)
{
	*this = *this / num;
	return *this;
}

Hugeint Hugeint::operator%(const Hugeint& num)const
{
	Hugeint a = *this, b = num;
	a.sign = b.sign = 1;
	Hugeint result, temp = a / b * b;
	result = a - temp;
	result.sign = sign;
	return result;
}

Hugeint Hugeint::pow(const Hugeint& num)const
{
	Hugeint result = 1;
	for (Hugeint i = 0; i < num; i++)
		result = result * (*this);
	return result;
}

Hugeint Hugeint::factorial()const
{
	Hugeint result = 1;
	for (Hugeint i = 1; i <= *this; i++)
		result *= i;
	return result;
}

void Hugeint::clean()
{
	if (len == 0) len++;
	while (len > 1 && s[len - 1] == '\0')
		len--;
}

Hugeint Hugeint::Sqrt()const
{
	if (*this < 0)return -1;
	if (*this <= 1)return *this;
	Hugeint l = 0, r = *this, mid;
	while (r - l > 1)
	{
		mid = (l + r) / 2;
		if (mid * mid > *this)
			r = mid;
		else
			l = mid;
	}
	return l;
}

Hugeint::~Hugeint()
{
}


