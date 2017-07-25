// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <iostream>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <netinet/ip.h> 
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#define PORT 8090
using namespace std;

enum STATUS{RESUME=0, PAUSE=1};

string get_request(int id){
	string resp =  "GET /job/" + to_string(id);
	return resp;
}

string post_request(int id, int status){
	string state = (status == 2)?"resume":"pause";  
	string resp = "POST /job/" +  to_string(id) + "/" + state;
	return resp;
}

string put_request(){
	return "PUT /job";
}

string delete_request(int id){
	string resp = "DELETE /job/" + to_string(id);
	return resp;
}

int main(int argc, char *argv[])
{
	struct sockaddr_in address;
	int sock = 0, valread;
	struct sockaddr_in serv_addr;
	char buffer[1024] = {0};
	char *hello = argv[1];
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("\n Socket creation error \n");
		return -1;
	}

	memset(&serv_addr, '0', sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	
	// Convert IPv4 and IPv6 addresses from text to binary form
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
	{
		printf("\nInvalid address/ Address not supported \n");
		return -1;
	}

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("\nConnection Failed \n");
		return -1;
	}
	while(1){
	// Chocie of selecting the request
	cout << "*** New Request ***" << endl;
	cout << " GET - 1,  PUT - 2, POST - 3, DELETE - 4" << endl;
	cout << "Choose the type of request " << endl;
	int choice;
	cin >> choice;
	string request = "";
	int id;
	switch(choice){
		case 1: 
			cout << "Select id = " <<endl;
			cin >> id;
			request = get_request(id);	
			break;
		case 2: 
			request = put_request();
			break;
		case 3:
			cout << "Select id = " << endl;
			cin >> id;
			int state;
			cout << " Please input PAUSE - 1  RESUME - 2" << endl;
			cin >> state;
			if (state > 2 || state < 0){
				cout << "Wrong selection, do it again" << endl;
				cin >> state;	
			}
			request = post_request(id, state);
			break;
		case 4: 
			cout << "Select id = " ;
			cin >> id;
			request = delete_request(id);
			break;
		default:
			cout << "Wrong selection" << endl;
			return 0;
	}

	
	int indicator = write(sock, request.c_str(), request.length());
	//send(sock , hello , strlen(hello) , 0 );
	valread = read(sock , buffer, sizeof(buffer));
	printf("Response received from client \n %s\n\n",buffer);
	fill(begin(buffer), end(buffer), '\0');
}
	return 0;
}


