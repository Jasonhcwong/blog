#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

void testFunc(char *str, int nTimes, size_t (*testedFunc)(const char *));
void printUsage(char *str);
