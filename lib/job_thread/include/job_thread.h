//
// Created by kira on 01.05.2020.
//

#ifndef RPI_LED_LIB_JOB_THREAD_INCLUDE_JOB_THREAD_H_
#define RPI_LED_LIB_JOB_THREAD_INCLUDE_JOB_THREAD_H_

#include <atomic>
#include <thread>

namespace executor {
class JobThread {
 public:
    virtual ~JobThread();
    void run();
    void stop();
 private:
    virtual void job() = 0;

    std::thread _job_thread;
    std::atomic<bool> _run = true;
};
}  // namespace executor

#endif //RPI_LED_LIB_JOB_THREAD_INCLUDE_JOB_THREAD_H_
