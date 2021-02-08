#include <iostream>
#include <pthread.h>
#include <vector>
#include <unistd.h>
#include <fcntl.h>  

int descripotrs[2];

void* writer( void* flag )
{
    std::string msg; //buffer for messages
    while ( *(bool*)(flag) == false ){
        msg =  std::to_string ( rand() );
        write(descripotrs[1],msg.c_str(), msg.size());
        sleep(3);
    }
    pthread_exit( NULL );
}

void* reader( void* flag )
{
    std::vector<char> msg;
    while ( *(bool*)(flag) == false ){
        msg.resize(100);
        read(descripotrs[0],msg.data(), msg.size());
        msg.shrink_to_fit();
        std::cout << "writer sent -> " <<  std::string(msg.data(), msg.size())  << std::endl;
        sleep(1);
    }
    pthread_exit( NULL );
}

int main()
{
    pthread_t thread1, thread2;
    bool flag = false;
    bool flag2 = false;
    int code, code2;
    pipe2(descripotrs, O_NONBLOCK);
    printf("press enter\n");
    //Создание 1 потока
    pthread_create(&thread1,NULL, writer, &flag);
    //Создание 2 потока
    pthread_create(&thread2,NULL, reader, &flag2);
    getchar();
    flag = true;
    flag2 = true;
    //Ожидание потоков
    pthread_join(thread1, NULL );
    pthread_join(thread2, NULL );
    close(descripotrs[0]);
    close(descripotrs[1]);
    return 0;
}

