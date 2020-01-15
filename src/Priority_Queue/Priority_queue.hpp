/*! A test class */

// Priority_queue.h
#ifndef PRIORITY_QUEUE 
#define PRIORITY_QUEUE_H

#pragma once

#include "IntervalTree.cpp"
#include "../BST/Treap.cpp"
#include "../BST/SegmentTree.cpp"
#include "../BST/PrioritySearchTree.cpp"
#include "../BST/PersistentTreap.cpp"

enum Operation {
  insertpush, insertpop, deletepush, deletepop
};

/**
  Implementação retroativa das operações em uma fila de prioridade
*/
namespace Retroactivity {
  /** 
  * Fila de prioridade parcialmente retroativa em tempo O(log(m)) por operação
  */
  template <typename T>
  class PartialPriorityQueue {
  private:
    /** Lista dos elementos contidos no estado atual da fila 
    * 
    * Árvore binária de busca que mantém como chave os tempos das inserções dos elementos
    * e como valor o próprio elemento
    */
    BST::Treap< int, T > qnow;


    /** Lista dos elementos que foram retirados da fila por operações Pop()
    * 
    * Árvore binária de busca que mantém como chave os tempos das inserções dos elementos
    * e como valor o próprio elemento
    */
    BST::Treap< int, T > nqnow;


    /** Árvore para a manutenção das pontes da estrutura
    * 
    * Árvore de segmentos que mantém a soma de prefixo de maneira dinâmica
    * Os nós folha dessa árvore representam os índices temporais, e são atualizados da seguinte forma:
    * 0   para as operações Insert(t, Push(data)) em qnow
    * +1  para as operações Insert(t, Push(data)) em nqnow
    * 0   para as operações Insert(t, Pop())
    */
    IntervalTreeSum< int > bridges;


    /** Tipo da operação realizada no tempo t
    * 
    *  Árvore binária que mantém o tipo da operação realizada em cada tempo
    *  Contém como chave os tempos de atualização (inteiros) e como valor os seguintes
    *  valores:
    *  -> 0 = nenhuma operação realizada no tempo t
    *  -> 1 = operação do tempo t é um Push e o elemento está contido em qnow
    *  -> 2 = operação do tempo t é um Push e o elemento está contido em nqnow
    *  -> 3 = operação do tempo t é um Pop
    */
    std::unordered_map< int, int > type;
  public:
    /** Construtor padrão para fila de prioridade parcialmente retroativa
    *
    */
    PartialPriorityQueue(){};


    /** Insere uma operação de Push(data) no tempo t
    * => Insert(t, Push(data))
    *
    * @param t -> tempo em que a operação Push(data) foi realizada
    * @returns vetor de operações realizadas nas filas qnow e nqnow
    */
    vector< pair<int, T> > insertPush(int t, T data);


    /** Insere uma operação de Pop() no tempo t
    * => Insert(t, Pop())
    *
    * @param t -> tempo em que a operação Pop() foi realizada
    * @returns -> vetor de operações realizadas nas filas qnow e nqnow com a execução da função
    * @pre ->
    */
    vector< pair<int, T> > insertPop(int t);


    /** Remove uma operação de Push(data) no tempo t
    * => Delete(t, Push(data))
    *
    * @param t -> tempo em que a operação Push(data) foi realizada
    * @returns -> vetor de operações realizadas nas filas qnow e nqnow
    * @pre -> deve existir uma operação Insert(t, Push(data)) na estrutura
    */
    vector< pair<int, T> > removePush(int t);


    /** Remove uma operação de Pop() no tempo t
    * => Delete(t, Pop())
    *
    * @param t -> tempo em que a operação Pop() foi realizada
    * @returns -> vetor de operações realizadas nas filas qnow e nqnow
    * @pre -> deve existir uma operação Delete(t, Pop()) na estrutura
    */
    vector< pair<int, T> > removePop(int t);


    /** Retorna se a fila está vazia no tempo presente
    * => Empty()
    *
    * @returns -> 'true' se a fila estiver vazia
    */
    bool empty();



    /** Retorna o menor elemento da fila de prioridade no tempo atual
    * => GetPeak()
    *
    * @returns -> o menor elemento da fila de prioridade após a execução de todas 
    *             as operações na estrutura.
    * @pre -> a estrutura deve conter pelo menos um elemento
    */
    T getPeak();
  };


  /** 
  * Fila de prioridade totalmente retroativa em tempo O(sqrt(m) * log(m)) por operação
  */
  template <typename T> 
  class FullPriorityQueue {
  private:
    /** Classe para armazenamento das operações de um bloco
    *
    */
    class Operation;


