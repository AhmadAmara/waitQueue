#include <iostream>
#include <queue>
#include <stdlib.h> 
#include <cstdlib>
#include <unistd.h>


size_t status = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t pop_cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t push_cond = PTHREAD_COND_INITIALIZER;


template<class T>
class WaitQueue
{
public:
	WaitQueue(size_t size) : m_size(size), m_capacity(0) {}

	T wait_pop();
	void wait_push(T t);
	void showq() const;
	size_t capacity() const { return m_capacity;}
	size_t size() const { return m_size;}

private:
	std::queue<T> m_queue;
	size_t m_size;
	size_t m_capacity;
};


template<class T>
inline T WaitQueue<T>::wait_pop()
{
	pthread_mutex_lock(&mutex); 
	T poped;

	while(m_capacity == 0)
	{
		std:: cout << "Waiting on pop condition variable cond" << std::endl;

		pthread_cond_wait(&pop_cond, &mutex);
	}

	poped = m_queue.front();
	m_queue.pop();
	m_capacity--;
	std:: cout << "poped : "<< poped <<" Signaling condition variable cond" << std::endl; 
	pthread_cond_signal(&push_cond); 

	pthread_mutex_unlock(&mutex); 


	std::cout << "Returning pop thread" << std::endl; 

	return poped;
}


template<class T>
inline void WaitQueue<T>::wait_push(T t)
{

	pthread_mutex_lock(&mutex);

	while(m_capacity >= m_size)
	{
		std::cout << "Waiting on push condition variable cond" << std::endl;
		pthread_cond_wait(&push_cond, &mutex);
	}

	m_queue.push(t);
	m_capacity++;
	std::cout << "pushed "<< t <<" :  Signaling condition variable cond" << std::endl; 
	pthread_cond_signal(&pop_cond);

	pthread_mutex_unlock(&mutex); 
	std::cout << "Returning push thread" << std::endl; 
	return;
}

template<class T>
inline void WaitQueue<T>::showq() const
{ 
    std::queue <T> g = m_queue; 
    if(m_capacity == 0)
    {
    	std::cout << '\t' <<"The waitQueue is empty" << std::endl; 
    }
    while (!g.empty()) 
    { 
        std::cout << '\t' << g.front(); 
        g.pop(); 
    } 
    std::cout << '\n'; 
}