#pragma once

#include "dataStructure.h"
#include <dirent.h>

/*
    Recursively searches directory tree, must be called from int loadList(...)
 */
void rLoadList(Entry** data,
               int length,
               int *index,
               DIR* currentdir,
               char* currentpath,
               int cplength,
               char* name,
               char* ext,
               char* username,
               char hidden);

/*
    Traversal entry point. Requires pointers for basic attributes, Entry list [**data] and path to start at
 */
int loadList(Entry** data,
             int length,
             int *index,
             char* path,
             char* name,
             char* ext,
             char* username,
             char hidden);
