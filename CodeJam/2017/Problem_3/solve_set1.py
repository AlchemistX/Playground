#!/usr/bin/env python3
from multiprocessing import Process, Queue
import sys
from itertools import combinations

def solve(R, B, P):
    r, b = 0, 0
    if len(P) == 0:
        for i in range(len(R) - 1):
            r = r + (R[i+1] - R[i])
        for i in range(len(B) - 1):
            b = b + (B[i+1] - B[i])
    else:
        pass
    return r + b 

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
        for i in range(L):
            R.append(int(ifile.readline()))
        for i in range(M):
            B.append(int(ifile.readline()))
        for i in range(N):
            P.append(int(ifile.readline()))
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
