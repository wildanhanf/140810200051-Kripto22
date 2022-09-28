/*
Nama    : Wildan Hanif M
NPM     : 140810200051
Kelas   : A
Program : hill cipher enkripsi
*/
#include<iostream>

using namespace std;
int main(){
    string teks; int k = 0, n; string result="";
    cout << "Besar matriks kunci: ";
    cin >> n;
    cout << "Masukkan matriks kunci\n";
    int a[n][n];
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> a[i][j];
        }
    }
    cout << "Masukkan plainteks: ";
    cin >> teks;
        
    while(k < teks.size()){
        for(int i=0; i<n; i++){
            int sum = 0;
            int temp = k;
            for(int j=0; j<n; j++){
                sum += (a[i][j] % 26 * (teks[temp++]-'a') % 26) % 26;
                sum = sum % 26;
            }
            result += (sum + 'a');
        }
        k += n;
    }
    cout<<"Cipherteks: " << result<<'\n';
    return 0;    
}