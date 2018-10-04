// Copyright (c) 2018 by Wesley Ferreira. All Rights Reserved.

#include <iostream>

using namespace std;

int main(int argc, char** argv){


    int i, x, a, b, num, M, n;

    cin >> M >> n;

    int *v = new int[n+1];
    int *p = new int[n+1];
    int **V = new int*[2];
    V[0] = new int[M+1];
    V[1] = new int[M+1];

    for(i = 0; i < M+1;i++){
        V[0][i] = 0;
        V[1][i] = 0;
    }

    for(i = 1; i < n+1; i++){
        cin >> v[i] >> p[i];
    }

    for (i = 1; i < n+1; i++) {
        num = i%2;
        for (x = 1; x < M+1; x++) {
            a = V[num][x];
            if (p[i] > x) b = 0;
            else b = V[num][x-p[i]] + v[i];
            V[1-num][x] = a > b ? a : b;

        }
    }

    cout << V[1-num][M] << endl;

    delete []v;
    delete []p;
    delete []V[0];
    delete []V[1];
    delete []V;
 }
