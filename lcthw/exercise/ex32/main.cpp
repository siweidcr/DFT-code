#include <iostream>
#include <cstring>

char* memoryOverflowExample()
{
    char* ret = new char;
    
    strcpy(ret, "Hello World\r\n");

    return ret;
}

int main()
{
    char* ret = memoryOverflowExample();
    std::cout << ret << std::endl;
    delete ret;
}

