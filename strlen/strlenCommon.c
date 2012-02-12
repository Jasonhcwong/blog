#include "strlenCommon.h"

void testFunc(int size, int nTimes, size_t (*testedFunc)(const char *))
{
  struct timeval startTime;
  struct timeval endTime;
  struct timespec startTimeNano;
  struct timespec endTimeNano;
  long int elapsedTime = 0;
  char *testStr;
  int i, j, k;
  

  srandom(19999);
  testStr = (char *) malloc(size);
  testStr[size-1] = '\0';
//  gettimeofday(&startTime, NULL);
  for(i = 0; i < nTimes; ++i) {
    for(j = 0; j < size -1; ++j) {
      testStr[j] = 1 + random()%100;
    }
    clock_gettime(CLOCK_REALTIME, &startTimeNano);
    for(k = 0; k < 100; ++k) {
      testedFunc(testStr);
    }
    clock_gettime(CLOCK_REALTIME, &endTimeNano);
    elapsedTime = ((endTimeNano.tv_sec - startTimeNano.tv_sec) * 1000 * 1000 * 1000 + (endTimeNano.tv_nsec - startTimeNano.tv_nsec));
  }
//  gettimeofday(&endTime, NULL);

//  printf("time elapsed: %ld\n", (endTime.tv_sec - startTime.tv_sec) * 1000 * 1000 + (endTime.tv_usec - startTime.tv_usec));
  printf("%ld", elapsedTime);
};

void printUsage(char *str)
{
  printf("Usage %s nTimes size\n", str);
}
