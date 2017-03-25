//Shared Memory : CLIENT

/*Special Thanks to Dave Marshall for tutorials 
https://users.cs.cf.ac.uk/Dave.Marshall/C/
*/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#define SHMSZ 27

 
struct details
{
char name[50];
int roll;
int mobile;
int marks[4];
};


int main()
{
    struct details *infoptr;
    int shmid;
    key_t key;
    /*We need to get the segment named "1658", created by the server.*/
    key = 1658;
	/*Locate the segment.*/
    shmid = shmget(key, SHMSZ, 0666);
    /*Now we attach the segment to our data space.*/
    infoptr = shmat(shmid, NULL, 0);
	/*Now read what the server put in the memory.*/
	printf("%s %d %d",infoptr->name,infoptr->roll,infoptr->mobile);	
 	exit(0);
return 0;
}
