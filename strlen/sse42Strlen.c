#include <nmmintrin.h>

#include "strlenCommon.h"

size_t sse42Strlen(const char *str)
{
  __m128i zero = _mm_setzero_si128(); int offset = 0;
  __m128i *ptr = (__m128i *) str;

  for(;;) {
    offset = _mm_cmpistri(zero, _mm_loadu_si128(ptr++), _SIDD_CMP_EQUAL_EACH);
    if (offset != 16) {
      break;
    }
    offset = _mm_cmpistri(zero, _mm_loadu_si128(ptr++), _SIDD_CMP_EQUAL_EACH);
    if (offset != 16) {
      break;
    }
    offset = _mm_cmpistri(zero, _mm_loadu_si128(ptr++), _SIDD_CMP_EQUAL_EACH);
    if (offset != 16) {
      break;
    }
    offset = _mm_cmpistri(zero, _mm_loadu_si128(ptr++), _SIDD_CMP_EQUAL_EACH);
    if (offset != 16) {
      break;
    }
  }
  return (char *) ptr - 16 - str + offset;
}


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

//  printf("%ld\n", sse42Strlen(testStr));
//  printf("%ld\n", strlen(testStr));
//  printf("sse42Strlen:  ");
  testFunc(size, nTimes, sse42Strlen);

  return 0;
}

