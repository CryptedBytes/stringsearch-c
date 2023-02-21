#include "stringsearchtest-imprv.h"


const char *FILEPATH = "/Users/bugraguray/Documents/test.txt";
// int elementsInArray = 0;
int dictEntryCount = 0;
int verboseResults = 0; // set to 1 for verbose results

int main()
{

    //elementsInArray = countLinesInFile("/Users/bugraguray/Documents/test.txt");
    // printf("lines in file: %d\n", elementsInArray);
    // //char* stringArray = malloc(sizeof(*stringArray) * elementsInArray);

    char stringArray[255][255];
    // char stringArray[255] = {"hello", "while", "test"};

    dictEntryCount = readDictionaryFile(FILEPATH,stringArray);
    // readExternalFile(FILEPATH,stringArray);

    // printf("%c\n", stringArray[2][0]);
    // printf("%s", stringArray[2]);

    printCharArray(stringArray);
    printf("\n");

    char *query;
    query = malloc(sizeof(char) * 256);
    printf("\nPlease enter search query: > ");
    gets(&query);
    printf("\n");
    searchString(&query, stringArray, dictEntryCount);

    // searchString("berry", stringArray, elementsInArray);
    return 0;
}


void searchString(char *string, char array[255][255], int arrayElementCount)
{

    if (strcmp(string, "*") == 0)
    {
        printCharArray(array);
        return;
    }

    int queryStrSize = sizeOfStr(string);
    int matches = 0;
    float sum = 0;
    float matchCounts[255];

    for (int i = 0; i < arrayElementCount; i++)
    {

        int subsqLtrs = 0;
        int found = 0;
        for (int x = 0; x < sizeOfStr(array[i]); x++)
        {

            if (array[i][x] != string[subsqLtrs])
            {
                // found = 0;
                if (subsqLtrs != 0 && verboseResults)
                {
                    float matchperc = ((subsqLtrs * 1.0f) / (1.0f * sizeOfStr(array[i]))) * 100;
                    float conf = ((subsqLtrs * 1.0f) / (1.0f * queryStrSize)) * 100;
                    // printf("Not matched with word '%s'. Confidence was %0.3f%%\n",array[i], matchperc);
                    printf("Not an exact match with query '%s' with word '%s'. match confidence was %0.3f%% and match ratio %0.3f%%\n", string, array[i], conf, matchperc);
                }

                subsqLtrs = 0;
                continue;
            }
            else
            {
                subsqLtrs++;
                // printf("\nnew algo: search string '%s'. searching in string '%s'. search string length: %d, subsq matched letters: %d", string, array[i], queryStrSize ,subsqLtrs);
                if (subsqLtrs == queryStrSize)
                {
                    found = 1;
                    if (verboseResults)
                    {
                        float matchperc = ((subsqLtrs * 1.0f) / (1.0f * sizeOfStr(array[i]))) * 100;
                        float conf = ((subsqLtrs * 1.0f) / (1.0f * queryStrSize)) * 100;
                        printf("Found exact match with query '%s' with word '%s' with a confidence of %0.3f%% and match ratio %0.3f%%\n", string, array[i], conf, matchperc);
                    }
                    printMatchingResult(array[i]);
                    break;
                }
            }
        }
        /*
            //TODO:the problem is, the array of words are iterated with the queryStrSize so even if a word has for example 10 letters, only first 5 will be checked bcs of this bug.
            for(int j = 0; j < queryStrSize; j++){
               if(array[i][j] != string[j]){
                   if(matches != queryStrSize) matches = 0; //TODO: not sure
                   //printf("\niterating ' %c ' of %s size of this str: %d\n ", array[i][j], array[i], queryStrSize);
                   continue;
                }
                else matches++;
            }
            //printf("\nsearch string '%s' has a match count of %d with the string '%s'", string, matches, array[i]);
            matchCounts[i] = matches;
            sum += matches;
            matches = 0;
            */
    }

    /*
        for (int i = 0; i < arrayElementCount; i++){
            //float percentage = ((matchCounts[i] / sum) *100.0);
            float percentage = ((matchCounts[i] / sizeOfStr(array[i])) * 100.0);
           // printf("\nsearch string match with line %d: %.2f%%", i, percentage);
        }
        */
}

void printMatchingResult(char *string)
{
    char *token = strtok(string, "@@%%!!**");
    printf("Match: %s\n", token);
}


