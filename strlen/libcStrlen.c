#include "strlenCommon.h"

int main(int argc, char **argv)
{
  char *testStr;
  int nTimes = 0;
  int size = 0;
  int i = 0;

  if (argc < 3) {
    printUsage(argv[0]);
    return 0;
  }

  nTimes = atoi(argv[1]);
  size = atoi(argv[2]);

  srandom(19999);
  testStr = (char *) malloc(size);
  for(i = 0; i < size -1; ++i) {
    testStr[i] = 1 + random()%100;
  }
  testStr[size-1] = '\0';

//  printf("libcStrlen:   ");
  testFunc(testStr, nTimes, strlen);

  return 0;
}

