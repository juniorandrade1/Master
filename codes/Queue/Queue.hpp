#pragma once

// Queue.h
#ifndef QUEUE 
#define QUEUE_H

#include "../BST/OrderedMap.cpp"

using namespace std;

namespace Retroactivity {
  template<typename T>
  class PartialQueue {
  private:
    /** Lista das operações Enqueue(x) ordenadas por tempo 
    * 
    * Árvore binária de busca que mantém como chave os tempos de inserção
    * das operações, e como valor o objeto inserido
    */
    BST::Treap<int, T> E;



    /** Ponteiros para os elementos inicial e final da fila
    * B(back) = último elemento a ser removido
    * F(front) = próximo elemento a ser removido
    */
    typename BST::Treap<int, T> :: iterator B, F;


  public:
    /** Insere uma operação Enqueue(x) no tempo t
    * => Insert(t, Enqueue(x))
    * 
    * Recebe um inteiro t (tempo de inserção da operação) em que a operação Enqueue(x)
    * será inserida
    *
    * @param t -> tempo de inserção da operação Enqueue(x)
    * @param x -> objeto a ser inserido na operação
    */
    void InsertEnqueue(int t, const T &x);



    /** Insere uma operação Dequeue() no tempo t
    * => Insert(t, Dequeue())
    * 
    * Recebe um inteiro t (tempo de inserção da operação) em que a operação Dequeue 
    * será inserida
    *
    * @param t -> tempo de inserção da operação Dequeue
    */
    void InsertDequeue(int t);



    /** Remove a operação de Enqueue realizada no tempo t
    * => Delete(t, Enqueue(x))
    *
    * @param t -> tempo em que uma operação Enqueue foi realizada
    * @pre -> precisa que uma operação Enqueue no tempo t tenha sido realizada
    */
    void DeleteEnqueue(int t);



    /** Remove a operação de Dequeue realizada no tempo t
    * => Delete(t, Dequeue())
    *
    * @param t -> tempo em que uma operação Dequeue foi realizada
    * @pre -> precisa que uma operação Dequeue no tempo t tenha sido realizada
    */
    void DeleteDequeue(int t);



    /** Retorna o proximo elemento a ser removido da fila considerando a versão mais atual da estrutura
    * => Front()
    *
    * @return -> O proximo elemento a ser removido da fila
    * @pre -> a fila não pode estar vazia
    */
    T front();



    /** Retorna o último elemento a ser removido da fila considerando a versão mais atual da estrutura
    * => Back()
    *
    * @return -> O último elemento a ser removido da fila
    * @pre -> a fila não pode estar vazia
    */
    T back();
  };

  template<typename T>
  class FullQueue {
    /** Árvore binária de busca que mantém as operações de Enqueue(x) ordenadas por tempo
    * 
    * Contém uma chave (inteiro) representando o tempo de inserção e um valor (T) corresepondente ao objeto inserido
    */
    BST::OrderedMap<int, T> te;



   /** Árvore binária de busca que mantém as operações de Dequeue(x) ordenadas por tempo
    * 
    * Contém uma chave (inteiro) representando o tempo de inserção e um valor (booleano), pois não é 
    * preciso armazenar informação referente a chave nessa árvore
    */
    BST::OrderedMap<int, bool> td;


    
  public:
   /** Insere uma operação Enqueue(x) no tempo t
    * => Insert(t, Enqueue(x))
    * 
    * Recebe um inteiro t (tempo de inserção da operação) em que a operação Enqueue(x)
    * será inserida
    *
    * @param t -> tempo de inserção da operação Enqueue(x)
    * @param x -> objeto a ser inserido na operação
    */
    void InsertEnqueue(int t, const T &x);



    /** Insere uma operação Dequeue() no tempo t
    * => Insert(t, Dequeue())
    * 
    * Recebe um inteiro t (tempo de inserção da operação) em que a operação Dequeue 
    * será inserida
    *
    * @param t -> tempo de inserção da operação Dequeue
    */
    void InsertDequeue(int t);



    /** Remove a operação de Enqueue realizada no tempo t
    * => Delete(t, Enqueue(x))
    *
    * @param t -> tempo em que uma operação Enqueue foi realizada
    * @pre -> precisa que uma operação Enqueue no tempo t tenha sido realizada
    */
    void DeleteEnqueue(int t);



    /** Remove a operação de Dequeue realizada no tempo t
    * => Delete(t, Dequeue())
    *
    * @param t -> tempo em que uma operação Dequeue foi realizada
    * @pre -> precisa que uma operação Dequeue no tempo t tenha sido realizada
    */
    void DeleteDequeue(int t);

    /** Consulta qual o índice do k-ésimo elemento da fila considerando as operações de Dequeue realizadas
    *
    * @param t -> tempo em que a consulta é realizada
    * @param k -> índice do elemento consultado
    * @return -> O k-ésimo elemento da fila no tempo t
    * @pre -> a fila não pode estar vazia no tempo t e k deve ser menor que o número de elemento na fila no tempo t
    */
    T getKth(int t, int k);


    /** Retorna o proximo elemento a ser removido da fila no tempo t
    * => Front(t)
    *
    * @param t -> tempo em que se deseja consultar o próximo elemento da fila
    * @return -> O proximo elemento a ser removido da fila no tempo t
    * @pre -> a fila não pode estar vazia no tempo t
    */
    T front(int t);
  };  
}


/**
  Implementação trivial das operações em uma fila retroativa
  Utilizada para a implementação dos testes
*/

namespace Brute {
  template<typename T>
  class FullQueue {
  public:
    map< int, T > q;
    void InsertEnqueue(int t, const T &x) {
      q[t] = x;
    }
    void InsertDequeue(int t) {
      q[t] = numeric_limits< T > :: min();
    }
    void DeleteEnqueue(int t) {
      q.erase(t);
    }
    void DeleteDequeue(int t) {
      q.erase(t);
    }
    T front(int t) {
      queue< int > f;
      for(typename map< int, T > :: iterator it = q.begin(); it != q.end(); it++) {
        if(it->first > t) break;
        if(it->first == numeric_limits< T > :: min()) f.pop();
        else f.push(it->second);
      }
      return f.front();
    }
  };

  template<typename T>
  class PartialQueue {
  public:
    map< int, T > q;
    void InsertEnqueue(int t, const T &x) {
      q[t] = x;
    }
    void InsertDequeue(int t) {
      q[t] = numeric_limits< T > :: min();
    }
    void DeleteEnqueue(int t) {
      q.erase(t);
    }
    void DeleteDequeue(int t) {
      q.erase(t);
    }
    T front() {
      queue< int > f;
      for(typename map< int, T > :: iterator it = q.begin(); it != q.end(); it++) {
        if(it->second == numeric_limits< T > :: min()) f.pop();
        else f.push(it->second);
      }
      assert(f.size() > 0);
      return f.front();
    }
  };
}

#include "Queue.cpp"

#endif /* QUEUE_H */
