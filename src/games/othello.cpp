#include "othello.hpp"
#include <iostream>

Othello::Othello(std::shared_ptr<Jogador> j1, std::shared_ptr<Jogador> j2)
    : jogador1(j1), jogador2(j2), turnoJogador1(true) {
    inicializarTabuleiro();
}

void Othello::inicializarTabuleiro() {
    tabuleiro = std::vector<std::vector<char>>(8, std::vector<char>(8, ' '));
    tabuleiro[3][3] = tabuleiro[4][4] = 'X';
    tabuleiro[3][4] = tabuleiro[4][3] = 'O';
}

bool Othello::jogadaValida(int linha, int coluna) {
    if (linha < 0 || linha >= 8 || coluna < 0 || coluna >= 8 || tabuleiro[linha][coluna] != ' ') {
        return false;
    }
    char jogador = turnoJogador1 ? 'X' : 'O';
    for (int dL = -1; dL <= 1; ++dL) {
        for (int dC = -1; dC <= 1; ++dC) {
            if (dL == 0 && dC == 0) continue;
            if (verificarCaptura(linha, coluna, dL, dC, jogador)) {
                return true;
            }
        }
    }
    return false;
}

bool Othello::verificarCaptura(int linha, int coluna, int dL, int dC, char jogador) {
    int i = linha + dL, j = coluna + dC;
    bool encontrouAdversario = false;
    char adversario = (jogador == 'X') ? 'O' : 'X';

    while (i >= 0 && i < 8 && j >= 0 && j < 8 && tabuleiro[i][j] == adversario) {
        encontrouAdversario = true;
        i += dL;
        j += dC;
    }

    return encontrouAdversario && i >= 0 && i < 8 && j >= 0 && j < 8 && tabuleiro[i][j] == jogador;
}

void Othello::capturarPecas(int linha, int coluna, char jogador) {
    for (int dL = -1; dL <= 1; ++dL) {
        for (int dC = -1; dC <= 1; ++dC) {
            if (dL == 0 && dC == 0) continue;
            if (verificarCaptura(linha, coluna, dL, dC, jogador)) {
                transformarPecas(linha, coluna, dL, dC, jogador);
            }
        }
    }
}

void Othello::transformarPecas(int linha, int coluna, int dL, int dC, char jogador) {
    int i = linha + dL, j = coluna + dC;

    // Continuar na direção até encontrar a peça do jogador
    while (tabuleiro[i][j] != jogador) {
        tabuleiro[i][j] = jogador;
        i += dL;
        j += dC;
    }
}

bool Othello::verificarFimDeJogo() {
    bool jogadasValidas = false;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (jogadaValida(i, j)) {
                jogadasValidas = true;
                break;
            }
        }
        if (jogadasValidas) break;
    }
    return !jogadasValidas;
}

void Othello::exibirJogadorAtual() {
    std::cout << "É a vez de " << (turnoJogador1 ? jogador1->getApelido() : jogador2->getApelido()) << std::endl;
}

void Othello::exibirTabuleiro() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            std::cout << (tabuleiro[i][j] == ' ' ? '.' : tabuleiro[i][j]) << " ";
        }
        std::cout << std::endl;
    }
}

int Othello::contarPecas(char jogador) {
    int count = 0;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (tabuleiro[i][j] == jogador) {
                count++;
            }
        }
    }
    return count;
}

void Othello::exibirVencedor() {
    int pecasX = contarPecas('X');
    int pecasO = contarPecas('O');
    if (pecasX > pecasO) {
        std::cout << "O vencedor é " << jogador1->getApelido() << " com " << pecasX << " peças!" << std::endl;
    } else if (pecasO > pecasX) {
        std::cout << "O vencedor é " << jogador2->getApelido() << " com " << pecasO << " peças!" << std::endl;
    } else {
        std::cout << "Empate! Ambos os jogadores têm o mesmo número de peças." << std::endl;
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
