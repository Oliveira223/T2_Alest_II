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
// 1. Adicionarif(u == -1 || distTo[j] < distTo[u])
            //            u = j;
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
// 1. Inicializar distTo[] com infinito, edgeTo[] com -1 e visitado[] com false; distTo[origem] = 0
// 2. Repetir n vezes:
//    2.1 Encontrar a cidade não visitada com menor distTo (cidade atual)
//    2.2 Marcá-la como visitada
//    2.3 Para cada vizinho da cidade atual:
//        - Calcular novo custo (distTo[atual] + peso da rota)
//        - Se novo custo for menor, atualizar distTo e edgeTo
// 3. Retornar edgeTo[] para reconstrução do caminho
vector<int> Mapa::dijkstra(int origem, Criterio criterio)
{
    int n = cidades.size();

    // Distancia para cada cidade (começa com infinito)
    vector<int> distTo(n, INT_MAX);
    distTo[origem] = 0;

    // De onde eu vim para chegar em cada cidade (para reconstruir o caminho)
    vector<int> edgeTo(n, -1);

    // Quais cidades já foram processadas definitivamente
    vector<bool> visitado(n, false);

    // Loop principal, repete N vezes, uma por cidade
    for(int i = 0; i < n; i++)
    {
        // Encontra qual cidade processar nessa iteração
        // varre distTo[] e retorna o índice u com menor custo ainda não visitado
        int u = -1;
        for (int j = 0; j < n; j++)
        {
            //Analisa cidades apenas não visitadas
            if(!visitado[j])
            {
                //Primeira cidade visitada ou cidade melhor que a atual
                if(u == -1 || distTo[j] < distTo[u])
                {
                    u = j;
                } 

                //Exemplo: lista = [5, 3, 8, 1, 4]
                // menor = -1
                // j=0: menor=-1 → menor=5 (cidade com id = 0)
                // j=1: 3 < 5?  → sim → menor=3
                // j=2: 8 < 3?  → não → menor=3
                // j=3: 1 < 3?  → sim → menor=1
                // j=4: 4 < 1?  → não → menor=1

            }

            // Indica que foi visitado
            visitado[u] = true;
        }

        
    }

}
