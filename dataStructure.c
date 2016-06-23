#include "dataStructure.h"

#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <libgen.h>


int reallocEntries(Entry **data, int size) {

    Entry *newData = realloc(*data, sizeof(Entry) * size * 2);
    if (!newData) {
        return 1;
    }
    *data = newData;
    return 0;
}


int cmpName(const void *a, const void *b) {

    Entry ea = *(Entry *) a;
    Entry eb = *(Entry *) b;
    char *aname = basename(ea.path);
    char *bname = basename(eb.path);

    int retVal = strcasecmp(aname, bname);
    if (retVal != 0) {
        return retVal;
    }
    return strcmp(ea.path, eb.path);
}

/*
    Comparator: extensions [helper]
 */
int cmpExtRaw(const void *a, const void *b) {
    Entry ea = *(Entry *) a;
    Entry eb = *(Entry *) b;
    char *aname = basename(ea.path);
    char *bname = basename(eb.path);
    //Detect name boundaries
    int stop = -1;
    char presence = 0;
    for (int i = 0; i < (int) strlen(aname); i++) {
        if (aname[i] == '.') {
            stop = i;
        }
    }
    if (stop > 0 && stop < (int) strlen(aname) - 1) {
        presence = 1;
    }
    //Set the results for a
    char acopy[strlen(aname) - stop];
    if (presence == 1) {
        memcpy(acopy, &aname[stop + 1], strlen(aname) - stop - 1);
        acopy[strlen(aname) - stop - 1] = 0;
    }
    stop = -1; //Reset flag
    for (int i = 0; i < (int) strlen(bname); i++) {
        if (bname[i] == '.') {
            stop = i;
        }
    }
    if (stop > 0 && stop < (int) strlen(bname) - 1) {
        presence += 2;
    }
    //Set the results for b
    char bcopy[strlen(bname) - stop];
    if (presence >= 2) {
        memcpy(bcopy, &bname[stop + 1], strlen(bname) - stop - 1);
        bcopy[strlen(bname) - stop - 1] = 0;
    }
    //Evaluate
    if (presence == 0) {
        return 0;
    }
    if (presence == 1) {
        return 1;
    }
    if (presence == 2) {
        return -1;
    }
    return strcmp(acopy, bcopy);
}

/*
    Comparator: extensions > names
 */
int cmpExt(const void *a, const void *b) {
    int retVal = cmpExtRaw(a, b);
    if (retVal != 0) {
        return retVal;
    }
    return cmpName(a, b);
}

/*
    Comparator: sizes [helper]
 */
int cmpSizeRaw(const void *a, const void *b) {
    Entry ea = *(Entry *) a;
    Entry eb = *(Entry *) b;
    long long asize = ea.size;
    long long bsize = eb.size;
    if (asize > bsize) {
        return -1;
    }
    if (asize < bsize) {
        return 1;
    }
    return 0;
}

/*
    Comparator: sizes > names
 */
int cmpSize(const void *a, const void *b) {
    int retVal = cmpSizeRaw(a, b);
    if (retVal != 0) {
        return retVal;
    }
    return cmpName(a, b);
}

/*
    Comparator: paths > names
 */
int cmpPath(const void *a, const void *b) {
    Entry ea = *(Entry *) a;
    Entry eb = *(Entry *) b;
    int retVal = strcmp(ea.path, eb.path);
    if (retVal != 0) {
        return retVal;
    }
    return cmpName(a, b);
}

/*
    Comparator: extensions > sizes
 */
int cmpExtSize(const void *a, const void *b) {
    int retVal = cmpExtRaw(a, b);
    if (retVal != 0) {
        return retVal;
    }
    return cmpSize(a, b);
}

/*
    Comparator: size > extensions
 */
int cmpSizeExt(const void *a, const void *b) {
    int retVal = cmpSizeRaw(a, b);
    if (retVal != 0) {
        return retVal;
    }
    return cmpExt(a, b);
}

/*
    Sorts the Entry list [**data] based on the provided comparator option
 */
void sortList(Entry **data, int length, char *sort) {
    if (sort && !strcmp(sort, "e")) {
        qsort(*data, (size_t) length, sizeof(Entry), cmpExt);
    }
    else if (sort && !strcmp(sort, "s")) {
        qsort(*data, (size_t) length, sizeof(Entry), cmpSize);
    }
    else if (sort && !strcmp(sort, "f")) {
        qsort(*data, (size_t) length, sizeof(Entry), cmpPath);
    }
    else if (sort && !strcmp(sort, "es")) {
        qsort(*data, (size_t) length, sizeof(Entry), cmpExtSize);
    }
    else if (sort && !strcmp(sort, "se")) {
        qsort(*data, (size_t) length, sizeof(Entry), cmpSizeExt);
    }
    else {
        qsort(*data, (size_t) length, sizeof(Entry), cmpName);
    }
}
