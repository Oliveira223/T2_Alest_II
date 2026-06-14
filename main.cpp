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
#include <queue>
#include <climits> //para infinito

using namespace std;

// REPRESENTAÇÃO DO MAPA
class Mapa
{
    enum Criterio{ DISTANCIA, TEMPO, PERIGO };
    
    struct Cidade
    {
        int id;
        string nome;
    };
    
    struct Rota
    {
        int origem, destino, distancia, tempo, perigo;

        //Auxiliar para Dijjkstra
        int getPeso(Criterio criterio)
        {
            switch(criterio)
            {
                case DISTANCIA:     return distancia;
                case TEMPO:         return tempo;
                case PERIGO:        return perigo;

                default:            return 0;
            }
        }
    };
    
    // Lista de adjacencia 
    // 1. Indice externo representa cidade de origem
    // 2. Indice interno, cada posição contem um vetor de Rota, representando todas conexçoes que saem daquela cidade
    vector<vector<Rota>> adj;
    
    //Vetor para guardar todas cidades
    vector<Cidade> cidades;
    
    public:
    
    //Métodos somente para armazenamento
        void addCidade(string nome, int id);
        void addRota(int origem, int destino, int distancia, int tempo, int perigo);
        
    //Consulta do grafo
        vector<Rota> getAdjacente(int id);
        void exibirCaminho(int origem, int destino, string criterio);
        string getCidade(int id );


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
        cout << "É a mesma cidade" << endl;
        return;
    }

    adj[origem].push_back({origem, destino, distancia, tempo, perigo});
    adj[destino].push_back({destino, origem, distancia, tempo, perigo});

}



//Auxiliar para Dijkstra no relaxamento
vector<Mapa::Rota> Mapa::getAdjacente(int id)
{
    return adj[id];
}

// Calcula o caminho mínimo a partir de uma origem usando o critério escolhido
// 1. Inicializar distTo[] com infinito e edgeTo[] com -1; distTo[origem] = 0
// 2. Inserir a origem na fila de prioridade com custo 0
// 3. Retirar da fila a cidade de menor custo acumulado
// 4. Se já foi visitada, ignorar e voltar ao passo 3
// 5. Para cada vizinho: calcular novo custo e, se menor, atualizar distTo e edgeTo e inserir na fila
// 6. Repetir 3, 4 e 5 até a fila esvaziar
// 7. Retornar edgeTo[] para reconstrução do caminho
vector<int> Mapa::dijkstra(int origem, Criterio criterio)
{
    //Distancia para cada cidade, onde:
    //n       -> numero de cidades
    //INT_MAX -> valor muito grande 
    vector<int> distTO(n, INT_MAX);

    //De onde eu vim para chegar em cada cidade (para reconstruir o caminho), onde
    //n       -> 
    vector<int> edgeTo(n, -1);

}
