#include "SHA-1.hpp"
#include "HugeInt.hpp"
//Ft函数
bitset<32> SHA1::Ft(int t, bitset<32> B, bitset<32> C, bitset<32> D)
{
	if (0 <= t && t <= 19)
	{
		return ((B & C) | ((~B) & D));
	}
	else if (20 <= t && t <= 39)
	{
		return (B ^ C ^ D);
	}
	else if (40 <= t && t <= 59)
	{
		return ((B & C) | (B & D) | (C & D));
	}
	else if (60 <= t && t <= 79)
	{
		return (B ^ C ^ D);
	}
}

//字符串的拓展函数
void  SHA1::SHA_PAD(string x)
{
	long long l = x.length();
	long long i = 0;
	pad[i] = 128;
	i++;
	l += 1;
	if ((l * 8) % 512 != 448)
	{
		for (; (l * 8) % 512 != 448; l++)
		{
			i++;
		}
	}
	l = x.length();
	l = l * 8;
	int a = 1;
	pad[i + 7] = l % 256;
	while (l / 256 > 0)
	{
		l = l / 256;
		pad[i + 7 - a] = l % 256;
		a++;
	}
	for (; a < 8; a++)
	{
		pad[i + 7 - a] = 0;
	}
	lenth_pad = i + 7;
}

//循环左移函数
bitset<32>  SHA1::ROTL(int s, bitset<32> W)
{
	bitset<32>m = W << s;
	for (int i = 0; i < s; i++)
	{
		m[i] = W[32 - s + i];
	}
	return m;
}

//模2^32加函数
bitset<32> SHA1::ADD(bitset<32>a, bitset<32>b)
{
	bitset<32> c;
	int d = 0;
	for (int i = 0; i < 32; i++)
	{
		c[i] = (a[i] + b[i] + d) % 2;
		if (a[i] + b[i] + d >= 2)
		{
			d = 1;
		}
		else if (a[i] + b[i] + d < 2)
		{
			d = 0;
		}
	}
	return c;
}

//循环体
void  SHA1::DO(bitset<512> M)
{
	bitset<32> Wt[80] = { 0 };
	for (int i = 0; i < 16; i++)
	{
		for (int n = 0; n < 32; n++)
		{
			Wt[i][n] = M[(15 - i) * 32 + n];
		}
	}
	for (int t = 16; t <= 79; t++)
	{
		Wt[t] = ROTL(1, Wt[t - 3] ^ Wt[t - 8] ^ Wt[t - 14] ^ Wt[t - 16]);
	}
	bitset<32> A = Ht[0];
	bitset<32> B = Ht[1];
	bitset<32> C = Ht[2];
	bitset<32> D = Ht[3];
	bitset<32> E = Ht[4];
	for (int t = 0; t <= 79; t++)
	{
		bitset<32> temp = ADD(ADD(ADD(ROTL(5, A), Ft(t, B, C, D)), ADD(E, Wt[t])), Kt[t / 20]);
		E = D;
		D = C;
		C = ROTL(30, B);
		B = A;
		A = temp;
	}
	Ht[0] = ADD(Ht[0], A);
	Ht[1] = ADD(Ht[1], B);
	Ht[2] = ADD(Ht[2], C);
	Ht[3] = ADD(Ht[3], D);
	Ht[4] = ADD(Ht[4], E);
}

string SHA1::hash(string x)
{
	std::ostringstream result_stream; // 使用 ostringstream 累积结果

	SHA_PAD(x);
	long long l = 0;
	// 循环处理输入字符串 x
	while (l < x.length()) 
	{
		long long i = l;
		std::string Sx;
		for (; (i < 64 + l) && (i < x.length()); i++) 
		{
			std::bitset<8> mark = static_cast<unsigned char>(x[i]);
			Sx += mark.to_string();
		}
		l += 64;
		if (i == x.length()) 
		{
			if (lenth_pad <= 63)
			{
				for (int n = 0; n <= lenth_pad; n++)
				{
					std::bitset<8> mark = static_cast<unsigned char>(pad[n]);
					Sx += mark.to_string();
				}
			}
			else 
			{
				int n = 0;
				for (; i < l; i++) 
				{
					std::bitset<8> mark = static_cast<unsigned char>(pad[n++]);
					Sx += mark.to_string();
				}
				std::bitset<512> Mx(Sx);
				DO(Mx);
				std::string last_Sx;
				for (; n <= lenth_pad; n++)
				{
					std::bitset<8> mark = static_cast<unsigned char>(pad[n]);
					last_Sx += mark.to_string();
				}
				std::bitset<512> last_Mx(last_Sx);
				DO(last_Mx);
				break;
			}
		}
		std::bitset<512> Mx(Sx);
		DO(Mx);
	}

	// 输出哈希值
	result_stream << "The hash of message is: ";
	for (int i = 0; i < 5; i++) 
	{
		std::string s = Ht[i].to_string();
		for (int n = 0; n < 32;)
		{
			int result = 0;
			for (int m = 0; m < 4; m++) 
			{
				result += (s[n + m] - '0') * std::pow(2, 3 - m);
			}
			result_stream << std::hex << result;
			n += 4;
		}
	}

	return result_stream.str(); // 返回累积的结果字符串
}

Hugeint SHA1::hextoHugeint(const string& hex)
{
	
	Hugeint result("0");
	Hugeint base("1");

	for (int i = hex.length() - 1; i >= 0; --i)
	{
		int digit = (hex[i] >= '0' && hex[i] <= '9') ? (hex[i] - '0')
			: (hex[i] >= 'A' && hex[i] <= 'F') ? (hex[i] - 'A' + 10)
			: (hex[i] - 'a' + 10); // 处理大小写字母

		Hugeint current = base * Hugeint(std::to_string(digit));
		result = result + current;
		base = base * Hugeint("16"); // 更新基数乘积
	}
	result.sign = 1;
	return result;
}