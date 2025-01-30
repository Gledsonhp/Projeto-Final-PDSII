#ifndef OTHELLO_HPP
#define OTHELLO_HPP

#include <vector>
#include <memory>
#include "jogador.hpp"

class Othello {
public:
    Othello(std::shared_ptr<Jogador> j1, std::shared_ptr<Jogador> j2);

    void jogar();

private:
    void inicializarTabuleiro();
    bool jogadaValida(int linha, int coluna);
    bool verificarCaptura(int linha, int coluna, int dL, int dC, char jogador);
    void capturarPecas(int linha, int coluna, char jogador);
    bool verificarFimDeJogo();
    void exibirJogadorAtual();
    void exibirTabuleiro();
    void transformarPecas(int linha, int coluna, char jogador);
    int contarPecas(char jogador);
    void exibirVencedor();

    std::shared_ptr<Jogador> jogador1;
    std::shared_ptr<Jogador> jogador2;
    bool turnoJogador1;
    std::vector<std::vector<char>> tabuleiro;
};

#endif // OTHELLO_HPP
