#ifndef JOB_H
#define JOB_H

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <queue> 
#include <thread>
#define JOB_TIME 6
using namespace std;

enum STATE {QUEUED=0, RUNNING=1, PAUSED=2, SUCCESSFUL=3, FAILED=4, DELETED=5, RESUME=6};
vector<string> states={"QUEUED", "RUNNING", "PAUSED", "SUCCESSFUL", "FAILED", "DELETED", "RESUME"};

class Job{
    public: 

    int job_id, life, status, socket_id;

    char *buffer = NULL;
    Job(int sock_id, int id, char *client_buffer, int time1){
        socket_id = sock_id;
        job_id = id; 
        buffer = client_buffer;
        life = JOB_TIME;
        status = QUEUED;
    }

    void send_response(char *send_buffer){    
        send(socket_id, send_buffer, strlen(send_buffer) , 0);
        return;
    }

    ~Job(){
        cout << "Destructor is executed\n";  
    }
};

#endif