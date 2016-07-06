#!/usr/bin/env python
lstCoord = [-8, -7, -6, -1, +1, 6, 7, 8]


def step(strBoard, nStart, strWord, nLength, nCur):
    if nCur == nLength:
        return True

    for delta in lstCoord:
        idx = nStart + delta
        if strBoard[idx] == strWord[nCur]:
            if step(strBoard, idx, strWord, nLength, nCur+1) is True:
                return True

    return False


def doBoggleGame(strBoard, strWord):
    if set(strWord) - set(strBoard):
        print "%s NO" % (strWord)
        return

    idx = strBoard.find(strWord[0])
    while (idx > 0):
        if step(strBoard, idx, strWord, len(strWord), 1) is True:
            print "%s YES" % (strWord)
            return
        idx = strBoard.find(strWord[0], idx+1)

    print "%s NO" % (strWord)


def main():
    strPadding = "0000000"
    nStageCount = raw_input()
    for _ in xrange(0, int(nStageCount)):
        strBoard = ""
        strBoard += strPadding
        for n in xrange(0, 5):
            strBoard += '0'
            strBoard += raw_input()
            strBoard += '0'
        strBoard += strPadding

        for _ in xrange(0, int(raw_input())):
            doBoggleGame(strBoard, raw_input())

if __name__ == "__main__":
    main()
