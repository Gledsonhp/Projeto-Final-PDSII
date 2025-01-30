#ifndef OTHELLO_HPP
#define OTHELLO_HPP

#include <memory>
#include <vector>
#include <iostream>
#include "Jogador.hpp"

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

#endif // OTHELLO_HPP
