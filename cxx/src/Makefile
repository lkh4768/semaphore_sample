CC = g++
CFLAGS = -Wall -c -g
LFLAGS = -Wall -g -lgtest -lgtest_main
SRCS = Semaphore.cxx Main.cxx
OBJS = $(SRCS:.cpp=.o) 
EXEC = SemaphoreApp 

$(EXEC) : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $@

.cxx.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o $(EXEC)
