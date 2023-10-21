//
// Created by Devon Coates on 9/7/23.
//

#ifndef JOBSYSTEM_RENDERJOB_H
#define JOBSYSTEM_RENDERJOB_H

#include <vector>
#include "job.h"


class RenderJob : public Job {
    public:
        RenderJob(unsigned long jobChannels, int jobType) : Job(jobChannels, jobType) {};
        ~RenderJob(){};

        std::vector<int> data;
        void Execute();
        void JobCompleteCallback();
};


#endif //JOBSYSTEM_RENDERJOB_H
