#ifndef GRAFO_PLOTTER_HPP
#define GRAFO_PLOTTER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class GrafoPlotter
{
private:
    struct Rota {
        int origem, destino, distancia, tempo, perigo;
    };

    vector<pair<int, string>> cidades;
    vector<Rota> rotas;
    set<pair<int, int>> arestas_adicionadas;

    string nomeCidade(int id) const
    {
        for(const auto& cidade : cidades)
        {
            if(cidade.first == id) return cidade.second;
        }

        return "Cidade_" + to_string(id);
    }

    bool existeCidade(int id) const
    {
        for(const auto& cidade : cidades)
        {
            if(cidade.first == id) return true;
        }

        return false;
    }

    vector<pair<int, string>> cidadesOrdenadas() const
    {
        vector<pair<int, string>> ordenadas = cidades;

        sort(ordenadas.begin(), ordenadas.end(), [](const auto& a, const auto& b) {
            return a.first < b.first;
        });

        return ordenadas;
    }

    int larguraCelula(int largura, const string& texto, int x) const
    {
        if(x < 0) return 0;
        return min((int)texto.size(), largura - x);
    }

    void escreverTexto(vector<string>& tela, int x, int y, const string& texto) const
    {
        if(y < 0 || y >= (int)tela.size() || x >= (int)tela[y].size()) return;

        int inicioTexto = 0;
        if(x < 0)
        {
            inicioTexto = -x;
            x = 0;
        }

        int qtd = larguraCelula(tela[y].size(), texto.substr(inicioTexto), x);
        for(int i = 0; i < qtd; i++)
        {
            tela[y][x + i] = texto[inicioTexto + i];
        }
    }

    void desenharSegmento(vector<string>& tela, int x1, int y1, int x2, int y2, char caractere) const
    {
        int passoX = (x1 == x2) ? 0 : (x1 < x2 ? 1 : -1);
        int passoY = (y1 == y2) ? 0 : (y1 < y2 ? 1 : -1);
        int x = x1;
        int y = y1;

        while(true)
        {
            if(x >= 0 && y >= 0 && y < (int)tela.size() && x < (int)tela[y].size())
            {
                char atual = tela[y][x];
                if(atual == ' ')
                {
                    tela[y][x] = caractere;
                }
                else if(atual == '-' || atual == '|' || atual == '+')
                {
                    tela[y][x] = '+';
                }
            }

            if(x == x2 && y == y2) break;

            x += passoX;
            y += passoY;
        }
    }

    void desenharRota(vector<string>& tela, int x1, int y1, int x2, int y2) const
    {
        int meioX = (x1 + x2) / 2;

        desenharSegmento(tela, x1, y1, meioX, y1, '-');
        desenharSegmento(tela, meioX, y1, meioX, y2, '|');
        desenharSegmento(tela, meioX, y2, x2, y2, '-');
    }

    pair<int, int> pontoNoMapa(int xPercentual, int yPercentual, int largura, int altura) const
    {
        int x = 2 + ((largura - 5) * xPercentual / 100);
        int y = 2 + ((altura - 5) * yPercentual / 100);

        return {x, y};
    }

    map<int, pair<int, int>> calcularPosicoes(int largura, int altura) const
    {
        map<int, pair<int, int>> posicoes;
        vector<pair<int, string>> ordenadas = cidadesOrdenadas();

        if(ordenadas.empty()) return posicoes;

        map<int, pair<int, int>> posicoesBase = {
            {0, pontoNoMapa(13, 20, largura, altura)},  // Solitude
            {1, pontoNoMapa(55, 53, largura, altura)},  // Whiterun
            {2, pontoNoMapa(78, 34, largura, altura)},  // Windhelm
            {3, pontoNoMapa(86, 80, largura, altura)},  // Riften
            {4, pontoNoMapa(8, 75, largura, altura)},   // Markarth
            {5, pontoNoMapa(34, 82, largura, altura)},  // Falkreath
            {6, pontoNoMapa(78, 10, largura, altura)},  // Winterhold
            {7, pontoNoMapa(55, 13, largura, altura)},  // Dawnstar
            {8, pontoNoMapa(36, 38, largura, altura)},  // Morthal
            {9, pontoNoMapa(54, 72, largura, altura)},  // Riverwood
            {10, pontoNoMapa(70, 66, largura, altura)}, // Ivarstead
            {11, pontoNoMapa(26, 28, largura, altura)}  // DragonBridge
        };

        int fallback = 0;
        for(const auto& cidade : ordenadas)
        {
            if(posicoesBase.find(cidade.first) != posicoesBase.end())
            {
                posicoes[cidade.first] = posicoesBase[cidade.first];
            }
            else
            {
                int xPercentual = 15 + (fallback % 5) * 18;
                int yPercentual = 15 + (fallback / 5) * 18;
                posicoes[cidade.first] = pontoNoMapa(xPercentual, yPercentual, largura, altura);
                fallback++;
            }
        }

        return posicoes;
    }

    void desenharCidade(vector<string>& tela, int id, const string& nome, pair<int, int> posicao) const
    {
        string rotulo = "[" + to_string(id) + "] " + nome;
        int xRotulo = posicao.first - ((int)rotulo.size() / 2);

        escreverTexto(tela, xRotulo, posicao.second, rotulo);
    }

public:
    GrafoPlotter() {}

    // Adicionar cidade ao plotter
    void addCidade(int id, string nome)
    {
        cidades.push_back({id, nome});
    }

    // Adicionar rota ao plotter
    void addRota(int origem, int destino, int distancia, int tempo, int perigo)
    {
        pair<int, int> chave = make_pair(min(origem, destino), max(origem, destino));
        
        if(arestas_adicionadas.find(chave) == arestas_adicionadas.end())
        {
            arestas_adicionadas.insert(chave);
            rotas.push_back({origem, destino, distancia, tempo, perigo});
        }
    }

    // Gerar arquivo DOT para visualização com GraphViz
    void gerarDOT(string nome_arquivo = "grafo.dot")
    {
        ofstream arquivo_dot(nome_arquivo);

        if(!arquivo_dot.is_open())
        {
            cerr << "Erro ao abrir arquivo " << nome_arquivo << endl;
            return;
        }

        // Cabeçalho do arquivo DOT
        arquivo_dot << "graph Mapa {" << endl;
        arquivo_dot << "  rankdir=LR;" << endl;
        arquivo_dot << "  bgcolor=\"#f0f0f0\";" << endl;
        arquivo_dot << "  node [shape=box, style=\"rounded,filled\", fillcolor=\"#87CEEB\", ";
        arquivo_dot << "fontname=\"Arial\", fontsize=10];" << endl;
        arquivo_dot << "  edge [color=\"#333333\", fontsize=8];" << endl;
        arquivo_dot << endl;

        // Adicionar nós (cidades)
        for(auto& cidade : cidades)
        {
            arquivo_dot << "  " << cidade.first << " [label=\"" << cidade.second << "\"];" << endl;
        }

        arquivo_dot << endl;

        // Adicionar arestas (rotas)
        for(auto& rota : rotas)
        {
            arquivo_dot << "  " << rota.origem << " -- " << rota.destino;
            arquivo_dot << " [label=\"D:" << rota.distancia 
                       << "\\nT:" << rota.tempo 
                       << "\\nP:" << rota.perigo << "\"];" << endl;
        }

        // Fechar arquivo DOT
        arquivo_dot << "}" << endl;
        arquivo_dot.close();

        cout << "✓ Arquivo '" << nome_arquivo << "' gerado com sucesso!" << endl;
    }
    
   
    // Exibir mapa completo direto no terminal
    void exibirGrafoTerminal(int largura = 120, int altura = 34)
    {
        if(cidades.empty())
        {
            cout << "\nNao ha cidades cadastradas para exibir no mapa.\n" << endl;
            return;
        }

        largura = max(90, largura);
        altura = max(26, altura);

        vector<string> tela(altura, string(largura, ' '));
        map<int, pair<int, int>> posicoes = calcularPosicoes(largura, altura);

        for(int x = 0; x < largura; x++)
        {
            tela[0][x] = '=';
            tela[altura - 1][x] = '=';
        }

        for(int y = 0; y < altura; y++)
        {
            tela[y][0] = '|';
            tela[y][largura - 1] = '|';
        }

        tela[0][0] = '+';
        tela[0][largura - 1] = '+';
        tela[altura - 1][0] = '+';
        tela[altura - 1][largura - 1] = '+';

        escreverTexto(tela, (largura - 21) / 2, 0, " MAPA DE ROTAS ");

        for(const auto& rota : rotas)
        {
            if(!existeCidade(rota.origem) || !existeCidade(rota.destino)) continue;

            auto origem = posicoes[rota.origem];
            auto destino = posicoes[rota.destino];
            desenharRota(tela, origem.first, origem.second, destino.first, destino.second);
        }

        for(const auto& cidade : cidadesOrdenadas())
        {
            desenharCidade(tela, cidade.first, cidade.second, posicoes[cidade.first]);
        }

        cout << endl;
        for(const auto& linha : tela)
        {
            cout << linha << endl;
        }

        cout << endl;
    }
};

#endif