// void printMatchingResult(char *string)
// {
//     int i = 0;
//     int tokenHit = 0;
//     char *result;
//     result = malloc(sizeof(char) * strlen(string));
//     while (string[i] != '\0' && !tokenHit)
//     {
//         char c = string[i];
//         if (c == '@')
//         {
//             char *token = malloc(sizeof(char) * strlen(string));
//             strcpy(token, string);

//             if (verboseResults)
//                 printf("\nstrlen(token)= %d\n", strlen(&token[i])); // check if the string has enough chars to fit the token
//             if (strlen(&token[i]) < 8)
//                 break;           // string is too short to contain a token, terminate
//             token[i + 8] = '\0'; // extract possible token
//             char *temp = &token[i];
//             token = temp;

//             // string[i+8] = '\0';
//             if (verboseResults)
//                 printf("possible token match: '%s'\n", token);
//             if (strcmp(token, "@@%%!!**") == 0)
//                 {
//                 if (verboseResults)
//                     printf("Exact token match found in word: '%s'. start index: %d.\n", string, i);
//                 //result[i] = '\0';
//                 break;
//             }
//         }
//         result[i] = string[i];
//         ++i;
//     }
//     result[i] = '\0';
//     printf("Match: %s\n", result);
// }

void printCharArray(char array[255][255])
{
    printf("\nprinting all array elements:\n");
    for (int i = 0; i < dictEntryCount; i++)
    {
        if (i == dictEntryCount - 1)
            printf("{%s}", array[i]);
        else
            printf("{%s}, ", array[i]);
    }
}

int sizeOfStr(char *strPtr)
{

    char *tempPtr = strPtr;
    int len = 0;
    while (*tempPtr != '\0')
    {
        tempPtr += 1;
        len++;
    }
    return len;
}

int readDictionaryFile(char *filePath, char ptr[255][255])
{
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int i = 0;
    int elementCount = 0;

    fp = fopen(filePath, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    printf("Indexing dictionary file...\n");

    while ((read = getline(&line, &len, fp)) != -1)
    {
        elementCount++;
        // printf("Retrieved line of length %zu:\n", read);
        // printf("%s", line);
        // printf("\nnew array item: %s", line);
        // stringArray[i] = line;

        int containsWhiteSpace = 0;
        char *capitals;
        capitals = (char *)malloc(sizeof(char) * 1024);
        *capitals = '\0';
        for (int j = 0; j < read; j++)
        {
            ptr[i][j] = line[j];
            if (line[j] == ' ')
            {
                // strcat(capitals, &line[j - 1]);
                strncat(capitals, &line[j + 1], 1);
                if (verboseResults)
                    printf("Found space\n");
                containsWhiteSpace = 1;
            }

            // toArray[i] = line;
        }

        ptr[i][strcspn(ptr[i], "\n")] = 0; // remove the trailing new lines from strings

        if (containsWhiteSpace)
        {
            if (verboseResults)
                printf("********\n");
            if (verboseResults)
                printf("ptr i before adding: %s\n", ptr[i]);
            strcat(ptr[i], "@@%%!!**");
            strncat(ptr[i], &line[0], 1);
            strcat(ptr[i], capitals);
            if (verboseResults)
                printf("capitals: %s\n", capitals);
            if (verboseResults)
                printf("ptr i after adding: %s\n", ptr[i]);
            containsWhiteSpace = 0;
            if (verboseResults)
                printf("********\n");
        }
        i++;
    }

    // removing newlines
    for (int j = 0; j < i; j++)
    {
        for (int k = 0; k < 255; k++)
        {
            if (ptr[j][k] == '\n')
            {
                ptr[j][k] = '\0';
            }
        }
    }

    printf("Dictionary index complete. Indexed %d entries.\n", elementCount);

    return elementCount;
}

int countLinesInFile(char *filePath)
{
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int i = 0;

    fp = fopen("/Users/bugraguray/Documents/test.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1)
    {
        i++;
    }
    return i;
}

void funTestWithPointers()
{

    char *stringptr = "bugra";
    char stringarr[] = "bugra";
    printf("%s\n", stringptr);
    printf("length: %d\n", strlen(stringptr));
    stringptr = "bugraggg";
    printf("%s\n", stringptr);
    printf("length: %d\n", strlen(stringptr));
    stringptr = "bugra";
    printf("length of input str is: %i\n", sizeOfStr(stringptr));

    printf("pointer manipulation below:\n\n");
    stringptr += 1;
    printf("%s", stringptr);
}