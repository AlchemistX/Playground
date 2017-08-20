#!/usr/bin/env python
from multiprocessing import Process, Queue
import sys
from itertools import combinations
from functools import reduce
MIN = -1000000000
MAX = 1000000000
def ncr(n, r):
    return reduce(lambda x, y: x * y[0] / y[1], zip(range(n - r + 1, n+1), range(1, r+1)), 1)

def ratio(pair):
    a = float(abs(pair[0][0] - pair[1][0]))
    b = float(abs(pair[0][1] - pair[1][1]))
    return a/b if b >= a else b/a

def ratiox(aa, bb, cc, dd):
    a = float(abs(aa - cc))
    b = float(abs(bb - dd))
    return a/b if b >= a else b/a

def perimeter(pair):
    a = abs(pair[0][0] - pair[1][0])
    b = abs(pair[0][1] - pair[1][1])
    return 2*(a+b)

def perimeterx(aa, bb, cc, dd):
    a = abs(aa - cc)
    b = abs(bb - dd)
    return 2*(a+b)

def progress(c, rep):
    print((float(c)/float(rep))*100)

def solve1(pointx, pointy):
    srat = 1.0
    sper = perimeter(((MIN, MIN), (MAX, MAX)))
    p, q, t, rep = 0, 1, len(pointx), ncr(len(pointy), 2)
    for c in range(int(rep)):
        if c != 0 and (c % 100000000) == 0:
            progress(c, rep)
        a = float(abs(pointx[p] - pointx[q]))
        b = float(abs(pointy[p] - pointy[q]))
        rat = a/b
        if rat > 1:
            rat = b/a
        if rat <= srat:
            srat = rat
            a = abs(pointx[p] - pointx[q])
            b = abs(pointy[p] - pointy[q])
            sper = 2*(a+b)
        q = q + 1
        if q == t:
            p = p + 1
            q = p + 1

    return sper

def solve0(pointx, pointy):
    srat = 1.0
    sper = perimeter(((MIN, MIN), (MAX, MAX)))
    rep = ncr(len(pointy), 2)
    c = 0
    for p in combinations(zip(pointx, pointy), 2):
        if c != 0 and (c % 100000000) == 0:
            progress(c, rep)
        c = c + 1
        rat = ratio(p)
        if rat <= srat:
            srat = rat
            sper = perimeter(p)
    return sper

def runOneIteration(pointx, pointy, idx, q):
    q.put({idx:solve1(pointx, pointy)})

def main(fn):
    ifile = open(fn, "r")
    ofile = open(fn.replace("in", "out"), "w")

    T = int(ifile.readline())

    procs, outputs = [], [Queue()]*T
    idxp = 0
    for t in range(T):
        pointx = []
        pointy = []
        idx = 0
        for i in range(int(ifile.readline())):
            x, y = map(int, ifile.readline().split())
            pointx.append(x)
            pointy.append(y)
            idx = idx + 1
        proc = Process(target=runOneIteration, args=(pointx, pointy, idxp, outputs[idxp]))
        procs.append(proc)
        proc.start()
        idxp = idxp + 1

    for p in procs:
        p.join()

    out = {}
    for o in outputs:
        out.update(o.get())

    for k in range(T):
        ofile.write(str(out[k]) + "\n")

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print(("Usage : %s input.in")%(sys.argv[0]))
    else:
        main (sys.argv[1])
