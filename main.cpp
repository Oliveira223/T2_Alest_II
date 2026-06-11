/*
    - Representar um  mapa composto por cidades e rotas (grafos)
    - Calcular caminhos entre diferentes localidades (algoritmos vistos em aula)
    - Permitir diferentes critérios de otimização (?)
    - Exibir os caminhos encontrados e seus rescpetivos custos

*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

// REPRESENTAÇÃO DO MAPA
class Mapa
{
    enum Criterio
    {    
        DISTANCIA, TEMPO, PERIGO
    };
    
    struct Cidade
    {
        int id;
        string nome;
    };
    
    struct Rota
    {
        int origem, destino, distancia, tempo, perigo;
    };
    
    
    // Lista de adjacencia 
    // 1. Indice externo representa cidade de origem
    // 2. Indice interno, cada posição contem um vetor de Rota, representando todas conexçoes que saem daquela cidade
    vector<vector<Rota>> adj;
    
    //Vetor para guardar todas cidades
    vector<Cidade> cidades;
    
    public:
    //métodos somente para armazenamento
        void addCidade(string nome, int id);
        void addRota(int origem, int destino, int distancia, int tempo, int perigo);
        
    // consulta do grafo
        int getPeso(const Rota& rota, Criterio criterio);
        vector<Rota> getAdjacente(int id);
        void exibirCaminho(int origem, int destino, string criterio);
        string getCidade(int id );

    //algoritmo de caminho mínimo
        
        //Ele guarda o menor custo conhecido até agora
        //int distTo();

        //de onde vim
        //void EdgeTo();

        vector<int> dijkstra(int origem, Criterio criterio);

    };

// Criar nova cidade
// 1. Adicionar
// 2. Criar novo vetor vazia em adjacencia para guardar futuras rotas
void Mapa::addCidade(string nome, int id)
{
    //colocar if caso exista a cidade
    cidades.push_back({id, nome});
    adj.push_back({});
}

// Criar nova rota
// 1. Criar uma Rota{destino, distancia, tempo, perigo}
// 2. Inserir a rota no vetor de adjacencia
// 3. Repetir 1. e 2. porém para o caminho de volta
void Mapa::addRota(int origem, int destino, int distancia, int tempo, int perigo)
{
    if(origem == destino){
        cout << "e a mesma cidade";
        return;
    }

    adj[origem].push_back({destino, distancia, tempo, perigo});
// colocar if se não existe a cidade
    adj[destino].push_back({origem, distancia, tempo, perigo});
}


int Mapa::getPeso(const Rota& rota,Criterio criterio)
{
     
    switch( criterio){

        case DISTANCIA: return rota.distancia;

        case TEMPO: return rota.tempo;
        
        case PERIGO: return rota.perigo;

        default: 
            cout<< " peso inválido !!!"<< endl;
            return 0;
    }

}

   vector<Mapa::Rota> Mapa::getAdjacente(int id)
{
    return adj[id];
}


vector<int> Mapa::dijkstra(int origem, Criterio criterio)
{

}
