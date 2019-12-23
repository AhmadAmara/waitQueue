#include "OsOpjectFactory.h"

class WindowsOsFactory: public OsOpjectFactory 
{

public:
	int Thread* createThread() { std::cout << "WindowsOsFactory" << std::endl;}
}