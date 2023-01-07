#include "thread_pool.hpp"

using namespace TP;

pthread_cond_t condition_var = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
queue<int *> job_queue;

void Thread_Pool::init_threads()
{
  for (int i = 0; i < THREAD_WORKERS; i++)
  {
    pthread_create(&thread_pool[i], NULL, thread_function, NULL);
  }
}

void *Thread_Pool::thread_function(void *arg)
{
  while (true)
  {
    pthread_mutex_lock(&mutex);
    int *client;
    if ((client = get_work()) == NULL)
      pthread_cond_wait(&condition_var, &mutex);

    pthread_mutex_unlock(&mutex);
    if (client != NULL)
      handle_request(client);
  }
  return NULL;
}

void Thread_Pool::add_work(int *conn)
{
  pthread_mutex_lock(&mutex);
  pthread_cond_signal(&condition_var);
  job_queue.push(conn);
  pthread_mutex_unlock(&mutex);
}

int *Thread_Pool::get_work()
{

  if (job_queue.empty())
    return NULL;
  int *work = job_queue.front();
  job_queue.pop();

  return work;
}