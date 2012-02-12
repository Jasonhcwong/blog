#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

void testFunc(int size, int nTimes, size_t (*testedFunc)(const char *));
void printUsage(char *str);
