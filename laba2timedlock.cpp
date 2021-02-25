#include <iostream>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

timespec getTime ( int tm ) {
    timespec time;
    clock_gettime( CLOCK_REALTIME, &time );
    time.tv_sec += tm;
    return time;
};


sem_t sem;
void* func1( void* flag )
{
    while ( !*(bool*)flag ){
        timespec calculatedTime = getTime(3);
        if ( sem_timedwait(&sem, &calculatedTime ) == 0 ){
            for (int32_t i = 0; i < 8; ++i){
                (std::cout << "1" ).flush();
                usleep(100000);
            }
            sem_post(&sem);
        }
        sleep(3);
    }
    pthread_exit( NULL );
}

void* func2( void* flag )
{
    while ( !*(bool*)flag ){
        timespec calculatedTime = getTime(1);
        if ( sem_timedwait(&sem, &calculatedTime ) == 0 ){
            for (int32_t i = 0; i < 8; ++i){
                (std::cout << "2" ).flush();
                usleep(100000);
            }
            sem_post(&sem);
        }
        sleep(3);
    }
    pthread_exit( NULL );
}


int main()
{
    int res1, res2;
    pthread_t trd1, trd2;
    

    sem_init(&sem, 0, 1);
    bool flag1 = false, flag2 = false;
    std::cout << "Press enter" << std::endl;

    pthread_create(&trd1,NULL, func1, &flag1);
    pthread_create(&trd2,NULL, func2, &flag2);

    getchar();
    
    flag1 = true;
    flag2 = true;

    std::cout << "Waiting threads..." << std::endl;
    pthread_join(trd1, NULL );
    pthread_join(trd2, NULL );

    sem_destroy(&sem);

    return 0;
}