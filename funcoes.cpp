#include <fstream>
#include <iostream>
#include "funcoes.h"
using namespace std;

/**
 * Aloca espaço para o banco de dados receber os nós
 * @return banco de dados vazio alocado
 */
BD *inicia_lista() {
  BD *tmp = new (BD);
  tmp->tam = 0;
  tmp->cabecalho = NULL;
  return tmp;
}

/**
 * Desaloca o espaço do banco de dados
 * @param bd é um ponteiro para o banco de dados
 * @return NULL atualiza o ponteiro do banco de dados
 */
BD *encerra_lista(BD *bd) {
  no *ant = bd->cabecalho;
  no *pont = bd->cabecalho;
  while (ant != NULL) {
    pont = ant->prox;
    delete (ant);
    ant = pont;
  }
  delete (bd);
  return NULL;
}

/**
 * Imprime o relatório dos veiculos
 * @param bd ponteiro para o bando de dados
 */
void imprime(BD *bd) {
  no *ptr = bd->cabecalho;
  cout << "----> RELATÓRIO DOS VEICULOS <----" << endl;
  while (ptr) {
    cout << ptr->veiculo->modelo << " ";
    cout << ptr->veiculo->marca << " ";
    cout << ptr->veiculo->tipo << " ";
    cout << ptr->veiculo->ano << " ";
    cout << ptr->veiculo->km << " ";
    cout << ptr->veiculo->potencia_do_motor << " ";
    cout << ptr->veiculo->combustivel << " ";
    cout << ptr->veiculo->cambio << " ";
    cout << ptr->veiculo->direcao << " ";
    cout << ptr->veiculo->cor << " ";
    cout << ptr->veiculo->portas << " ";
    cout << ptr->veiculo->placa << " ";
    cout << ptr->veiculo->valor << endl;
    ptr = ptr->prox;
  }
}

/**
 * Busca pela placa dentro da lista encadeada.
 * @param placa a ser buscada.
 * @param bd ponteiro para o banco de dados.
 * @return o nó referente a placa se o elemento foi encontrado e NULL caso
 * contrário.
 */
no *busca(BD *bd, string placa) {
  no *ptr = bd->cabecalho;

  while (ptr != NULL && ptr->veiculo->placa != placa) {
    ptr = ptr->prox;
  }
  return ptr;
}

/**
 * Remove em qualquer posição o veículo encontrado através da placa.
 * @param placa do veículo a ser removido.
 * @param bd ponteiro para o banco de dados.
 * @return verdareiro se o elemento foi encontrado.
 */
no *remove_escolha(BD *bd, string placa) {
  if (bd->tam == 0)
    return NULL;
  no *p = bd->cabecalho;
  no *ant = p;
  no *aux = busca(bd, placa);
  if (aux) {
    while (p->veiculo->placa != aux->veiculo->placa) {
      ant = p;
      p = p->prox;
    }
    if (p->veiculo->placa == aux->veiculo->placa) {
      if (ant == p) {
        bd->cabecalho = p->prox;
      }
      ant->prox = p->prox;
      p->prox = NULL;
    }
    bd->tam--;
    return p;
  }
  return NULL;
}

/**
 * Remove o primeiro elemento da lista se ele existir.
 * @return NULL caso a lista seja vazia e o nó removido caso contrário.
 */
no *remove_inicio(BD *bd) {
  no *p;
  if (bd->tam == 0)
    return NULL;
  p = bd->cabecalho;
  bd->cabecalho = p->prox;
  p->prox = NULL;
  bd->tam--;
  return p;
}

/**
 * Remove o último elemento da lista se ele existir.
 * @return NULL caso a lista seja vazia e o nó removido caso contrário.
 */
no *remove_fim(BD *bd) {
  no *p, *ant;
  if (bd->tam == 0) {
    return NULL;
  }
  p = bd->cabecalho;
  while (p->prox != NULL) {
    ant = p;
    p = p->prox;
  }
  if (p == bd->cabecalho) {
    bd->cabecalho = NULL;
  } else {
    ant->prox = NULL;
  }
  bd->tam--;
  return p;
}

