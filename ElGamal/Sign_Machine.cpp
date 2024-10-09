#include "HugeInt.hpp"
#include "ElGamal.hpp"
#include "SHA-1.hpp"

auto main() -> int
{
  
    ElGamal myEG;//实例化对象
    SHA1 sha1;

   
    cout << "You are welcome to use the ElGamal-Signature-Algorithm of SEUer_LK123425! \n" << endl;
    while (true)
    {
        char choice;
        cout << "-Please enter the corresponding number for operation:\n  1.Simulate the process of ElGamal-Signature-Algorithm \t2.Quit the Machine " << endl;
    Lab1:
        cout << "-Choice: ";
        cin >> choice;

        switch (choice)
        {
        case '1':
        {
            char c;
            cout << "-Now,you're Alice, and you'd like to send a message to Bob with your signature. " << endl;
            cout << "\n#Key Generation Section:" << endl;
            cout << "-About the two public parameters 'p' and 'g', which would you prefer?\n  1.Automatic allocation(It may take a few seconds) \t2.Choose for yourself " << endl;
        Lab2:
            cout << "-You prefer: ";
            cin >> c;

            Hugeint p;
            Hugeint g; 
           
            switch (c)
            {
            case '1':
            {
                p = myEG.ChooseNumber();
           
                g =myEG.generatePrimitiveRoot(p);
               
            
                cout << "-The Large prime number 'p' is: " << p << endl;
                cout << "-The Primordial root 'g' is: " << g << endl;
            }break;
            case '2':
            {
            
                cout << "-The Large prime number 'p' is: ";
                cin >> p;
                if (!myEG.isPrime(p))
                {
                    cout << "ERROR! Enter 'p' again! " << endl << "p: ";
                    while (!myEG.isPrime(p))
                    {
                        cin >> p;
                    }
                }
                cout << "-The Primordial root 'g' is: ";
                cin >> g;
                if (!myEG.isPrimitiveRoot(g,p))
                {
                    cout << "ERROR! Enter 'p' again! " << endl << "p: ";
                    while (!myEG.isPrimitiveRoot(g, p))
                    {
                        cin >> g;
                    }
                }
                cout << endl;

            }break;
            default:
            {
                cout << "ERROR!" << endl;
                goto Lab2;
            }break;
            }
            Hugeint a;
            a = myEG.ChooseNumber()%1000+100;
            cout << "-Now, you've got the two public parameters 'p' and 'g', \n and your Private-Key 'a' is automatically allocated:" << endl << " a = " << a << endl;
   
            Hugeint A = myEG.DeMo2(g, a, p);
            cout << "-Then, you've got your Public-Key: (A, g ,p) =" << " (" << A << ", " << g << ", " << p << ")" << endl;
            cout << "\n#Signature Section" << endl;
            cout << "-You want to send your message to Bob, here is your message:" << endl << " ";
            string M;
            cin >> M;
            
            string Text;
            Text = sha1.hash(M);
            /*cout << Text << endl;*/
            Hugeint HM = sha1.hextoHugeint(Text);
           /* cout << HM << endl;*/
            Hugeint b;
            b = myEG.ChooseNumber() % 1000 + 1000;
            cout << "-Thus, your temporary Private-Key 'b' is automatically allocated:" << endl << " b = " << b << endl;

            Hugeint Sig,B;
            B = myEG.DeMo2(g, b, p);
            Hugeint b_inv = myEG.modInverse(b, p - 1);

            //a = 666;//假设使用错误的私钥进行签名

            Sig = ((HM - a * B) * b_inv) % (p - 1);
            cout << "-And, you've got your signature of message: (Sig, B) =" << " (" << Sig << ", " << B << ")" << endl;
          
            
            
            cout << "\n#Verification Section" << endl;
            cout << "- Now, you're Bob, and you'd received a message Alice with her signature." << endl;
            cout << "-First, you compute the (hex)hash-value 'h(M)' of message" << endl << " " << Text << endl;
            cout << "-Secondly, you compute LHS value of (A^B)*(B^Sig) and RHS value of g^h(M) mod p:" << endl;
            Hugeint LHS = (myEG.DeMo2(A, B, p)) *( myEG.DeMo2(B, Sig, p))%p;
            Hugeint RHS = myEG.DeMo2(g, HM, p);
            cout << "-LHS value of (A^B)*(B^Sig) = " << LHS << endl;
            cout << "-RHS value of g^h(M) mod p = " << RHS << endl;
            if (LHS == RHS)
            {
                cout << "\n-Well done! You've achieved the ElGamal-Signature Process! \n\n\n";
            }
            else
            {
                cout << "Sorry, some error occurred!" << endl;//签名无效
            }
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

	system("pause");
	return 0;
}