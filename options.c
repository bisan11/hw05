#include "options.h"

#include <string.h>
#include <stdlib.h>


int parseArgs(int argc,char** argv,char** path,char** name,char** ext,char** username,int* hidden,char** sort) {

    for (int i=1;i<argc;i++) {
        if (argv[1][0] != '-' && !*path) {
            *path = malloc(strlen(argv[i])+1);
            strcpy(*path,argv[i]);
            if((*path)[strlen(*path)-1] == '/') {
                (*path)[strlen(*path)-1] = 0;
            }
            continue;
        }
        if (!strcmp(argv[i],"-h")) {
            return 1;
        }
        if (!strcmp(argv[i],"-a") && *hidden == 0) {
            *hidden = 1;
            continue;
        }
        if (!strcmp(argv[i],"-u") && !*username) {
            if (++i == argc) {
                return 2;
            }
            *username = malloc(strlen(argv[i])+1);
            strcpy(*username,argv[i]);
            continue;
        }
        if (!strcmp(argv[i],"-n") && !*name) {
            if (++i == argc) {
                return 2;
            }
            *name = malloc(strlen(argv[i])+1);
            strcpy(*name,argv[i]);
            continue;
        }
        if (!strcmp(argv[i],"-e") && !*ext) {
            if (++i == argc) {
                return 2;
            }
            *ext = malloc(strlen(argv[i])+1);
            strcpy(*ext,argv[i]);
            continue;
        }
        if (!strcmp(argv[i],"-s") && !*sort) {
            if (++i == argc) {
                return 2;
            }
            *sort = malloc(strlen(argv[i])+1);
            strcpy(*sort,argv[i]);
            continue;
        }

        return 3;
    }
    return 0;
}
