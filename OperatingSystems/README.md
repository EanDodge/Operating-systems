#cs33211
Hello, my name is Ean DOdge. This is a program that has a producer and a consumer. They will have a shared 
buffer, and will use semaphores to get into the critical section

**What does the code contain?**
The project has two files in c++
producer.cpp has the producer included into it, and consumer.cpp includes the consumer

**how to run the program**
There are 3 lines of command prompt
1st: g++ producer.cpp -pthread -lrt -o producer
2nd: g++ consumer.cpp -pthread -lrt -o consumer
3rd: ./producer & ./consumer &

**problems faced**
The problem that i faced was learning the semaphores functions. 