CC = g++
CFLAGS = -Wall -c -g
LFLAGS = -Wall -g -lgtest -lgtest_main
SRCS = ../src/Semaphore.cxx SemaphoreTest.cxx MainTest.cxx
OBJS = $(SRCS:.cpp=.o) 
EXEC = testAll

$(EXEC) : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $@

.cxx.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o $(EXEC)
