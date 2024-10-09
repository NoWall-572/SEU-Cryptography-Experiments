#pragma warning(disable:4996)
#include"DES.hpp"


// DES
const unsigned char DES::IP_Table[64] = 
{
	58, 50, 42, 34, 26, 18, 10, 2, 
	60, 52, 44, 36, 28, 20, 12, 4,
	62, 54, 46, 38, 30, 22, 14, 6,
	64, 56, 48, 40, 32, 24, 16, 8,
	57, 49, 41, 33, 25, 17,  9, 1, 
	59, 51, 43, 35, 27, 19, 11, 3,
	61, 53, 45, 37, 29, 21, 13, 5, 
	63, 55, 47, 39, 31, 23, 15, 7
};
// 初置换 

const unsigned char DES::IPR_Table[64] = 
{
	40, 8, 48, 16, 56, 24, 64, 32, 
	39, 7, 47, 15, 55, 23, 63, 31,
	38, 6, 46, 14, 54, 22, 62, 30, 
	37, 5, 45, 13, 53, 21, 61, 29,
	36, 4, 44, 12, 52, 20, 60, 28, 
	35, 3, 43, 11, 51, 19, 59, 27,
	34, 2, 42, 10, 50, 18, 58, 26, 
	33, 1, 41,  9, 49, 17, 57, 25
};
// 逆初始置换 

const unsigned char DES::E_Table[48] = 
{
	32,  1,  2,  3,  4,  5,  4,  5,  6,  7,  8,  9,
	 8,  9, 10, 11, 12, 13, 12, 13, 14, 15, 16, 17,
	16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25,
	24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32,  1
};
// E表 

const unsigned char DES::P_Table[32] = 
{
	16, 7, 20, 21, 29, 12, 28, 17, 1,  15, 23, 26, 5,  18, 31, 10,
	2,  8, 24, 14, 32, 27, 3,  9,  19, 13, 30, 6,  22, 11, 4,  25
};
// 置换选择 

const unsigned char DES::PC1_Table[56] = 
{
	57, 49, 41, 33, 25, 17,  9,  1, 58, 50, 42, 34, 26, 18,
	10,  2, 59, 51, 43, 35, 27, 19, 11,  3, 60, 52, 44, 36,
	63, 55, 47, 39, 31, 23, 15,  7, 62, 54, 46, 38, 30, 22,
	14,  6, 61, 53, 45, 37, 29, 21, 13,  5, 28, 20, 12,  4
};
//置换选择1

const unsigned char DES::PC2_Table[48] = 
{
	14, 17, 11, 24,  1,  5,  3, 28, 15,  6, 21, 10,
	23, 19, 12,  4, 26,  8, 16,  7, 27, 20, 13,  2,
	41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48,
	44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32
};
//置换选择2 

const unsigned char DES::LOOP_Table[16] = 
{
	1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1
};
// 密钥位移（左移次数） 

const unsigned char DES::S_Box[8][4][16] = 
{
	//8个S盒 ，每个盒为4行16列
	// 定义S1盒
	14,	 4,	13,	 1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7,
	 0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8,
	 4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0,
	15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13,
	// 定义S2盒 
	15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10,
	 3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5,
	 0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15,
	13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9,
	// 定义S3盒 
	10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8,
	13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1,
	13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7,
	 1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12,
	// 定义S4盒 
     7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15,
    13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9,
	10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4,
     3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14,
	// 定义S5盒 
	 2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9,
	14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6,
	 4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14,
	11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3,
	// 定义S6盒 
	12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11,
	10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8,
	 9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6,
	 4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13,
	// 定义S7盒
	 4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1,
	13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6,
	 1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2,
	 6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12,
	// 定义S8盒
	13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7,
	 1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2,
	 7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8,
	 2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11
};

void depart(char byte, int a[64], int q) 
{
	int i;
	for (i = 0; i < 8; i++) {
		a[7 - i + q] = byte & 1;
		byte >>= 1;
		//把byte右移一位的值赋值给byte
	}
}


void DES::set_key(unsigned char const* yonghu_key) //用户输入的64位密钥首地址
{
	//密钥扩展算法
	int arr[64];
	int ary[56];
	int i, curry = 0;
	for (i = 0; i < 8; i++) 
	{
		depart(yonghu_key[i], arr, curry);
		curry = curry + 8;
	}
	for (i = 0; i < 56; i++) 
	{
		ary[i] = arr[PC1_Table[i] - 1];
	}
	for (i = 0; i < 16; i++) 
	{
		if (i == 0 || i == 1 || i == 8 || i == 15) 
		{
			int j, temp0, temp1;
			temp0 = ary[0]; temp1 = ary[28];
			for (j = 0; j < 27; j++) 
			{
				ary[j] = ary[j + 1];
				ary[j + 28] = ary[j + 29];
			}
			ary[27] = temp0; ary[55] = temp1;
		}
		else 
		{
			int j, temp0, temp1;
			temp0 = ary[0]; temp1 = ary[28];
			for (j = 0; j < 27; j++) 
			{
				ary[j] = ary[j + 1];
				ary[j + 28] = ary[j + 29];
			}
			ary[27] = temp0; ary[55] = temp1;
			temp0 = ary[0]; temp1 = ary[28];
			for (j = 0; j < 27; j++) 
			{
				ary[j] = ary[j + 1];
				ary[j + 28] = ary[j + 29];
			}
			ary[27] = temp0; ary[55] = temp1;
		}
		int j;
		for (j = 0; j < 48; j++)
			enkey[i][j] = (bool)ary[PC2_Table[i] - 1];
	}
}