/**
 * Carrega os dados do arquivo na lista encadeada.
 * @param bd ponteiro para o banco de dados.
 */
void carrega_arq(BD *bd) {
  Tveiculo *veiculoTemp;
  ifstream arq("BD_veiculos_2.txt");
  if (arq.is_open()) {
    while (!arq.eof()) {
      veiculoTemp = new Tveiculo;
      arq >> veiculoTemp->modelo;
      arq >> veiculoTemp->marca;
      arq >> veiculoTemp->tipo;
      arq >> veiculoTemp->ano;
      arq >> veiculoTemp->km;
      arq >> veiculoTemp->potencia_do_motor;
      arq >> veiculoTemp->combustivel;
      arq >> veiculoTemp->cambio;
      arq >> veiculoTemp->direcao;
      arq >> veiculoTemp->cor;
      arq >> veiculoTemp->portas;
      arq >> veiculoTemp->placa;
      arq >> veiculoTemp->valor;
      no *novo_no = new no;
      novo_no->veiculo = veiculoTemp;
      novo_no->prox = NULL;
      if (bd->tam == 0) {
        bd->cabecalho = novo_no;
        bd->cauda = novo_no;
        bd->tam++;
      } else {
        bd->cauda->prox = novo_no;
        bd->cauda = novo_no;
        bd->tam++;
      }
    }
    arq.close();
  } else {
    cout << "Não foi possível abrir o arquivo." << endl;
  }
  bd->tam--;
}

/**
 * Insere o elemento no início da lista encadeada.
 * @param bd ponteiro para o banco de dados.
 * @param veiculo ponteiro para o veículo a ser inserido.
 */
void insere_inicio(BD *bd, Tveiculo *veiculo) {
  no *p;
  p = new (no);
  p->veiculo = veiculo;
  p->prox = bd->cabecalho;
  bd->cabecalho = p;
  bd->tam++;
}

/**
 * Insere o elemento no fim da lista encadeada.
 * @param bd ponteiro para o banco de dados.
 * @param veiculo ponteiro para o veículo a ser inserido.
 */
void insere_fim(BD *bd, Tveiculo *veiculo) {
  if (bd->tam == 0) {
    insere_inicio(bd, veiculo);
    return;
  } else {
    no *p = bd->cabecalho;
    while (p->prox != NULL) {
      p = p->prox;
    }
    p->prox = new (no);
    p->prox->veiculo = veiculo;
    p->prox->prox = NULL;
    bd->tam++;
  }
}

/**
 * Ordena as placas em ordem crescente e imprime elas na tela.
 * @param bd ponteiro para o banco de dados.
 */
void ordenacao_placa(BD *bd) {
  BD *lista_ord = inicia_lista();
  no *temp = bd->cabecalho;
  no *aux = new no;
  aux->veiculo = temp->veiculo;
  aux->prox = NULL;
  lista_ord->cabecalho = aux;
  lista_ord->tam = 1;

  for (int i = 0; i < bd->tam; i++) {
    temp = temp->prox;          // atravessa o banco de dados original
    aux = lista_ord->cabecalho; // reinicia o aux para a próxima iteração
    for (int j = 0; j < lista_ord->tam; j++) {
      no *novo_no = new no;
      if (temp->veiculo->placa < aux->veiculo->placa) {
        if (j == 0) {
          novo_no->veiculo = temp->veiculo;
          lista_ord->cabecalho = novo_no;
          novo_no->prox = aux;
          break;
        }
        novo_no->prox = aux->prox;
        novo_no->veiculo = aux->veiculo;
        aux->veiculo = temp->veiculo;
        aux->prox = novo_no;
        break;
      } else if (!aux->prox) {
        novo_no->prox = NULL;
        novo_no->veiculo = temp->veiculo;
        aux->prox = novo_no;
        break;
      }
      aux = aux->prox;
    }
    lista_ord->tam++;
  }
  imprime(lista_ord);
  encerra_lista(lista_ord);
}

/**
 * Escreve os nós da lista encadeada no arquivo de texto (persistência de
 * dados).
 * @param bd ponteiro para o banco de dados.
 */
