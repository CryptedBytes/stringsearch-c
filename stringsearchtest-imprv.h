#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int sizeOfStr(char *strPtr);
int readDictionaryFile(char *filePath, char ptr[255][255]);
int countLinesInFile(char *filePath);
void funTestWithPointers();
void printCharArray(char array[255][255]);
void searchString(char *string, char array[255][255], int arrayElementCount);
void printMatchingResult(char *string);