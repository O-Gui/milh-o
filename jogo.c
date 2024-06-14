#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jogo.h"

void trim(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len-1] == '\n') {
        str[len-1] = '\0';
    }
}

int lerPerguntas(const char *arquivoPergunta, Pergunta **items, int *qtdPerguntas) {
    FILE *arquivo = fopen(arquivoPergunta, "r");

    if (!arquivo) {
        printf("ERRO ao abrir o arquivo de perguntas.\n");
        return -1;
    }

    char linha[MAXIMO_DE_LINHAS];
    int index = 0;
    *qtdPerguntas = 0;

    // Contagem de linhas para determinar a quantidade de perguntas
    while (fgets(linha, sizeof(linha), arquivo)) {
        trim(linha);
        if (strcmp(linha, "*") == 0) {
            continue; // Ignorar linha de separação
        }
        (*qtdPerguntas)++;
    }

    // Voltar ao início do arquivo
    rewind(arquivo);

    // Alocar memória para armazenar as perguntas
    *items = (Pergunta *)malloc(*qtdPerguntas * sizeof(Pergunta));
    if (*items == NULL) {
        printf("ERRO ao alocar memória para as perguntas.\n");
        fclose(arquivo);
        return -1;
    }

    // Ler as perguntas do arquivo
    index = -1; // Iniciar com -1 para ignorar a linha de separação inicial
    while (fgets(linha, sizeof(linha), arquivo)) {
        trim(linha);
        if (strcmp(linha, "*") == 0) {
            index++;
            continue; // Ignorar linha de separação
        }
        if (index >= 0) {
            if (strlen(linha) == 1 && (linha[0] == 'A' || linha[0] == 'B' || linha[0] == 'C' || linha[0] == 'D' || linha[0] == 'E')) {
                strcpy((*items)[index].respostas[linha[0] - 'A'], linha + 3);
            } else {
                strcpy((*items)[index].perguntas, linha);
            }
        }
    }

    fclose(arquivo);

    return 0;
}

int lerRespostasCertas(const char *arquivoRespostasCertas, Pergunta **items, int *qtdPerguntas) {
    FILE *arquivo = fopen(arquivoRespostasCertas, "r");
    if (arquivo == NULL) {
        printf("ERRO ao abrir o arquivo de respostas certas.\n");
        return -1;
    }

    char linha[MAXIMO_DE_LINHAS];
    int id, perguntaIndex;
    char respostaCorreta;

    while (fgets(linha, sizeof(linha), arquivo)) {
        if (sscanf(linha, "%d", &id) != 1) {
            continue;
        }

        for (perguntaIndex = 0; perguntaIndex < *qtdPerguntas; ++perguntaIndex) {
            if (id == perguntaIndex + 1) {
                break;
            }
        }

        if (fgets(linha, sizeof(linha), arquivo) != NULL) {
            trim(linha);
            sscanf(linha, "%c", &respostaCorreta);
            (*items)[perguntaIndex].respostaCertaIndex = respostaCorreta - 'A';
        }
    }

    fclose(arquivo);
    return 0;
}

void exibirPergunta(Pergunta pergunta) {
    printf("\n%s\n", pergunta.perguntas);
    for (int i = 0; i < 5; ++i) {
        printf("%c) %s\n", 'A' + i, pergunta.respostas[i]);
    }
}

void exibirRespostaCorreta(Pergunta pergunta) {
    printf("\nResposta correta:\n%s\n%c) %s\n", pergunta.perguntas, 'A' + pergunta.respostaCertaIndex, pergunta.respostas[pergunta.respostaCertaIndex]);
}

void liberarMemoriaPerguntas(Pergunta *items, int qtdPerguntas) {
    if (items) {
        free(items);
    }
}
