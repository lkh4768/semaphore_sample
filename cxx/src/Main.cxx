#include "Semaphore.hxx"

#include <unistd.h>

#include <cstdio>
#include <cstdlib>

void handle_sem(void* arg)
{
	pid_t* pid = (pid_t*)arg;

	printf("process %d in critical section\n", *pid);

	sleep(5);

	printf("process %d leaving critical section\n", *pid);
}

int main()
{
	key_t key = 0x200;
	mode_t mode = 0600;
	Semaphore* semaphore[3];

	try
	{
		for(int i =0; i < 3; i++)
			semaphore[i] = new Semaphore(key, mode);
	}
	catch(const std::exception e)
	{
		printf("main -> %s", e.what());
		exit(1);
	}

	for(int i = 0; i < 3; i++)
	{
		if(fork() == 0)
		{
			try
			{
				pid_t pid = getpid();
				semaphore[i]->set_callback_func(handle_sem, (void*)&pid);
				semaphore[i]->execute();
			}
			catch(const std::exception& e)
			{
				printf("main -> execute() -> %s", e.what());
				exit(1);
			}

			exit(0);
		}
	}

	exit(0);
}
