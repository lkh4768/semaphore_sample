#include "pv.h"

void handlesem(key_t skey)
{
	int semid;
	pid_t pid = getpid();

	if((semid = initsem(skey)) < 0)
		exit(1);

	printf("\nprocess %d before critical section\n", pid);

	p(semid);

	printf("process %d in critical section\n", pid);

	sleep(10);

	printf("process %d leaving critical section\n", pid);

	v(semid);

	printf("process %d exiting\n", pid);
	exit(0);
}

int main()
{
	key_t semkey = 0x200;
	int i;

	for(i = 0; i <3; i++)
	{
		if(fork() == 0)
			handlesem(semkey);
	}
	return 0;
}
