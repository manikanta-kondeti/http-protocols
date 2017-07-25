#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "utils.h"
#include "requests.h"

#define MAX_THREADS_COUNT 4
using namespace std;

void execute_job(Job *job, int *thread_count){
    job->status = RUNNING;
    int check_time = job->life;
    while(check_time--){

        this_thread::sleep_for (std::chrono::seconds(1));
        if(job->status == DELETED || job->status == PAUSED){       
            job->life = check_time;
            (*thread_count)--;
            return;
        }
    }
    job->status = SUCCESSFUL;
    (*thread_count)--;
    return;
}

void handle_jobs(){
    int thread_count = 0;
    while(1) {
        while(thread_count == MAX_THREADS_COUNT || requests_queue.empty()){ 
        }   
        Job *job = requests_queue.front();
        requests_queue.pop();
        if(job->status == QUEUED || job->status == RESUME){
            thread *job_polling_thread = new thread(execute_job, job, &thread_count);
            thread_count++;
        } 
    }
    return;
}

#endif