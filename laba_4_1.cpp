#include <iostream>
#include <unistd.h>

int main(int argc, const char** argv) 
{
    std::cout << "Its child process id: " << getpid() << std::endl;
    std::cout << "Its parent process id: " << getppid() << std::endl;

    if ( argc < 3 || argc > 5)
    {
        return -1;
    }

    for (size_t i = 1; i < argc; ++i)
    {
        printf("%s\n",argv[i]);
        sleep(1);
    }
    return 0;
}