// Priority_queue.h
#ifndef QUEUE 
#define QUEUE_H

#pragma once

#include "IntervalTree.cpp"
#include "../BST/Treap.cpp"

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
    PartialPriorityQueue(){};


    /** Insere uma operação de Push(data) no tempo t
    * => Insert(t, Push(data))
    *
    * @param t -> tempo em que a operação Push(data) foi realizada
    * @returns -> vetor de operações realizadas nas filas qnow e nqnow
    * @pre ->
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
};

/**
  Implementação trivial das operações em uma fila de prioridade retroativa
  Utilizada para a implementação dos testes
*/

namespace Brute {
  template <typename T>
  class PartialPriorityQueue {
  public:
    std::multiset< pair<int, pair<int, T> > > all;
    void insertPush(int t, T data) {
      all.insert(make_pair(t, make_pair(1, data)));
    }
    void insertPop(int t) {
      all.insert(make_pair(t, make_pair(-1, T())));
    }
    void removePush(int t) {
      auto f = all.lower_bound(make_pair(t, make_pair(-1, -1)));
      all.erase(f);
    }
    void removePop(int t) {
      auto f = all.lower_bound(make_pair(t, make_pair(-1, -1)));
      all.erase(f);
    }
    T getPeak() {
      multiset< T > qnow;
      for(typename multiset< pair<int, pair<int, T> > > :: iterator it = all.begin(); it != all.end(); it++) {
        pair<int, pair<int, T> > foo = *it;
        if(foo.second.first == 1) qnow.insert(foo.second.second);
        else {
          qnow.erase(qnow.begin());
        }
      }
      return *qnow.begin();
    }
    bool empty() {
      multiset< T > qnow;
      for(typename multiset< pair<int, pair<int, T> > > :: iterator it = all.begin(); it != all.end(); it++) {
        pair<int, pair<int, T> > foo = *it;
        if(foo.second.first == 1) qnow.insert(foo.second.second);
        else {
          qnow.erase(qnow.begin());
        }
      }
      return qnow.size() == 0;
    }
  };
  template < typename T >
  class FullPriorityQueue {
  public:
    std::multiset< pair<int, pair<int, T> > > all;
    void insertPush(int t, T data) {
      all.insert(make_pair(t, make_pair(1, data)));
    }
    void insertPop(int t) {
      all.insert(make_pair(t, make_pair(-1, T())));
    }
    void removePush(int t) {
      auto f = all.lower_bound(make_pair(t, make_pair(-1, -1)));
      all.erase(f);
    }
    void removePop(int t) {
      auto f = all.lower_bound(make_pair(t, make_pair(-1, -1)));
      all.erase(f);
    }
    T getPeak(int t) {
      multiset< T > qnow;
      for(typename multiset< pair<int, pair<int, T> > > :: iterator it = all.begin(); it != all.end(); it++) {
        pair<int, pair<int, T> > foo = *it;
        if(foo.first > t) continue;
        if(foo.second.first == 1) qnow.insert(foo.second.second);
        else {
          qnow.erase(qnow.begin());
        }
      }
      return *qnow.begin();
    }
    bool empty(int t) {
      multiset< T > qnow;
      for(typename multiset< pair<int, pair<int, T> > > :: iterator it = all.begin(); it != all.end(); it++) {
        pair<int, pair<int, T> > foo = *it;
        if(foo.first > t) continue;
        if(foo.second.first == 1) qnow.insert(foo.second.second);
        else {
          qnow.erase(qnow.begin());
        }
      }
      return qnow.size() == 0;
    }
  };
};


#include "Priority_queue.cpp"

#endif /* QUEUE_H */