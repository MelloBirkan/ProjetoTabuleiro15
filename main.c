#include "jogoDaMinhaInfanciaFunc.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
 * Nome: Marcello Gonzatto Birkan TIA:42020034
 * ----------------------------------------------------README-----------------------------------------------------------
 * A função searchNChange está na versão de windows no código, entretanto possua
 * a versão de UNIX comentada logo a baixo O Código pode ser usado com qualuer
 * arquvio que siga o padrão base de: ladrilho.txt cedido pelo querido prof
 * Joaquim O Programa não resolve de maneira automatica o jogo, apenas segue os
 * passos do usuario e apresenta os resultados Existe a variavel MATRIX
 * declarada de maneira GLOBAL no Header file.
 */

FILE *f;
int matrix;

// Função abre o arquivo e começa a leitura
void readMatrix() {

  f = fopen("ladrilho.txt", "r");
  if (f == 0) {
    printf("Erro na leitura do ladrilho");
    exit(1);
  }
  fscanf(f, "%d", &matrix);
}

// Função printa a matrix
void printMap(int (*mapa)[matrix]) {

  for (int i = 0; i < matrix; i++) {
    for (int j = 0; j < matrix; ++j) {
      if (mapa[i][j] > 9)
        printf("%d  ", mapa[i][j]);
      else
        printf("%d   ", mapa[i][j]);
      if (j == 3)
        printf("\n");
    }
  }
}

// Função auxiliar para fazer as trocas no tabuleiro
void change(int (*mapa)[matrix], int a, int b, int c, int d) {

  int temp = 0;
  temp = mapa[a][b];
  mapa[a][b] = mapa[c][d];
  mapa[c][d] = temp;
}

// Função versão Windows
// Função principal do programa, procura a cordenada a ser trocada e aplica a
// função troca
void searchNChange(int (*mapa)[matrix]) {

  char direction;
  int times, nToChange, flag = 0;

  fscanf(f, "%d", &times);
  for (int z = 0; z < times; ++z) {

    if (z == 0)
      printMap(mapa);
    sleep(3);
    flag = 0;
    fscanf(f, "%d %c", &nToChange, &direction);

    for (int i = 0; i < matrix; ++i) {
      if (flag == 1)
        break;

      for (int j = 0; j < matrix; ++j) {
        if (flag == 1)
          break;

        if (mapa[i][j] == nToChange) {
          system("clear");
          switch (direction) {
          case 'd':
            change(mapa, i, j, i, j + 1);
            printf("[%d] vai para a direita:\n", mapa[i][j + 1]);
            break;

          case 'b':
            change(mapa, i, j, i + 1, j);
            printf("[%d] vai para baixo:\n", mapa[i + 1][j]);
            break;

          case 'e':
            change(mapa, i, j, i, j - 1);
            printf("[%d] vai para a esquerda:\n", mapa[i][j - 1]);
            break;

          case 'c':
            change(mapa, i, j, i - 1, j);
            printf("[%d] vai para cima:\n", mapa[i - 1][j]);
            break;
          }
          printMap(mapa);
          if (z == times - 1)
            sleep(5);
          flag++;
        }
      }
    }
  }
}

int main() {

  // Aloca a matrix de maneira variavel, dependendo do tamanho determinado pelo
  // arquivo
  readMatrix();
  int map[matrix][matrix];
  for (int i = 0; i < matrix; i++) {
    for (int j = 0; j < matrix; ++j) {
      fscanf(f, "%d", &map[i][j]);
    }
  }
  searchNChange(map);
  fclose(f);
}
