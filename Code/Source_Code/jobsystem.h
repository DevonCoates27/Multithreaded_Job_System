//
// Created by Devon Coates on 9/12/23.
//

#ifndef JOBSYSTEM_JOBSYSTEM_H
#define JOBSYSTEM_JOBSYSTEM_H

#include <vector>
#include <deque>
#include <mutex>
#include <string>
#include <cstring>

constexpr int JOB_TYPE_ANY = -1;

class JobWorkerThread;

enum JobStatus{
    JOB_STATUS_NEVER_SEEN,
    JOB_STATUS_QUEUED,
    JOB_STATUS_RUNNING,
    JOB_STATUS_COMPLETED,
    JOB_STATUS_RETIRED,
    NUM_JOB_STATUSES
};

struct JobHistoryEntry{
    JobHistoryEntry(int jobType, JobStatus jobStatus)
        : m_jobType(jobType)
        , m_jobStatus(jobStatus){}

        int m_jobType = -1;
        int m_jobStatus = JOB_STATUS_NEVER_SEEN;
};

class Job;

class JobSystem{
    friend class JobWorkerThread;

public:
    JobSystem();
    ~JobSystem();

    static JobSystem* CreateOrGet();
    static void Destroy();
    int totalJobs = 0;

    void CreateWorkerThread(const char* uniqueName, unsigned long workerJobChannels=0xFFFFFFFF);
    void DestroyWorkerThread(const char* uniqueName);
    void QueueJob(Job* job);

    //Status Queries
    JobStatus GetJobStatus(int jobID) const;
    bool IsJobComplete(int jobID) const;

    void FinishCompletedJobs();
    void FinishJob(int jobID);

    void startAllThreads();
    void destroyAllThreads();

private:
    Job* ClaimAJob(unsigned long workerJobFlags);
    void OnJobCompleted(Job* jobJustExecuted);

    static JobSystem* s_jobSystem;

    std::vector<JobWorkerThread*> m_workerThreads;
    mutable std::mutex            m_workerThreadsMutex;
    std::deque<Job*>              m_jobsQueued;
    std::deque<Job*>              m_jobsRunning;
    std::deque<Job*>              m_jobsCompleted;
    mutable std::mutex            m_jobsQueuedMutex;
    mutable std::mutex            m_jobsRunningMutex;
    mutable std::mutex            m_jobsCompletedMutex;

    std::vector<JobHistoryEntry>  m_jobHistory;
    mutable int                   m_jobHistoryLowestActiveIndex = 0;
    mutable std::mutex            m_jobHistoryMutex;
};
#endif //JOBSYSTEM_JOBSYSTEM_H
