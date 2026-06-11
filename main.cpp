/*
    - Representar um  mapa composto por cidades e rotas (grafos)
    - Calcular caminhos entre diferentes localidades (algoritmos vistos em aula)
    - Permitir diferentes critérios de otimização (?)
    - Exibir os caminhos encontrados e seus rescpetivos custos

*/

#include <iostream>
#include <string>
#include <vector>

struct Cidade
{
    int id;
    string nome;
};

struct Rota
{
    int destino;
    int distancia;
    int tempo;
    int perigo;
};


// REPRESENTAÇÃO DO MAPA
class Mapa
{
    //Vetor para guardar todas cidades
    vector<Cidade> cidades;
    
    // Lista de adjacencia 
    // 1. Indice externo representa cidade de origem
    // 2. Indice interno, cada posição contem um vetor de Rota, representando todas conexçoes que saem daquela cidade
    vector<vector<Rota>> adj;

    public:
        void addCidade(string nome);
        void addRota  (int origem, int destino, int distancia, int tempo, int perigo);
        vector<int> dijkstra(int origem, string criterio);
        void exibirCaminho(int origem, int destino, string criterio);
};

// Criar nova cidade
// 1. Adicionar ID sequencial para ela
// 2. Criar nova linha vazia em adjacencia para guardar futuras rotas
void Mapa::addCidade(string nome)
{

}

// Criar nova rota
// 1. Criar uma Rota{destino, distancia, tempo, perigo}
// 2. Inserir a rota no vetor de adjacencia
// 3. Repetir 1. e 2. porém para o caminho de volta
void Mapa::addRota(int origem, int destino, int distancia, int perigo)
{

}


// Bah
vector<int> Mapa::dijkstra(int origem, string criterio)
{

}
