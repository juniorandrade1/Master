//IntervalTree.hpp

#ifndef INTERVALTREE 
#define INTERVALTREE_H

#pragma once

#include <bits/stdc++.h>

using namespace std;

const int N = (int)66666;


/**
* Estrutura que mantém uma árvore de segmentos referente a fila de prioridade
* e armazena as pontes do algoritmo proposto por Demaine et. al.
*/
template <typename T>
class IntervalTreeSum {
  /** 
  * Estrutura que mantem um nó da árvore de intervalos
  */
  struct Node;

public:

  /** Armazena os nós da árvore de segmentos
  * 
  */
  std::vector< Node > tr;


  /** Armazena o vetor de lazy propagation da árvore de segmentos
  * 
  */
  std::vector< int > lz;


  /** Armazena o indice para o filho da esquerda de um nó.
  * 
  */
  std::vector< int > L;


  /** Armazena o indice para o filho da direita de um nó.
  * 
  */
  std::vector< int > R;


  /** Tamanho do intervalo temporal que a estrutura representa
  * 
  */
  int n;


  /** Cria um novo nó na árvore de segmentos
  *
  * Inicializa um novo nó, gerando os filhos esquerdo e direito bem como o vertor de propagação
  * @param l -> intervalo inicial que o nó contém
  * @param r -> intervalo final que o nó contém
  */
  int createNode(int l, int r);


  /** Construtor para a árvore de segmentos
  */
  IntervalTreeSum();

  void build(int no, int l, int r);

  /** Função para atualização do lazy propagation
  *
  * @param no -> índice do nó atualizado
  * @param l -> índice do filho esquerdo do nó atualizado
  * @param r -> índice do filho direito do nó atualizado
  */
  void propagate(int no, int l, int r);


  /** Função para atualização de uma posição t na árvore de segmentos
  *
  * @param no -> índice do nó atualizado
  * @param l -> limite inferior do intervalo que o nó atual representa
  * @param r -> limite superior do intervalo que o nó atual representa
  * @param t -> índice da posição a ser atualizada
  * @param inc -> indica o valor do incremento ao elemento no indice t
  */
  void update(int no, int l, int r, int t, int inc);

  /** Retorna um nó resultante da união dos nós que representam o intervalo [i, j] na árvore de segmentos
  *
  * @param no -> índice do nó atualizado
  * @param l -> limite inferior do intervalo que o nó atual representa
  * @param r -> limite superior do intervalo que o nó atual representa
  * @param i -> limite inferior da consulta desejada
  * @param j -> limite superior da consulta desejada
  */
  Node query(int no, int l, int r, int i, int j);

  /** Imprime os nós necessários para a geração do intervalo [l, r] na árvore de segmentos
  *
  * @param no -> índice do nó atualizado
  * @param l -> limite inferior da consulta desejada
  * @param r -> limite superior da consulta desejada
  */
  void showTree(int no, int l, int r);

  /** Retorna um nó resultante da união dos nós que representam o intervalo [l, r] na árvore de segmentos
  *
  * @param l -> limite inferior da consulta desejada
  * @param r -> limite superior da consulta desejada
  */
  Node query(int l, int r);

  /** Função para atualização de uma posição t na árvore de segmentos
  *
  * @param t -> índice da posição a ser atualizada
  * @param inc -> indica o valor do incremento ao elemento no indice t
  */
  void update(int t, T inc);

  /** Imprime todos os nós da árvore
  *
  */
  void showTree();


  /** Retorna a primeira ponte anterior ao tempo t.
  *
  * Uma ponte é o instante temporal mais próximo e anterior a t com soma acumulada igual a 0
  * @param t -> tempo da consulta
  * @returns -> um inteiro, o instante da última ponte antes do tempo t 
  */
  int getLastBridge(int t);

  /** Retorna a primeira ponte posterior ao tempo t.
  *
  * Uma ponte é o instante temporal mais próximo e posterior a t com soma acumulada igual a 0
  * @param t -> tempo da consulta
  * @returns -> um inteiro, o instante da proxima ponte após do tempo t 
  */
  int getNextBridge(int t);
};

#include "IntervalTree.cpp"

#endif /* INTERVALTREE_H */