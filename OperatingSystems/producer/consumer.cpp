#include <iostream>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/types.h>

void PrintSemaphoreValue(std::string name, sem_t *semaphore, int &value);
int main()
{
    const char *name = "Shared Memory";
    const char *fillSem = "Full";
    const char *avail = "Available"; //for semaphores open functions
    const char *mutexSem = "Mutex";
    const int SIZE = 2;
    sem_t *fill, *ready, *mutex;
    int shared_memory_file_descriptor;
    int *buffer;
    int loop_count = 5;

    // Make shared process between prod and cons
    shared_memory_file_descriptor = shm_open(name, O_CREAT | O_RDWR, 0666);

    // Set the size of the memory
    ftruncate(shared_memory_file_descriptor, sizeof(int));

    buffer = (int *)mmap(0, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shared_memory_file_descriptor, 0);

    fill = sem_open(fillSem, O_RDWR);

    ready = sem_open(avail, O_RDWR);

    mutex = sem_open(mutexSem, O_RDWR);

    int value = -1;
    while(loop_count--){
        std::cout<<"in con\n";
        sem_wait(fill);
        //sleep(rand()%2+1);
        sem_wait(mutex);

        (* buffer)--;
        sem_post(mutex);
        std::cout << "consumed an item\n"; //take item out of buffer
        sem_post(ready); //send that semephore is open
    }
    
    std::cout << "limit " << *buffer << " left\n";
    
    
    // Close and unlink semaphores Remove Shared memory
    sem_close(fill);
    sem_close(ready);
    sem_close(mutex);
    sem_unlink(fillSem); //once you open, you need to close
    sem_unlink(avail);
    sem_unlink(mutexSem);

    /* close and unlink shared memory*/
    munmap(buffer, sizeof(int));
    close(shared_memory_file_descriptor);
    shm_unlink(name);

    return 0;
}



void PrintSemaphoreValue(std::string name, sem_t *semaphore, int &value) {
    std::cout << name << " value: " << sem_getvalue(semaphore, &value) << std::endl;
}