    /** Tamanho da linha temporal da estrutura
    *
    */
    int m;


    /** Tamanho do bloco de operações 
    * 
    */
    int b;


    /** Lista que mantém as estruturas parcialmente retroativas para cada bloco de tamanho b
    *
    */
    std::vector< PartialPriorityQueue< T > > p;


    /** Conjunto de todas as operações realizadas na estrutura
    *
    */
    std::set< Operation > all;
  public:
    FullPriorityQueue(){
      m = N;
      b = sqrt(m);
      p.resize((m + b - 1) / b);
    };
    FullPriorityQueue(int _m) {
      m = _m;
      b = sqrt(m);
      p.resize((m + b - 1) / b);
    }



    /** Insere uma operação de Push(data) no tempo t
    * => Insert(t, Push(data))
    *
    * @param t -> tempo em que a operação Push(data) foi realizada
    */
    void insertPush(int t, T data);


     /** Insere uma operação de Pop() no tempo t
    * => Insert(t, Pop())
    *
    * @param t -> tempo em que a operação Pop() foi realizada
    * @pre ->
    */
    void insertPop(int t);


     /** Remove uma operação de Push(data) no tempo t
    * => Delete(t, Push(data))
    *
    * @param t -> tempo em que a operação Push(data) foi realizada
    * @pre -> deve existir uma operação Insert(t, Push(data)) na estrutura
    */
    void removePush(int t);


    /** Remove uma operação de Pop() no tempo t
    * => Delete(t, Pop())
    *
    * @param t -> tempo em que a operação Pop() foi realizada
    * @pre -> deve existir uma operação Delete(t, Pop()) na estrutura
    */
    void removePop(int t);


    /** Retorna se a fila está vazia no tempo t
    * => Empty(t)
    *
    * @param t -> tempo em que se deseja saber se a fila está vazia
    * @returns -> 'true' se a fila estiver vazia no tempo t
    */
    bool empty(int t);


    /** Retorna o menor elemento da fila de prioridade no tempo t
    * => GetPeak(t)
    *
    * @param t -> tempo em que se deseja consultar o menor elemento da fila
    * @returns -> o menor elemento da fila de prioridade após a execução de todas 
    *             as operações até o tempo t
    * @pre -> a estrutura deve conter pelo menos um elemento no tempo t
    */
    T getPeak(int t);
  };

  /** 
  * Fila de prioridade com retroatividade não-consistente
  */
  template <typename T>
  class NonObliviousPriorityQueue {
  private:
    /** Estrutura que mantém os segmentos horizontais referentes a linha temporal dos elementos

    * 
    * Consiste em uma árvore de segmentos que mantém os segmentos referentes aos elementos.
    * Na estrutura, o ínicio de um segmento horizontal corresponde ao tempo de inserção do elemento
    * enquanto o fim de um segmento representa a sua remoção. Já a sua altura representa o 
    * valor do elemento inserido
    */
    BST::SegmentTree H;


    /** Estrutura que mantém os segmentos verticais referentes a operações de remoção

    * 
    * Consiste em uma priority search tree com pontos (x, y) correspondente a um segmento vertical (x, [-inf, y])
    * O ponto mais alto do segmento vertical corresponde ao elemento removido por essa operação
    */
    BST::DynamicPST<int, int> V;


    /** Tamanho máximo da linha do tempo

    */
    int MAX = (int)1e5;
  public:


    /** Insere uma operação de Push(data) no tempo t
    * => Insert(t, Push(data))
    *
    * @param t -> tempo em que a operação Push(data) foi realizada
    * @return -> primeira operação inconsistente apos a execução da operação 
    */
    int InsertPush(int t, T x);


    /** Insere uma operação de Pop() no tempo t
    * => Insert(t, Pop())
    *
    * @param t -> tempo em que a operação Pop() foi realizada
    * @return -> primeira operação inconsistente apos a execução da operação 
    */
    int InsertPop(int t);


    /** Remove a operação de Push realizada no tempo t
    * => Delete(t, Push(x))
    *
    * @param t -> tempo em que uma operação Push(x) foi realizada
    * @pre -> precisa que uma operação Push no tempo t tenha sido realizada
    * @return -> um inteiro com o tempo da primeira operação inconsistente
    */
    int DeletePush(int t);


