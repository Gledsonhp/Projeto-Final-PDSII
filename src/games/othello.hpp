#ifndef OTHELLO_HPP
#define OTHELLO_HPP

#include <vector>
#include <memory>
#include "Jogador.hpp"

class Othello {
private:
    std::vector<std::vector<char>> tabuleiro;
    std::shared_ptr<Jogador> jogador1;
    std::shared_ptr<Jogador> jogador2;
    bool turnoJogador1;

    void inicializarTabuleiro();
    bool jogadaValida(int linha, int coluna);
    bool verificarCaptura(int linha, int coluna, int dL, int dC, char jogador);
    void capturarPecas(int linha, int coluna, char jogador);
    void transformarPecas(int linha, int coluna, int dL, int dC, char jogador);
    bool verificarFimDeJogo();
    int contarPecas(char jogador);

public:
    Othello(std::shared_ptr<Jogador> j1, std::shared_ptr<Jogador> j2);
    void exibirJogadorAtual();
    void exibirTabuleiro();
    void exibirVencedor();
    void jogar();
};

#endif // OTHELLO_HPP
