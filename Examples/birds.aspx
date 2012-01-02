% stratified program
% birds example

nbb(200000).
b(1..N) :- nbb(N).
o(1..K) :- nbb(N), K = N / 10.
p(K..N) :- nbb(N), K = N - (N / 5).
sp(K..N) :- nbb(N), K = N - (N / 10).

p(X) :- sp(X).
b(X) :- p(X).
b(X) :- o(X).

f(X) :- b(X), not p(X), not o(X).
f(X) :- sp(X).
nf(X) :- p(X), not sp(X).
nf(X) :- o(X).

