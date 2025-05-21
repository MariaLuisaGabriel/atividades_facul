%meu simuladinho para a prova 1
%ATENÇÃO: não precisa desesperar pra fazer toda essa lista KKKKKKKKKKKK
%ela é DE PROPOSITO mais difícil que as provas, afim de ir folgado pra prova
%se fizer pelo menos 5 questões dessa lista, considere-se foda
%se fizer pelo menos 7 questões dessa lista, considere-se muito foda
%se fez tudo ce é o deus do prolog
%brincadeira KKKKKKKKKKKKKK

%MAIS DETALHES DAS QUESTÕES ESTÃO NO GABARITO
/*
questao 1: converta uma lista em binário para uma lista em octal.
questao 2: converta de binario para gray, de 3 em 3 bits
questao 3: converta um numero recebido em uma lista com seus fatores primos
questao 4: converta uma lista de 2 bits pra decimal e depois pra alfabeto (<-usar casamento de padrões) (2 retornos).
questao 5: receba uma lista e devolva outra que é resultado da soma de pares consecutivos da lista dada.
questao 6: receba uma lista e a divida numa lista so com seus pares e uma so com seus impares.(2 retornos)
questao 7: mmc de dois numeros. 
questao 8: mdc de dois numeros.
questao 9: gere uma lista de 5 elementos pseudoaleatorios, com classe de aleatoriedade(m) escolhida pelo usuario.
*/

%GABARITO:

/*questao 1:converta uma lista em binário para uma lista em octal.*/

%DE CAUDA
tam(L,N):-tam(L,0,N).
tam([],R,R):-!.
tam([X|Y],N,R):-
N1 is N+1,
tam(Y,N1,R).

/*SEM CAUDA
tam([],0).
tam([X|Y],R):-
tam(Y,R1),
R is R1+1.
*/

insere(X,[],[X]):-!.
insere(X,[Y|Z],[X|[Y|Z]]).

inverte(L,L1):- inverte(L,[],L1).
inverte([],L1,L1):-!.
inverte([Y|X],L2,L1):-
insere(Y,L2,L3),
inverte(X,L3,L1).

corrige(L,N,R):-
insere(0,L,L1),
N1 is N+1,
converte(L1,N1,R).

separa(L,N,L1,L3):- separa(L,N,0,[],L1,L3).
separa(L,N,N,L2,L2,L):-!.
separa([X|Y],N,N1,L2,L1,L3):-
N2 is N1+1,
insere(X,L2,L4),
separa(Y,N,N2,L4,L1,L3).

pot2(0,1):-!.
pot2(P,R):-
P1 is P-1,
pot2(P1,R1),
R is 2*R1.

decimal(L,N1,N):-decimal(L,N1,0,N).
decimal([],_,N,N):-!.
decimal([X|Y],N1,S,N):-
pot2(N1,N2),
S1 is (X*N2)+S,
N3 is N1-1,
decimal(Y,N3,S1,N).

octal(L,R1,R2):-
decimal(L,2,N),
insere(N,R1,R2).

converte(L,R):-tam(L,N),converte(L,N,R).

converte(L,N,R):-
N mod 3 =\= 0,
corrige(L,N,R),!.

converte(L,N,R):- N mod 3 =:= 0,inverte(L,L1),converte(L1,N,[],R).

converte([],0,R,R):-!.
converte(L,N,R1,R):-
N mod 3 =:= 0,
separa(L,3,L1,L3),
octal(L1,R1,R2),
N1 is N-3,
converte(L3,N1,R2,R).

/*questao 2: converta de binario para gray, de 3 em 3 bits*/

inseremult([H|[H1|[H2]]],L,R):-%inserçao de 3 elementos diretão
    insere(H2,L,L1),
    insere(H1,L1,L2),
    insere(H,L2,R).

soma(M,N,0):-M=:=N,!.
soma(M,N,1):-M=\=N,!.
gray([H1|[H2|[H3]]],[H1|[R1|[R2]]]):-
    soma(H1,H2,R1),
    soma(H2,H3,R2).

convgray(L,R):- tam(L,N),convgray(L,N,[],R).

convgray(L,N,R1,R):-
N mod 3 =\= 0,
insere(0,L,L1),
N1 is N+1,
convgray(L1,N1,R1,R).

convgray(L,N,R1,R):- inverte(L,L1),convgrayI(L1,N,R1,R).

convgrayI([],0,R,R):-!.
convgrayI(L,N,R1,R):-
    separa(L,3,L1,L2),
    gray(L1,L3),
    inseremult(L3,R1,R2),
    N1 is N-3,
    convgrayI(L2,N1,R2,R).

/*questao 3: converta um numero recebido em uma lista com seus fatores primos*/
%ex: recebe 12, retorna [2,2,3].
%ATENÇÃO: função comando dessa questão é o fatora, e não o primos (primos é auxiliar)

/*
TEOREMA DE MCC: um número qualquer N>0 é composto por primos menores ou iguais que sua própria raiz quadrada, SEMPRE.
*/

inserefim(X,[],[X]):-!.
inserefim(X,[H|L],[H|R]):-
    inserefim(X,L,R).

tira([H|L],H,L).

entre(A, B, A) :- A =< B.
entre(A, B, C) :- A < B, A1 is A+1,
entre(A1, B, C).

raiz(N, R) :- N >= 0, entre(0, N, S),
S*S =< N, (S+1)*(S+1) > N,
R is S,!.

%devolve false = numero composto; devolve true = numero primo.
divisivel([],_):-!.
divisivel([H|L],R):-
    R mod H =\= 0,
    divisivel(L,R).

