#include "fileInfo.h"
#include "dataStructure.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char getInfo(struct dirent *dir,
             struct stat *info,
             struct passwd **pw,
             char* currentpath,
             char* filepath,
             char* hasOwner)
{
    strcpy(filepath,currentpath);
    strcat(filepath,"/");
    strcat(filepath,dir->d_name);
    if (stat(filepath, info) == -1)
    {
        fprintf(stderr, "Stat function failed for %s\n", filepath);
        return 1;
    }
    *hasOwner = 0;
    if ((*pw = getpwuid(info->st_uid)) != NULL)
    {
        *hasOwner = 1;
    }
    return 0;
}

void splitFileName(struct dirent *dir, char** filename, char** fileext)
{

    int stop = -1;
    for (unsigned int i=0; i<strlen(dir->d_name); i++)
    {
        if (dir->d_name[i] == '.')
        {
            stop = i;
        }
    }
    if (stop < 1)
    {
        stop = strlen(dir->d_name);
    }
    *filename = malloc(stop+1);
    memcpy(*filename,dir->d_name,stop);
    (*filename)[stop] = 0;

    if (stop < (int)strlen(dir->d_name)-1)
    {
        *fileext = malloc(strlen(dir->d_name)-stop);
        memcpy(*fileext, &dir->d_name[stop+1], strlen(dir->d_name)-stop-1);
        (*fileext)[strlen(dir->d_name)-stop-1] = 0;
    }
}


void enlist(int* index, int* length, Entry** data, char* filepath, struct stat *info)
{

    if (*index == *length)
    {
        reallocEntries(data, *length);
        (*length) *= 2;
    }

    (*data)[*index].path = malloc(strlen(filepath)+1);
    strcpy((*data)[*index].path, filepath);
    (*data)[*index].size = info->st_size;
    ++*index;
}

char processFile(Entry** data,
                 struct dirent *dir,
                 struct passwd *pw,
                 struct stat *info,
                 char* name,
                 char* ext,
                 char* username,
                 char hasOwner,
                 char* filepath,
                 int* length,
                 int* index)
{


    char* filename = NULL;
    char* fileext = NULL;
    splitFileName(dir, &filename, &fileext);


    if ((name && strstr(filename, name) == NULL)
            || (ext && !fileext && strlen(ext) != 0)
            || (ext && fileext && strcmp(ext,fileext))
            || (username && hasOwner && strcmp(username, pw->pw_name)))
    {
        free(filepath);
        free(filename);
        if (fileext)
        {
            free(fileext);
        }
        return 1;
    }
    free(filename);
    if (fileext)
    {
        free(fileext);
    }


    enlist(index, length, data, filepath, info);
    return 0;
}
