//Shared Memory : SERVER 

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
    
    int shmid;
    key_t key;
    
    struct details *infoptr;
	/*We'll name our shared memory segment"1658".*/
    key = 1658;
	/*Create the segment.*/
    shmid = shmget(key, SHMSZ, IPC_CREAT | 0666);
	/*Now we attach the segment to our data space.*/
    infoptr =(struct details *)shmat(shmid,NULL, 0);
    /*Now put some things into the memory for the other process to read.*/
    infoptr->roll=39;
    infoptr->mobile=94108;
    infoptr->marks[0]=45;
    infoptr->marks[1]=55;
    infoptr->marks[2]=60;
    infoptr->marks[0]=79;
    strcpy(infoptr->name,"tarpit");

    while (1)			//Keep The Server On !!
        sleep(1);

    exit(0);
    return 0;
}
