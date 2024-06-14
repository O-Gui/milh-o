#ifndef JOGO_H
#define JOGO_H

#define MAXIMO_DE_LINHAS 256

typedef struct {
    char perguntas[MAXIMO_DE_LINHAS];
    char respostas[5][MAXIMO_DE_LINHAS];
    int respostaCertaIndex;
} Pergunta;

int lerPerguntas(const char *arquivoPergunta, Pergunta **items, int *qtdPerguntas);
int lerRespostasCertas(const char *arquivoRespostasCertas, Pergunta **items, int *qtdPerguntas);
void exibirPergunta(Pergunta pergunta);
void exibirRespostaCorreta(Pergunta pergunta);
void liberarMemoriaPerguntas(Pergunta *items, int qtdPerguntas);

#endif // JOGO_H
