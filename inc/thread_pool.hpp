#ifndef _THREAD_POOL_HPP
#define _THREAD_POOL_HPP 1

#include <queue>
#include <pthread.h>
#include "request.hpp"

using namespace std;

#define THREAD_WORKERS 20
namespace TP
{
  class Thread_Pool
  {
  private:
    pthread_t thread_pool[THREAD_WORKERS];

    // Init function
    void init_threads();
    // thread function
    static void *thread_function(void *arg);

  public:
    // Constructor
    Thread_Pool()
    {
      // Initialize threads
      init_threads();
    }

    // Add work
    void add_work(int *conn);
    // Get work
    static int *get_work();
  };
}

#endif