void transfere(BD *bd) {
  no *ptr = bd->cabecalho;
  ofstream arq;
  arq.open("BD_veiculos_2.txt");
  while (ptr) {
    arq << ptr->veiculo->modelo << " ";
    arq << ptr->veiculo->marca << " ";
    arq << ptr->veiculo->tipo << " ";
    arq << ptr->veiculo->ano << " ";
    arq << ptr->veiculo->km << " ";
    arq << ptr->veiculo->potencia_do_motor << " ";
    arq << ptr->veiculo->combustivel << " ";
    arq << ptr->veiculo->cambio << " ";
    arq << ptr->veiculo->direcao << " ";
    arq << ptr->veiculo->cor << " ";
    arq << ptr->veiculo->portas << " ";
    arq << ptr->veiculo->placa << " ";
    arq << ptr->veiculo->valor;
    if(ptr->prox) {
        arq << endl;
    }
    ptr = ptr->prox;
  }
  arq.close();
}

/**
 * Atravessa a lista encadeada inserindo o veículo na PILHA quando a direção for
 * hidráulica e removendo da pilha quando houver algum de direção elétrica.
 * @param bd ponteiro para o banco de dados.
 */
void criaPilha(BD *bd) {
  BD *bdPilha = inicia_lista();
  no *atravessaLista = bd->cabecalho;

  while (atravessaLista) {
    if (atravessaLista->veiculo->direcao == "Hidráulica") {
      insere_fim(bdPilha, atravessaLista->veiculo);
    } else if (atravessaLista->veiculo->direcao == "Elétrica") {
      remove_fim(bdPilha);
    }
    atravessaLista = atravessaLista->prox;
  }
  imprime(bdPilha);
  encerra_lista(bdPilha);
}

/**
 * Atravessa a lista encadeada inserindo o veículo na FILA quando o câmbio for
 * automático e removendo da fila quando houver algum de câmbio manual.
 * @param bd ponteiro para o banco de dados.
 */
void criaFila(BD *bd) {
  BD *fila = inicia_lista();
  no *aux = bd->cabecalho;

  while (aux) {
    if (aux->veiculo->cambio == "Automático") {
      insere_fim(fila, aux->veiculo);
    } else if (aux->veiculo->cambio == "Manual") {
      remove_inicio(fila);
    }
    aux = aux->prox;
  }
  imprime(fila);
  encerra_lista(fila);
}

/**
 * Menu que exibe as opções para o usuário e executa funções baseado na escolha.
 * @param bd ponteiro para o banco de dados.
 */
