#include <iostream>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/types.h>


int main()
{
    const char *name = "Shared Memory";
    const char *fillSem = "Full";
    const char *avail = "Available";
    const char *mutexSem = "Mutex"; //for semaphores open fucntion
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

    fill = sem_open(fillSem, O_CREAT, 0666, 0);

    ready = sem_open(avail, O_CREAT, 0666, 3);

    mutex = sem_open(mutexSem, O_CREAT, 0666, 1);

    std::cout << "\n"
              << std::endl;
    while (loop_count--)
    {
        
        sem_wait(ready);
        sleep(rand()%2+1); //wait to see if it is available, and wait on the mutex lock
        sem_wait(mutex);

        // limit table size
        if (*buffer < SIZE)
        {
            (*buffer)++; //added an item to the buffer
            std::cout << "Produced an item" << std::endl;
            sem_post(mutex); 
            sem_post(fill); // send that semaphore is open

            if (*buffer == SIZE)
            {
                std::cout << "The producer table is full\n";
            }
        }
    }

    
    std::cout << "limit " << *buffer << " left\n";

    // Close and unlink semaphores Remove Shared memory
    sem_close(fill);
    sem_close(ready);
    sem_close(mutex);       //once you open, need to close
    sem_unlink(fillSem);
    sem_unlink(avail);
    sem_unlink(mutexSem);

    // close and unlink shared memory
    munmap(buffer, sizeof(int));
    close(shared_memory_file_descriptor);
    shm_unlink(name);

    return 0;
}