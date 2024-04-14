#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
using namespace std;

unordered_map<char, char> removeDuplicate(string key, string message) {
    unordered_set<char> seen;
    string key2, message2;
    for (char c : key) {
        if (seen.find(c) == seen.end() and c != ' ') {
            key2 += c;
            seen.insert(c);
        }
    }
    seen.clear();
    for (char c : message) {
        if (seen.find(c) == seen.end() and c != ' ') {
            message2 += c;
            seen.insert(c);
        }
    }
    seen.clear();
    unordered_map<char, char> keyMap;
    for (int i = 0; i < message2.length(); i++) {
        keyMap[message2[i]] = key2[i];
    }
    return keyMap;
}

string encrypte(unordered_map<char, char> keyMap, string message) {
    string cipher;
    for (int i = 0; i < message.length(); i++) {
        auto it = keyMap.find(message[i]);
        if (it != keyMap.end()) {
            cipher += it->second;
        } else {
            cipher += message[i];
        }
    }
    return cipher;
}

string decrypte(unordered_map<char, char> keyMap, string cipher) {
    string plaintext;
    for (int i = 0; i < cipher.length(); i++) {
        auto it = keyMap.begin();
        while (it != keyMap.end()) {
            if (it->second == cipher[i]) {
                plaintext += it->first;
                break;
            }
            ++it;
        }
        if (it == keyMap.end()) {
            plaintext += cipher[i];
        }
    }
    return plaintext;
}

int main() {
    string message;
    string key = "jumpy foxes quickly zap the quirky big wavy quait";

    unordered_map<char, char> keyMap;
    string cipher2;

    while (true)
    {
        int casetype;
        cout << "type 0 for encrypt and 1 for decrypt\t:\t";
        cin >> casetype;
        
        switch (casetype){
        case 0:

            cin.ignore();
            cout << "Enter the plain text you need to encrypt\t:\t";
            getline(cin, message);
            keyMap = removeDuplicate(key, message);
            cout << "Encrypted output\t:\t" << encrypte(keyMap, message) << endl;
            break;

        case 1:
            cin.ignore();
            cout << "Enter the cipher you need to encrypt\t:\t" ;
            getline(cin, cipher2);
            cout << "Decrypted output\t:\t" << decrypte(keyMap, cipher2) << endl;
            break;
        
        default:
            break;
        }
    }
    return 0;
}
