#include "strlenCommon.h"

size_t naiveStrlen(const char *str)
{
  const char *p = str;

  while(*p) p++;

  return p-str;
}


int main(int argc, char **argv)
{
  char *testStr;

  int nTimes = 1000000;
  int size = 100;

  int i;

  srandom(19999);
  testStr = (char *) malloc(size);
  for(i = 0; i < size -1; ++i) {
    testStr[i] = 1 + random()%100;
  }
  testStr[size-1] = '\0';

  testFunc(testStr, nTimes,naiveStrlen);

  return 0;
}

