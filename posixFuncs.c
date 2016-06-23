#include "posixFuncs.h"
#include "fileInfo.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>


void rLoadList(Entry** data,
               int length,
               int *index,
               DIR* currentdir,
               char* currentpath,
               int cplength,
               char* name,
               char* ext,
               char* username,
               char hidden)
{

    struct dirent *dir;
    struct passwd *pw;
    struct stat info;
    char hasOwner;
    int nextlength;
    while ((dir = readdir(currentdir)))
    {

        if (!strcmp(dir->d_name,".") || !strcmp(dir->d_name,".."))
        {
            continue;
        }
        if (dir->d_name[0] == '.' && !hidden)
        {
            continue;
        }


        nextlength = (int)(strlen(currentpath) + strlen(dir->d_name) + 2);
        if (nextlength >= cplength)   //Fix limiting lengths
        {
            cplength += nextlength;
        }


        char* filepath = malloc(cplength);
        if (getInfo(dir, &info, &pw, currentpath, filepath, &hasOwner))
        {
            continue;
        }


        if (S_ISDIR(info.st_mode))
        {
            DIR *next = opendir(filepath);
            if (!next)
            {
                fprintf(stderr, "Cannot access %s, skipping...\n", filepath);
                continue;
            }

            rLoadList(data, length, index, next, filepath, cplength, name, ext, username, hidden);
            closedir(next);
        }
        if (S_ISREG(info.st_mode))
        {
            if (processFile(data, dir, pw, &info, name, ext, username, hasOwner, filepath, &length, index))
            {
                continue;
            }
        }


        free(filepath);
    }
}


int loadList(Entry** data,
             int length,
             int *index,
             char* path,
             char* name,
             char* ext,
             char* username,
             char hidden)
{

    DIR *start = opendir(path);
    if (!start)
    {
        return 1;
    }
    rLoadList(data, length, index, start, path, 256, name, ext, username, hidden);
    closedir(start);
    return 0;
}
