#include <iostream>
#include <string>
#include <vector>

#include "jobsystem.h"
#include "job.h"
#include "renderjob.h"
#include "compilejob.h"

int main(void) {

    std::string command;
    bool loop = true;

    while(true) {
        std::cout
                << "Welcome, professor. Would you like to create a Job System? (yes/no)"
                << std::endl;
        std::cin >> command;

        if (command == "yes")
            break;
        else if(command == "no")
            return 0;
        else{
            std::cout << "Not a valid input, try again." << std::endl;
        }
    }

    std::cout << "Creating Job System" << std::endl;

    JobSystem* js = JobSystem::CreateOrGet();

    std::cout << "Job System created. Would you like to create worker threads? (yes/no)" << std::endl;
    std::cin >> command;

    while(true){
        if(command == "yes")
            break;
        else if(command == "no") {
            std::cout
                    << "Well, theres nothing much else you're able to do with this program if you don't say yes, so we'll do it anyways"
                    << std::endl;
            break;
        }
        else
            std::cout << "Invalid command. Try again" << std::endl;

    }

    std::cout << "Creating Worker Threads" << std::endl;

    js->CreateWorkerThread("Thread1", 0xFFFFFFFF);
    js->CreateWorkerThread("Thread2", 0xFFFFFFFF);
    js->CreateWorkerThread("Thread3", 0xFFFFFFFF);
    js->CreateWorkerThread("Thread4", 0xFFFFFFFF);
    js->CreateWorkerThread("Thread5", 0xFFFFFFFF);
    js->CreateWorkerThread("Thread6", 0xFFFFFFFF);
    js->CreateWorkerThread("Thread7", 0xFFFFFFFF);
    js->CreateWorkerThread("Thread8", 0xFFFFFFFF);
    js->CreateWorkerThread("Thread9", 0xFFFFFFFF);

    std::cout << "Creating Jobs " << std::endl;

    std::vector<Job*> jobs;

    CompileJob* cjb = new CompileJob(0xFFFFFFFF, 1);
    jobs.push_back(cjb);

    for(int j = 0; j < 0; j++){
        RenderJob* rjb = new RenderJob(0xFFFFFFFF, 1);
        for(int i = 0; i < 100000; i++){
            rjb->data.push_back(i+j);
        }
        jobs.push_back(rjb);
    }

    std::cout << "Queueing Jobs" << std::endl;

    std::vector<Job*>::iterator it = jobs.begin();

    for(; it != jobs.end(); ++it){
        js->QueueJob(*it);
    }

    int running = 1;

    while(running){
        std::cout << "Enter a command (stop, destroyThreads, destroySystem, destroyJobs, finish, status, start): ";
        std::cin >> command;

        if(command == "stop")
            running = 0;
        else if(command == "destroyThreads")
            js->destroyAllThreads();
        else if(command == "destroySystem") {
//            js->FinishCompletedJobs();
            js->Destroy();
            running = 0;
        }
        else if(command == "destroyJobs"){
            for(int i = 0; i < jobs.size(); i++){
                jobs[i]->~Job();
            }
        }
        else if(command == "finish"){
            js->FinishCompletedJobs();
            std::cout << "Total Jobs Completed " << js->totalJobs << std::endl;
        }
        else if(command == "status"){
            int num;
            std::cout << "Enter job ID: ";
            std::cin >> num;
            int status = (int)js->GetJobStatus(num);
            if(status == 0)
                std::cout << "Job " << num << " status: NEVER_SEEN" << std::endl;
            else if(status == 1)
                std::cout << "Job " << num << " status: QUEUED" << std::endl;
            else if(status == 2)
                std::cout << "Job " << num << " status: RUNNING" << std::endl;
            else if(status == 3)
                std::cout << "Job " << num << " status: COMPLETED" << std::endl;
            else if(status == 4)
                std::cout << "Job " << num << " status: RETIRED" << std::endl;
        }
        else if(command == "start"){
            js->startAllThreads();
        }
        else{
            std::cout << "Invalid Command" << std::endl;
        }
    }

    return 0;
}
