#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "cpu.h"

struct cpu init_CPU(){
	struct cpu ncpu;
	ncpu.job = NULL;
	return ncpu;
}

int setWork(struct cpu acpu ,struct node *job,char *cpus, int num_core){
	//before it adds the job it checks to see if that job is being worked
	int i =0;
	for(i;i<num_core;i++){
		if(job->job == cpus[i]){return 0;} // can't give it a job if that jobs already being done
	}
	apcu.job= job->job;

}

int empty(struct cpu *acpu){
	acpu->job = NULL;
	return 1;
}

int doWork(struct cpu *acpu){
	if(acpu->job == NULL){return 0;} // No work to be done
	acpu->job->dur--;
}

int hasJob(struct cpu *acpu){
	if(acpu->job == NULL){return 0;}
	return 1;
}