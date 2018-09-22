#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "cpu.h"

struct cpu init_CPU(){
	struct cpu ncpu;
	ncpu.job = NULL;
	ncpu.cur_job = '*';
	return ncpu;
}

int setWork(struct cpu *acpu ,struct node *job){
	// sets the cpu job
	//printf("Setting work : %c\n",job->job );
	acpu->job = job;
	acpu->cur_job = job->job;
return 1;
}

int empty(struct cpu *acpu){
	acpu->job = NULL;
	acpu->cur_job = '*';
	return 1;
}

int doWork(struct cpu *acpu){
//	printf("In do work: %c\n",acpu->cur_job);
	if(acpu->cur_job == '*'){return 0;} // No work to be done
	//printf("Trying to accsess job\n");
//	printf("WORKING ON JOB %c\n",acpu->cur_job );
//	printf("%d\n", acpu.job->dur);
	acpu->job->dur--;
//	printf("Did work\n" );
	return 1;
}

char hasJob(struct cpu *acpu){
	if(acpu->job != NULL){return acpu->job->job;}
	return '*';

}

void destroy_CPU(struct cpu acpu){
	//free(&acpu);
}
