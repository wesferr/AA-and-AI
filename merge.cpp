#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

void merge (long long int v[], long long int ini, long long int meio, long long int fim){

    long long int a = ini;
    long long int b = meio+1;
    long long int* aux = new long long int[fim-ini+1];
    if(!aux)exit(1);
    long long int c = 0;
    
    while(a <= meio && b <= fim){
    
        if(v[a] < v[b]){
            aux[c++] = v[a++];
        } else {
           aux[c++] = v[b++];
        }
    }
    
    while(a <= meio)aux[c++] = v[a++];
        
    while(b<=fim)aux[c++] = v[b++];
    
    for(c = ini; c <= fim; c++)v[c] = aux[c-ini];
    
    delete []aux;
    
}

void mergeSort (long long int v[], long long int esq, long long int dir){

    if(dir == esq) return;
    else{
        long long int meio = (esq+dir)/2;
        mergeSort(v,esq,meio);
        mergeSort(v,meio+1,dir);
        merge(v,esq,meio,dir);
    }
    
}


int main(int argc, char **argv){

    if(argc < 2){
        cout << "Modo de uso: " << argv[0] << " <nome do arquivo>" << endl;
        return(1);
    }
    
    long long int n;
    
    ifstream entrada;
    entrada.open(argv[1]);
    entrada >> n;
    
    long long int *v = new long long int[n+1];
    if(!v) exit(1);
    
    for (long long int i = 0; i < n; i++) {
        entrada >> v[i];
    }    
    
    mergeSort(v,0,n-1);
    
    for (long long int i = 0; i < n; i++) {
        cout << v[i] << " ";
    }
    cout << endl;
    
    delete []v;
    return 0;
    
}
