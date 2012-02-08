#include "strlenCommon.h"

size_t betterStrlen(const char *str)
{
  const char *char_ptr;
  const unsigned long int *longword_ptr;
  unsigned long int longword, himagic, lomagic;

  for (char_ptr = str; ((unsigned long int) char_ptr 
                       & (sizeof (longword) - 1)) != 0; 
                       ++char_ptr) {
    if (*char_ptr == '\0') {
      return char_ptr - str;
    }
  }

  longword_ptr = (unsigned long int *) char_ptr;

  himagic = 0x80808080L;
  lomagic = 0x01010101L;
  if (sizeof (longword) > 4) {
    himagic = ((himagic << 16) << 16) | himagic;
    lomagic = ((lomagic << 16) << 16) | lomagic;
  }

  for (;;) {
    longword = *longword_ptr++;

    if (((longword - lomagic) & ~longword & himagic) != 0) {
      const char *cp = (const char *) (longword_ptr - 1);
  
      if (cp[0] == 0) return cp - str;
      if (cp[1] == 0) return cp - str + 1;
      if (cp[2] == 0) return cp - str + 2;
      if (cp[3] == 0) return cp - str + 3;
  
      if (sizeof (longword) > 4) {
        if (cp[4] == 0) return cp - str + 4;
        if (cp[5] == 0) return cp - str + 5;
        if (cp[6] == 0) return cp - str + 6;
        if (cp[7] == 0) return cp - str + 7;
      }
    }
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

//  printf("betterStrlen: ");
  testFunc(testStr, nTimes, betterStrlen);

  return 0;
}

