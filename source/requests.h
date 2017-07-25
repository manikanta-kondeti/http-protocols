#ifndef REQUESTS_H
#define REQUESTS_H

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

using namespace std;

void put(int socket_id, char *buffer1, int t){
    
    static int job_id = 0;
    Job *new_job = new Job(socket_id, job_id, buffer1, t);
    requests_queue.push(new_job);
    job_status_map[job_id] = (new_job);
   
    char *buffer = (char *)malloc(sizeof(char)*100);
    buffer = create_message("200\n", to_string(job_id).c_str(), to_string(new_job->status).c_str());

    new_job->send_response(buffer);
   
    job_id++;
    free(buffer);
    return;
}

void get(int socket_id, vector<string> attributes){
    int id = stoi(attributes[2]);
    
    char *buffer = (char *)malloc(sizeof(char)*100);
    bool job_exists = check_if_job_exists(id);
    if(!job_exists){
        send_404_response(socket_id);
        return;
    }
    Job * job = job_status_map[id];
    buffer = create_message("200\n", to_string(id).c_str(), to_string(job->status).c_str());
    job->send_response(buffer);
    
    return;
}

void post(int socket_id, vector<string> attributes){
    int id = stoi(attributes[2]);
    string state_order = attributes[3];
    int state = (state_order == "pause") ? 2 : 6;

    char *buffer = (char *)malloc(sizeof(char)*100);
    
    bool job_exists = check_if_job_exists(id);
    if(!job_exists){
        send_404_response(socket_id);
        return;
    }

    Job * job = job_status_map[id];
    // if - pause the job, else if - resume the job 

    if(state == PAUSED){
        if(job->status == RUNNING || job->status == PAUSED){
            job->status = PAUSED;
            buffer = create_message("200\n", to_string(id).c_str(), to_string(job->status).c_str());
            job->send_response(buffer);
        }else if(job->status == SUCCESSFUL || job->status == FAILED || job->status == QUEUED){
            char * new_buf = "403\n";
            job->send_response(new_buf);
        }
    }
    else if(state == RESUME){
        if(job->status == PAUSED || job->status == RUNNING){
            if(job->status == PAUSED){
                job->status = RESUME; 
                requests_queue.push(job);
            }
            buffer = create_message("200\n", to_string(id).c_str(), to_string(RUNNING).c_str());
            job->send_response(buffer);
        }else if(job->status == SUCCESSFUL || job->status == FAILED || job->status == QUEUED){
            char * new_buf = "403\n";
            job->send_response(new_buf);
        }
    }
    return;
}

void delete_req(int socket_id, vector<string> attributes){
    int id = stoi(attributes[2]);

    char *buffer = (char *)malloc(sizeof(char)*100);
    bool job_exists = check_if_job_exists(id);
    if(!job_exists){
        send_404_response(socket_id);
        return;
    }

    Job * job = job_status_map[id];

    if(job->status == DELETED || job->status == RUNNING || job->status == PAUSED || job->status == QUEUED){
        job->status = DELETED;
        buffer = create_message("200\n", to_string(id).c_str(), to_string(job->status).c_str());
        job->send_response(buffer);
    }else if(job->status == SUCCESSFUL || job->status == FAILED){
        char * new_buf = "403\n";
        job->send_response(new_buf);
    }
    
    return;
}

#endif