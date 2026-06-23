/*
    - Representar um  mapa composto por cidades e rotas (grafos)
    - Calcular caminhos entre diferentes localidades (algoritmos vistos em aula)
    - Permitir diferentes critérios de otimização
    - Exibir os caminhos encontrados e seus respectivos custos

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
    
    public:
    //(precisa ser public E declarado antes de Rota)
    enum Criterio{ DISTANCIA, TEMPO, PERIGO };
    
    private:

        struct Cidade
        {
            int id;
            string nome;
        };

        struct Rota
        {
            int origem, destino, distancia, tempo, perigo;

            //Auxiliar para Dijkstra
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
        void exibirCaminho(int origem, int destino, Criterio criterio);
        string getCidade(int id);

        pair<vector<int>, vector<int>> dijkstra(int origem, Criterio criterio);

    };

// Criar nova cidade
// 1. Adicionar cidade no vetor
// 2. Criar novo vetor vazia em adjacencia para guardar futuras rotas
void Mapa::addCidade(string nome, int id)
{
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

// Auxiliar para exibir caminho final
string Mapa::getCidade(int id)
{
    // Cidades é um vetor onde cada posição (id) é uma cidade
    return cidades[id].nome;
}

// DIJKSTRA: Calcula o caminho mínimo a partir de uma origem usando o critério escolhido 
// 1. Inicializar distTo[] com infinito, edgeTo[] com -1 e visitado[] com false; distTo[origem] = 0
// 2. Repetir n vezes:
//    2.1 Encontrar a cidade não visitada com menor distTo (cidade atual)
//    2.2 Marcá-la como visitada
//    2.3 Para cada vizinho da cidade atual:
//        - Calcular novo custo (distTo[atual] + peso da rota)
//        - Se novo custo for menor, atualizar distTo e edgeTo
// 3. Retornar edgeTo[] e distTo[] — edgeTo para reconstruir o caminho, distTo para o custo total
pair<vector<int>, vector<int>> Mapa::dijkstra(int origem, Criterio criterio)
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
            }

        }
        // Indica que a cidade foi visitada
        visitado[u] = true;

        // Relaxamento: percorre vizinhos de u e atualiza distTo[] se passar por u for mais barato
        for(int k = 0; k < adj[u].size(); k++)
        {
            Rota r = adj[u][k];
        
            // custo total para chegar no vizinho passando por u
            int novoCusto = distTo[u] + r.getPeso(criterio);
            
            // vale a pena ir por u? só atualiza se for mais barato (na primeira iteração tem que ser mais barato pois r.destino é infinito)
            if(novoCusto < distTo[r.destino])
            {
                // atualiza o custo do vizinho
                distTo[r.destino] = novoCusto;
                
                // registra que chegamos no vizinho vindo de u (para reconstruir o caminho depois)
                edgeTo[r.destino] = u;
            }
        }
        
    }
    // Retorna edgeTo[] para reconstruir o caminho e distTo[] para o custo total
    return {edgeTo, distTo};
}

// Por fim, pegar todas as informações que temos e exibir o melhor caminho disponivel
void Mapa::exibirCaminho(int origem, int destino, Criterio criterio)
{
    // Recebe edgeTo[] (para reconstruir o caminho) e distTo[] (para o custo total)
    pair<vector<int>, vector<int>> resultado = dijkstra(origem, criterio);
    vector<int> edgeTo = resultado.first;
    vector<int> distTo = resultado.second;

    // Vetor para armazenar o caminho
    vector<int> caminho;

    // vamos percorrer do destino à origem, usando o edgeTo para voltar
    int atual = destino;
    
    // Enquanto atual não for a origem (-1)
    while(atual != -1)
    {
        //Coloca o atual no vetor
        caminho.push_back(atual);

        // Avança para a cidade de onde veio antes do atual
        atual = edgeTo[atual];
    }

    // Imprimir o vetor (de trás para frente para ficar na ordem certa)
    for(int i = caminho.size() - 1; i >= 0; i--)
    {
        cout << getCidade(caminho[i]);
        if(i > 0) cout << " -> ";
    }

    cout << "\nCusto total: " << distTo[destino] << endl;
}


