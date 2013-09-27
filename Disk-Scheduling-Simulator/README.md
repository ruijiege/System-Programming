#Disk Scheduling Simulator
**author: Ruijie Ge**

>**DESCRIPTION:** simdisk is a simple disk scheduling simulator. It takes a sequence of disk cylinder I/O requests as an input, as well as the total number of cylinders on the disk. It performs the scheduling of incoming I/O requests using the disk scheduling policy specified by the user, and measures total number of cylinders travelled by the disk head.

**SYNOPSIS:** ./simdisk [-h] [-n number-of-cylinders] [-d disk-shed-policy] [-i input]

This is summary of all options:

-n number-of-cylinders : Set the total number cylinders on the disk.By default it should be 200.(disk cylinder indexes would be between 0-199)

-d disk-shed-policy : Set the disk scheduling policy.It can be either FCFS (First-come-firstserved), SSTF (Shortest-seek-time-first),C-SCAN, or LOOK. The default will be FCFS. Assume at the t=t0, the disk head was moving from 0 towards other end of the disk.

-i input file : Read the I/O request sequence from a specified file. If not given,the sequence should be read from STDIN (ended with ENTER).

**NOTES:** If specified a file, each I/O request should have double space interval.For example"1  2  3". If no file specified, just type the sequence after "-i" and should have one space interval, for example "-i 1 2 3". 
