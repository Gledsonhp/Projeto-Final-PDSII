#ifndef CAMPO_MINADO_HPP
#define CAMPO_MINADO_HPP

#include "tabuleiro.hpp"
#include "jogador.hpp"
#include <vector>

class CampoMinado : public Tabuleiro {
private:
    int minas; // N�mero de minas no tabuleiro
    std::vector<std::vector<char>> tabuleiroVisivel;

public:
    // Construtor
    CampoMinado(int tamanho, int minas);

    // Fun��es do jogo
    void gerarMinas();
    void calcularNumeros();
    void revelar(int x, int y);
    bool verificarVitoria() const;
    bool perdeu(int x, int y) const;
    void exibirVisivel() const;
};

#endif

