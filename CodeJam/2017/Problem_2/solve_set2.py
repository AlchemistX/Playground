#!/usr/bin/env pypy
from multiprocessing import Process, Queue
import sys
from itertools import combinations, izip
MIN = -1000000000
MAX = 1000000000
def ncr(n, r):
    return reduce(lambda x, y: x * y[0] / y[1], izip(xrange(n - r + 1, n+1), xrange(1, r+1)), 1)

def ratio(pair):
    a = float(abs(pair[0][0] - pair[1][0]))
    b = float(abs(pair[0][1] - pair[1][1]))
    return a/b if b >= a else b/a

def perimeter(pair):
    a = abs(pair[0][0] - pair[1][0])
    b = abs(pair[0][1] - pair[1][1])
    return 2*(a+b)

def progress(c, rep):
    print((float(c)/float(rep))*100)

def solve(points):
    srat = 1.0
    sper = perimeter(((MIN,MIN), (MAX,MAX)))
    p, q, t, rep = 0, 1, len(points), ncr(len(points), 2)
    print(len(points), rep)
    for c in xrange(rep): # combinations(points.keys(), 2):
        if (c % 100000000) == 0:
            progress(c, rep)
        pair = (points[p],points[q])
        #rat = ratio(pair)
        q = q + 1
        if q == t:
            p = p + 1
            q = p + 1
        continue
        if rat <= srat:
            if rat == srat:
                a = perimeter(pair)
                if a < sper:
                    srat = rat
                    sper = a
            else:
                srat = rat
                sper = perimeter(pair)


    return sper

def runOneIteration(points, idx, q):
    q.put({idx:solve(points)})

def main(fn):
    ifile = open(fn, "r")
    ofile = open(fn.replace("in", "out"), "w")

    T = int(ifile.readline())

    procs, inputs, outputs = [], [], [Queue()]*T
    for t in range(T):
        points = []
        idx = 0
        for i in range(int(ifile.readline())):
            x, y = map(int, ifile.readline().split())
            points.append((x, y))
            idx = idx + 1
        inputs.append(points)

    idx = 0
    for i in inputs:
        proc = Process(target=runOneIteration, args=(i, idx, outputs[idx]))
        procs.append(proc)
        proc.start()
        idx = idx + 1

    for p in procs:
        p.join()

    out = {}
    for o in outputs:
        out.update(o.get());

    for k in out:
        ofile.write (str(out[k]) + "\n")

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print(("Usage : %s input.in")%(sys.argv[0]))
    else:
        main (sys.argv[1])
