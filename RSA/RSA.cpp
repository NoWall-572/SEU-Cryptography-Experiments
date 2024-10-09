#include"RSA.hpp"

long long int RSA::exgcd(long long int a, long long int b, long long int* x, long long int* y)//拓展欧几里得算法
{
    if (b == 0)
    {
        *x = 1;
        *y = 0;
        return a;
    }
    long long int gcd = exgcd(b, (long long int)(a % b), x, y);
    long long int temp = *x;
    *x = *y;
    *y = temp - a / b * (*y);

    return gcd;
}



long long int RSA::isprime(long long int a) //素数判断
{
    long long int i;
    for (i = 2; i < 1 + (a / 2); i++) 
    {
        if (a % i == 0)return 1;
    }
    return 0;
}

void RSA::primegenerator(long long prime[500])//生成素数表
{
    long long int i, j = 0;
    for (i = 91; i <= 10000000000; i++)
    {
        if (isprime(i) == 0) 
        {
            prime[j] = i;
            j++;
        }
        if (j > 499)break;
    }
}

void RSA::rsa_encryption()//加密函数
{

    cout << "Please put in the KEY(d,n)or(e,n) of decryption: " << endl;
    string TypeIn;
    cin >> TypeIn;
    const char* typein = TypeIn.c_str();

    char* E = new char[1024];
    char* N = new char[1024];

    for (int i = 0, index = 0; i <= strlen(typein); i++)
    {
        if (typein[i] == ',' || typein[i] == '，')
        {
            break;
        }

        if (typein[i] == '(' || typein[i] == '（' || typein[index] == ' ')
        {
            index++;
        }
        else
        {
            E[i - index] = typein[i];
        }
    }
    {
        int index = 0;
        for (int i = 0; i <= strlen(typein) && typein[i] != ')' && typein[i] != '）'; i++)
        {

            if (typein[i] == ',' || typein[i] == '，' || typein[i] == '\0')
            {
                index = i;
            }

        }

        for (int i = index + 1; i <= strlen(typein) && typein[i] != ')' && typein[i] != '）'; i++)
        {
            N[i - index - 1] = typein[i];
        }
    }

    long long int e = atoi(E);
    long long int n = atoi(N);
    
    string PlainText;//明文字符串       
    cout << "Please put in the plain text: " << endl;
    cin >> PlainText;
    const char* plaintext = PlainText.c_str();
    long long int* input_plaintext = new long long int[strlen(plaintext)];
    for (int i = 0; i < strlen(plaintext); i++)
    {
        input_plaintext[i] = plaintext[i];
    }
    long long int* input_ciphertext = new long long int[strlen(plaintext)];  //录入结束，开始加密

    long long int mi = 0;
    for (int i = 0; i < strlen(plaintext); i++)
    {
        mi = input_plaintext[i];
        input_ciphertext[i] = 1;
        for (long long int j = 1; j <= e; j++)
        {
            input_ciphertext[i] = (input_ciphertext[i] * mi) % n;
        }
    }
    cout << "Cipher text is: "<<endl;
    {
        int i = 0;
        for (i = 0; i < strlen(plaintext); i++)
        {
            cout << input_ciphertext[i] << ' '; //加密结束，输出密文
        }
        cout << endl << "Length of the cipher text is: " << i << endl << endl;
    }
 
    delete[]E;
    E = NULL;
    delete[]N;
    N = NULL;
    delete[]input_plaintext;
    input_plaintext = NULL;
    delete[]input_ciphertext;
    input_ciphertext = NULL;

}

void RSA::rsa_decryption()//解密函数
{
    long long int input_solvingciphertext[10000];

    cout << "Please type in the length of cipher text: ";
    int k;
    cin >> k;
    cout << "Please type in the cipher text:" << endl; //录入密文
    int t = 0;
    for (int i = 0; i < k; i++)
    {
        cin >> input_solvingciphertext[i];
    }
    int sizel = k;

    cout << "Please put in the KEY(d,n)or(e,n) of decryption: " << endl;
    string TypeIn;
    cin >> TypeIn;
    const char* typein = TypeIn.c_str();
    
    char* D1=new char[1024];
    char* N1=new char[1024];
    
    for (int i= 0,index=0; i <= strlen(typein); i++)
    {
        if (typein[i] == ',' || typein[i] == '，')
        {
            break;
        }

        if (typein[i] == '('|| typein[i] == '（'|| typein[index] == ' ')
        {
            index++;
        }
        else
        {
            D1[i - index] = typein[i];
        }
    }
    {
        int index = 0;
        for (int i = 0; i <= strlen(typein) && typein[i] != ')' && typein[i] != '）'; i++)
        {

            if (typein[i] == ',' || typein[i] == '，' || typein[i] == '\0')
            {
                index = i;
            }

        }

        for (int i = index+1; i <= strlen(typein) && typein[i] != ')' && typein[i] != '）'; i++)
        {
            N1[i - index - 1] = typein[i];
        }
    }

    long long int d1 = atoi(D1);
    long long int n1 = atoi(N1);
    
    long long int ming;
    long long int* input_solvingplaintext = new long long int[sizel];  //开始解密
    for (int i = 0; i < sizel; i++)
    {
        ming = input_solvingciphertext[i];
        input_solvingplaintext[i] = 1;
        for (long long int j = 0; j < d1; j++)
        {
            input_solvingplaintext[i] = (input_solvingplaintext[i] * ming) % n1;
        }
    }

    char* solvingplaintext = new char[sizel];
    for (int i = 0; i < sizel; i++)
    {
        solvingplaintext[i] = input_solvingplaintext[i];
    }
    cout << "Plaintext is: " << endl;  //输出明文
    for (int i = 0; i < sizel; i++)
    {
        cout << solvingplaintext[i];
    }

    cout << endl << endl;
    delete[]D1;
    D1 = NULL;
    delete[]N1;
    N1 = NULL;
    delete[]input_solvingplaintext;
    input_solvingplaintext = NULL;
    delete[]solvingplaintext;
    solvingplaintext = NULL;

}

void RSA::distributekey()//生成密钥
{
    
    long long int prime[500];
    primegenerator(prime);
    long long int seed, p, q;
    
    mt19937 mt;
    mt.seed(chrono::system_clock::now().time_since_epoch().count());
    srand(uniform_real_distribution<long double>(1, 10000)(mt));  //生成在范围内的随机素数p，q
    p = rand() % 499;

    do
    {
        q = rand() % 499;
    } while (q == p);
    long long int e, d, n, fi_n, r, nu, w1, w2;
    

        n = prime[p] * prime[q];
        fi_n = (prime[p] - 1) * (prime[q] - 1);
    do
    {
    
        srand(uniform_real_distribution<long double>(2,fi_n / 2)(mt));  //生成在范围内的随机数
        for (r = fi_n / 2; n >= 1; r = rand())
        {   //求得公钥
            if (exgcd(r, fi_n, &w1, &w2) == 1)
            {
                e = r;
                break;
            }
        }

        r = exgcd(e, fi_n, &d, &nu);
    } while (d < 0);//保证d非负
   

    cout << endl << "The public-key(e,n) of decryption is: ";//公钥
    cout << "(" << e << "," << n << ")" << endl;

    cout << "The private-key(d,n) of decryption is: ";//密钥
    cout << "(" << d << "," << n << ")" << endl << endl;
}