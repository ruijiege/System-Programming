#Virtual Memory Manager

**Author: Ruijie Ge**

> **DESCRIPTION:** virtualmem is a simple virtual memory manager. It takes a sequence of page references as an input, as well as the number of available frames. It performs the placement of these pages to the available frames using the page replacement policy specified by the user.

##dec_server:
first type "make" in the source code directory

**SYNOPSIS:** ./dec_server [-h]  [-p port]  [-l log file]

Summary of all options:

  -h : Print a usage summary with all options and exit.

  -p : You can set the port number, default value of port number is 9090.

  -l : Log all requests and responses to the given file. If not, print all to stdout(Input the file name here, include the path)


For example:

./dec_server -h 

./dec_server -p 8899

./dec_server -p 8899 -l ./log.txt



##dec_client:
first type "make" in the source code directory

**SYNOPSIS:** ./dec_client [-h] [-p port] [-s hostname]

Summary of all options:

-h : Print a usage summary with all options and exit.

-p : You can set the port number, default value of port number is 9090.

-s : Connect to the specified host(by hostname or by IP address).If not provided, connect to the localhost(127.0.0.1)


For example:

./dec_client -h 

./dec_client -p 8899

./dec_client -p 8899 -s timberlake.cse.buffalo.edu
