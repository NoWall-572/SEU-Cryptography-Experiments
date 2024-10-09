// Diffie-Hellman.cpp
#include "HugeInt.hpp"

using namespace std;

int main()
{
	srand(time(0));
	cout << "p = " << p << "\na = " << a << endl;
	cout << "�û�Aѡ��һ�����ܵ��������Xa\n";
	Hugeint Xa = rand();
	cout << "Xa = " << Xa << endl;
	cout << "�û�A��Ya = a^Xa mod p ���͸��û�B\n";
	Hugeint Ya = Hugeint.DeMo2(a, Xa, p);
	cout << "Ya = " << Ya << endl;
	cout << "�û�Bѡ��һ�����ܵ��������Xb\n";
	Hugeint Xb = rand();
	cout << "Xb = " << Xb << endl;
	cout << "�û�B��Yb = a^Xb mod p ���͸��û�A\n";
	Hugeint Yb = MoChongFuPingFangJiSuanFa(a, Xb, p);
	cout << "Yb = " << Yb << endl;
	Hugeint K1 = MoChongFuPingFangJiSuanFa(Yb, Xa, p);
	cout << "�û�A��K = Yb^Xa mod p ������Ĺ�����ԿK1��" << K1 << endl;
	Hugeint K2 = MoChongFuPingFangJiSuanFa(Ya, Xb, p);
	cout << "�û�B��K = Ya^Xb mod p ������Ĺ�����ԿK2��" << K2 << endl;
	return 0;
}