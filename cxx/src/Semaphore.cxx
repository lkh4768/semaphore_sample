#include "Semaphore.hxx"

Semaphore::Semaphore(key_t key, mode_t mode) : key_(key), mode_(mode)
{
	init();	
}

Semaphore::Semaphore(key_t key, mode_t mode, void(*callback_func)(void*), void* arg) : key_(key), mode_(mode), callback_func_(callback_func), callback_func_arg(arg)
{
	init();
}

void Semaphore::init()
{
	if((id = semget(key_, 1, mode_ | IPC_CREAT | IPC_EXCL)) == -1)
	{
		if(errno == EEXIST)
			id = semget(key_, 1, 0);
		else
		{
			std::string what1 = "Semaphore constructor -> semget() error - ";
			make_throw_what(what1);
			throw std::runtime_error(what1);
		}
	}
	else
	{
		arg.val = 1;
		if(semctl(id, 0, SETVAL, arg) == -1)
		{
			std::string what2 = "Semaphore constructor -> semctl() error - ";
			make_throw_what(what2);
			throw std::runtime_error(what2);
		}

	}
}

void Semaphore::make_throw_what(std::string& s)
{
	s += strerror(errno);
	s += "\n";
}

void Semaphore::p()
{
	struct sembuf p_buf;

	p_buf.sem_num = 0;
	p_buf.sem_op = -1;
	p_buf.sem_flg = SEM_UNDO;

	if(semop(id, &p_buf, 1) == -1)
	{
		std::string s = "Semaphore p() -> semop() error - ";
		make_throw_what(s);
		throw std::runtime_error(s);
	}
}

void Semaphore::v()
{
	struct sembuf v_buf;

	v_buf.sem_num = 0;
	v_buf.sem_op = 1;
	v_buf.sem_flg = SEM_UNDO;

	if(semop(id, &v_buf, 1) == -1)
	{
		std::string s = "Semaphore v() -> semop() error - ";
		make_throw_what(s);
		throw std::runtime_error(s);
	}
}

void Semaphore::execute()
{
	p();

	callback_func_(callback_func_arg);

	v();
}

void Semaphore::set_callback_func(void(*callback_func)(void*), void* arg)
{
	callback_func_ = callback_func;
	callback_func_arg = arg;
}

int Semaphore::get_id()
{
	return id;
}
