#pragma once

#include "dataStructure.h"

#include <dirent.h>
#include <pwd.h>
#include <sys/stat.h>


char getInfo(struct dirent *dir,
             struct stat *info,
             struct passwd **pw,
             char* currentpath,
             char* filepath,
             char* hasOwner);


void splitFileName(struct dirent *dir, char** filename, char** fileext);


void enlist(int* index, int* length, Entry** data, char* filepath, struct stat *info);


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
                 int* index);
