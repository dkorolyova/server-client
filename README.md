Cross-platform socket

There are two programs: a client and a server. A server performs
 some functions by request from a client. 
 
 A client requests a server to sort files by next parameters: 
 name/type/date. Server replies with number of sorted files in a directory.
 
The program has “Makefile" to compile it.

The program is written in C.

The program is cross-compilable - it can be used for OS Linux as well as for Windows OS.

The code is divided into modules: network and platform. It also has modules with functions 
that are needed for parsing config file (for client and for server) and sorting type 
(for server). Config file includes a port and a path to a folder.

NOTE: don't type a new line in the end of config file.

Compiling

For compiling the program can be used "Makefile". 

For Linux should be installed gcc compiler: https://gcc.gnu.org/ 

For Windows should be installed MinGW compiler: http://www.mingw.org/category/wiki/download