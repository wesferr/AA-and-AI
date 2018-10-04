#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

// Mapa do nome da pessoa para o vértice
unordered_map<string, int> indexes;
// Vértice para o nome
vector<string> reverse_index;

// Lista de adjancências
vvi adj_list;
// Conta quantas arestas chegam no vértice i
vi indegree;
// Verifica se o nó foi removido do grafo (remoção lógica)
vector<bool> removed;
// Resposta da ordenação topológica
vi top_order;

/*
Retorna verdadeiro caso tenha conseguido encontrar uma ordenação topológica.
Nesse caso, a resposta está em top_order
*/
bool top_sort()
{
    queue<int> q;

    int u;

    /* 
    Adiciona na fila todos os vértices que não possuem
    nenhuma aresta chegando nele.
    */
    for (int i=0; i< adj_list.size(); ++i)
    {
        if (indegree[i] == 0 )
        {
            q.push(i);            
        }        
    }
    while (!q.empty())
    {
        u = q.front(); q.pop();
        /*
        Se esse nó estava na fila, então nenhuma aresta chegava nele.
        O que significa que ele não depende mais de ninguém e, portanto,
        é parte da ordenação.
        */
        top_order.push_back(u);

        /* Marca o nó como removido do grafo */
        removed[u] = true;

        /*
        Se o nó foi removido, para cada nó adjacente precisamos
        diminuir 1 do contador de arestas que chegam nesse nó adjacente, afinal,
        o nó não existe mais.
        */
        for (int k=0; k<adj_list[u].size(); ++k)
        {
            int v = adj_list[u][k];
            /*
            Caso o nó adjancente não tenha sido removido, então subtraímos 1 do contador
            de arestas. Caso o nó adjacente fique com 0 arestas, significa que ele agora
            será um candidato a ser colocado na fila, e o processo se repetirá.
            */
            if (!removed[v]  && --indegree[v] == 0)
            {
                q.push(v);
            }
        }
    }
    /* Se ao final do processo, todos os nós foram adicionados na em top_order,
    então significa que todos os elementos foram para a fila, o que significa
    que todas as pendências anteriores a ele foram satisfeitas e, portanto, 
    encontramos uma ordem.
    */
    return adj_list.size() == top_order.size();

}

void clear_all(int n)
{
    indexes.clear();
    reverse_index.clear();
    
    adj_list.clear();
    adj_list.resize(n);    

    indegree.clear();
    indegree.resize(n,0);

    removed.clear();
    removed.resize(n, false);
    
    top_order.clear();
}

int main()
{
    int n;
    string name;
    string source, target;
    int k, u, v;
    int test_case = 1;

    cin >> n;
    
    while (n)
    {
        clear_all(n);

        for (int i=0; i<n; ++i)
        {
            cin >> name;
            indexes[name] = i;
            reverse_index.push_back(name);
        }

        for (int i=0; i<n; ++i)
        {
            cin >> target >> k;

            v = indexes[target];
            for (int j=0; j< k; ++j)
            {
                cin >> source;            
                u = indexes[source];
                
                indegree[v]++;
                adj_list[u].push_back(v);
            }    
        }
        cout << "Teste "<< test_case++ << endl;
        if (top_sort())
        {
            for (int i=0; i<top_order.size(); ++i)    
            {
                if (i!=0)
                {
                    printf(" ");
                }
                cout << reverse_index[top_order[i]];
                
            }
            printf("\n");
        }
        else
        {
            printf("impossivel\n");
        }
        
        cin >> n;    
        if (n) cout << endl;
    }

    return 0;
}
