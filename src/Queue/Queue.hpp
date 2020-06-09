/**
 * Fila de prioridade retroativa
 */

// Queue.h
#ifndef QUEUE 
#define QUEUE_H

#pragma once

#include "../BST/Treap.hpp"

using namespace std;


/**
  Implementação retroativa das operações em uma fila
*/
namespace Retroactivity {
  /** 
  * Fila parcialmente retroativa
  */
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

  /** 
  * Fila totalmente retroativa
  */
  template<typename T>
  class FullQueue {
    /** Árvore binária de busca que mantém as operações de Enqueue(x) ordenadas por tempo
    * 
    * Contém uma chave (inteiro) representando o tempo de inserção e um valor (T) corresepondente ao objeto inserido
    */
    BST::Treap<int, T> te;



   /** Árvore binária de busca que mantém as operações de Dequeue(x) ordenadas por tempo
    * 
    * Contém uma chave (inteiro) representando o tempo de inserção e um valor (booleano), pois não é 
    * preciso armazenar informação referente a chave nessa árvore
    */
    BST::Treap<int, bool> td;



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

  /** 
  * Fila com retroatividade não consistente
  */
  template<typename T>
  class NonObliviousQueue {
  private:
    /** Árvore binária de busca que mantém as operações de Enqueue(x) ordenadas por tempo
    * 
    * Contém uma chave (inteiro) representando o tempo de inserção da operação Enqueue e um 
    * par (T, int) representando o objeto inserido, e, se existir, o tempo de remoção desse objeto.
    */
    BST::Treap<int, std::pair<T, int> > te;



    /** Árvore binária de busca que mantém as operações de Dequeue(x) ordenadas por tempo
    * 
    * Contém uma chave (inteiro) representando o tempo de inserção da operação Dequeue e um valor (inteiro) representando o 
    * o objeto removido por essa operação
    */
    BST::Treap<int, int> td;



    /** Inteiro representando o valor nulo
    */
    const int NULLVALUE = -1;
  public:


    /** Insere uma operação Enqueue(x) no tempo t
    * => Insert(t, Enqueue(x))
    * 
    * Recebe um inteiro t (tempo de inserção da operação) em que a operação Enqueue(x)
    * será inserida
    *
    * @param t -> tempo de inserção da operação Enqueue(x)
    * @param x -> objeto a ser inserido na operação
    * @return -> um inteiro com o tempo da primeira operação Dequeue inconsistente
    */
    int InsertEnqueue(int t, T x);



    /** Insere uma operação Dequeue() no tempo t
    * => Insert(t, Dequeue())
    * 
    * Recebe um inteiro t (tempo de inserção da operação) em que a operação Dequeue 
    * será inserida
    *
    * @param t -> tempo de inserção da operação Dequeue
    * @return -> um inteiro com o tempo da primeira operação Dequeue inconsistente
    */
    int InsertDequeue(int t);



    /** Remove a operação de Enqueue realizada no tempo t
    * => Delete(t, Enqueue(x))
    *
    * @param t -> tempo em que uma operação Enqueue foi realizada
    * @pre -> precisa que uma operação Enqueue no tempo t tenha sido realizada
    * @return -> um inteiro com o tempo da primeira operação Dequeue inconsistente
    */
    int DeleteEnqueue(int t);



    /** Remove a operação de Dequeue realizada no tempo t
    * => Delete(t, Dequeue())
    *
    * @param t -> tempo em que uma operação Dequeue foi realizada
    * @pre -> precisa que uma operação Dequeue no tempo t tenha sido realizada
    * @return -> um inteiro com o tempo da primeira operação Dequeue inconsistente
    */
    int DeleteDequeue(int t);


    /** Remove a operação de Dequeue realizada no tempo t
    * => Front(t)
    *
    * @param t -> tempo em que deseja-se saber o elemento na frente da fila
    * @pre -> precisa que exista um elemento na fila
    * @return -> o iterator do elemento na posição frontal da fila
    */
    typename BST::Treap<int, std::pair<T, int> > :: iterator Front(int t);



    /** Corrige a estrutura após uma inconsistencia no tempo t
    *
    * @param t -> tempo em que ocorreu uma inconsistencia na estrutura
    */
    void fixDequeueOperation(int t);



    /** Função auxiliar para mostrar os elementos do conjuto das inserções
    *
    * @return -> os elementos do conjunto Te no formato "tempoInsercao, (elemento, tempoRemocao)"
    */
    void showTe();



    /** Função auxiliar para mostrar os elementos do conjuto das remocoes
    *
    * @return -> os elementos do conjunto Td no formato "tempoDelecao, (elementoDeletado)"
    */
    void showTd();
  };
}

namespace Brute {
  /** 
  * Fila de prioridade parcialmente retroativa por força-bruta
  */
  template<typename T>
  class PartialQueue {
    /** Árvore binária que mantém as operações realizadas em uma fila retroativa
    * 
    * Mantem um par chave valor em que a chave representa o tempo de cada operação executada na fila e o valor
    * representa o elemtno inserido
    */
    map< int, T > q;
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
  };


  /** 
  * Fila de prioridade totalmente retroativa por força-bruta
  */
  template<typename T>
  class FullQueue {
     /** Árvore binária que mantém as operações realizadas em uma fila retroativa
    * 
    * Mantem um par chave valor em que a chave representa o tempo de cada operação executada na fila e o valor
    * representa o elemtno inserido
    */
    map< int, T > q;
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

#include "Queue.cpp"

#endif /* QUEUE_H */
