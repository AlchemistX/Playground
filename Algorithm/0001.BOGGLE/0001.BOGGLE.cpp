#include <cstdio>
#include <cstring>

const int gnWidth = 7;
const int gnHeight = 7;
const int gnSize = gnWidth*gnHeight;
const int garrCoord[8] = 
{
  -gnWidth - 1,
  -gnWidth - 0,
  -gnWidth + 1,
  - 1,
  + 1,
  +gnWidth - 1,
  +gnWidth + 0,
  +gnWidth + 1
};
char garrBoard[gnSize] = {0,};
char szWord[11] = {0,};
char *gpBegin = garrBoard;
char *gpEnd = garrBoard+gnSize;
char *pStage = garrBoard + gnWidth + 1;

inline char* find(char *pBegin, char *pEnd, char nVal)
{
  while (pBegin != pEnd) {
    if (*pBegin == nVal) return pBegin;
    ++pBegin;
  }

  return pEnd;
}

inline bool step(char *pStart, char *szWord, char nLength, int nCur)
{
  if (nLength == nCur)
    return true;

  for (int i = 0; i < 8; i++) {
    char *pPos = pStart + garrCoord[i];
    if (*pPos == szWord[nCur])
      if (step(pPos, szWord, nLength, nCur+1))
        return true;
  }

  return false;
}

inline bool doBoggleGame(char *szWord)
{
  int nLength = strlen(szWord);
  char *pStart = gpEnd;
  for (int i = nLength; i >= 0; --i)
    if (find(gpBegin, gpEnd, *(szWord+i)) == gpEnd)
      return false;

  pStart = find(gpBegin, gpEnd, *szWord);
  while (pStart != gpEnd) {
    if (step(pStart, szWord, nLength, 1))
      return true;
    pStart = find(pStart+1, gpEnd, *szWord);
  }

  return false;
}

int main (int argc, char** argv)
{
  int nStageCount = 0;
  int nWordCount = 0;
  int i = 0;

  scanf("%d", &nStageCount);
  while (nStageCount--)
  {
    for (i = 0; i < 5; i++)
      scanf("%s", (pStage + i*gnWidth));

    scanf("%d", &nWordCount);
    for (i = 0; i < nWordCount; i++) {
      scanf("%s", szWord);
      printf("%s %s\n", szWord, doBoggleGame(szWord) ? "YES" : "NO");
    }
  }

  return 0;
}
