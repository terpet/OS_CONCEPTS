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
	
	int temp=tid-1;
	
	if(temp%2==0)
	{
		sem_wait(&chopstick[temp]);				//Picking first ChopStick
		printf("Philosopher No. '%d' picked Chopstick'%d' \n\n",temp,temp);
		sleep(5);
		
		sem_wait(&chopstick[(temp+MAX-1)%MAX]);			//Picking Second Chopstick
		printf("Philosopher No. '%d' picked Chopstick'%d' \n\n",temp,(temp+MAX-1)%MAX);
		sleep(5);
	}
	else
	{
		sem_wait(&chopstick[(temp+MAX-1)%MAX]);			//Picking First ChopStick
		printf("Philosopher No. '%d' picked Chopstick'%d' \n\n",temp,(temp+MAX-1)%MAX);
		sleep(5);
		
		sem_wait(&chopstick[temp]);					//Picking Second ChopStick
		printf("Philosopher No. '%d' picked Chopstick'%d' \n\n",temp,temp);
		sleep(5);
	}

	printf("\n\nPhilosopher No. '%d' Eating !\n\n",temp);
	
	sem_post(&chopstick[temp]);			//Releasing First ChopStick
	printf("Philosopher No. '%d' released Chopstick'%d' \n\n",temp,temp);
	
	sem_post(&chopstick[(temp+MAX-1)%MAX]);			//Releasing Second ChopStick
	printf("Philosopher No. '%d' released Chopstick'%d' \n\n",temp,(temp+MAX-1)%MAX);
	
}
void main()
{
	pthread_t t[MAX];			//Declaring Thread Variable
	int i;
	
	for(i=0;i<MAX;i++)
	{
		sem_init(&chopstick[i], 0,1);		//Initialising Semaphore
	}
	
	for(i=0;i<MAX;i++)
	{
	pthread_create(&t[i], NULL, P, NULL);		//Creating Thread
	}
	
	for(i=0;i<MAX;i++)
	{
	pthread_join(t[i], NULL);
	}
	
	for(i=0;i<MAX;i++)
	{
		sem_destroy(&chopstick[i]);		//Destroying Semaphore
	}
	return 0;
}
