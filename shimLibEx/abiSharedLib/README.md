#Redirect Functionality

Example of shim library being used to redirect the stdlib rand function to this user defined one.

##Use
Note that Makefile defines and elf and a so output by filenames not explicit step
$ make
g++ -Wall -g -o shimTest.elf shimTest.cpp
g++ -Wall -g -fPIC -shared -o shimLib.so shimLib.cpp
$ LD_PRELOAD=./shimLib.so ./shimTest.elf 
0: 888
1: 888
2: 888
3: 888
4: 888
...