void menu(BD *bd) {
  int escolha = 0;
  bool sair = false;

  do {
    cout << "\n|-------------------------------------------------|" << endl;
    cout << "|1) Inserir carro                                 |" << endl;
    cout << "|2) Buscar carro                                  |" << endl;
    cout << "|3) Listar carros                                 |" << endl;
    cout << "|4) Listar ordenado                               |" << endl;
    cout << "|5) Pilha com carros de --> direção hidráulica <--|" << endl;
    cout << "|6) Fila com carros de  --> câmbio automático  <--|" << endl;
    cout << "|7) Sair                                          |" << endl;
    cout << "|-------------------------------------------------|" << endl;
    cout << "Digite o número de uma das opções: ";
    while (!(cin >> escolha)) {
      cout << "Erro! Digite novamente o número de uma das opções: ";
      // limpa o input anterior
      cin.clear();
      // ignora os últimos 123 caracteres que estavam no input até o \n
      cin.ignore(123, '\n');
    }

    switch (escolha) {
    case 1: {
      Tveiculo *novoVeiculo = new Tveiculo;
      cout << "\n(Ao invés de espaço entre as palavras use o caractére: _)";
      cout << "\nInsira MODELO: ";
      cin >> novoVeiculo->modelo;
      cout << "\nInsira MARCA: ";
      cin >> novoVeiculo->marca;
      cout << "\nInsira TIPO: ";
      cin >> novoVeiculo->tipo;
      cout << "\nInsira ANO: ";
      while (!(cin >> novoVeiculo->ano)) {
        cout << "Digite novamente o Ano: ";
        cin.clear();
        cin.ignore(123, '\n');
      }
      cout << "\nInsira KM: ";
      while (!(cin >> novoVeiculo->km)) {
        cout << "Digite novamente o Km: ";
        cin.clear();
        cin.ignore(123, '\n');
      }
      cout << "\nInsira POTENCIA: ";
      while (!(cin >> novoVeiculo->potencia_do_motor)) {
        cout << "Digite novamente a Potência do Motor: ";
        cin.clear();
        cin.ignore(123, '\n');
      }
      cout << "\nInsira COMBUSTIVEL: ";
      cin >> novoVeiculo->combustivel;
      cout << "\nInsira CAMBIO: ";
      cin >> novoVeiculo->cambio;
      cout << "\nInsira DIRECAO: ";
      cin >> novoVeiculo->direcao;
      cout << "\nInsira COR: ";
      cin >> novoVeiculo->cor;
      cout << "\nInsira PORTAS: ";
      while (!(cin >> novoVeiculo->portas)) {
        cout << "Digite novamente o número de Portas: ";
        cin.clear();
        cin.ignore(123, '\n');
      }
      cout << "\nInsira PLACA: ";
      cin >> novoVeiculo->placa;
      cout << "\nInsira VALOR: ";
      while (!(cin >> novoVeiculo->valor)) {
        cout << "Digite novamente o Valor: ";
        cin.clear();
        cin.ignore(123, '\n');
      }
      cout << "\nInserindo novo veiculo no fim da lista..." << endl;
      insere_fim(bd, novoVeiculo);
      cout << "Sucesso ao inserir!" << endl;
      break;
    }
    case 2: {
      cout << "\nBuscando por placa no bd: " << endl;
      string placaABuscar = "";
      cout << "Digite a placa do carro que deseja buscar (deve estar em "
              "maiúsculo): ";
      cin >> placaABuscar;
      no *carroBuscado = busca(bd, placaABuscar);
      if (carroBuscado) {
        cout << "O carro buscado foi: " << endl;
        cout << "--> " << carroBuscado->veiculo->modelo << " ";
        cout << carroBuscado->veiculo->marca << " ";
        cout << carroBuscado->veiculo->tipo << " ";
        cout << carroBuscado->veiculo->ano << " ";
        cout << carroBuscado->veiculo->km << " ";
        cout << carroBuscado->veiculo->potencia_do_motor << " ";
        cout << carroBuscado->veiculo->combustivel << " ";
        cout << carroBuscado->veiculo->cambio << " ";
        cout << carroBuscado->veiculo->direcao << " ";
        cout << carroBuscado->veiculo->cor << " ";
        cout << carroBuscado->veiculo->portas << " ";
        cout << carroBuscado->veiculo->placa << " ";
        cout << carroBuscado->veiculo->valor << endl;
        string acao;
        do {
          cout << "Deseja remove-lo? (S/N): " << endl;
          cin >> acao;
        } while ((acao != "s" && acao != "S") && (acao != "n" && acao != "N"));
        if (acao == "S" || acao == "s") {
          remove_escolha(bd, carroBuscado->veiculo->placa);
          cout << "Carro removido com sucesso!" << endl;
        } else {
          cout << "Carro não removido. Você será direcionado de volta ao menu!"
               << endl;
        }
      } else {
        cout << "Carro não encontrado no banco de dados." << endl;
      }
      break;
    }
    case 3:
      imprime(bd);
      break;
    case 4: {
      ordenacao_placa(bd);
      break;
    }
    case 5:
      cout << "\nCriando Pilha apenas com carros de direção hidráulica..."
           << endl;
      criaPilha(bd);
      break;
    case 6:
      cout << "\nCriando Fila apenas com carros de câmbio automático..."
           << endl;
      criaFila(bd);
      break;
    case 7:
      transfere(bd);
      //cout << "cabecalho atual: " << bd->cabecalho->veiculo->modelo << endl;
      //cout << "cauda atual: " << bd->cauda->veiculo->modelo << endl;
      cout << "Saindo... Até Breve!" << endl;
      sair = true;
      break;
    default:
      cout << "Opção inválida, tente novamente." << endl;
      break;
    }
  } while (!sair);
}