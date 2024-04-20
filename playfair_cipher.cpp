#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;

void printVector(const vector<string> &vec)
{
    cout << "[";
    for (size_t i = 0; i < vec.size(); ++i)
    {
        cout << vec[i];
        if (i != vec.size() - 1)
        {
            cout << ", ";
        }
    }
    cout << "]" << endl;
}

string removeDuplicate(string key)
{
    unordered_set<char> seen;
    string key2;
    for (char c : key)
    {
        if (seen.find(c) == seen.end() and c != ' ')
        {
            key2 += c;
            seen.insert(c);
        }
    }
    seen.clear();

    return key2;
}

vector<string> plainDivided(string plainText)
{
    vector<string> plainDevided;
    bool remained = false;

    for (int i = 0; i < plainText.length(); i += 2)
    {
        string ar;
        if (remained)
        {
            ar = plainText.substr(i - 1, 2);
            plainDevided.push_back(ar);
            remained = false;
        }
        else
        {
            ar = plainText.substr(i, 2);
            if (i + 1 < plainText.length() && ar[0] == ar[1])
            {
                ar[1] = 'x';
                remained = true;
            }
            plainDevided.push_back(ar);
        }
    }
    return plainDevided;
}

string encrypte(char key[5][5], string plainText)
{
    string cipher;
    int row1, column1;
    int row2, column2;

    for (string st : plainDivided(plainText))
    {
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                if (key[i][j] == st[0])
                {
                    row1 = i;
                    column1 = j;
                }
                else if (key[i][j] == st[1])
                {
                    row2 = i;
                    column2 = j;
                }
            }
        }

        if (row1 == row2)
        {
            column1 = (column1 + 1) % 5;
            column2 = (column2 + 1) % 5;
        }
        else if (column1 == column2)
        {
            row1 = (row1 + 1) % 5;
            row2 = (row2 + 1) % 5;
        }
        else
        {
            swap(column1, column2);
        }

        cipher += key[row1][column1];
        cipher += key[row2][column2];
    }

    return cipher;
}

string decrypte(char key[5][5], string cipher)
{
    string plainText;
    int row1, column1;
    int row2, column2;

    for (string st : plainDivided(cipher))
    {
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                if (key[i][j] == st[0])
                {
                    row1 = i;
                    column1 = j;
                }
                else if (key[i][j] == st[1])
                {
                    row2 = i;
                    column2 = j;
                }
            }
        }

        if (row1 == row2)
        {
            column1 = (column1 - 1 + 5) % 5;
            column2 = (column2 - 1 + 5) % 5;
        }
        else if (column1 == column2)
        {
            row1 = (row1 - 1 + 5) % 5;
            row2 = (row2 - 1 + 5) % 5;
        }
        else
        {
            swap(column1, column2);
        }

        plainText += key[row1][column1];
        plainText += key[row2][column2];
    }

    return plainText;
}

void key(char key[5][5])
{
    string rawKey;
    string alpha = "abcdefghijklmnopqrstuvwxy";

    cout << "Enter the key: ";
    getline(cin, rawKey);

    rawKey = removeDuplicate(rawKey + alpha);

    int keyIndex = 0;
    for (char c : rawKey)
    {
        if (c != 'z')
        {
            key[keyIndex / 5][keyIndex % 5] = c;
            keyIndex++;
        }
    }

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (key[i][j] == '\0')
            {
                key[i][j] = alpha[keyIndex++];
            }
        }
    }
}

int main()
{
    char keyMatrix[5][5] = {};
    key(keyMatrix);

    char choice;
    cout << "Do you want to encrypt (E) or decrypt (D)? ";
    cin >> choice;
    cin.ignore();

    string inputText, outputText;
    if (toupper(choice) == 'E')
    {
        cout << "Enter the plaintext: ";
        getline(cin, inputText);
        outputText = encrypte(keyMatrix, inputText);
        cout << "Encrypted text: " << outputText << endl;
    }
    else if (toupper(choice) == 'D')
    {
        cout << "Enter the ciphertext: ";
        getline(cin, inputText);
        outputText = decrypte(keyMatrix, inputText);
        cout << "Decrypted text: " << outputText << endl;
    }
    else
    {
        cout << "Invalid choice. Please enter 'E' for encryption or 'D' for decryption." << endl;
    }

    return 0;
}
