#include "strlenCommon.h"

void testFunc(char *str, int nTimes, size_t (*testedFunc)(const char *))
{
  struct timeval startTime;
  struct timeval endTime;
  int i;

  gettimeofday(&startTime, NULL);
  for(i = 0; i < nTimes; ++i) {
    testedFunc(str);
  }
  gettimeofday(&endTime, NULL);

  printf("time elapsed: %ld\n", (endTime.tv_sec - startTime.tv_sec) * 1000 * 1000 + (endTime.tv_usec - startTime.tv_usec));
};
