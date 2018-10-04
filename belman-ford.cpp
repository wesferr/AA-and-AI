#include <iostream>
#define INFINITY 0x3f3f3f3f
#define NODOS 1000

using namespace std;

typedef struct {
	int source;
	int dest; //destino
	int weight; //peso
} Edge;

int distancia[NODOS];

void BellmanFord(Edge edges[], int edgecount, int nodecount, int source) {
	int i,j,trocou;
	//seta todas as distancias como infinito
	for (i = 0; i < nodecount; i++) {
		distancia[i] = INFINITY;
	}
	//seta a distancia do vertice inicial como 0
	distancia[source]=0;
	
	//para cada vertice define a nova distancia calculada des de que seja menor que a distancia ja calculada
	for (i = 0; i < nodecount; i++) {
		trocou = 0;
		for (j = 0; j < edgecount; j++) {
			if (distancia[edges[j].dest] > distancia[edges[j].source] + edges[j].weight) {
				distancia[edges[j].dest] = distancia[edges[j].source] + edges[j].weight;
				trocou=1;
			}
		}
		
		// se nenhuma iteração teve efeito, futuras iterações estão dispensadas
		if (trocou==0) break;
	}
	
	// usado somente para detectar ciclos negativos (dispensável)
	for (i = 0; i < edgecount; i++) {
		if (distancia[edges[i].dest] > distancia[edges[i].source] + edges[i].weight) {
			cout << "Ciclo negativo de pesos de arestas detectado" << endl;
			break;
		}
	}
	for (i = 0; i < nodecount; i++) {
		cout << "A distancia mais curta entre os nodos " << source << " e " << i <<" eh " << distancia[i] << endl;
	}
}
int main (void){

	// Este caso de teste produzira as distancias entre o nodo 0 e os outros nodos
	Edge Arestas[10] = 	{{0, 1, 5}, {0,2, 8}, {0,3, -4}, {1,0, -2}, {2, 1, -3}, {2,3, 9}, {3,1, 7}, {3,4, 2}, {4,0, 6}, {4,2, 7}};
	// BellmanFord(Estrutura, arestas, vertices,origem);
	BellmanFord(Arestas, 10, 5, 0);
	return 0;
	
}