    /** Remove a operação de Pop realizada no tempo t
    * => Delete(t, Pop())
    *
    * @param t -> tempo em que uma operação Pop foi realizada
    * @pre -> precisa que uma operação Pop no tempo t tenha sido realizada
    * @return -> um inteiro com o tempo da primeira operação inconsistente
    */
    int DeletePop(int t);


    /** Obtem o elemento minimo na estrutura no tempo t
    *
    * @param t -> o tempo que deseja-se consultar o menor elemento na estrutura
    * @return -> o menor elemento na estrutura no tempo t
    */
    T Peak(int t);


    /** Corrige a estrutura após uma inconsistencia no tempo t
    *
    * @param t -> tempo em que ocorreu uma inconsistencia na estrutura
    */
    void fixOperation(int t, Operation type);
  };

  typedef pair<int, int> ii;

  /** 
  * Fila de prioridade totalmente retroativa em tempo polilogaritmico
  */
  template <typename T>
  class PolylogarithmPriorityQueue {
  private:
    /** Estrutura que representa um nó na checkpoint tree.

    * 
    * Em um nó é mantido uma fila de prioridade parcialmente retroativa correspondente ao intervalo
    * contido por esse nó, e duas árvores binárias balanceadas persistentes, qnow e qdel, 
    * contendo os elementos inseridos e os tempos de deleção desses elementos respectivamente
    */
    class Node;


    /** Estrutura auxiliar para a manutenção dos conjuntos qnow e qdel de cada nó

    * 
    * Contém um array t de pares (qnow, qdel)
    */
    class QueryNode;

    /** Tamanho da linha do tempo da estrutura

    */
    int m; 


    /** Estrutura que mantem os nós de uma checkpoint tree

    */
    vector< Node > tr;
  public:
    

    /** Função construtora da Fila de prioridade polilogarítmica.
    
    */
    PolylogarithmPriorityQueue(int _m);


    /** Função para obtenção do numero de elementos em q
    * 
    * Obtem a quantidade de elementos em q
    *
    * @param q -> conjunto de árvores binárias balanceadas
    * @pre -> o tipo abstrato T deve conter uma ordenação consistente.
    * @return -> um inteiro, o numero de elementos em q
    */
    int getQueryNodeSize(QueryNode q);


    /** Função para obtenção do numero de elementos em q maiores que key
    * 
    * Obtem a quantidade de elementos em q maiores que key
    *
    * @param q -> conjunto de árvores binárias balanceadas
    * @param key -> elemento na qual deseja-se consultar o número de elementos maiores
    * @pre -> o tipo abstrato T deve conter uma ordenação consistente.
    * @return -> um inteiro, o número de elementos em q maiores que key
    */
    int getQtdGE(QueryNode q, T key);


    /** Função para obtenção do menor elemento dentre todos os conjuntos em f
    * 
    * Obtem o valor do menor elemento nas árvore binárias balanceadas em f (em qnow)
    *
    * @param f -> conjunto de elementos na qual deseja-se saber o menor elemento
    * @pre -> o tipo abstrato T deve conter uma ordenação consistente.
    * @return -> um tipo abstrato T, contendo o menor elemento em todos os qnow's no conjunto f
    */
    T getMinimumKey(QueryNode f);


    /** Função que adiciona um push no tempo i com o elemento data
    * => Insert(i, Push(data))
    * 
    * Insere na checkpoint tree o elemento data no tempo i
    *
    * @param no -> indice do nó atual da recursao para inserção do elemento
    * @param l -> limite inferior do intervalo contido por no
    * @param r -> limite superior do intervalo contido por no
    * @param i -> tempo em que o elemento data será inserido na estrutura
    * @param data -> elemento a ser inserido no tempo i
    * @pre -> não deve existir nenhuma outra operação no tempo i
    */
    void addPush(int no, int l, int r, int i, T data);


    /** Função que adiciona a operação pop no tempo i
    * => Insert(i, Pop())
    * 
    * Insere na checkpoint tree uma deleção no tempo i
    *
    * @param no -> indice do nó atual da recursao para inserção do elemento
    * @param l -> limite inferior do intervalo contido por no
    * @param r -> limite superior do intervalo contido por no
    * @param i -> tempo em que a operação Pop será inserida na estrutura
    * @pre -> não deve existir nenhuma outra operação no tempo i
    */
    void addPop(int no, int l, int r, int i);


