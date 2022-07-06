#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <dlfcn.h>

// Name: Manav Gohil
// netID: mrg225
// RUID: 200004193
// your code for readdir goes here

struct dirent *readdir(DIR *dirp)
{
    int bool = 0;

    struct dirent *p, *(*realReaddir)(DIR *) = dlsym(RTLD_NEXT, "readdir");

    char *hid2323 = getenv("HIDDEN");
    char *hidcopy = (char *)malloc(512 * sizeof(char));

    while ((bool == 0) && (p = realReaddir(dirp)))
    {
        if (p != NULL)
        {
            strcpy(hidcopy, hid2323);
            char *hid = strtok(hidcopy, ":");
            while (hid != NULL)
            {
                if (strcmp(p->d_name, hid) == 0)
                    break;

                hid = strtok(NULL, ":");
            }
            bool = hid == NULL ? 1 : 0;
        }
    }

    free(hidcopy);
    return p;
}