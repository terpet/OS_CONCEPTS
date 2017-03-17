#include <stdio.h>
#include<stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX 5
#define MAXSLEEP 100
#define ROUNDS 10
sem_t chopstick[MAX];		//Semaphore Declaration

void *P()
{	
	int tid=pthread_self();		//Getting Thread ID
	
	sem_wait(&chopstick[tid-1]);				//Picking First ChopStick
	printf("Philosopher No. '%d' picked Chopstick'%d' \n\n",tid-1,tid-1);
	sleep(5);
	
	sem_wait(&chopstick[(tid-1+MAX-1)%MAX]);				//Picking Second ChopStick
	printf("Philosopher No. '%d' picked Chopstick'%d' \n\n",tid-1,(tid-1+MAX-1)%MAX);
	sleep(5);
	
	printf("\n\nPhilosopher No. '%d' Eating !\n\n",tid-1);
	
	sem_post(&chopstick[tid-1]);			//Releasing First ChopStick
	printf("Philosopher No. '%d' released Chopstick'%d' \n\n",tid-1,tid-1);
	
	sem_post(&chopstick[(tid-1+MAX-1)%MAX]);			//Releasing Second ChopStick
	printf("Philosopher No. '%d' released Chopstick'%d' \n\n",tid-1,(tid-1+MAX-1)%MAX);
	
}
void main()
{
	
	printf("Dining Philosopher Problem !\nIncorrect Solution (DeadLock Prone)\n\n");
	
	pthread_t t[MAX];			//Thread Array Declaration
	int i;
	
	for(i=0;i<MAX;i++)
	{
		sem_init(&chopstick[i], 0,1);		//Initialising Semaphore
	}
	
	for(i=0;i<MAX;i++)
	{
	pthread_create(&t[i], NULL, P, NULL);			//Creating THread
	}
	
	for(i=0;i<MAX;i++)
	{
	pthread_join(t[i], NULL);
	}
	
	for(i=0;i<MAX;i++)
	{
	sem_destroy(&chopstick[i]);			//Destroying Semaphores
	}
}
