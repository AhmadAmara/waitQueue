#include <iostream>
#include <pthread.h>
#include <vector>
#include <unistd.h>
#include <cstdlib>

int counter = 0;

template <class T>
class Producer
{

public:
    Producer(int id, WaitQueue<T> *queue) :
    m_id(id), m_ammount(40), m_queue(queue) {}

    virtual ~Producer(){}
    bool produce();

    void start()
    {
        int rc = pthread_create(&thread, NULL, Producer::ThreadFunc, this);
        if (rc)
        {
         cout << "Error:unable to create thread," << rc << endl;
         return;
        }
    }

    void stop()
    {
        void* status;
        pthread_join(thread, &status);
    }
  
private:
    int m_id;
    int m_ammount;  
    pthread_mutex_t* m_lock;
    pthread_t thread;
    WaitQueue<T> *m_queue;

    static void* ThreadFunc(void *threadData)
    {
        Producer<int> *_this = (Producer<int>*)threadData;
        while(1)
        {
            if(!_this->produce())
            {
                break;
            }

        }
       pthread_exit(NULL);
    }

};


template <class T>
inline bool Producer<T>::produce()
{
    if (m_ammount > 0)
    {
       
        m_queue->wait_push(counter++);
        m_ammount--;

        return true;
    }
    return false;
     
}