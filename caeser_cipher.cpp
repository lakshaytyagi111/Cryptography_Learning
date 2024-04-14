#include <bits/stdc++.h>
using namespace std;

string encrypte(string input, int shift)
{
    string cipher;
    for (char c : input)
    {
        if (c == ' ')
        {
            cipher += " ";
        }
        else
        {
            if (isupper(c))
            {
                cipher += char(int(c + shift - 65) % 26 + 65);
            }
            else
            {
                cipher += char(int(c + shift - 97) % 26 + 97);
            }
        }
    }
    return cipher;
}

string decrypte(string input, int shift)
{
    string plain_text;
    for (char c : input)
    {
        if (c == ' ')
        {
            plain_text += " ";
        }
        else
        {
            if (isupper(c))
            {
                plain_text += char(abs(int(c - shift - 65 + 26) % 26) + 65);
            }
            else
            {
                plain_text += char(abs(int(c - shift - 97 + 26) % 26) + 97);
            }
        }
    }
    return plain_text;
}
int main()
{


    while (true)
    {
        string input;
        int shift;
        int casetype;
        cout << "type 0 for encrypt and 1 for decrypt\t:\t";
        cin >> casetype;
        switch (casetype)
        {
        case 0:

            cout << "Enter number of shifts\t:\t";
            cin >> shift;
            cin.ignore();
            cout << "Enter the plain text you need to encrypt\t:\t" << endl;
            getline(cin, input);
            cout << "Encrypted output\t:\t" << encrypte(input, shift) << endl;
            break;

        case 1:

            cout << "Enter number of shifts\t:\t";
            cin >> shift;
            cin.ignore();
            cout << "Enter the cipher you need to encrypt\t:\t" << endl;
            getline(cin, input);
            cout << "Decrypted output\t:\t" << decrypte(input, shift) << endl;
            break;
        }
    }

    return 0;
}
