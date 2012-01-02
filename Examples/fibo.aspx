%% Fibonacci

fibo(0,0).
fibo(1,1).

tocomputefibo(10).

fibo(N+2,F1+F) :- fibo(N,F), fibo(N+1,F1), tocomputefibo(K), K > N+1.

%% for Lparse and Gringo
%fibo(N2,F2) :- p(N), p(F), p(F1), fibo(N,F), N1=N+1, fibo(N1,F1), tocomputefibo(K), K>N1,  N2=N1+1, F2=F1+F.

