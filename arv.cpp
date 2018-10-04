#include <iostream>
#include <cstdlib>

using namespace std;
struct Arv{
    char info;
    Arv* esq;
    Arv* dir;

};

int arv_vazia(Arv* a){
    return (a == NULL);
}

Arv* arv_criavazia(){
    return NULL;
}


Arv* arv_cria(char c, Arv* sae, Arv* sad){
    Arv* a = new Arv();
    a->info = c;
    a->esq = sae;
    a->dir = sad;
    return a;
}

Arv* arv_libera(Arv* a){
    if(!arv_vazia(a)){
            arv_libera(a->dir);
            delete a;
    }
    return NULL;

}

Arv* arv_busca(Arv* a, int v){
  if(a == NULL) return NULL;
  else if (a->info > v) return arv_busca(a->esq, v);
  else if (a->info < v) return arv_busca(a->dir, v);
  else return a;
}

void arvore_imprime(Arv* a, int nivel){
    int i;
    if(!arv_vazia(a)){
       cout << a->info << endl;
       if(a->esq != NULL){
            for(i = 0; i< nivel; i++) cout << "  ";
            arvore_imprime(a->esq, nivel+1);
       }
       if(a->dir!= NULL){
            for(i = 0; i< nivel; i++) cout << "  ";
            arvore_imprime(a->dir, nivel+1);
       }
    }
}

Arv* insere(Arv* a, int v){
    if (a == NULL){
        a = new Arv;
            if (a!=NULL){
            a->info = v;
            a->esq = NULL;
            a->dir = NULL;
        }
    }
    else if(v < a->info){
        a->esq = insere(a->esq, v);
    }
    else a->dir = insere(a->dir, v);

}

int max2(int a, int b){
  return (a>b)? a:b;
}

int arv_altura(Arv* a){
  if(arv_vazia(a)) return 0;
  else
    return 1 + max2( arv_altura(a->esq), arv_altura(a->dir) );
}


Arv* gera_dados (Arv* a, int tamanho){
    int i = 0, j = 0, value = 0, flag = 0;
    int aux;

    srand(time(NULL));

    for (i = 0; i<tamanho; i++){

      if(a == NULL){
        a = insere(a, rand()%tamanho);
      }
      else{

      }

    }


}

Arv* retira(Arv* a, int v){
  if(a==NULL) return NULL;
  else if(a->info > v) a->esq = retira(a->esq, v);
  else if(a->info < v) a->dir = retira(a->dir, v);
  else{
    if(a->esq == NULL && a->dir == NULL){
      free (a);
      a = NULL;
    }
    else if(a->esq == NULL){
      Arv* t = a;
      a = a->dir;
      free (t);
    }
    else if(a->dir == NULL){
      Arv* t = a;
      a = a->esq;
      free(t);
    }
    else{
      Arv* pai = a;
      Arv* f = a->esq;
      while(f->dir != NULL){
        pai = f;
        f = f->dir;

      }
      a->info = f->info;
      a->info = v;
      a->esq = retira(a->esq, v);
    }
  }
  return a;
}

//EX1: mostra os elementos na ordem RAIZ - ESQUERDA - DIREITA
Arv* preOrdem(Arv* a){
  if(a == NULL) return NULL;
  else{
    cout << a->info;
    preOrdem(a->esq);
    preOrdem(a->dir);
   }

}

//EX1: mostra os elementos em ordem simetrica ESQUERDA - RAIZ - DIREITA
Arv* emOrdem(Arv* a){
  if(a == NULL) return NULL;
  else{
    emOrdem(a->esq);
    cout << a->info;
    emOrdem(a->dir);
   }

}

//EX1: mostra os elementos na ordem ESQUERDA - DIREITA - RAIZ
Arv* posOrdem(Arv* a){
  if(a == NULL) return NULL;
  else{
    posOrdem(a->esq);
    posOrdem(a->dir);
    cout << a->info;
   }

}

//EX2: conta recursivamente as folhas apartir do caso "se é folha retorna um" acumulando recurcivamente
int contafolhas(Arv* a){
  if(a->esq == NULL && a->dir == NULL) return 1;
  else if(a->dir == NULL) return contafolhas(a->esq);
  else if(a->esq == NULL) return contafolhas(a->dir);
  else return contafolhas(a->esq) + contafolhas(a->dir);

}

//EX3: compara as arvores e as subarvores recursivamente, elemento a elemento, ponteiro a ponteiro
int is_equal(Arv* a, Arv* b){
  if(a == NULL && b == NULL) return 1;
  else if(a != NULL && b != NULL){
    if(a->info == b->info){
      if(is_equal(a->esq, b->esq) && is_equal(a->dir, b->dir)) return 1;
    }
    else return 0;
  }
  else return 0;
}


//EX4: verifica se a arvore(ou subarvore) esta balanceada dada a formula FB = hSAD -hSAE
int balanceada(Arv* a){
  if(a != NULL){
  int x = (arv_altura(a->dir) - arv_altura(a->esq));
    if( x > 1 || x < -1)return 1;
    else return 0;
  }

}

//EX4: verifica com a formula FB = hSAD - hSE do nodo raiz e da suas folhas para saber qual é o caso de balanceamento
int caso_rotacao(Arv* a, int altura = 0){
  int FB, FBE, FBD;
  FB = arv_altura(a->dir) - arv_altura(a->esq);
  if(altura == 0){
    FBE = caso_rotacao(a->esq, 1);
    FBD = caso_rotacao(a->dir, 1);
    cout << FB << " " << FBD << " " << FBE << " " << FBD-FBE << endl;
    if(FB > 1){
      if ((FBD - FBE) > 0) cout << "rotação simples" << endl;
      if ((FBD - FBE) < 0) cout << "rotação dupla" << endl;
    }
    else if(FB < -1){
      if ((FBD - FBE) < 0) cout << "rotação simples" << endl;
      if ((FBD - FBE) > 0) cout << "rotação dupla" << endl;
    }
    else cout << "arvore balanceada" << endl;
    return 0;
  }
  if(altura == 1){
    return FB;
  }
}

int main(){

    cout << "Arvore Binaria" << endl;

    Arv* a;
    a = arv_criavazia();
    a = insere(a, 'f');
    a = insere(a, 'c');
    a = insere(a, 'd');
    a = insere(a, 'e');
    a = insere(a, 'b');
    a = insere(a, 'h');
    a = insere(a, 'i');
    a = insere(a, 'g');

    Arv* b;
    b = arv_criavazia();
    b = insere(b, 'f');
    b = insere(b, 'c');
    b = insere(b, 'b');
    b = insere(b, 'a');
    b = insere(b, 'a'-1);
    b = insere(b, 'h');
    b = insere(b, 'g');
    

    arvore_imprime(a, 1);
    arvore_imprime(b, 1);
    cout << arv_altura(a) << endl;
    preOrdem(a);
    cout << endl;
    emOrdem(a);
    cout << endl;
    posOrdem(a);
    cout << endl;
    cout << contafolhas(a) << endl;
    cout << is_equal(a,b) << endl;
    caso_rotacao(b);

    return 0;
}