void DES::en_transform(const unsigned char* In , unsigned char* Out) //待解密的64位数据首地址
{
	//加密变换算法
	int arr[64];
	int ary[64];
	int i, j, curry = 0;
	for (i = 0; i < 8; i++) 
	{
		depart(In[i], arr, curry);
		curry = curry + 8;
	}
	for (i = 0; i < 64; i++) 
	{
		ary[i] = arr[IP_Table[i] - 1];
	}

	int larr[32];
	int rarr[32];
	for (i = 0; i < 32; i++) 
	{
		larr[i] = ary[i];
		rarr[i] = ary[i + 32];
	}
	for (i = 0; i < 16; i++) 
	{
		int temp[32];
		for (j = 0; j < 32; j++) 
		{
			temp[j] = larr[j];
			larr[j] = rarr[j];
		}
		int i0, j0, q;
		int e[48];
		for (i0 = 0; i0 < 48; i0++)
			e[i0] = rarr[E_Table[i0] - 1];
		int w;
		for (w = 0; w < 48; w++) 
		{
			e[w] = (e[w] + enkey[i][w]) % 2;
		}

		for (j0 = 0; j0 < 8; j0++) 
		{
			int hang = e[j0 * 6] * 2 + e[j0 * 6 + 5];
			int lie = e[j0 * 6 + 1] * 8 + e[j0 * 6 + 2] * 4 + e[j0 * 6 + 3] * 2 + e[j0 * 6 + 4];
			int num = S_Box[j0][hang][lie];
			for (q = 0; q < 4; q++) 
			{
				rarr[j0 * 4 + 3 - q] = num & 1;
				num >>= 1;
			}
		}
		int temp0[32];
		for (j = 0; j < 32; j++) 
		{
			temp0[j] = rarr[j];
		}
		for (j = 0; j < 32; j++) 
		{
			rarr[j] = temp0[P_Table[j] - 1];
		}

		for (j = 0; j < 32; j++) 
		{
			rarr[j] = ((rarr[j] + temp[j]) % 2);
		}
	}

	int temp[32];
	for (i = 0; i < 32; i++) 
	{
		temp[i] = larr[i];
		larr[i] = rarr[i];
		rarr[i] = temp[i];
	}
	for (i = 0; i < 32; i++) 
	{
		ary[i] = larr[i];
		ary[i + 32] = rarr[i];
	}
	for (i = 0; i < 64; i++) 
	{
		arr[i] = ary[IPR_Table[i] - 1];
	}

	for (i = 0; i < 8; i++) 
	{
		Out[i] = arr[i * 8] * 128 + arr[i * 8 + 1] * 64 + arr[i * 8 + 2] * 32 + arr[i * 8 + 3] * 16 + arr[i * 8 + 4] * 8 + arr[i * 8 + 5] * 4 + arr[i * 8 + 6] * 2 + arr[i * 8 + 7];
	}
}

void DES::de_transform(const unsigned char* In , unsigned char* Out) //待加密的64位数据首地址
{
	//解密变换算法
	int arr[64];
	int ary[64];
	int i, j, curry = 0;


	for (i = 0; i < 8; i++) 
	{
		depart(In[i], arr, curry);
		curry += 8;
	}
	for (i = 0; i < 64; i++) 
	{
		ary[i] = arr[IP_Table[i] - 1];
	}

	int larr[32];
	int rarr[32];
	for (i = 0; i < 32; i++) 
	{
		larr[i] = ary[i];
		rarr[i] = ary[i + 32];
	}


	for (i = 0; i < 16; i++) 
	{
		int temp[32];
		for (j = 0; j < 32; j++) 
		{
			temp[j] = larr[j];
			larr[j] = rarr[j];
		}
		int i0, j0, q;
		int e[48];
		for (i0 = 0; i0 < 48; i0++)
			e[i0] = rarr[E_Table[i0] - 1];
		int w;
		for (w = 0; w < 48; w++) {
			e[w] = (e[w] + enkey[15 - i][w]) % 2;
		}

		for (j0 = 0; j0 < 8; j0++) 
		{
			int hang = e[j0 * 6] * 2 + e[j0 * 6 + 5];
			int lie = e[j0 * 6 + 1] * 8 + e[j0 * 6 + 2] * 4 + e[j0 * 6 + 3] * 2 + e[j0 * 6 + 4];
			int num = S_Box[j0][hang][lie];
			for (q = 0; q < 4; q++) 
			{
				rarr[j0 * 4 + 3 - q] = num & 1;
				num >>= 1;
			}
		}

		int temp0[32];
		for (j = 0; j < 32; j++) 
		{
			temp0[j] = rarr[j];
		}
		for (j = 0; j < 32; j++) 
		{
			rarr[j] = temp0[P_Table[j] - 1];
		}
		for (j = 0; j < 32; j++) 
		{
			rarr[j] = ((rarr[j] + temp[j]) % 2);
		}

	}
	int temp[32];
	for (i = 0; i < 32; i++)
	{
		temp[i] = larr[i];
		larr[i] = rarr[i];
		rarr[i] = temp[i];
	}

	for (i = 0; i < 32; i++)
	{
		ary[i] = larr[i];
		ary[i + 32] = rarr[i];
	}
	for (i = 0; i < 64; i++) 
	{
		arr[i] = ary[IPR_Table[i] - 1];
	}
	for (i = 0; i < 8; i++) 
	{
		Out[i] = arr[i * 8] * 128 + arr[i * 8 + 1] * 64 + arr[i * 8 + 2] * 32 + arr[i * 8 + 3] * 16 + arr[i * 8 + 4] * 8 + arr[i * 8 + 5] * 4 + arr[i * 8 + 6] * 2 + arr[i * 8 + 7];
	}
}




