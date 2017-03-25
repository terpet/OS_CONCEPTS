//Producer Consumer Problem (Single Instance)
#include <stdio.h>
#include<stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX 5
#define MAXSLEEP 100
#define ROUNDS 10
sem_t hydro,group;
int h_num=0;
int o_num=0;
int water=0;
void *hydrogen()
{	int tid = pthread_self();
	while(1)
	{
	sleep((rand() % MAXSLEEP)%5);
	sem_post(&hydro);
	printf("\nHydrogen #%d",++h_num);
	sem_wait(&group);	
	
	}
}
void *oxygen()
{	
	int tid = pthread_self();
	while(1)
	{
		//sleep((rand() % MAXSLEEP)%5);
	printf("\nOxygen #%d",++o_num);
	sem_wait(&hydro);
	sem_wait(&hydro);
	printf("\n\nWater Generated (#%d)",++water);
	sem_post(&group);
	sem_post(&group);
	sleep((rand() % MAXSLEEP)%5);
}
}



int main(void) 
{	

    pthread_t tid0,tid1,tid2,tid3,tid4,tid5;
    {
	
	
	sem_init(&hydro, 0, 0);
    sem_init(&group, 0,0);

        pthread_create(&tid0, NULL, hydrogen, NULL);
        pthread_create(&tid1, NULL, oxygen, NULL);
        pthread_create(&tid2, NULL, hydrogen, NULL);
        pthread_create(&tid3, NULL, oxygen, NULL);
    	pthread_create(&tid4, NULL, hydrogen, NULL);
        pthread_create(&tid5, NULL, oxygen, NULL);
        
		pthread_join(tid0, NULL);
        pthread_join(tid1, NULL);
	    
		pthread_join(tid2, NULL);
        pthread_join(tid3, NULL);
	
		pthread_join(tid4, NULL);
        pthread_join(tid5, NULL);
	
	
	sem_destroy(&hydro);
    sem_destroy(&group);
	
	}
	
	
    return 0;
}
