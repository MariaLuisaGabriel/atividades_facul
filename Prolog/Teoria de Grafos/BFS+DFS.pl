%o Grafo: um banco com relacionamentos Vertex/2, cujos argumentos são um átomo simples 
% (nro do vertice) e uma lista (adjacentes do vertice).

nb_setval(Val, 0).

inicio:-
    dynamic(graph/5), % graph(ID, é direcionado, é ponderado, lista de pesos ,lista de vértices e seus adjacentes)
    consult("Grafo.pl"), % arquivo com um montão de grafos
    menu.

menu0:-
    write('PERSONALIZANDO SEU GRAFO ============='),nl,
    write('1- Direcionado;'),nl,
    write('2- Nao Direcionado.'),nl,
    le_escolha(Op),
    menu1(Op),!.

menu1(A):-
    write('1- Ponderado;'),nl,
    wtite('2- Nao Ponderado.'),nl,
    le_escolha(Op),
    menu2(A,Op,[],[],0),!.

menu2(A,B,P,G,1):-escreveArquivo(A,B,P,G),!.

menu2(A,B,P,G,S):-
    write('1- Adicionar aresta;'),nl,
    write('2- Adicionar vertice;'),nl,
    write('3- Remover aresta;'),nl,
    write('4- Remover vertice;'),nl,
    write('5- Finalizar.'),nl,
    le_escolha(Op),
    graph_executa(A,B,P,G,Op,G1,S1),
    menu2(A,B,P,G1,S1),!.

menu:-
    write('1-listar grafos;'),nl,
    write('2-criar grafo;'),nl,
    write('3-remove grafo;'),nl,
    write('4-Busca em largura;'),nl,
    write('5-Busca em profundidade;'),nl,
    write('6-menor caminho por Busca em Largura'),nl,
    write('7-desenhar grafo com certa ID'),nl,
    write('8-fechar.'),nl,
    le_escolha(Op),
    executa(Op),!.

le_escolha(Op):-
    write('digite sua opcao: '),
    le_atomo(Op).

%leitura de um valor sem necessidade de um ponto:
le_atomo(Atomo) :-
le_str(String),
name(Atomo, String).

le_str(String) :-
get0(Char),
le_str_aux(Char, String).

le_str_aux(-1, []) :- !. % EOF
le_str_aux(10, []) :- !. % EOL(UNIX)
le_str_aux(13, []) :- !. % EOL (DOS)

le_str_aux(Char, [Char|Resto]) :-
le_str(Resto).

graph_executa(_,_,_,G,5,G,1):-!.

graph_executa(1,_,_,G,1,G1,S1):- %adic aresta em GD
    write('escreva o primeiro vértice: '),
    le_atomo(V1),
    write('escreva o segundo vértice: '),
    le_atomo(V2),
    pairs_keys_values(Pair,[V1],[V2]),
    add_edges(G,Pair,FG),
    G1 is FG,
    S1 is 0,!.

graph_executa(2,_,_,G,1,G1,S1):- %adic aresta em GND
    write('escreva o primeiro vértice: '),
    le_atomo(V1),
    write('escreva o segundo vértice: '),
    le_atomo(V2),
    pairs_keys_values(Pair,[V1],[V2]),
    pairs_keys_values(Pair1,[V2],[V1]),
    add_edges(G,Pair,FG),
    add_edges(G,Pair1,FG),
    G1 is FG,
    S1 is 0,!.

graph_executa(_,1,P,G,2,G1,S1):-%adic vertice em grafo ponderado
    ,!.

executa(1):-
    reconsult("Grafo.pl"),% = aderir informaçoes de banco_de_atores.pl para a base de conhecimento do prolog
    findall(A,graph(A,_,_,_,_),L),% = pega tudo da base de conhecimento do prolog relacionado a ator/4 e bota em uma lista
    escreve(L),% pega essa lista e escreve um por um dos elementos
    inicio.
    
executa(2):-
    menu0,
    nb_getval('Val', Aux),
    Aux1 is Aux + 1,
    nb_setval('Val', Aux1),
    inicio.

executa(3):-
    nb_getval('Val', Aux),
    not(Aux=:=0),
    Aux1 is Aux - 1,
    nb_setval('Val', Aux1),
    reconsult("Grafo.pl"),
    removeLinha,
    inicio,!.

executa(3):-
    nb_getval('Val', Aux),
    Aux=:=0,
    write('AVISO: não há grafos a serem retirados.'),!.

executa(4):-
    reconsult("banco_de_atores.pl"),
    write('escreva o ator que quer contar: '),
    le_atomo(X),
    findall(A,ator(X,A,_,_),L),
    length(L,N),%retorna em N o tamanho de uma lista L
    write('o ator '),
    write(X),
    write(' possui '),
    write(N),
    write(' filmes.'),nl,
    inicio.

executa(5):-
    !.

escreve([]):-!.
escreve([X|L]):-
    write(X),nl,
    escreve(L).

processaArquivo:-%escrever todos os atores com tal nome para o usuário
    read(ator(X,_,_,_)),
    processa(X).

processa(end_of_file):-!.
processa(X):-
    write(X),
    processaArquivo.

escreveArquivo(A,B,P,G):-
    append('Grafo.pl'),%no lugar de tell, pois o tell apaga tudo do arquivo
    nl,%bota nova linha no arquivo banco_de_atores.pl
    nb_getval('Val', Aux),
    write(graph(Aux,A,B,P,G)),%escreve no fim de Graph.pl o novo grafo
    write('.'),
    nl,
    told.

removeLinha:-
    write('escreva o Id do Grafo que quer remover: '),
    le_atomo(X),nl,
    retract(grafo(X,_,_,_,_)),%tira da base do conhecimento de prolog( não do arquivo) tudo com aquele ator específico
    tell('banco_de_atores.pl'),%apaga o arquivo todo
    listing(ator/4),%pega os relacionamentos restantes do conhecimento do prolog( tudo menos oq foi tirado) e manda eles de volta pro arquivo
    told.