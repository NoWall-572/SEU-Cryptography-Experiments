#include "Diffie_Hellman.hpp"
#include "HugeInt.hpp"
using namespace std;

auto main() -> int
{
    DH mydh;//实例化对象

    cout << "You are welcome to use the Diffie-Hellman Key-Change-Machine of SEUer_LK123425! \n" << endl;
    while (true)
    {
        char choice;
        cout << "-Please enter the corresponding number for operation:\n  1.Simulate the process of Diffie-Hellman Key-Change\t2.Quit the Machine " << endl;
        Lab1:
        cout << "-Choice: ";
        cin >> choice;

        switch (choice)
        {
        case '1':
        {
            char c;
            cout << "\n-Now,you're Alice, and you'd like to communicate with Bob to obtain a Shared-Key. " << endl;
            cout << "-About the two public parameters 'p' and 'g', which would you prefer?:\n  1.Automatic allocation \t2.Choose for yourself " << endl;
            Lab2:
            cout << "-You prefer: ";
            cin >> c;
            
            Hugeint p;
            Hugeint g;
            switch (c)
            {
            case '1':
            {    
                srand(time(NULL));
                g = rand() % 5 + 2;
                p = mydh.HugePrimeTable[rand() % 10];
                cout << "-The Large prime number 'p' is:" << endl << "  " << p << endl;
                cout << "-The Primordial root 'g' is: " << g << endl;
            }break;
            case '2':
            {
                cout << "-The Large prime number 'p' is:" << endl << "  ";
                cin >> p;
                cout << "-The Primordial root 'g' is: ";
                cin >> g;
                cout << endl;
                
            }break;
            default:
            {
                cout << "ERROR!" << endl;
                goto Lab2;
            }break;
            }

            cout << endl << "-Now, you've got the two public parameters 'p' and 'g', \n and which would you prefer about your Private-Key 'a':" <<
                endl << "  1.Automatic allocation \t2.Choose for yourself " << endl;
            Hugeint a;
            cout << "-You chooce: ";
            char choose;
        Lab3:
            cin >> choose;
            switch (choose)
            {
            case'1':
            {
                a = mydh.ChooseNumber();
                cout << "-Your Private-Key is: " << endl << "  " << a << endl;
            }break;
            case'2':
            {
                cout << "-Your Private-Key is: ";
                cin >> a;
            }break;
            default:
            {
                cout << "ERROR!" << endl;
                goto Lab3;
            }
            }

            Hugeint A = mydh.DeMo2(g, a, p);
            cout << "\n-After a few secongds' calculation, you've got your Public-Key 'A': " << endl << "  " << A << endl;
            cout << "-You send your Public-Key 'A' to Bob, Bob's got it and send his Publice-Key 'B' to you:" << endl << "  ";
            Hugeint b = mydh.ChooseNumber();
            Hugeint B = mydh.DeMo2(g, b, p);
            cout << B << endl;
            Hugeint Shared_A = mydh.DeMo2(B, a, p);
            Hugeint Shared_B = mydh.DeMo2(A, b, p);
            cout << "As you calculate the Shared-Key is:" << endl << "  " << Shared_A << endl;
            cout << "Then, Bob's calculated the Shared-Key either:" << endl << "  " << Shared_B << endl << endl;
            cout << "Well done! You've achieved the Diffie-Hellman key-change with Bob! \n\n\n";

        }break;
        case '2':
        {
            system("pause");
            return 0;//退出程序
        }break;
        default:
        {
            cout << "ERROR!" << endl;
            goto Lab1;
        }break;

        }

    }

	//system("pause");
	return 0;
}
