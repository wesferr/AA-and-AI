#include <iostream>
#include <fstream>
using namespace std;

long int merge (long int v[],int ini, int meio,int fim){

    long int a = ini;
    long int b = meio+1;
    long int aux[fim-ini+1];
    long int c = 0;
    long int inv = 0;
    
    while(a <= meio && b <= fim){
    
        if(v[a] < v[b]){
            aux[c++] = v[a++];
        } else {
            aux[c++] = v[b++];
            inv+=meio-a+1;
        }
    }
    
    while(a <= meio) aux[c++] = v[a++];
        
    while(b<=fim) aux[c++] = v[b++];
    
    for(c = ini; c <=fim; c++) v[c] = aux[c-ini];
        
    return inv;
    
}

long int mergeSort (long int v[],int esq, int dir){

    long int inv = 0;
    if(dir == esq) return 0;
    else{
        long int meio = (esq+dir)/2;
        inv = mergeSort(v,esq,meio);
        inv += mergeSort(v,meio+1,dir);
        inv += merge(v,esq,meio,dir);
    }
    return inv;
    
}


int main(int argc, char **argv){

    if(argc < 2){
        cout << "Modo de uso: " << argv[0] << " <nome do arquivo>" << endl;
        return(1);
    }
    
    long int n;
    
    ifstream entrada;
    entrada.open(argv[1]);
    entrada >> n;
    
    long int *v = new long int[n+1];
    
    for (long int i = 0; i < n; i++) {
        entrada >> v[i];
    }    
    
    long int conta = mergeSort(v,0,n-1);   
    
    cout << conta << "\n";
    
    delete []v;
    return 0;
    
}
