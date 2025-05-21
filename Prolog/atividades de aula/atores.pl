/*
Cada fato ator/4 é composto por:
1. argumento (ator): nome completo do ator colocado (entre apóstrofos);
2. argumento (filme): nome completo do filme (entre apóstrofos);
3. argumento (data): ano de lançamento do filme (número inteiro);
4. argumento (rank): o rank (colocação) do ator no filme, de acordo com os
créditos (por exemplo,1 se protagonista ou 0 se não recebeu créditos).
*/

inicio:-
    dynamic(ator/4),
    consult("banco_de_atores.pl"), %substitui o see(arquivo);
    escreve_menu,
    le_escolha(Op),
    executa(Op).

escreve_menu:-
    write('1-lista atores;'),nl,
    write('2-adiciona ator;'),nl,
    write('3-remove ator;'),nl,
    write('4-quantos filmes um ator especifico fez;'),nl,
    write('5-sair.'),nl.

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

%fim do código da leitura sem precisar de ponto

executa(1):-
    reconsult("banco_de_atores.pl"),% = aderir informaçoes de banco_de_atores.pl para a base de conhecimento do prolog
    findall(A,ator(A,_,_,_),L),% = pega tudo da base de conhecimento do prolog relacionado a ator/4 e bota em uma lista
    escreve(L),% pega essa lista e escreve um por um dos elementos
    inicio.
    
executa(2):-
    escreveArquivo,
    inicio.

executa(3):-
    reconsult("banco_de_atores.pl"),
    removeLinha,
    inicio.

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

escreveArquivo:-
    write('nome do ator : '),
    le_atomo(X),nl,
    write('nome do filme: '),
    le_atomo(Y),nl,
    write('ano do filme: '),
    le_atomo(Z),nl,
    write('ranking do filme: '),
    le_atomo(W),nl,
    append('banco_de_atores.pl'),%no lugar de tell, pois o tell apaga tudo do arquivo
    nl,%bota nova linha no arquivo banco_de_atores.pl
    write(ator(X,Y,Z,W)),%escreve no fim de banco_de_atores.pl o novo ator
    write('.'),
    nl,
    told.

removeLinha:-
    write('escreva o nome do ator que quer remover: '),
    le_atomo(X),nl,
    write('escreva o nome do filme do ator que quer remover: '),
    le_atomo(Y),nl,
    write('escreva o nome o ano do filme que quer remover: '),
    le_atomo(Z),nl,
    write('escreva a classificacao do filme que quer remover: '),
    le_atomo(W),nl,
    retract(ator(X,Y,Z,W)),%tira da base do conhecimento de prolog( não do arquivo) tudo com aquele ator específico
    tell('banco_de_atores.pl'),%apaga o arquivo todo
    listing(ator/4),%pega os relacionamentos restantes do conhecimento do prolog( tudo menos oq foi tirado) e manda eles de volta pro arquivo
    told.