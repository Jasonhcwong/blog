#include <emmintrin.h>

#include "strlenCommon.h"

size_t sse2Strlen(const char *str)
{
  __m128i zero = _mm_setzero_si128(); int offset = 0;
  __m128i xmm1;
  const char *char_ptr;
  int mask;

  for (char_ptr = str; ((unsigned long int) char_ptr 
                       & (sizeof (__m128i) - 1)) != 0; 
                       ++char_ptr) {
    if (*char_ptr == '\0') {
      return char_ptr - str;
    }
  }

  for(;;) {
    xmm1 = _mm_cmpeq_epi8(_mm_load_si128((__m128i *) char_ptr), zero);
    if ((mask = _mm_movemask_epi8(xmm1)) != 0) {
	return (char *) (char_ptr) + __builtin_ctz(mask) - str;
    }
    char_ptr += 16;
    
    xmm1 = _mm_cmpeq_epi8(_mm_load_si128((__m128i *) char_ptr), zero);
    if ((mask = _mm_movemask_epi8(xmm1)) != 0) {
	return (char *) (char_ptr) + __builtin_ctz(mask) - str;
    }
    char_ptr += 16;

    xmm1 = _mm_cmpeq_epi8(_mm_load_si128((__m128i *) char_ptr), zero);
    if ((mask = _mm_movemask_epi8(xmm1)) != 0) {
	return (char *) (char_ptr) + __builtin_ctz(mask) - str;
    }
    char_ptr += 16;

    xmm1 = _mm_cmpeq_epi8(_mm_load_si128((__m128i *) char_ptr), zero);
    if ((mask = _mm_movemask_epi8(xmm1)) != 0) {
	return (char *) (char_ptr) + __builtin_ctz(mask) - str;
    }
    char_ptr += 16;
  }
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

//  printf("%ld\n", sse2Strlen(testStr));
//  printf("%ld\n", strlen(testStr));
//  printf("sse2Strlen:  ");
  testFunc(size, nTimes, sse2Strlen);

  return 0;
}

