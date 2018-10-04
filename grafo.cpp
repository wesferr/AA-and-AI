#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <fstream>
#define infinito 0x3f3f3f3f

using namespace std;

class Vertex{
    private:
        int value;
        int distancia;
        Vertex* menInci;
    public:
        Vertex(int val){
            this->value = val;
            distancia = 0;
        }
        Vertex(int val, int dis){
            this->value = val;
            distancia = dis;
        }
        int getValue(){
            return value;
        }
        void setValue(int val){
            this->value = val;
        }
        int getDistancia(){
            return this->distancia;
        }
        
        void setDistancia(int distancia){
            this->distancia = distancia;
        }
};

class Edge{
    private:
        Vertex *v1, *v2;
        int value;
    public:
        Edge(Vertex* v1, Vertex* v2, int value){
            this->v1 = v1;
            this->v2 = v2;
            this->value = value;
        }
        
        int getValue(){
            return this->value;
        }
        void setValue(int value){
            this->value = value;
        }
        Vertex* getV1(){
            return this->v1;
        }
        Vertex* getV2(){
            return this->v2;
        }
        void setV1(Vertex* v1){
            this->v1 = v1;
        }
        void setV2(Vertex* v2){
            this->v2 = v2;
        }
};


class Grafo{
    private:
        vector<Vertex*> vertices;
        vector<Edge*> arestas;
        
    public:
    
        Grafo(){}
        ~Grafo(){}
        
        int exist(int value){
            for( int i = 0; i < vertices.size(); i++ )
                if(value == vertices[i]->getValue())
                    return i+1;
            return 0;
        }
        
        void insertVertex(Vertex* v){
            if( !exist( v->getValue() ) )
                vertices.push_back(v);
        }
        
        Vertex* insertVertex(int value){
            int indice = exist( value );
            Vertex* novov;
            
            if( !indice )
                novov = new Vertex(value);
            else
                return vertices[indice-1];
                
            vertices.push_back( novov );
            return novov;
        }
        
        void insertEdge(Vertex* v1, Vertex* v2, int valEdge){
            insertVertex(v1);
            insertVertex(v2);
            Edge* edge = new Edge(v1,v2, valEdge);
            arestas.push_back(edge);
        }
        
        void insertEdge(int valV1, int valV2, int valEdge){
            Vertex* v1 = insertVertex(valV1);
            Vertex* v2 = insertVertex(valV2);
            Edge* edge = new Edge(v1,v2, valEdge);
            arestas.push_back(edge);
        }
        
        void mostraArestas(){
            for(int i = 0; i < arestas.size(); i++){
                cout << arestas[i]->getV1()->getValue() << " " << arestas[i]->getV2()->getValue() << " " << arestas[i]->getValue() << endl;
            }
        }
        void mostraVertices(int v){
            for(int i = 0; i < vertices.size();i++){
                if(i != v){
                    if(vertices[i]->getDistancia() != 1061109567)
                        cout << vertices[i]->getValue() << " " << vertices[i]->getDistancia()  << endl;
                    else 
                        cout << vertices[i]->getValue() << " " << "inf" << endl;
                }
            }
        }
        
        void inicializacao(int origem){
            for(int i = 0; i < vertices.size(); i++){
                if(vertices[i]->getValue() == origem){
                    vertices[i]->setDistancia(0);
                }else{
                    vertices[i]->setDistancia(infinito);
                }
            }  
        }
        
        void relaxamento(Vertex* u, Vertex* v, int peso){
            if(u->getDistancia() + peso < v->getDistancia()){
                v->setDistancia(u->getDistancia() + peso);
            }
        }
        
        int BellmanFord(int origem){
        
            inicializacao(origem);
            for(int i = 0; i < vertices.size()-1; i++){ // até n-1
                for(int k = 0; k < arestas.size(); k++){// todas as arestas direcionadas aquele vertice
                    relaxamento( arestas[k]->getV1(), arestas[k]->getV2(), arestas[k]->getValue() );
                }  
            }
            
            for(int i = 0; i < arestas.size(); i++){
                if( arestas[i]->getV2()->getDistancia() > (
                    arestas[i]->getV1()->getDistancia() + arestas[i]->getValue()
                ) )
                    return false;
            }
            return true;
            
        }
        
        static bool comp(Vertex* a, Vertex* b){
                return a->getDistancia() < b->getDistancia();
        }
        
        void Dijkstra(int origem){
        
            inicializacao(origem);
            vector<Vertex*> Q = vertices;
            make_heap(Q.begin(), Q.end(), comp);
            
            while(Q.size() > 0){
                Vertex* atual = Q.back();
                Q.pop_back();
                make_heap(Q.begin(), Q.end(), comp);
                for(int i = 0; i < arestas.size(); i++){
                    if(arestas[i]->getV1() == atual){
                        relaxamento( atual, arestas[i]->getV2(), arestas[i]->getValue() );
                    }
                }
            }
        }
        
        void Johnson(int origem){
            
            Vertex* aux = new Vertex(-1);
            vector<Vertex*> temp;
            
            
            for(int i = 0; i < vertices.size(); i++){
                insertEdge(aux, vertices[i], 0);
            }
            if( BellmanFord(-1) ){
                while(true){
                
                    Edge* aux = arestas.back();
                    if( aux->getV1()->getValue() == -1 )
                        arestas.pop_back();
                    else
                        break;
                
                }
                vertices.pop_back();
                for(int i = 0; i < arestas.size(); i++){
                    arestas[i]->setValue(
                        arestas[i]->getValue() +
                        arestas[i]->getV1()->getDistancia() -
                        arestas[i]->getV2()->getDistancia()
                    );
                }
                Dijkstra(origem);
                
                cout << "Vértice " << origem << ":\n"; 
                mostraVertices(origem);
            }
            
            
        }
        

};

int main(int argc, char** argv){
    int vnum, anum, origem;
    Grafo* g = new Grafo();
    
    ifstream ifile(argv[1], ifstream::in);
    ifile >> vnum;
    ifile >> anum;
    for(int i = 0; i < anum; i++){
        int v1, v2, ed;
        ifile >> v1 >> v2 >> ed;
        g->insertEdge(v1, v2, ed);
    }
    ifile.close();
    
    origem = atoi(argv[2]);
    g->Johnson(origem);
    
    
    delete g;

}
