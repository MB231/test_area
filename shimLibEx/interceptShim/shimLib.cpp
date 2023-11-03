#define _GNU_SOURCE
#include <unistd.h>
#include <dlfcn.h>
#include <stdio.h>

// ensures C linkage and not C++ which will mangle the name
extern "C" {
    int rand();
}

int rand() {
    printf("non gnu rand called here\n");
    typedef int (*func)(void);
    func f;
    f = (func)dlsym(RTLD_NEXT, "rand");
    return f() % 1000;
}
