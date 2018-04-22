# Prolog e C++

## Descrição dos programas:

Este trabalho tem 4 ficheiros, dois em Prolog e dois em C++. Em C++ temos os ficheiros “voos.cpp” e “gramatica.cpp”. O primeiro corresponde ao 1º exercício e permite-nos obter voos diretos entre dois lugares, os voos necessários para chegar de um local a outro e um plano de circuitos. O segundo permite-nos verificar se uma frase está bem formada ou não. Em prolog temos os ficheiros “voos.pl” e “gramatica.pl” que correspondem aos ficheiros em C++ e fazem exatamente o mesmo.
 
-------------------------------------------

## Requerimentos:
* Compilador g++ com c++ versão 11.
* Swipl. 

-------------------------------------------

## Instruções para compilar e executar:

### Voos:
##### C++
* Compilar: g++ -std=c++11 voos.cpp -lreadline -o voos
* executar: ./voos

##### Prolog
* abrir swipl e escrever: ['voos.pl'].

### Gramatica:
##### C++
* Compilar: g++ -std=c++11 gramatica.cpp -lreadline -o gramatica.
* executar: ./gramatica

##### Prolog
* abrir swipl e escrever: ['gramatica.pl'].

-------------------------------------------

## Execução:

### Voos:
##### C++
No inicio do “voos.cpp” vai aparecer um menu com várias opções para o utilizador escolher o que pretende fazer. Caso escolha a primeira vão-lhe ser pedidos dois locais e obterá depois os dias e horas de todos os voos diretos entre esses dois locais. Caso escolha a segunda vão-lhe ser pedidos dois locais e um dia, sendo este da forma: “mo”, “tu”,”we”,”th”,”fr”,”sa” ou “su”. Aqui vão-lhe ser devolvidos os voos necessários para chegar de um local ao outro, podendo ter locais intercalares, no entanto é garantido que são todos no mesmo dia e que existe um tempo de no minímo 40 minutos entre voos para a transferência. Casa escolha a terceira opção vai-lhe ser pedido o local de partida, que é também o ultimo destino, e depois quantas cidades pretende visitar pedindo depois o nome das mesmas. Por fim vai ter que colocar o dia da partida. O programa retorna todos os voos por ordem.

##### Prolog
Para responder as 3 questões utilizar os seguintes queries, repectivamente:

?- day_flight(Place1, Place2).
?- available_flight(Place1, Place2, Day).
?- plan_visit(OriginPlace, [C1, C2, .., Cn], StartingDay, LengthOfPlan). 

### Gramatica:
##### C++
No programa “gramatica.cpp” é pedido o numero de linhas, N, e seguem se N linhas a pedir uma frase para avaliar. Se a frase estiver errada mostra o local onde está o erro, caso contrário é descrita a composição da mesma.

##### Prolog
Para analisar uma frase utilizar o seguinte querie:
?- sentence(StructOfPhrase,Phrase,[]).
Onde Phrase é do tipo ['A', menina, corre].

-------------------------------------------

## Autores:

| Nome              | Numero UP     |
| ----------------- | ------------- |
| Diogo Pereira     | 201605323     |
| Afonso Fernandes  | 201606852     |


