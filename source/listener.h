#ifndef LISTENER_H
#define LISTENER_H

#include "utils.h"
#include "requests.h"

using namespace std;
#define PORT 8090

void handle_request(char * buffer, vector<string> attributes, int socket_id){
    
    if(attributes[0]=="GET "){
        get(socket_id, attributes); 
    }else if(attributes[0]=="PUT "){
        put(socket_id, buffer, 10); 
    }else if(attributes[0]=="POST "){
        post(socket_id, attributes); 
    }else if(attributes[0]=="DELETE "){
        delete_req(socket_id, attributes); 
    }
}

void listen_jobs(){   
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *hello = "Hello from server";
    int job_id = 0;
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );

    if(::bind(server_fd, (struct sockaddr *)&address, sizeof(address))){
        perror("bind error");
        exit(EXIT_FAILURE);   
    }

    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    } 
        while(1){
        // A new job is being added 
    
        cout << "Server listening to a single client... !" << endl;
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, 
                        (socklen_t*)&addrlen))<0)
        {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        cout << "A client with socket id:"<< new_socket << " connected" << endl;
        while(1){
            memset(buffer, 0, sizeof(buffer));
            valread = read(new_socket , buffer, 1024);
            cout << "Client's request :  " << buffer << endl;
            job_id++;
            
            vector<string> attributes = parse_request(buffer);
            handle_request(buffer, attributes, new_socket);
        }
    }
}

#endif