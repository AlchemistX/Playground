#!/usr/bin/env python
MAX = 500
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
    n = []
    for x, y in a:
        for dx, dy in delta:
            cx, cy = x + dx, y + dy
            if (cx >= 1 and cx <= MAX) and (cy >= 1 and cy <= MAX):
                if (cx, cy) not in c:
                    if check (c, cx, cy):
                        n.append((cx, cy))
    n = list(set(n))
    return n

def step (T):
    if T == 0: return

    coord, adv = [], []
    for i in range(int(input())):
        x, y = map(int, input().split())
        if x <= MAX and y <= MAX:
            coord.append((x, y))
            adv.append((x, y))

    tick = 0
    while 1:
        adv = advance (coord, adv)
        if len(adv) == 0: break;
        tick = tick + 1
        coord.extend(adv)

    print (tick)

    step(T-1)

if __name__ == "__main__":
    step (int(input()))
