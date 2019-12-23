#include "OsOpjectFactory.h"

class LinuxObjectFactory: public OsOpjectFactory 
{

public:
	int Thread* createThread() { std::cout << "LinuxObjectFactory" << std::endl;}
}