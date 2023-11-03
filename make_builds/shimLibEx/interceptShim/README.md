#Intercept Functionality

Example of shim library being used to intercept the stdlib rand function adding user defined functions

##Use
Note that Makefile defines and elf and a so output by filenames not explicit step

$ make
g++ -Wall -g -o shimTest.elf shimTest.cpp
g++ -Wall -g -fPIC -shared -Wl,--no-as-needed -ldl -o shimLib.so shimLib.cpp
shimLib.cpp:1: warning: "_GNU_SOURCE" redefined
    1 | #define _GNU_SOURCE
      | 
<command-line>: note: this is the location of the previous definition
$ LD_PRELOAD=./shimLib.so ./shimTest.elf 
non gnu rand called here
0: 383
non gnu rand called here
1: 886
non gnu rand called here
2: 777
non gnu rand called here
3: 915
non gnu rand called here
4: 793
non gnu rand called here
5: 335
non gnu rand called here
6: 386
non gnu rand called here
7: 492
non gnu rand called here
8: 649
non gnu rand called here
9: 421
