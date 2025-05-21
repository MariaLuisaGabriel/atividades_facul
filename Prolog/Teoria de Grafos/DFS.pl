v(0,-10):-!.
v(1,20):-!.
v(2,-10):-!.
v(3,40):-!.
v(4,-30):-!.
v(5,-10):-!.
a(0,1):-!.
a(1,2):-!.
a(2,0):-!.
a(3,4):-!.
a(4,5):-!.
a(5,3):-!.

markV(N,V,VR):- markV(0,N,V,VR),!.
markV(_,_,[],[]):-!.
markV(NP,N,[H|T],[H|L]):-
NP=\=N,
NP1 is NP+1,
markV(NP1,N,T,L),!.
markV(NP,N,[H|T],[1|L]):-
NP=:=N,
NP1 is NP+1,
markV(NP1,N,T,L),!.

g_At(N,L,R):- g_At(N,0,L,R),!.
g_At(_,_,[],-1):-!.
g_At(N,NP,[(A,B)|T],R):-
N=:=NP,
R is A,!.
g_At(N,NP,[H|T],R):-
N>NP,
NP1 is NP+1,
g_At(N,NP1,T,R1),
R is R1,!.

g_AtV(N,L,R):- g_AtV(N,0,L,R),!.
g_AtV(_,_,[],-1):-!.
g_AtV(N,NP,[(A,B)|T],R):-
N=:=NP,
R is B,!.
g_AtV(N,NP,[H|T],R):-
N>NP,
NP1 is NP+1,
g_AtV(N,NP1,T,R1),
R is R1,!.

isMarked(N,L):- isMarked(N,0,L),!.
isMarked(_,_,[]):-fail.
isMarked(N,NP,[H|T]):-%pode retornar falso se H não for 1 (não foi visitado)
N=:=NP,
H=:=1,!.
isMarked(N,NP,[H|T]):-
N>NP,
NP1 is NP+1,
isMarked(N,NP1,T),!.

verifyVisitados([],0):-!.
verifyVisitados([H|T],N):-
H=:=1,
verifyVisitados(T,N1),
N is N1 + 1,!.
verifyVisitados([H|T],N):-
H=:=0,
verifyVisitados(T,N1),
N is N1,!.

pushBack([],N,M,[(N,M)]):-!.
pushBack([H|T],N,M,[H|L]):-
pushBack(T,N,M,L),!.

pushBack([],N,[N]):-!.
pushBack([H|T],N,[H|L]):-
pushBack(T,N,L),!.

showT([]):-!.
showT([(A,B)|T]):-
writeln(A-B),
showT(T),!.

showL([]):-!.
showL([H|T]):-
writeln(H),
showL(T),!.

solucao(X):-
X=:=0,writeln("POSSIBLE"),!.

solucao(_):-
writeln("IMPOSSIBLE"),!.

montaGrafo():-
montaGrafo(0,N1,[],R),
geraArrayVisitados(N1,[],R1),
/*showL(R1),*/
/*showT(R),*/
loopDfs(0,N1,R1,R,0,X),
solucao(X),!.

montaGrafo(6,6,R,R):-!.

montaGrafo(N,E,L,R):-
v(N,P),
a(N,V),
pushBack(L,P,V,L1),
N1 is N+1,
montaGrafo(N1,E,L1,R),!.

geraArrayVisitados(0, R, R):-!.
geraArrayVisitados(N, L, R):-
pushBack(L,0,L1),
N1 is N-1,
geraArrayVisitados(N1, L1, R),!.

loopDfs(_,S,V,G,R,R):-
verifyVisitados(V,N),
S=:=N,!.

loopDfs(A,S,V,G,R,R):-
S=:=A,!.

loopDfs(A,S,V,G,0,R):-
A<S,
verifyVisitados(V,N),
S>N,
dfs(G,A,V,V1,0,R1),
A1 is A+1,
loopDfs(A1,S,V1,G,R1,R),!.

loopDfs(_,_,_,_,_,1):-!.

dfs(G,A,V,V1,R,RR):-
not(isMarked(A,V)),
markV(A,V,V2),
g_At(A,G,RV),
g_AtV(A,G,RG),
R1 is R + RV,
dfs(G,RG,V2,V1,R1,RR),!.

dfs(_,_,V,V,R,R):-!.