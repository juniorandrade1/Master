### Conjunto de entradas de teste para pilha

As entradas contém um número inteiro $n$, representando o número de operações realizadas. 

As próximas $n$ linhas contém as operações no seguinte formato:

I E t x -> insere uma operação push no tempo t com o valor x

I D t -> insere uma operação pop no tempo t

D E t -> deleta a operação push realizada no tempo t

D D t -> deleta a operação dequeue realizada no tempo t

Q T t -> consulta o elemento no topo da pilha no tempo t (t é vazio se a pilha é parcialmente retroativa)

Todos os códigos das estruturas foram testados com o [googletest](https://github.com/google/googletest/). 

A documentação das estruturas pode ser acessada [aqui](https://juniorandrade1.github.io/Master/)
