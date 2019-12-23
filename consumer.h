#include <iostream>
#include <pthread.h>
#include <vector>
#include <unistd.h>
#include <cstdlib>


template <class T>
class Consumer
{

public:
    Consumer(int id, WaitQueue<T> *queue) :
    m_id(id), m_ammount(30), m_queue(queue) {}

    virtual ~Consumer(){}
    bool consume();

    void start()
    {
        int rc = pthread_create(&thread, NULL, Consumer::ThreadFunc, this);
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
        Consumer<int> *_this = (Consumer<int>*)threadData;
        while(1)
        {
            if(!_this->consume())
            {
                break;
            }

        }
       pthread_exit(NULL);
    }

};


template <class T>
inline bool Consumer<T>::consume()
{
    if (m_ammount > 0)
    {
        
        m_queue->wait_pop();
        m_ammount--;
        return true;
    }
    return false;
     
}


