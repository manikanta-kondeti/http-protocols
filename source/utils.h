#ifndef UTILS_H
#define UTILS_H

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

using namespace std;

unordered_map<int, Job*> job_status_map;
queue<Job*> requests_queue;

char *create_message(const char *buffer1, const char *buffer2, const char *buffer3){
    char *resp_buffer = (char *)malloc(sizeof(char *));
    ::strcpy(resp_buffer, buffer1);
    if(::strcmp(buffer3, "") == 0 && ::strcmp(buffer2, "") == 0){
        
        return resp_buffer;
    }
   
    ::strcat(resp_buffer, buffer2);
    ::strcat(resp_buffer, "  ");
    if (::strcmp(buffer3, "") != 0){
        stringstream strval;
        strval << buffer3;
        int state_id;
        strval >> state_id;
        
        if(state_id > 5 || state_id < 0){
            ::strcat(resp_buffer, buffer3);
            return resp_buffer;
        }
        
        const char * buffer4 = states[state_id].c_str();
         ::strcat(resp_buffer, buffer4);
    }
    else{
        ::strcat(resp_buffer, buffer3);
    }
    buffer1 = NULL, buffer2 = NULL, buffer3 = NULL;
    return resp_buffer;
}

bool check_if_job_exists(int id){
	if(job_status_map.find(id) == job_status_map.end()){
        return false;
    }
    return true;
}

void send_404_response(int socket_id){
	char *new_buffer = "404\n";
    send(socket_id, new_buffer, strlen(new_buffer) , 0);
    return;
}

vector<string> parse_request(char *string_buffer){
    /*
     * usage: Ref : https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
     * return: attributes(request_type, job, (id  | status)) 
     */
    stringstream data(string_buffer);
    vector<string> attributes;
    string line;
    while(getline(data, line, '/')){
        attributes.push_back(line);        
    }
    return attributes;
}

#endif