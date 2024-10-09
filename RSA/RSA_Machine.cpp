#include"RSA.hpp"

auto main() -> int
{
    RSA myrsa;//实例化对象
    

    cout << "You are welcome to use the RSA machine of SEUer_LK123425! \n" << endl;
    while (true)
    {
        char choice;
        cout << "Please enter the corresponding number for operation:\n1.Distributing chain-keys(Auto)\t\t2.Encryption\t3.Decryption\t4.Quit " << endl;
        cout << "Choice: ";
        cin >> choice;

        switch (choice)
        {
        case '1':
        {
            myrsa.distributekey();//分发密钥
        }break;
        case '2':
        {
            myrsa.rsa_encryption();//调用加密函数
        }break;
        case'3':
        {
            myrsa.rsa_decryption();//调用解密函数
        }break;

        case'4':
        {
            system("pause");
            return 0;
        }break;
        }

    }


    return 0;
}
