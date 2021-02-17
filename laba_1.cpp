#include <iostream>
#include <unistd.h> // для unsigned int sleep(unsigned int __seconds)
#include <pthread.h>
#include <string.h>


void* firstPotok( void* flag )
{
    while ( *(bool*)(flag) == false ){
        (std::cout << "1").flush();
        sleep(1);
    }
    pthread_exit( NULL );
}

void* secondPotok( void* flag )
{
    while ( *(bool*)(flag) == false ){
        (std::cout << "2").flush();
        sleep(2);
    }
    pthread_exit( (void*) 911 );
}

int main()
{
    bool flag = false;
    bool flag2 = false;
    pthread_t thread, thread2;

    printf("enter to exit\n");
    //Создание 1ого потока
    pthread_create(&thread,NULL, firstPotok, &flag);
    
    pthread_detach(thread);

    //Создание 2ого потока
    pthread_create(&thread2,NULL, secondPotok, &flag2);

    getchar();
    
    flag = true;
    flag2 = true;

    int code, code2;

    //Ожидаем завершение 2х потоков
    int i = pthread_join(thread, (void**)&code ); //Поток отсоединен
    (std::cout << "System error " << i << " " << strerror(i) << std::endl).flush();

    pthread_join(thread2, (void**)&code2 );

    //printf("First code is %d\n",code );
    printf("Second code is %d\n",code2 );

    return 0;
}
