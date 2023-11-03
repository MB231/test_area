#include <stdio.h>
#include <stdlib.h>
// application to call GNU rand from a shim lib

int main(int argc, char *argv[]) {

    // print 10 random numbers using std lib rand call
    for (int i = 0; i < 10; i++) {
        printf("%d: %d\n", i, rand());
    }
    return 0;
}
