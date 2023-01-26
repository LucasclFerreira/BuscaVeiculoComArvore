#include <string>
#ifndef FUNCOES_H
#define FUNCOES_H

// Registro com as informações do veículo
typedef struct Tveiculo {
  std::string modelo, marca, tipo, combustivel, cambio, direcao, cor, placa;
  int ano, km, portas;
  float potencia_do_motor, valor;
} Tveiculo;

// Registro que aponta para um veiculo e para o proximo nó.
typedef struct no_ {
  Tveiculo *veiculo;
  struct no_ *prox;
} no;

// Registro inical que possui o tamanho e ponteiro para o primeiro e o último nó.
typedef struct bd_ {
  int tam;
  no *cabecalho; // aponta para primeiro no
  no *cauda;     // aponta para ultimo no
} BD;

BD *inicia_lista();
BD *encerra_lista(BD *bd);
void imprime(BD *bd);
no *busca(BD *bd, std::string placa);
no *remove_escolha(BD *bd, std::string placa);
no *remove_fim(BD *bd);
void carrega_arq(BD *bd);
void insere_inicio(BD *bd, Tveiculo *veiculo);
void insere_fim(BD *bd, Tveiculo *veiculo);
void ordenacao_placa(BD *bd);
void transfere(BD *bd);
void criaPilha(BD *bd);
void criaFila(BD *bd);
void menu(BD *bd);

#endif