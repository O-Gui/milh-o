#include <stdio.h>
#include <stdlib.h>
#include "jogo.h"

int main(void) {
    Pergunta *perguntas;
    int quantidadePerguntas;

    printf("SHOW DO MILHAO\n");
    printf("Para jogar, aperte a tecla 'y'. Para fechar o jogo, aperte a tecla 'n'.\n");

    char escolha;
    scanf(" %c", &escolha);

    if (escolha != 'y') {
        printf("Jogo encerrado.\n");
        return 0;
    }

    if (lerPerguntas("arquivoPergunta.txt", &perguntas, &quantidadePerguntas) != 0) {
        printf("Erro ao carregar perguntas.\n");
        return 1;
    }

    if (lerRespostasCertas("respostasCertas.txt", &perguntas, &quantidadePerguntas) != 0) {
        printf("Erro ao carregar respostas certas.\n");
        liberarMemoriaPerguntas(perguntas, quantidadePerguntas);
        return 1;
    }

    printf("Começando o jogo...\n");

    int idPerguntaAtual = 0;
    while (idPerguntaAtual < quantidadePerguntas) {
        Pergunta perguntaAtual = perguntas[idPerguntaAtual];

        exibirPergunta(perguntaAtual);

        char respostaJogador;
        printf("\nDigite sua resposta (A, B, C, D ou E): ");
        scanf(" %c", &respostaJogador);

        int respostaIndex = respostaJogador - 'A';
        if (respostaIndex < 0 || respostaIndex >= 5) {
            printf("Opção inválida. Tente novamente.\n");
            continue;
        }

        if (respostaIndex == perguntaAtual.respostaCertaIndex) {
            exibirRespostaCorreta(perguntaAtual);
            printf("\nResposta correta! Avançando para a próxima pergunta.\n");
            idPerguntaAtual++;
        } else {
            printf("\nGame Over! Resposta incorreta.\n");
            break;
        }
    }

    liberarMemoriaPerguntas(perguntas, quantidadePerguntas);

    printf("\nFim do jogo.\n");

    return 0;
}
