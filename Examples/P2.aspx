p(1..400).

a :- not b.
b :- not a.

:- a.

pa(X) :- a, p(X).
pb(X) :- b, p(X).

aa(X,Y) :- pa(X), pa(Y).
bb(X,Y) :- pb(X), pb(Y).

%% for Lparse
% aa(X,Y) :- p(X), p(Y), pa(X), pa(Y).
% bb(X,Y) :- p(X), p(Y), pb(X), pb(Y).
