#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <time.h>

// Name: Manav Gohil
// netID: mrg225
// RUID: 200004193
// your code for time() goes here

static int called=0;

time_t (*realTimeH)(time_t*);

time_t time(time_t *tloc){
    if(called==0){
        called = 1;

        struct tm tm;
        strptime("1 Jan 2021 00:00:00", "%d %b %Y %T", &tm);
        time_t fakeTime = mktime(&tm);

        if (tloc != NULL)
            *tloc = fakeTime;
        return fakeTime;
    }
    else{
        realTimeH = dlsym(RTLD_NEXT, "time");
        time_t realTime = realTimeH(NULL);

        if (tloc != NULL)
            *tloc = realTime;
        return realTime;
    }
}