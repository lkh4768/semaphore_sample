#ifndef SEMAPHORE_H
#define SEMAPHORE_H
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#include <cstring>
#include <cerrno>

#include <string>
#include <stdexcept>

union semun
{
	int val;
	struct semid_ds *buf;
	ushort *array;
};


class Semaphore
{
	private:
		const key_t key_;
		const mode_t mode_;
		int id;
		union semun arg;
		void(*callback_func_)(void*);
		void* callback_func_arg;
		void init();
		void p();
		void v();
		void make_throw_what(std::string& s);
	public:
		Semaphore(key_t key, mode_t mode);
		Semaphore(key_t key, mode_t mode, void(*callback_func)(void*), void* arg);
		void execute();
		void set_callback_func(void(*callback_func)(void*), void* arg);
		int get_id();
};

#endif
