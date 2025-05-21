%grafo já processado (sem cavalos nem posições de perigo) do exemplo do OnlineJudge
v((0,'.'),[4],1):-!.
v((1,'.'),[5],1):-!.
v((2,'A'),[5],1):-!.
v((3,'.'),[4],1):-!.
v((4,'.'),[0,3],0):-!.
v((5,'.'),[1,2,6,7],4):-!.
v((6,'.'),[5,9],2):-!.
v((7,'.'),[5,10],2):-!.
v((8,'.'),[11],1):-!.
v((9,'.'),[6,11,12],3):-!.
v((10,'.'),[7,13,14],3):-!.
v((11,'.'),[8,9],2):-!.
v((12,'B'),[9,13],2):-!.
v((13,'.'),[10,12,14],3):-!.
v((14,'.'),[10,13],2):-!.

adjNotMarked(_,[],[]):-!.

adjNotMarked(V,[H|T],[H|L]):-
not(isMarked(H,V)),
adjNotMarked(V,T,L),!.

adjNotMarked(V,[H|T],L):-
isMarked(H,V),
adjNotMarked(V,T,L),!.

%só insere na fila os elementos não visitados
insertAllQueue([],V,L,L):-!.
insertAllQueue([H|T],V,L,R):-
not(isMarked(H,V)),
insertQueue(H,L,L1),
insertAllQueue(T,V,L1,R),!.

insertAllQueue([H|T],V,L,R):-
isMarked(H,V),
insertAllQueue(T,V,L,R),!.

insertQueue(X,[],[X]):-!.
insertQueue(X,[H|T],[H|R]):-
insertQueue(X,T,R),!.

g_At(N,L,R):- g_At(N,0,L,R),!.
g_At(_,_,[],-1):-!.
g_At(N,N,[H|T],H):-!.
g_At(N,NP,[H|T],R):-
N>NP,
NP1 is NP+1,
g_At(N,NP1,T,R1),
R is R1,!.

markAllV(N,V,VR):- markAllV(0,N,V,VR),!. %marcar todos os vértices que foram postos na lista N

markAllV(_,_,[],[]):-!. %lista de vertices do grafo acabou

markAllV(A,[],[H|T],[H|L]):- %lista de vertices a marcar acabou
markAllV(A,[],T,L),!.

markAllV(NP,[A|B],[H|T],[H|L]):- 
NP=\=A,
NP1 is NP+1,
markAllV(NP1,[A|B],T,L),!.
markAllV(NP,[A|B],[H|T],[1|L]):-
NP=:=A,
NP1 is NP+1,
markAllV(NP1,B,T,L),!.

markAllD(VI,N,M,V,VR):- markAllD(VI,0,N,M,V,VR),!.

markAllD(_,_,_,_,[],[]):-!.

markAllD(V,A,[],M,[H|T],[H|L]):-
markAllD(V,A,[],M,T,L),!.

markAllD(V,NP,[A|B],M,[H|T],[H|L]):-
NP=\=A,
NP1 is NP+1,
markAllD(V,NP1,[A|B],M,T,L),!.

markAllD(V,NP,[A|B],M,[H|T],[M|L]):-
NP=:=A,
NP1 is NP+1,
markAllD(V,NP1,B,M,T,L),!.

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

isMarked(N,L):- isMarked(N,0,L),!.
isMarked(_,_,[]):-fail.
isMarked(N,NP,[H|T]):-%pode retornar falso se H não for 1 (não foi visitado)
N=:=NP,
H=:=1,!.
isMarked(N,NP,[H|T]):-
N>NP,
NP1 is NP+1,
isMarked(N,NP1,T),!.

%BFS/4 no formato: (fila de vertices (já começando no reino A), vetor de visitação, vetor de pesos, resultado), pensando que cada aresta tem peso 1
bfs([],V,D,D):-!.

bfs([H|T],V,D,R):-
v((H,_),A,_), %pega os adjacentes
markAllV(A,V,V1),
g_At(H,D,M),
M1 is M+1,
adjNotMarked(V,A,A1),
markAllD(V,A1,M1,D,D1),
insertAllQueue(A,V,T,T1),
bfs(T1,V1,D1,R),!.

generateBFS() :- bfs([2], [0,0,1,0,0,0,0,0,0,0,0,0,0,0,0], [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0], R), g_At(12,R,M), writeln('menor distância do reino A ao B:'), write(M), !.