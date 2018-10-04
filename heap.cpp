#include <iostream>
#include <fstream>
using namespace std;

void heapifyDown(long int *vetor, int n, int i)
{
    int maior = i;
    int filhoesq = 2*i + 1;
    int filhodir = 2*i + 2;
    
    if ( filhoesq < n && vetor[filhoesq] > vetor[maior] ) maior = filhoesq;
    if ( filhodir < n && vetor[filhodir] > vetor[maior] ) maior = filhodir;
    if (maior != i){
        swap(vetor[i], vetor[maior]);
        heapifyDown(vetor, n, maior);
    }
}
 
void heapSort(long int *vetor, int n){
    for (int i = n / 2 - 1; i >= 0; i--)
        heapifyDown(vetor, n, i);
    for (int i=n-1; i>=0; i--){
        swap(vetor[0], vetor[i]);
        heapifyDown(vetor, i, 0);
    }
}

int main(int argc, char **argv){

    if(argc < 2){
        cout << "Modo de uso: " << argv[0] << " <nome do arquivo>" << endl;
        return(1);
    }
    
    int n;
    ifstream entrada;
    entrada.open(argv[1]);
    entrada >> n;
    
    long int *v = new long int[n+2];
    v[0] = 0;
    
    for (long int i = 1; i < n+1; i++) {
        entrada >> v[i];
    }    
    
    heapSort(v,n+1);
    
    for (long int i = 1; i < n+1; i++) {
        cout << v[i] << " ";
    }
    cout << endl;
    
    delete []v;
    return 0;
    
}
