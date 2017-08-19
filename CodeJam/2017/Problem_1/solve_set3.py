#!/usr/bin/env python3
from multiprocessing import Process, Queue
import sys
MAX = 1000000000
delta = [(-1, 0), (0, -1), (1, 0), (0, 1)]

def check (c, x, y):
    cnt = 0
    for dx, dy in delta:
        cx, cy = x + dx, y + dy
        if (cx >= 1 and cx <= MAX) and (cy >= 1 and cy <= MAX):
            if (cx, cy) in c:
                cnt = cnt + 1
    return True if cnt > 1 else False

def advance (c, a):
    n = set()
    for x, y in a:
        for dx, dy in delta:
            cx, cy = x + dx, y + dy
            if (cx >= 1 and cx <= MAX) and (cy >= 1 and cy <= MAX):
                if (cx, cy) not in c:
                    if check (c, cx, cy):
                        n.add((cx, cy))
    return n

def runOneIteration(coord, idx, q):
    tick = 0
    adv = set(coord)
    while 1:
        adv = advance (coord, adv)
        if len(adv) == 0: break;
        tick = tick + 1
        coord.update(adv)
    q.put({idx:tick})

def main (fn):
    ifile = open(fn, "r")
    ofile = open(fn.replace("in", "out"), "w")

    T = int(ifile.readline())

    procs = []
    outputs = [Queue()] * T
    coords = []
    for t in range(T):
        coord = set()
        for i in range(int(ifile.readline())):
            x, y = map(int, ifile.readline().split())
            if x <= MAX and y <= MAX:
                coord.add((x, y))
        coords.append(coord)

    idx = 0
    for c in coords:
        proc = Process(target=runOneIteration, args=(c, idx, outputs[idx]))
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
