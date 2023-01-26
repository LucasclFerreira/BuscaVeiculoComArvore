/*−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−---
 ∗ UNIFAL − Universidade Federal de Alfenas .
 ∗ BACHARELADO EM CIENCIA DA COMPUTACAO.
 ∗ Trabalho..: BuscaCar
 ∗ Disciplina: AEDS II
 ∗ Professor.: Paulo Alexandre Bressan
 ∗ Aluno.....: Gustavo Fidelis Camilo e Lucas Costa Lima Ferreira
 * Matrículas: 2021.1.08.043 e 2021.1.08.015
 ∗ Data......: 02/12/2022
 * Descrição.: Programa em C++ que permite realizar buscas, inserções e remoções
 *             utilizando estruturas de dados como lista encadeada, pilha e fila.
 ∗−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−---*/


#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include "funcoes.h"
using namespace std;

int main() {
  BD *dataBase = inicia_lista();
  carrega_arq(dataBase);
  menu(dataBase);
  encerra_lista(dataBase);
  return 0;
}