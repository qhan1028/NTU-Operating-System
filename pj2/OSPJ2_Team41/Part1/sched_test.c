#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sched.h>
#include <string.h>
#include <sys/types.h>

void *thread_func(void *arg) 
{
	double block = CLOCKS_PER_SEC * 0.5;
	for (int i=0 ; i<3 ; i++) {
		printf("thread %d running %d\n", *(int*)arg, i+1);
		while (clock() < block);
	}
	pthread_exit(arg);
}

int main(int argc, char* argv[]) 
{
	// set 1 cpu
	cpu_set_t set;
	CPU_ZERO(&set); CPU_SET(0, &set);
	sched_setaffinity(getpid(), sizeof(set), &set);
	printf("set affinity success\n");
	
	// set scheduling policy
	struct sched_param param;
	param.sched_priority = 99;
	if (argc>1 && strcmp(argv[1], "SCHED_FIFO")==0) 
		sched_setscheduler(getpid(), SCHED_FIFO, &param);
	printf("set seheduling policy success\n");
	
	// create thread
	pthread_t tid[2];
	pthread_attr_t attr;
	int args[2]={1,2};
	void *tret;

	for (int i=0 ; i<2 ; i++) {
		if (!pthread_create(&tid[i], NULL, thread_func, &args[i])) 
			printf("create thread %d success\n", i+1);
		else printf("create thread %d fail\n", i+1);
	}

	// delete thread
	for (int i=0 ; i<2 ; i++) {
		if (!pthread_join(tid[i], &tret)) printf("thread %d exit\n", *(int*)tret);
	}
	printf("\n");

	exit(0);
}
