// Server side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <queue> // (empty, size, front, back, push_back, pop_front)
#include "job.h"
#include <thread>
#include <unordered_map>
#include <sstream>
#include <functional>
#include <chrono>
#include "utils.h"
#include "requests.h"
#include "executor.h"
#include "listener.h"

using namespace std;

int main(int argc, char const *argv[])
{
    // a thread that listens to the requests from client 
    thread listen(listen_jobs);
    
    // a thread that executes the requests in order 
    thread execute(handle_jobs);
   
    execute.join();
    listen.join();   

    return 0;
}
