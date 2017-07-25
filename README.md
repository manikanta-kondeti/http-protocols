# How to run?
* cd source/
* ./run  
* ./server (in first tab)
* ./client (in second tab)
 

# Assumptions:
* The current implementation works perfectly for a single client for all given conditions
* Time is assumed to be 6 secs for each process (To change the value, please change the macro "JOB_TIME" defined in job.h ) 
* Maximum jobs at once can be 4 (To change the value, please change the macro "MAX_THREADS" defined in executor.h ) 

# Files:
* Listener(listener.h) is a thread listening to all the requests and executor(executor.h) is a thread executing each thread
* Used multithreading for running jobs at once.
* requests.h : contains methods for handling all the requests
* job.h has the definition of job class
* utils.h has the functions used once/frequently in the entire program
* client.cpp : A single client for requesting the server 


# Technologies:
* Implemented in c++ and should run with c++11 compiler 
* Uses multithreading <thread> library in c++
