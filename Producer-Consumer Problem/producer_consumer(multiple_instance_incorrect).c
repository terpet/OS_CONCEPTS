//Producer Consumer Problem (Multiple Instance)
//Incorrect Implementation

#include <stdio.h>
#include<stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX 5
#define MAXSLEEP 100
#define ROUNDS 10
sem_t num_filled,num_empty;

int item=100,in=0,out=0,buffer[MAX];
int count=0;

void *producer()
{	int tid = pthread_self();
	
	while(1)
	{
	sleep((rand() % MAXSLEEP)%5);
	sem_wait(&num_empty);
	count++;
	buffer[in]=item;
	printf("\nProducer %d \nProduced Item '%d' at Index %d\n",tid,item,in);
	in=(in+1)%MAX;
	item+=100;
	sem_post(&num_filled);
	if(item%300==0)
	{
	printf("\nPress Any Key To Continue !!\n");
	
	getch();
	}
	}
}
void *consumer()
{	int temp,status;
	int tid = pthread_self();
	while(1)
	{

	sem_wait(&num_filled);
	temp=buffer[out];
	
	printf("\nConsumer %d \nConsumed Item '%d' from Index %d\n",tid,temp,out);
	out=(out+1)%MAX;
	sem_post(&num_empty);
	sleep((rand() % MAXSLEEP)%5);
}
}



int main(void) 
{	

    pthread_t tid0,tid1,tid2,tid3,tid4,tid5,tid6,tid7;
    {
	
	
	sem_init(&num_filled, 0, 0);
    sem_init(&num_empty, 0, MAX);

        pthread_create(&tid0, NULL, producer, NULL);
        pthread_create(&tid1, NULL, consumer, NULL);
        pthread_create(&tid2, NULL, producer, NULL);
        pthread_create(&tid3, NULL, consumer, NULL);
        pthread_create(&tid4, NULL, producer, NULL);
        pthread_create(&tid5, NULL, consumer, NULL);
        pthread_create(&tid6, NULL, producer, NULL);
        pthread_create(&tid7, NULL, consumer, NULL);
        
		pthread_join(tid0, NULL);
        pthread_join(tid1, NULL);
		pthread_join(tid2, NULL);
        pthread_join(tid3, NULL);
		pthread_join(tid4, NULL);
	    pthread_join(tid5, NULL);
		pthread_join(tid6, NULL);
	    pthread_join(tid7, NULL);
	
	
	sem_destroy(&num_filled);
    sem_destroy(&num_empty);
	
	}
	
	
    return 0;
}
