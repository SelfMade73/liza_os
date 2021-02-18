#include <iostream>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex;

void* potok( void* flag )
{
    while ( *(bool*)(flag) == false ){
        if ( pthread_mutex_trylock( &mutex ) == 0 ){
            for (int i = 0; i < 8; ++i)
            {
                (std::cout << "1" ).flush();
                usleep(200000);
            }
            pthread_mutex_unlock( &mutex );
        }
        sleep(1);
    }
    pthread_exit( NULL );
}

void* potok2( void* flag )
{
    while ( *(bool*)(flag) == false ){
        if ( pthread_mutex_trylock( &mutex ) == 0 ){
            for (int i = 0; i < 8; ++i)
            {
                (std::cout << "2" ).flush();
                usleep(200000);
            }
            pthread_mutex_unlock( &mutex );
        }
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
    
    
    // Инициализация мьютекса
    pthread_mutex_init(&mutex, NULL);


    printf("press enter\n");
    //Создание 1 потока
    pthread_create(&thread1,NULL, potok, &flag);
    //Создание 2 потока
    pthread_create(&thread2,NULL, potok2, &flag2);

    getchar();

    flag = true;

    flag2 = true;

    //Ожидание потоков
    pthread_join(thread1, NULL );
    pthread_join(thread2, NULL );


    //Уничтожение мьютекса
    pthread_mutex_destroy(&mutex);

    return 0;
}
