#!/usr/bin/env python3
from multiprocessing import Process, Queue
import sys

def sum_edges(G):
    s = 0
    for i in range(len(G) - 1):
        s = s + (G[i+1] - G[i])
    return s

def sum_partial_edges(P, G):
    F = list(filter(lambda x : x <= P[0], G))
    F.append(P[0])
    s = sum_edges(F)

    for i in range(len(P) - 1):
        F = list(filter(lambda x : P[i] < x and x < P[i+1], G))
        if len(F) == 0:
            continue
        elif len(F) == 1:
            s = s + min(F[0] - P[i], P[i+1] - F[0])
        else:
            K = []
            for c in range(len(F) - 1):
                p = (F[c] - P[i]) if c == 0 else (F[c] - F[c-1])
                n = F[c+1] - F[c]
                if p < n: s = s + p
                else: K.append(n)
            K.append(P[i+1] - F[-1])
            K.sort()
            K.pop(-1)
            s = s + sum(K)
    F = list(filter(lambda x : x >= P[-1], G))
    F.append(P[-1])
    s = s + sum_edges(F)

    return s

def solve(R, B, P):
    s = sum_edges(P)
    if len(R) == 0:
        s = s + sum_partial_edges(P, B)
    elif len(B) == 0:
        s = s + sum_partial_edges(P, R)
    return s

def runOneIteration(R, B, P, idx, q):
    q.put({idx:solve(R, B, P)})

def main(fn):
    ifile = open(fn, "r")
    ofile = open(fn.replace("in", "out"), "w")

    T = int(ifile.readline())

    procs, inputs, outputs = [], [], [Queue()]*T
    idx = 0
    for t in range(T):
        L, M, N = map(int, ifile.readline().split())
        R, B, P = [], [], []
        for i in range(L): R.append(int(ifile.readline()))
        for i in range(M): B.append(int(ifile.readline()))
        for i in range(N): P.append(int(ifile.readline()))
        R.sort()
        B.sort()
        P.sort()
        proc = Process(target=runOneIteration, args=(R, B, P, idx, outputs[idx]))
        procs.append(proc)
        proc.start()
        idx = idx + 1

    for p in procs:
        p.join()

    out = {}
    for o in outputs:
        out.update(o.get());

    for k in range(T):
        ofile.write (str(out[k]) + "\n")

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print(("Usage : %s input.in")%(sys.argv[0]))
    else:
        main (sys.argv[1])
