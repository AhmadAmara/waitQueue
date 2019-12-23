#include <iostream>

class WindowsThread : public MyThread
{
public:
	int th_join() { std::cout << "WindowsThread th_join" <<std::endl;}

}
