
Write a program with 2 threads. 
first thread should print even numbers in sequence and 
second thread should print odd numbers in sequence
from the given array. 


neelagga@~$ gcc -o multithreading.o multithreading.c 
neelagga@~$ ./multithreading.o
size: 16
Thread_name = odd_thread shared_index = 1
Thread_name = odd_thread shared_index = 3
Thread_name = even_thread shared_index = 2
Thread_name = even_thread shared_index = 4
Thread_name = odd_thread shared_index = 5
Thread_name = odd_thread shared_index = 7
Thread_name = even_thread shared_index = 6
Thread_name = odd_thread shared_index = 9
Thread_name = even_thread shared_index = 10
Thread_name = odd_thread shared_index = 11
Thread_name = even_thread shared_index = 12
Thread_name = odd_thread shared_index = 13
Thread_name = even_thread shared_index = 0
Thread_name = odd_thread shared_index = 3
Thread_name = odd_thread shared_index = 7
Thread_name = even_thread shared_index = 8
^C
neelagga@~$
