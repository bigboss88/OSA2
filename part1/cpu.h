#ifndef cpu_h
#define cpu_h
#include "node.h"
struct cpu{
	struct node *job; 
}cpu_t;

struct cpu init_CPU();
int setWork(struct cpu acpu ,struct node *job,char cpus,int num_core);
int empty(struct cpu *acpu);
int doWork(struct cpu *acpu);
int hasJob(struct cpu *acpu);
#endif