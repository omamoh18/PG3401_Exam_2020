#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <stdbool.h>

char array[10];
sem_t pSemConsumer;
sem_t pSemProducer;

void* workerThread (void* p) {

   FILE *pFile;
   char **argV = (char**) p;
   int i = 0;

   // Open the file for reading 
   pFile = fopen(argV[1], "r");
   while (!feof(pFile)) {
          // Waiting for consumer to have an open slot
         sem_wait(&pSemProducer);
         
         if(fgets(array, 10, pFile) == NULL) break;
         i++;
         
         // Checking if data is produced
         printf("Wroking thread produced data : %s\n", array);
         
         // Signaling that something is produced
         sem_post(&pSemConsumer); 
   }
   
   // Closing the semaphore's
   sem_close(&pSemProducer);
   sem_close(&pSemConsumer);
}

int main (int argc, char **argV) {

    // Counter for how many letters read
    int counter = 0;
    
   // The thread id
   pthread_t id;
    
   // Create thread
   pthread_create(&id, NULL, workerThread, argV);
  
   // Initialing semaphore for producer
   sem_init(&pSemProducer, 0, 1);
   
   // Initialing semaphore for consumer
   sem_init(&pSemConsumer, 0, 0);
   
   while (true) {

         // Waiting for producer signal
         sem_wait(&pSemConsumer);
         
         if (strlen(array) > 0) {
            printf("Consumer is Reading data : %s\n", array);
            bool done = (strcmp(array, "quit") == 0);
            array[0] = 0;
            if (done){break;}
            
         }
          
         // Sending signal to producer
         sem_post(&pSemProducer);
         
         
   }
   
   // Closing the semaphore's
   sem_close(&pSemConsumer);
   sem_close(&pSemProducer);
}

