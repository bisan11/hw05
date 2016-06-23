#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "dataStructure.h"
#include "fileInfo.h"
#include "options.h"
#include "posixFuncs.h"



void printList(Entry** data, int length)
{
    for (int i=0; i<length; i++)
    {
        printf("%s\n", (*data)[i].path);
    }
}

void printHelp()
{

    printf("Usage: myfind [path] [-n name] [-e ext] [-s sort] [-u user] [-a] [-h] \n\
           -a search for hidden files and in hidden directories \n\
           -h prints this help message");
}

void dealloc(Entry** data,
             int index,
             char** name,
             char** ext,
             char**username,
             char** sort,
             char** path)
{

    for (int i=0; i<index; i++)
    {
        free((*data)[i].path);
    }
    free(*data);
    if (*name)
    {
        free(*name);
    }
    if (*ext)
    {
        free(*ext);
    }
    if (*username)
    {
        free(*username);
    }
    if (*sort)
    {
        free(*sort);
    }
    free(*path);
}

int main(int argc, char** argv)
{
    char *path=NULL;
    char *name=NULL;
    char *ext=NULL;
    char *username=NULL;
    char *sort=NULL;
    int hidden = 0;
    int retVal = parseArgs(argc, argv, &path, &name, &ext, &username, &hidden, &sort);
    int length = 128;
    int index = 0;
    Entry *data = malloc(length*sizeof(Entry));
    switch(retVal)
    {
    case 1:
        printHelp();
        dealloc(&data, index, &name, &ext, &username, &sort, &path);
        return 0;
    case 2:
        fprintf(stderr,"No data supplied to argument, run with [-h] for usage.\n");
        dealloc(&data, index, &name, &ext, &username, &sort, &path);
        return 1;
    case 3:
        fprintf(stderr,"Invalid switch used, run with [-h] for usage.\n");
        dealloc(&data, index, &name, &ext, &username, &sort, &path);
        return 2;
    }

    if (!path)
    {
        path = malloc(2);
        strcpy(path, ".");
    }



    if (loadList(&data, length, &index, path, name, ext, username, hidden))
    {
        fprintf(stderr, "No path found or access denied, bye.\n");
        dealloc(&data, index, &name, &ext, &username, &sort, &path);
        return 3;
    }
    sortList(&data, index, sort);
    printList(&data, index);
    dealloc(&data, index, &name, &ext, &username, &sort, &path);
    return 0;
}