//测试主函数


auto main() ->int
{
	unsigned int seq[8];
	unsigned char key[9];	//密钥 
	unsigned char plain[9];	//明文 
	unsigned char cipher[9];//密文 
	char type_in[17];	    //键盘输入的字符 
	char choice = ' ';
	DES mydes;	            //实例化对象 
	int i, j;
	int s;

	while (true) 
	{
		cout << "You are welcome to use the DES machine of SEUer_LK123425! \n" << endl;
		do 
		{
			cout << "Please enter the corresponding operation number:\n1.Encrypt\t2.Decrypt\t3.Quit" << endl;
			cin >> choice;
		} while (choice != '1' && choice != '2' && choice != '3');

		switch (choice) 
		{
		case '1':
			cout<<"Please enter the secret key (length = 16):\n";
			cin>>type_in;;
			sscanf(type_in, "%2x%2x%2x%2x%2x%2x%2x%2x", &seq[0], &seq[1], &seq[2], &seq[3], &seq[4], &seq[5], &seq[6], &seq[7]);
			for (i = 0; i < 8; i++)
				key[i] = seq[i];
			//将输入的字符依次存到密钥数组中
			cout<<endl;
			cout<<"Please enter plaintext (length = 16):\n";
			cin>>type_in;;
			cout<<endl;
			sscanf(type_in, "%2x%2x%2x%2x%2x%2x%2x%2x", &seq[0], &seq[1], &seq[2], &seq[3], &seq[4], &seq[5], &seq[6], &seq[7]);
			for (j = 0; j < 8; j++)
				plain[j] = seq[j];
			//将输入的字符依次存到明文数组中 

			mydes.set_key(key);
			mydes.en_transform(plain, cipher);
			//调用加密算法函数完成加密

			for (s = 0; s < 8; s++)
				seq[s] = cipher[s];
			printf("ciphertext:\n%02x%02x%02x%02x%02x%02x%02x%02x\n", seq[0], seq[1], seq[2], seq[3], seq[4], seq[5], seq[6], seq[7]);
			//将密文数组中的字符存入缓存数组并输出 
			cout<<endl;
			break;


		case '2':
			cout<<"Please enter the secret key (length = 16):\n";
			cin>>type_in;
			sscanf(type_in, "%2x%2x%2x%2x%2x%2x%2x%2x", &seq[0], &seq[1], &seq[2], &seq[3], &seq[4], &seq[5], &seq[6], &seq[7]);
			for (i = 0; i < 8; i++)
				key[i] = seq[i];
			//将输入的字符依次存到明文数组中 
			cout<<endl;
			cout<<"Please enter the ciphertext (length = 16):\n";
			cin>>type_in;
			cout<<endl;
			sscanf(type_in, "%2x%2x%2x%2x%2x%2x%2x%2x", &seq[0], &seq[1], &seq[2], &seq[3], &seq[4], &seq[5], &seq[6], &seq[7]);
			for (j = 0; j < 8; j++)
				cipher[j] = seq[j];
			//将输入的字符依次存到密文数组中 

			mydes.set_key(key);
			mydes.de_transform(cipher, plain);
			//调用解密算法函数完成解密
			for (s = 0; s < 8; s++)
				seq[s] = plain[s];
			printf("plaintext:\n%02x%02x%02x%02x%02x%02x%02x%02x\n", seq[0], seq[1], seq[2], seq[3], seq[4], seq[5], seq[6], seq[7]);
			cout<<endl;
			break;
		case '3':
			return 0;
			break;
		}
	}


	system("pause");
	return 0;
}
