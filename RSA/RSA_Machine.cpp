#include"RSA.hpp"

auto main() -> int
{
    RSA myrsa;//ʵ��������
    

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
            myrsa.distributekey();//�ַ���Կ
        }break;
        case '2':
        {
            myrsa.rsa_encryption();//���ü��ܺ���
        }break;
        case'3':
        {
            myrsa.rsa_decryption();//���ý��ܺ���
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
