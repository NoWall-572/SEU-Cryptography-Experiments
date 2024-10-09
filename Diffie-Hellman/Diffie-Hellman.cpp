// Diffie-Hellman.cpp
#include "HugeInt.hpp"

using namespace std;

int main()
{
	srand(time(0));
	cout << "p = " << p << "\na = " << a << endl;
	cout << "用户A选择一个保密的随机整数Xa\n";
	Hugeint Xa = rand();
	cout << "Xa = " << Xa << endl;
	cout << "用户A将Ya = a^Xa mod p 发送给用户B\n";
	Hugeint Ya = Hugeint.DeMo2(a, Xa, p);
	cout << "Ya = " << Ya << endl;
	cout << "用户B选择一个保密的随机整数Xb\n";
	Hugeint Xb = rand();
	cout << "Xb = " << Xb << endl;
	cout << "用户B将Yb = a^Xb mod p 发送给用户A\n";
	Hugeint Yb = MoChongFuPingFangJiSuanFa(a, Xb, p);
	cout << "Yb = " << Yb << endl;
	Hugeint K1 = MoChongFuPingFangJiSuanFa(Yb, Xa, p);
	cout << "用户A由K = Yb^Xa mod p 计算出的共享密钥K1：" << K1 << endl;
	Hugeint K2 = MoChongFuPingFangJiSuanFa(Ya, Xb, p);
	cout << "用户B由K = Ya^Xb mod p 计算出的共享密钥K2：" << K2 << endl;
	return 0;
}