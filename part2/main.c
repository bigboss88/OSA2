//#include "process.h"
#include "node.h"
#include "user.h"
#include "cpu.h"
#include <stdio.h>
#include <stdlib.h>
//Test
int find_CPU(struct cpu cpus[], int num_cpu,struct node *job){
//	printf("In find CPU\n");
	int i =0;
	//Firt look to see if the job is being worked on already
	for(i;i<num_cpu;i++){
		if(cpus[i].cur_job == job->job){return 0;} // if it's already being worked on then ignore it
	}
	i=0;
	//then look for which cpu it should use, first free one, or take over a longer job
	for(i;i<num_cpu;i++){
		//printf("%c\n",cpus[i].cur_job);
		if(cpus[i].cur_job == '*' ){
			// /printf("Setting in empty cpu\n");
			setWork(&cpus[i],job);
			//printf("Job in cpu %d: %c\n",i,cpus[i].cur_job );
			return 1;
		}
	}

	// if they are all full

	i=0;
	for(i;i<num_cpu;i++){
		if(cpus[i].job->pri > job->pri){ // based on priority
			setWork(&cpus[i],job);
		//	printf("Job in cpu %d: %c\n",i,cpus[i].cur_job );
			return 1;
		}
		//lots of nested ifs inbound don't look
		else if(cpus[i].job->pri == job->pri){ // if same priority 
			if(cpus[i].job->arr > job->arr){
				setWork(&cpus[i],job);
				return 1;
			}

			if(cpus[i].job->arr == job->arr){
				if(cpus[i].job->dur > job->dur){
				setWork(&cpus[i],job);
				return 1;
				}
			}
		}
	}
	return 0; // else job has to wait
}
//Does work on all cpus that has a job
int work_CPUS(struct cpu cpus[],int num_cpu){
	int i =0;
	for(i;i<num_cpu;i++){
		if(cpus[i].cur_job != '*'){
			doWork(&cpus[i]);
			empty(&cpus[i]);
		}
	}
	return 1;
}

void print_CPUS(struct cpu cpus[],int num_cpu,int time){
	int i =0;
	printf("%d 	",time);
	for(i;i<num_cpu;i++){
		if(cpus[i].cur_job != '*'){
			printf("%c	",cpus[i].cur_job);
		}
		else{
			printf("	");
		}
	}
	printf("\n");
}

int main(int argc, char  *argv[]){
	if(argc != 2){printf("%d Worng number of inputs, should be ./run int\n",argc);return 0;}
	int num_cpu = atoi(argv[1]);
	if(num_cpu < 1){printf("Can't have less than 1 cpu\n");return 0;}
	//printf("%d \n",num_cpu );
	struct cpu cpus[num_cpu];
	char dump[100];
	int time = 0;
	int i =0;
	for(i;i<5;i++){
		scanf("%s",dump);
	}
	char user[50];
	char job;
	int arrive;
	int dur;
	int pri;
	i = 0;
	struct node **job_list = (struct node**) malloc(sizeof(struct node));
	struct node *test;
	struct user **user_list = (struct user**) malloc(sizeof(struct user));
	int min =0;
	while(scanf("%s %c %d %d %d",user,&job,&arrive,&dur,&pri)>4){
		if(i==0){
			*job_list = init(user,job,arrive,dur,pri);
			*user_list = init_USER(user,arrive);
			min=arrive;
		}
		else{
			test = init(user,job,arrive,dur,pri);
			 insert(job_list,test);
			 insert_USER(user_list,user,arrive);
			 if(arrive < min){
			 	min = arrive;
			 }
		}
		i++;
	}
	printf("time");
	for(i = 0;i<num_cpu;i++){
		cpus[i] = init_CPU();
		printf("	CPU%d",i+1);
		
	}
	printf("\n");
	time = min;
	while(*job_list != NULL){ // while there are still jobs
		//if(time == 7 ){print_list(job_list);}
		struct node *cur = (struct node *) malloc(sizeof(struct node));
		cur = *job_list;

		while (cur != NULL){ // go through list;
			
			if(cur->arr <= time){ // if it has arrived
				//has arrived and is smallest dur
				//printf("dur of usr %d  arr of user %d\n",cur->dur,cur->arr );
				find_CPU(cpus, num_cpu,cur);
			}
			if(cur->dur <= 1){ // if this job is done remove it for some reason it will work on 0 so I set to 1
				struct node *tmp = (struct node *) malloc(sizeof(struct node));
				tmp =cur;
				setTime(user_list,tmp->user,time+1);
				cur = cur->next;
				pop(job_list,tmp->job);
			}
			if(cur == NULL){break;}

			cur = cur->next;
		}

		print_CPUS(cpus,num_cpu,time);
		work_CPUS(cpus,num_cpu);
		time++;
	}
	printf("%d 	IDLE\n", time++);
	printf("\nSummary\n");
	print_USERlist(user_list);
	delete_list(job_list);
	delete_USERlist(user_list);
}