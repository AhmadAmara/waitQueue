#include <iostream>

class LinuxThread : public MyThread
{
public:
	int th_join() { std::cout << "LinuxThread th_join" <<std::endl;}
	
}