    /** Função que remove a operação push do tempo i
    * 
    * Insere na checkpoint tree uma deleção da operação Push no tempo i
    *
    * @param no -> indice do nó atual da recursao para inserção do elemento
    * @param l -> limite inferior do intervalo contido por no
    * @param r -> limite superior do intervalo contido por no
    * @param i -> tempo em que a operação Push será deletada da estrutura
    */
    void delPush(int no, int l, int r, int i);


    /** Função que remove a operação pop do tempo i
    * 
    * Insere na checkpoint tree uma deleção da operação Pop no tempo i
    *
    * @param no -> indice do nó atual da recursao para inserção do elemento
    * @param l -> limite inferior do intervalo contido por no
    * @param r -> limite superior do intervalo contido por no
    * @param i -> tempo em que a operação Pop será deletada da estrutura
    */
    void delPop(int no, int l, int r, int i);


    /** Função que obtém os indices dos nós contidos em um intervalo [i, j]
    * 
    *
    * @param no -> indice do nó atual da recursao para inserção do elemento
    * @param l -> limite inferior do intervalo contido por no
    * @param r -> limite superior do intervalo contido por no
    * @param i -> limite inferior da consulta realizada
    * @param j -> limite superior da consulta realizada
    * @param s -> vetor com os índices retornados pela função
    */
    void getNodes(int no, int l, int r, int i, int j, vector< int > &s);


    /** Funçao que obtem o valor que os conjuntos qnow e qdel devem ser divididos
    * de modo que existam A elementos.
    * 
    * @param A -> número de elementos desejado
    * @param all -> conjunto das árvores (qnow, qdel) existentes.
    * @return -> o valor em que deve-se dividir as árvores de modo que os menores A elementos 
    *    estejam separados do restante da árvore
    */
    T getSplitKey(T A, vector< ii > all);


    /** Função que retorna as árvores após a sua divisão por um valor x
    * 
    * @param x -> valor na qual deseja-se dividir os conjuntos.
    * @param all -> conjunto das árvores (qnow, qdel) existentes.
    * @return -> conjunto das árvores após a divisão pelo valor x.
    */
    pair< QueryNode, QueryNode > getSplitedTrees(int x, vector< ii > all);


    /** Função que une dois conjuntos q1(qnow, qdel) e q2(qnow, qdel)
    * de modo que a união dos conjuntos representem uma fila de prioridade
    * retroativa que abrange o intervalo que q1 e q2 abrangiam.
    * 
    * @param q1 -> (qnow, qdel) representando o intervalo [l1, r1]
    * @param q2 -> (qnow, qdel) representando o intervalo [l2, r2]
    * @return -> (qnow, qdel) representando a união de q1 e q2 com o intervalo [l1, r2]
    * @pre -> q1 e q2 devem ser intervalos disjuntos continuos (r1 < l2)
    */
    pair< QueryNode, QueryNode > Fuse(pair< QueryNode, QueryNode > q1, pair< QueryNode, QueryNode > q2);
    

    /** Função que obtém os conjuntos dos nós contidos em um intervalo [i, j]
    * 
    *
    * @param no -> indice do nó atual da recursao para inserção do elemento
    * @param l -> limite inferior do intervalo contido por no
    * @param r -> limite superior do intervalo contido por no
    * @param i -> limite inferior da consulta realizada
    * @param j -> limite superior da consulta realizada
    * @return s -> os conjuntos (qnow, qdel) que formam o intervalo [i, j]
    */
    pair< QueryNode, QueryNode > query(int no, int l, int r, int i, int j);


    /** Insere uma operação de Push(data) no tempo t
    * => Insert(t, Push(data))
    *
    * @param t -> tempo em que a operação Push(data) foi realizada
    * @param data -> elemento inserido
    */
    void insertPush(int t, T data);


     /** Insere uma operação de Pop() no tempo t
    * => Insert(t, Pop())
    *
    * @param t -> tempo em que a operação Pop() foi realizada
    * @pre ->
    */
    void insertPop(int t);


    /** Remove uma operação de Push(data) no tempo t
    * => Delete(t, Push(data))
    *
    * @param t -> tempo em que a operação Push(data) foi realizada
    * @pre -> deve existir uma operação Insert(t, Push(data)) na estrutura
    */
    void removePush(int t);


    /** Remove uma operação de Pop() no tempo t
    * => Delete(t, Pop())
    *
    * @param t -> tempo em que a operação Pop() foi realizada
    * @pre -> deve existir uma operação Delete(t, Pop()) na estrutura
    */
    void removePop(int t);


