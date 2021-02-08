#include <iostream>

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, const char** argv) {
    pid_t process_id = fork();
    int status_code;
    if ( !process_id  ){
        char *const params[] = { "laba_4_1", "Param1", "Param2", "Param3", NULL}; 
        execv(params[0],params);
    }
    else
    {
        //Ждем завершения дочернего процесса
        while( waitpid(process_id, &status_code, WNOHANG) == 0 )
            usleep(500000);
        std::cout  <<  "Grandparent process id " << getppid() << std::endl << "Parent process id " << getpid() << std::endl << "Child id " << process_id << std::endl;
        printf("Process finished with: %d\n",status_code );
    }
    return 0;
}