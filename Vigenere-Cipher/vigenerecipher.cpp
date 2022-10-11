/*
Nama    : Wildan Hanif M
NPM     : 140810200051
Kelas   : A
Program : vigenere Cipher
*/

#include <iostream>

using namespace std;

//generate key digunakan untuk extending key kalo misal keynya kurang dari plainteks
//tapi ini juga membuat penggunaan spasi tidak bisa karena akan berpengaruh pada jumlah plainteks dan ngaruh ke extending keynya juga
string generateKey(string str, string key) 
{
    int x = str.size();
 
    for (int i = 0; ; i++)
    {
        if (x == i) 
            i = 0;
        if (key.size() == str.size())
            break;
        key.push_back(key[i]);
    }
    return key;
}

string encrypt(string text, string key)
{
    string result;
    // penelurusan char dalam string
    for (int i = 0; i < text.size(); i++) {
        //buat uppercase
        if (isupper(text[i])){
            // karena dijumlahkannya dengan char juga maka 22nya harus dikurang, biar pas modulo sesuai, berlaku untuk semua.
            result += char((text[i] - 65 + key[i] - 65) % 26 + 65); 
        } 
        // buat lowercase
        else if (islower(text[i])) {
            result += char((text[i] - 97 + key[i] - 97) % 26 + 97);
        }
        else
            result.push_back(text[i]);
    }
    // return hasilnya
    return result;
}

string decrypt(string text, string key)
{
    string result;
    // penelurusan char dalam string
    for (int i = 0; i < text.size(); i++) {
        //buat uppercase
        if (isupper(text[i])){
            result += char(((text[i] - 65 - key[i] - 65) % 26 + 26) % 26 + 65);
        } 
        // buat lowercase
        else if (islower(text[i])) {
            result += char(((text[i] - 65 - key[i] - 97) % 26 + 26) % 26 + 97);
        }
        else
            result.push_back(text[i]);
    }
    // return hasilnya
    return result;
}

int main()
{
    string plaintext = "", cipherteks = " "; 
    string keyword;
    cout << "Masukkan Kata: ";
    cin >> plaintext;
    cout << "Masukkan Kunci: ";
    cin >> keyword;
    string key = generateKey(plaintext, keyword);
    cout << "\nPlaintext : " << plaintext;
    cout << "\nKunci: " << key;
    cipherteks = encrypt(plaintext, key);
    cout << "\nCipherteks: " << cipherteks;
    cout << "\nDekripsi: " << decrypt(cipherteks, key);
    return 0;
}