    /** Retorna o menor elemento da fila de prioridade no tempo t
    * => GetPeak(t)
    *
    * @param t -> tempo em que se deseja consultar o menor elemento da fila
    * @returns -> o menor elemento da fila de prioridade após a execução de todas 
    *             as operações até o tempo t
    * @pre -> a estrutura deve conter pelo menos um elemento no tempo t
    */
    T getPeak(int t);


    /** Retorna os conjuntos qnow e qdel considerando a fila de prioridade retroativa no tempo t
    *
    * @param t -> tempo em que se deseja consultar o menor elemento da fila
    * @returns -> um par contendo as árvores contendo os conjuntos qnow e qdel respectivamente
    */
    pair< QueryNode, QueryNode > getView(int t);


    //void showQueryNode(pair< QueryNode, QueryNode > q3);
  };

};

namespace Brute {
  template <typename T>
  class PartialPriorityQueue {
  private:
    std::multiset< pair<int, pair<int, T> > > all;
  public:
    /** Insere uma operação de Push(data) no tempo t
    * => Insert(t, Push(data))
    *
    * @param t -> tempo em que a operação Push(data) foi realizada
    * @returns vetor de operações realizadas nas filas qnow e nqnow
    */
    void insertPush(int t, T data);


    /** Insere uma operação de Pop() no tempo t
    * => Insert(t, Pop())
    *
    * @param t -> tempo em que a operação Pop() foi realizada
    * @returns -> vetor de operações realizadas nas filas qnow e nqnow com a execução da função
    * @pre ->
    */
    void insertPop(int t);


    /** Remove uma operação de Push(data) no tempo t
    * => Delete(t, Push(data))
    *
    * @param t -> tempo em que a operação Push(data) foi realizada
    * @returns -> vetor de operações realizadas nas filas qnow e nqnow
    * @pre -> deve existir uma operação Insert(t, Push(data)) na estrutura
    */
    void removePush(int t);


    /** Remove uma operação de Pop() no tempo t
    * => Delete(t, Pop())
    *
    * @param t -> tempo em que a operação Pop() foi realizada
    * @returns -> vetor de operações realizadas nas filas qnow e nqnow
    * @pre -> deve existir uma operação Delete(t, Pop()) na estrutura
    */
    void removePop(int t);


    /** Retorna se a fila está vazia no tempo presente
    * => Empty()
    *
    * @returns -> 'true' se a fila estiver vazia
    */
    bool empty();



    /** Retorna o menor elemento da fila de prioridade no tempo atual
    * => GetPeak()
    *
    * @returns -> o menor elemento da fila de prioridade após a execução de todas 
    *             as operações na estrutura.
    * @pre -> a estrutura deve conter pelo menos um elemento
    */
    T getPeak();
  };
  template < typename T >
  class FullPriorityQueue {
    std::multiset< pair<int, pair<int, T> > > all;
  public:
    /** Insere uma operação de Push(data) no tempo t
    * => Insert(t, Push(data))
    *
    * @param t -> tempo em que a operação Push(data) foi realizada
    */
    void insertPush(int t, T data);


     /** Insere uma operação de Pop() no tempo t
    * => Insert(t, Pop())
    *
    * @param t -> tempo em que a operação Pop() foi realizada
    * @pre ->
    */
    void insertPop(int t);


     /** Remove uma operação de Push(data) no tempo t
    * => Delete(t, Push(data))
    *
    * @param t -> tempo em que a operação Push(data) foi realizada
    * @pre -> deve existir uma operação Insert(t, Push(data)) na estrutura
    */
    void removePush(int t);


    /** Remove uma operação de Pop() no tempo t
    * => Delete(t, Pop())
    *
    * @param t -> tempo em que a operação Pop() foi realizada
    * @pre -> deve existir uma operação Delete(t, Pop()) na estrutura
    */
    void removePop(int t);


    /** Retorna se a fila está vazia no tempo t
    * => Empty(t)
    *
    * @param t -> tempo em que se deseja saber se a fila está vazia
    * @returns -> 'true' se a fila estiver vazia no tempo t
    */
    bool empty(int t);


    /** Retorna o menor elemento da fila de prioridade no tempo t
    * => GetPeak(t)
    *
    * @param t -> tempo em que se deseja consultar o menor elemento da fila
    * @returns -> o menor elemento da fila de prioridade após a execução de todas 
    *             as operações até o tempo t
    * @pre -> a estrutura deve conter pelo menos um elemento no tempo t
    */
    T getPeak(int t);
  };
};


#include "Priority_queue.cpp"

#endif /* PRIORITY_QUEUE_H */