/*
Nama    : Wildan Hanif M
NPM     : 140810200051
Kelas   : A
Program : hill cipher dekripsi
*/

#include<iostream>
#include<vector>
using namespace std;

int modInverse(int a, int m){ 
    a = a % m; 
    for(int x=-m; x<m; x++) 
       if((a*x) % m == 1) 
          return x; 
} 

void getCofactor(vector<vector<int> > &a, vector<vector<int> > &temp, int p, int q, int n){ 
    int i=0, j=0; 
    for(int row=0; row<n; row++){ 
        for(int col=0; col<n; col++){ 
            if(row != p && col != q){ 
                temp[i][j++] = a[row][col]; 
                if (j==n-1){ 
                    j=0; 
                    i++; 
                } 
            } 
        } 
    } 
}

int determinant(vector<vector<int> > &a, int n, int N){ 
    int D = 0;
    if(n==1) 
        return a[0][0]; 
    vector<vector<int> > temp(N, vector<int>(N));
    int sign = 1;
    for(int f=0; f<n; f++){ 
        getCofactor(a, temp, 0, f, n); 
        D += sign * a[0][f] * determinant(temp, n - 1, N); 
        sign = -sign; 
    }
    return D; 
} 

void adjoint(vector<vector<int> > &a,vector<vector<int> > &adj,int N){ 
    if(N == 1){ 
        adj[0][0] = 1; 
        return; 
    } 
    int sign = 1;
    vector<vector<int> > temp(N, vector<int>(N));
    for(int i=0; i<N; i++){ 
        for(int j=0; j<N; j++){ 
            getCofactor(a, temp, i, j, N); 
            sign = ((i+j) % 2 == 0) ? 1 : -1; 
            adj[j][i] = (sign)*(determinant(temp, N-1 , N)); 
        } 
    } 
} 

bool inverse(vector<vector<int> > &a, vector<vector<int> > &inv, int N){ 
    int det = determinant(a, N, N); 
    if(det == 0){ 
        cout << "Inverse does not exist"; 
        return false; 
    } 
    int invDet = modInverse(det,26);
    cout << "Mod Determinan: " << det % 26 << '\n' << "Invers Determinan: " << invDet <<'\n';
    vector<vector<int> > adj(N, vector<int>(N));
    adjoint(a, adj, N);  
    for(int i=0; i<N; i++) 
        for(int j=0; j<N; j++) 
            inv[i][j] = (adj[i][j] * invDet) % 26; 
    return true; 
} 


int main(){
    int k = 0, n; string teks; string result;
    cout<<"Masukkan besaran matriks kunci: ";
    cin>>n;
    cout<<"Masukkan nilai matriks kunci:\n";
    vector<vector<int> > a(n, vector<int>(n));
    vector<vector<int> > adj(n, vector<int>(n));
    vector<vector<int> > inv(n, vector<int>(n));

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> a[i][j];
        }
    }
    if(inverse(a,inv,n)){
        cout << "Inverse exist\n";
    }

    cout<<"Masukkan cipherteks: ";
    cin>>teks;
   
   //perkalian cipherteks dengan invers dari key matriks, P = C * K^-1
    while(k < teks.size()){
        for(int i=0; i<n; i++){
            int sum = 0;
            int temp = k;
            for(int j=0; j<n; j++){
                sum += ((teks[temp++]-'a') % 26) % 26 * (inv[i][j] + 26) % 26;
                sum = sum % 26;
            }
            result += (sum + 'a');
        }
        k += n;
    }

    int f = result.size()-1;
    
    cout << "Plainteks: ";
    for(int i=0; i<=f; i++){
        cout << result[i];
    }
    return 0;    
}