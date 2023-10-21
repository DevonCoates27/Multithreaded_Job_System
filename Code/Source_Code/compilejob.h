//
// Created by Devon Coates on 9/7/23.
//

#ifndef JOBSYSTEM_COMPILEJOB_H
#define JOBSYSTEM_COMPILEJOB_H

#include "job.h"

class CompileJob : public Job{
public:
    CompileJob( unsigned long jobChannels, int jobType ) : Job(jobChannels, jobType) {};
    ~CompileJob() {};

    std::string output;
    int returnCode;

    void Execute();
    void JobCompleteCallback();
};


class compilejob {

};


#endif //JOBSYSTEM_COMPILEJOB_H
