#include <iostream>
#include "waitQueue.h"
#include <iostream>
#include <stdlib.h> 

using namespace std;


#include "consumer.h"
#include "producer.h"
#include <iostream>
#include <vector>
#include <stdlib.h> 
#include <cstdlib>

pthread_mutex_t boxesLock;
using namespace std;

struct thread_data
{
   int  thread_id;
   std::vector<int>* boxes;
	pthread_mutex_t* lock;
};





void* run_consume(void *threadData)
{

	Consumer<int> *consumer = (Consumer<int>*)threadData;
	while(1)
	{
		if(!consumer->consume())
		{
			break;
		}

	}
	delete consumer;
   pthread_exit(NULL);

}

int main()
{
	Producer<int>* p[3];
	Consumer<int>* c[4];

	int i;
	int padding = 3;

	WaitQueue<int>  *wqueue = new WaitQueue<int>(6);
	for( i = 0; i < 3; i++ )
	{
      cout <<"main() : creating producers thread num , " << i << endl;
	  p[i] =  new Producer<int>(i, wqueue);
	  p[i]->start();
	}

	for( i = 0; i < 4; i++ )
	{
      cout <<"main() : creating consumers thread num , " << i + padding << endl;
	  c[i] =  new Consumer<int>(i, wqueue);
	  c[i]->start();
	}




   for( i = 0; i < 3; i++ ) {
   		p[i]->stop(); 
   }

	for( i = 0; i < 4; i++ ) {
   		c[i]->stop(); 
   }

   

   pthread_exit(NULL);

}

