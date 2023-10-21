//
// Created by Devon Coates on 9/7/23.
//

#ifndef JOBSYSTEM_JOB_H
#define JOBSYSTEM_JOB_H

#pragma once  //Makes it so that you can only have one job class, if there are two, you get a compile error (can't redefine)
#include <mutex>
#include <map>
#include <deque>
#include <vector>
#include <thread>

class Job {
    friend class JobSystem;
    friend class JobWorkerThread;

public:
    Job(unsigned long jobChannels = 0xFFFFFFFF, int jobType = -1) : m_jobChannels(jobChannels), m_jobType(jobType) {
        static int s_nextJobID = 0;
        m_jobID = s_nextJobID++;
    }

    virtual ~Job(){}

    virtual void Execute() = 0; // This MUST be inherited by the inheritor class - this is now an abstract class
    virtual void JobCompleteCallback(){}; // This CAN be inherited by the inheritor class
    int GetUniqueID() const { return m_jobID; }
    int GetJobType() const { return m_jobType; }
    unsigned long GetJobChannels() const { return m_jobChannels; }

private:
    int     m_jobID     = -1;
    int     m_jobType   = -1;

    unsigned long m_jobChannels = 0xFFFFFFFF;



};


#endif //JOBSYSTEM_JOB_H
