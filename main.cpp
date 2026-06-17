#include <iostream>
#include <fstream>
#include <string>
#include "Mapa.hpp"
using namespace std;

// Função para centralizar texto
string centralizarTexto(string texto, int largura = 80) {
    int espacos = (largura - texto.length()) / 2;
    if (espacos < 0) espacos = 0;
    return string(espacos, ' ') + texto;
}

// Função para criar uma caixa com barra e texto centralizado
void exibirCaixaTexto(string texto) {
    int largura = max((int)texto.length() + 4, 45);
    int espacosTotal = largura - texto.length();
    int espacosEsq = espacosTotal / 2;
    int espacosDir = espacosTotal - espacosEsq;
    
    string textoCentralizado = string(espacosEsq, ' ') + texto + string(espacosDir, ' ');
    string barra = "||" + string(largura, '=') + "||";
    
    cout << barra << endl;
    cout << "||" << textoCentralizado << "||" << endl;
    cout << barra << endl;
}

int main()
{
    ifstream  arquivo_cidades ("mapa_base.txt");
    ifstream  arquivo_rotas   ("rotas.txt");

    // Inicializar mapa
    Mapa mapa;

    // Inicializar cidades
    int id;
    string nome;
    while(arquivo_cidades >> id >> nome)
    {
        mapa.addCidade(nome, id);
    }

    // Inicializar rotas
    int origem, destino, distancia, tempo, perigo;
    while(arquivo_rotas >> origem >> destino >> distancia >> tempo >> perigo)
    {
        mapa.addRota(origem, destino, distancia, tempo, perigo);
    }

    // Fechar arquivos
    arquivo_cidades.close();
    arquivo_rotas.close();

    //inicio do programa
    int cidades = 12;
    int criterio = 10;  
    int c1=0;
    int c2=0;
    int a;  // Declarar fora do switch
    int c = 0;  // Declarar fora do switch
    string sn;
    bool continuar = true;

    while(continuar){

        switch(criterio)
            {             
                case 0:
                    {
                        string mensagem = "Menor distancia: " + mapa.getCidade(c1) + " --> " + mapa.getCidade(c2);
                        exibirCaixaTexto(mensagem);
                    }
                    mapa.exibirCaminho(c1, c2, Mapa::DISTANCIA);
                    cout << endl;
                    
                    criterio = 6;
                    break;
                    
                case 1:
                    {
                        string mensagem = "Menor tempo: " + mapa.getCidade(c1) + " --> " + mapa.getCidade(c2);
                        exibirCaixaTexto(mensagem);
                    }
                    mapa.exibirCaminho(c1, c2, Mapa::DISTANCIA);
                    cout << endl;
                    
                    criterio = 6;
                    break;
                    
                    
                case 2:
                    {
                        string mensagem = "Menor perigo: " + mapa.getCidade(c1) + " --> " + mapa.getCidade(c2);
                        exibirCaixaTexto(mensagem);
                    }
                    mapa.exibirCaminho(c1, c2, Mapa::DISTANCIA);
                    cout << endl;
                    
                    criterio = 6;
                    break;
                
                case 3:
                    cout << endl;
                    cout << "||===============================================||" << endl;
                    cout << "||Escolha duas cidades e qual critério você quer ||" << endl;
                    cout << "||===============================================||" << endl;
                    
                    
                    cout << endl;

                    cout << "||==========================||" << endl;
                    cout << "||     Lista de Cidades     ||" << endl;
                    cout << "||==========================||" << endl;
                    cout << "|| ID | Nome da Cidade      ||" << endl;  
                    cout << "||==========================||" << endl;                                      
                    cout << "||  0 | Solitude            ||" << endl;
                    cout << "||  1 | Whiterun            ||" << endl;
                    cout << "||  2 | Windhelm            ||" << endl;
                    cout << "||  3 | Riften              ||" << endl;
                    cout << "||  4 | Markarth            ||" << endl;
                    cout << "||  5 | Falkreath           ||" << endl;
                    cout << "||  6 | Winterhold          ||" << endl;
                    cout << "||  7 | Dawnstar            ||" << endl;
                    cout << "||  8 | Morthal             ||" << endl;
                    cout << "||  9 | Riverwood           ||" << endl;
                    cout << "|| 10 | Ivarstead           ||" << endl;
                    cout << "|| 11 | DragonBridge        ||" << endl;
                    cout << "||==========================||" << endl;
                    
                    cout << endl;
                    
                    cout << "||==============================||" << endl;
                    cout << "||  Escolha a cidade de Origem  ||" << endl;
                    cout << "||==============================||" << endl;
                    cout << endl;
                    cout << "Resposta: "; 
                    
                    cin >> c1;                    
                    // Limpar buffer se houver erro
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(10000, '\n');
                    }                    
                    cout << endl;
                    
                    if (c1 < 0 || c1 >= cidades){
                        cout << endl;
                        cout << "||================================||" << endl;
                        cout << "||  Esta cidade não existe !!!    ||" << endl;
                        cout << "||================================||" << endl;
                        cout << endl;
                        criterio = 3;
                        break;                    
                    }
                    criterio = 4;
                    break;
                    
                case 4:
                    cout << endl;
                    cout << "||================================||" << endl;
                    cout << "||  Escolha a cidade de Destino   ||" << endl;
                    cout << "||================================||" << endl;
                    
                    cout << endl;
                    
                    cout << "Resposta: "; cin >> c2;
                    
                    // Limpar buffer se houver erro
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(10000, '\n');
                    }
                    
                    cout << endl;
                    
                    if (c2 < 0 || c2 >= cidades){
                        cout << endl;
                        cout << "||================================||" << endl;
                        cout << "||  Esta cidade não existe !!!    ||" << endl;
                        cout << "||================================||" << endl;
                        cout << endl;
                        criterio = 4;
                        break;
                    }
                    cout << endl;
                    criterio = 5;
                    break;
                    
                case 5:

                    cout << endl;
                    cout << "||==============||" << endl;
                    cout << "|| Criterios:   ||" << endl;
                    cout << "||==============||" << endl;
                    cout << "|| 0: Distancia ||" << endl;
                    cout << "|| 1: Tempo     ||" << endl;
                    cout << "|| 2: Perigo    ||" << endl;
                    cout << "||==============||" << endl;
                    cout << endl;

                    cout << "Resposta: "; cin >> a;
                    
                    // Limpar buffer se houver erro
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(10000, '\n');
                    }
                    
                    if (a > 2 || a < 0){

                        cout << endl;
                        cout << "||================================||" << endl;
                        cout << "|| Este número não é permitido!!! ||" << endl;
                        cout << "||================================||" << endl;
                        cout << endl;
                        criterio = 5;
                        break;
                    } else{
                        cout << endl;
                        cout << "||================================||" << endl;
                        cout << "|| Este número não é permitido!!! ||" << endl;
                        cout << "||================================||" << endl;
                        cout << endl;
                        criterio = 5;

                    }
                    criterio = a;
                    break;
                    
                    
                    
                case 6:
                    cout << endl;
                    cout << "||=================||" << endl;
                    cout << "|| Quer continuar? ||" << endl;
                    cout << "||=================||" << endl;
                    cout << "||       s/n       ||" << endl;
                    cout << "||=================||" << endl;
                    cout << endl;

                    cout << "Resposta: ";
                    cin  >> sn;
                    cout << endl;

                    if(sn == "n") {
                        criterio = -1;
                    } else if(sn == "s") {
                        criterio = 3;
                    } else {
                        cout << endl;
                        cout << "||==================================||" << endl;
                        cout << "|| Esta resposta não é permitido!!! ||" << endl;
                        cout << "||==================================||" << endl;
                        cout << endl;
                        criterio = 6;
                    }
                    break;
                
                case 7:
                    continuar = false;
                    break;
                
                default:
                    
                    cout<<"|||================================================================================================|||"<< endl;
                    cout<<"|||================================================================================================|||"<< endl;     
                    cout<<"|||                                                                                                |||"<< endl;
                    cout<<"|||                                                                                                |||"<< endl;
                    cout<<"|||   █   █ █████ █   █ █   █    █████  ███   ████ █████    █████ ████   ███  █   █ █████ █        |||"<< endl;
                    cout<<"|||   ██ ██░█░░░░░██  █░█░  █░   █░░░░░█ ░░█ █ ░░░░ ░█░░░    ░█░░░█░░░█ █ ░░█ █░  █░█░░░░░█░       |||"<< endl;
                    cout<<"|||   █░█ █░████░░█░█ █░█░░ █░░  ████░░█████░ ███░░░ █░░░░    █░░░████░░█████░█░░ █░████░░█░░      |||"<< endl;
                    cout<<"|||   █░░░█░█░░░░ █░░██░█░░ █░░  █░░░░ █░░░█░░ ░░█   █░░      █░░ █░░█░ █░░░█░░█░█ ░█░░░░ █░░      |||"<< endl;
                    cout<<"|||   █░░ █░█████░█░░ █░░███ ░░  █░░░░░█░░░█░████░░  █░░      █░░ █░░░█░█░░░█░░ █ ░ █████░█████    |||"<< endl;
                    cout<<"|||    ░░  ░░░░░░░ ░░  ░░ ░░░ ░   ░░    ░░  ░░░░░░ ░  ░░       ░░  ░░  ░ ░░  ░░  ░ ░ ░░░░░ ░░░░░   |||"<< endl;
                    cout<<"|||     ░   ░ ░░░░░ ░   ░  ░░░     ░     ░   ░ ░░░░    ░        ░   ░   ░ ░   ░   ░   ░░░░░ ░░░░░  |||"<< endl;
                    cout<<"|||                                                                                                |||"<< endl;
                    cout<<"|||                                ████ █   █ █   █ ████  ███ █   █                                |||"<< endl;
                    cout<<"|||                               █ ░░░░█░ █ ░ █ █ ░█░░░█  █░░██ ██░                               |||"<< endl;
                    cout<<"|||                                ███░░███ ░ ░ █ ░ ████░░ █░░█░█ █░░                              |||"<< endl;
                    cout<<"|||                                 ░░█ █░░█ ░  █░ ░█░░█░ ░█░░█░░░█░░                              |||"<< endl;
                    cout<<"|||                               ████░░█░░░█   █░░ █░░░█░███░█░░ █░░                              |||"<< endl;
                    cout<<"|||                                ░░░░ ░░░  ░   ░░  ░░  ░ ░░░ ░░  ░░                              |||"<< endl;
                    cout<<"|||                                 ░░░░  ░   ░   ░   ░   ░ ░░░ ░   ░                              |||"<< endl;
                    cout<<"|||                                                                                                |||"<< endl;
                    cout<<"|||                                                                                                |||"<< endl;
                    cout<<"|||                                            #       @                                           |||"<< endl;
                    cout<<"|||                                           @@      @@@                                          |||"<< endl;
                    cout<<"|||                                          @+         @%                                         |||"<< endl;
                    cout<<"|||                                         @@   %      *@+                                        |||"<< endl;
                    cout<<"|||                                        @@-   @@@@    @@.                                       |||"<< endl;
                    cout<<"|||                                       @@@   @@@@@    #@@                                       |||"<< endl;
                    cout<<"|||                                      @@@*  .*     @   @@@                                      |||"<< endl;
                    cout<<"|||                                     @@@@         @#   @@@@                                     |||"<< endl;
                    cout<<"|||                                    @@@@. @   @@@    .- @@@@                                    |||"<< endl;
                    cout<<"|||                                   @@@@@     @@         #@@@@                                   |||"<< endl;
                    cout<<"|||                                  +@@@@%     @@@         @@@@@                                  |||"<< endl;
                    cout<<"|||                                 .@@@@@#   @#@@@@#.=@    @@@@@@                                 |||"<< endl;
                    cout<<"|||                                  *@@@@@@@@@@@@@@@@@@@@@@@@@@@                                  |||"<< endl;
                    cout<<"|||                                   @@@@@@@@@@@@@@@@@@@@@@@@@@                                   |||"<< endl;
                    cout<<"|||                                    @@@@@@@@@@@@@@@@@@@@@@@@                                    |||"<< endl;
                    cout<<"|||                                     @@@@@  @ *@@@* =  @@@@                                     |||"<< endl;
                    cout<<"|||                                      @@@:      @@     @@@                                      |||"<< endl;
                    cout<<"|||                                       @@+      @@     @@.                                      |||"<< endl;
                    cout<<"|||                                        @@@=    @@   @@@-                                       |||"<< endl;
                    cout<<"|||                                         @@@   -@   @@@*                                        |||"<< endl;
                    cout<<"|||                                          @@  #@    @@@                                         |||"<< endl;
                    cout<<"|||                                           @  @-    @@                                          |||"<< endl;
                    cout<<"|||                                               @    @                                           |||"<< endl;
                    cout<<"|||                                              @                                                 |||"<< endl;
                    cout<<"|||                                             @                                                  |||"<< endl;
                    cout<<"|||                                              @@@@                                              |||"<< endl;
                    cout<<"|||                                               @@                                               |||"<< endl;
                    cout<<"|||                                                                                                |||"<< endl;
                    cout<<"|||================================================================================================|||"<< endl;
                    cout<<"|||================================================================================================|||"<< endl;
                    cout<<"|||                                                                                                |||"<< endl;
                    cout<<"|||                                                                                                |||"<< endl;
                    cout<<"|||            ███  ████  █████ ████  █████ █████     ███     █████ █████  ███  █      ███         |||"<< endl;
                    cout<<"|||           █   █ █   █ █     █   █   █   █        █   █      █   █     █     █     █   █        |||"<< endl;
                    cout<<"|||           █████ ████  ████  ████    █   ████     █████      █   ████  █     █     █████        |||"<< endl;
                    cout<<"|||           █   █ █     █     █  █    █   █        █   █      █   █     █     █     █   █        |||"<< endl;
                    cout<<"|||           █   █ █     █████ █   █   █   █████    █   █      █   █████  ███  █████ █   █        |||"<< endl;
                    cout<<"|||                                                                                                |||"<< endl;
                    cout<<"|||                                                                                                |||"<< endl;
                    cout<<"|||              ▓        ▓▓▓▓▓  ▓▓▓   ▓▓▓▓ ▓▓▓▓▓    ▓▓▓▓▓ ▓▓▓▓   ▓▓▓  ▓   ▓ ▓▓▓▓▓ ▓               |||"<< endl;
                    cout<<"|||             ▓▓   ▓    ▓     ▓   ▓ ▓       ▓        ▓   ▓   ▓ ▓   ▓ ▓   ▓ ▓     ▓               |||"<< endl;
                    cout<<"|||              ▓        ▓▓▓▓  ▓▓▓▓▓  ▓▓▓    ▓        ▓   ▓▓▓▓  ▓▓▓▓▓ ▓   ▓ ▓▓▓▓  ▓               |||"<< endl;
                    cout<<"|||              ▓   ▓    ▓     ▓   ▓     ▓   ▓        ▓   ▓  ▓  ▓   ▓  ▓ ▓  ▓     ▓               |||"<< endl;
                    cout<<"|||             ▓▓▓       ▓     ▓   ▓ ▓▓▓▓    ▓        ▓   ▓   ▓ ▓   ▓   ▓   ▓▓▓▓▓ ▓▓▓▓▓           |||"<< endl;
                    cout<<"|||                                                                                                |||"<< endl;
                    cout<<"|||                                                                                                |||"<< endl;
                    cout<<"|||                                                                                                |||"<< endl;
                    cout<<"|||             ▓▓▓        ▓▓▓▓  ▓▓▓  ▓▓▓ ▓▓▓▓                                                     |||"<< endl;
                    cout<<"|||            ▓   ▓ ▓    ▓     ▓   ▓  ▓  ▓   ▓                                                    |||"<< endl;
                    cout<<"|||               ▓        ▓▓▓  ▓▓▓▓▓  ▓  ▓▓▓▓                                                     |||"<< endl;
                    cout<<"|||              ▓   ▓        ▓ ▓   ▓  ▓  ▓  ▓                                                     |||"<< endl;
                    cout<<"|||            ▓▓▓▓▓      ▓▓▓▓  ▓   ▓ ▓▓▓ ▓   ▓                                                    |||"<< endl;
                    cout<<"|||                                                                                                |||"<< endl;
                    cout<<"|||                                                                                                |||"<< endl;                   
                    cout<<"|||================================================================================================|||"<< endl;
                    cout<<"|||================================================================================================|||"<< endl;
                    cout << endl;
                    cout << "Resposta: ";
                    
                    cin >> c;
                    
                    // Limpar buffer se houver erro (digitou letra)
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(10000, '\n');
                    }

                    if (c == 1){
                        criterio = 3; 
                    } else if (c == 2){
                        criterio = 7;
                    }
                    else {
                        cout << endl;
                        cout << "||=========================================||" << endl;
                        cout << "|| Este número/caracter não é permitido!!! ||" << endl;
                        cout << "||=========================================||" << endl;
                        cout << endl;
                    }
                    break;

                }

    // // Testes
    // cout << "=== Menor distancia: Whiterun -> Riften ===" << endl;
    // mapa.exibirCaminho(1, 3, Mapa::DISTANCIA);

    // cout << "\n=== Menor tempo: Solitude -> Riften ===" << endl;
    // mapa.exibirCaminho(0, 3, Mapa::TEMPO);

    // cout << "\n=== Menor perigo: Whiterun -> Markarth ===" << endl;
    // mapa.exibirCaminho(1, 4, Mapa::PERIGO);
    }
    return 0;
}