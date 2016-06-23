#pragma once


typedef struct _entry
{

    char* path;
    long long size;
} Entry;


int reallocData(char** data, int size);
int reallocEntries(Entry** data, int size);
int cmpName (const void * a, const void * b);
int cmpExtRaw (const void * a, const void * b);
int cmpExt (const void * a, const void * b);
int cmpSizeRaw (const void * a, const void * b);
int cmpSize(const void * a, const void * b);
int cmpPath (const void * a, const void * b);
int cmpExtSize (const void * a, const void * b);
int cmpSizeExt (const void * a, const void * b);
void sortList(Entry** data, int length, char* sort);
