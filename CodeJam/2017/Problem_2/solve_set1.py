#!/usr/bin/env python3
from multiprocessing import Process, Queue
import sys
from itertools import combinations

def ratio(pair):
    a = float(abs(pair[0][0] - pair[1][0]))
    b = float(abs(pair[0][1] - pair[1][1]))
    return a/b if b >= a else b/a

def perimeter(pair):
    a = abs(pair[0][0] - pair[1][0])
    b = abs(pair[0][1] - pair[1][1])
    return 2*(a+b)

def solve(points):
    srat = 1.0
    sper = 0
    for p in combinations(points, 2):
        rat = ratio(p)
        if rat <= srat:
            srat = rat
            sper = perimeter(p)
    return sper

def runOneIteration(points, idx, q):
    q.put({idx:solve(points)})

def main(fn):
    ifile = open(fn, "r")
    ofile = open(fn.replace("in", "out"), "w")

    T = int(ifile.readline())

    procs, inputs, outputs = [], [], [Queue()]*T
    idx = 0
    for t in range(T):
        points = []
        for i in range(int(ifile.readline())):
            x, y = map(int, ifile.readline().split())
            points.append((x, y))
        proc = Process(target=runOneIteration, args=(points, idx, outputs[idx]))
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
