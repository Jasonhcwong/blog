#include <nmmintrin.h>

#include "strlenCommon.h"

size_t sse42Strlen(const char *str)
{
  __m128i zero = _mm_setzero_si128(); int offset = 0;
  __m128i *ptr = (__m128i *) str;

  do {
    offset = _mm_cmpistri(zero, _mm_loadu_si128(ptr), _SIDD_CMP_EQUAL_EACH);
    ptr++;
  } while(offset == 16);

  return (char *) ptr - 16 - str + offset;
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

  testFunc(testStr, nTimes,sse42Strlen);

  return 0;
}

