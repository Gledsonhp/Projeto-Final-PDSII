#include <vector>
#include <iostream>
#include <memory>

class Othello {
public:
    Othello(std::shared_ptr<Jogador> j1, std::shared_ptr<Jogador> j2);
    void jogar();
    void exibirTabuleiro();
    void exibirJogadorAtual();
    void exibirVencedor();
    
private:
    void inicializarTabuleiro();
    bool jogadaValida(int linha, int coluna);
    bool verificarCaptura(int linha, int coluna, int dL, int dC, char jogador);
    void capturarPecas(int linha, int coluna, char jogador);
    void transformarPecas(int linha, int coluna, int dL, int dC, char jogador);
    bool verificarFimDeJogo();
    int contarPecas(char jogador);
    
    std::vector<std::vector<char>> tabuleiro;
    std::shared_ptr<Jogador> jogador1, jogador2;
    bool turnoJogador1;
    
    std::vector<std::pair<int, int>> pecasCapturadasJogador1;
    std::vector<std::pair<int, int>> pecasCapturadasJogador2;
};

void Othello::capturarPecas(int linha, int coluna, char jogador) {
    pecasCapturadasJogador1.clear();
    pecasCapturadasJogador2.clear();
    
    for (int dL = -1; dL <= 1; ++dL) {
        for (int dC = -1; dC <= 1; ++dC) {
            if (dL == 0 && dC == 0) continue;
            if (verificarCaptura(linha, coluna, dL, dC, jogador)) {
                transformarPecas(linha, coluna, dL, dC, jogador);
                
                int i = linha + dL, j = coluna + dC;
                while (tabuleiro[i][j] != jogador) {
                    if (jogador == 'X') {
                        pecasCapturadasJogador1.push_back({i, j});
                    } else {
                        pecasCapturadasJogador2.push_back({i, j});
                    }
                    i += dL;
                    j += dC;
                }
            }
        }
    }
}

void Othello::exibirTabuleiro() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            std::cout << (tabuleiro[i][j] == ' ' ? '.' : tabuleiro[i][j]) << " ";
        }
        std::cout << std::endl;
    }
}

void Othello::exibirJogadorAtual() {
    std::cout << "É a vez de " << (turnoJogador1 ? jogador1->getApelido() : jogador2->getApelido()) << std::endl;
    if (turnoJogador1) {
        std::cout << "Peças capturadas por " << jogador1->getApelido() << ": ";
        for (auto& p : pecasCapturadasJogador1) {
            std::cout << "(" << p.first << ", " << p.second << ") ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "Peças capturadas por " << jogador2->getApelido() << ": ";
        for (auto& p : pecasCapturadasJogador2) {
            std::cout << "(" << p.first << ", " << p.second << ") ";
        }
        std::cout << std::endl;
    }
}

void Othello::jogar() {
    std::cout << "Iniciando o jogo Othello...\n";
    while (!verificarFimDeJogo()) {
        exibirTabuleiro();
        exibirJogadorAtual();

        int linha, coluna;
        std::cout << "Digite a linha e a coluna para a jogada: ";
        std::cin >> linha >> coluna;

        if (jogadaValida(linha, coluna)) {
            capturarPecas(linha, coluna, turnoJogador1 ? 'X' : 'O');
            tabuleiro[linha][coluna] = turnoJogador1 ? 'X' : 'O';
            turnoJogador1 = !turnoJogador1;
        } else {
            std::cout << "Jogada inválida. Tente novamente.\n";
        }
    }

    std::cout << "O jogo terminou!" << std::endl;
    exibirTabuleiro();
    exibirVencedor();
}