%primos possiveis de dividir um numero qualquer: qualquer numero primo anterior ou igual à raiz desse numero
primos(2,[2]):-!.
primos(3,[3]):-!.
primos(N,L):- raiz(N,R),R1 is R+1,primos([2],R1,3,L),!.
primos(L,R,R1,L):-R1=:=R+1,!. %a lista para de inserir pelo fato de ter passado da raíz de N (teorema comprova isso)
primos(L1,R,R1,L):-
    divisivel(L1,R1), %verifica se o numero R1 é realmente primo (só ver se ele é ou não divisível por todos aqueles primos já inseridos na lista), se não for ele desce para a linha 137
    inserefim(R1,L1,L2), %já que é primo, insere ele na lista de primos
    R2 is R1+1, %vai pro próximo valor
    primos(L2,R,R2,L). %
primos(L1,R,R1,L):-
    not(divisivel(L1,R1)),
    R2 is R1+1,
    primos(L1,R,R2,L).

fatora(N,[N]):-
N>3,
primos(N,L),
divisivel(L,N),!.

%vai dividindo o número dado com cada um dos elementos da lista de primos (head por head), caso haja um divisível, ele não pula aquele primo que é fator, mas o repete (casos onde um número é fatorado por vários primos iguais)
%caso aquele número (head da lista de primos) já não seja mais divisor do número dado, a função pula aquela cabeça e agora lida so com sua cauda

fatora(1,[1]):-!.
fatora(N,L):- primos(N,L1), fatora(N,L1,[],L),!. /*FUNÇÃO PRINCIPAL*/
fatora(1,_,L,L):-!.
fatora(N,[],L2,L):-
    N1 is N/N,
    inserefim(N,L2,L3),
    fatora(N1,[],L3,L).
fatora(N,L1,L2,L):-
    tira(L1,H,_),
    N mod H =:= 0,
    N1 is N/H,
    inserefim(H,L2,L4),
    fatora(N1,L1,L4,L),!.
fatora(N,L1,L2,L):-
    tira(L1,H,L3),
    fatora(N,L3,L2,L).

/*questao 4: converta uma lista de 2 bits pra decimal e depois pra alfabeto(ou seja, 2 retornos).*/
%é pra treino de casamento de padrões

alf(0,a).
alf(1,b).
alf(2,c).
alf(3,d).
ba(L,N,A):-
decimal(L,1,N),
alf(N,A).

/*questao 5: receba uma lista e devolva outra que é resultado da soma de pares consecutivos da lista dada.*/
%ex: recebe [1,2,3,4] retorna [3,5,7] (3 = 1+2, 5 = 2+3, 7 = 3+4)

pares(L,R):-tam(L,N),inverte(L,L1),separa(L1,1,H,L2),pares(H,N,L2,[],R). %inverto a lista para que quando vier a resposta, ela seja organizada da forma certa (estou inserindo no inicio a cada operação)
pares(_,1,[],R,R):-!.
pares(H,N,[H1|L3],R1,R):-
    J is H+H1,
    insere(J,R1,R2),
    N1 is N-1,
    pares(H1,N1,L3,R2,R).

/*questao 6: receba uma lista e a divida numa lista so com seus pares e uma so com seus impares.(2 retornos)*/

pi(L,P,I):-inverte(L,L1),par(L1,P),impar(L1,I),!.

%varre-se a lista duas vezes, uma pra juntar so os pares e outra so pros impares

par(L,P):-par(L,[],P).
par([],P,P):-!.
par([H|L1],P1,P):-
    H mod 2 =:= 0,
    insere(H,P1,P2),
    par(L1,P2,P).
par([H|L1],P1,P):-
    H mod 2 =\= 0,
    par(L1,P1,P).

impar(L,I):-impar(L,[],I).
impar([],I,I):-!.
impar([H|L1],I1,I):-
    H mod 2 =\= 0,
    insere(H,I1,I2),
    impar(L1,I2,I).
impar([H|L1],I1,I):-
    H mod 2 =:= 0,
    impar(L1,I1,I).

/*questao 7:mmc de dois numeros.*/
%sabemos, pelo que vimos em MCC, que MDC(a,b)*MMC(a,b) = a*b; e podemos usar isso nessa questão.(resultados somente inteiros)

mmc(A,B,R):-
    mdc(A,B,R1),
    R is (A*B)/R1.

/*questao 8:mdc de dois numeros.*/
%existe uma propriedade em MCC antes citada, onde, MDC(a,b)=MDC(b,r), onde a = b.Q + r (r é o resto da divisao), e assim sucessivamente

mdc(A,0,A):-!.

mdc(A,B,R):-
B>0,
A1 is A mod B,
mdc(B,A1,R),!.

mdc(A,B,R):-
B<0,
B1 is B*(-1),
mdc(A,B1,R).

/*questao 9: gere uma lista de 5 elementos pseudoaleatorios, com classe de aleatoriedade(m) escolhida pelo usuario.*/
%como vimos em MCC:
%pseudo-aleatoriedade, fórmula: Xn+1 = (aXn+c) mod m.
%para essa questão, pus c=0(crescendo) e a=1234, Xn=1(crescendo). (padrões)

aleatorio(M,R):-aleatorio(M,1,0,5,0,[],R).

aleatorio(M,X,_,N,N,R,R):-!.

aleatorio(M,X,C,N,N1,R1,R):-
X1 is (1234*X + C) mod M,
insere(X1,R1,R2),
N2 is N1+1,
C1 is C+1,
aleatorio(M,X1,C1,N,N2,R2,R).