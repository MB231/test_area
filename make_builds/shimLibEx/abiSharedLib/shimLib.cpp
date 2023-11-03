
// ensures C linkage and not C++ which will mangle the name
extern "C" {
    int rand();
}

int rand() {
    return 888;
}
