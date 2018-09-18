//#include "process.h"
#include "node.h"
#include "user.h"
#include "cpu.h"
#include <stdio.h>
#include <stdlib.h>
//Test
int main(int argc, char  *argv[]){
	if(argc != 2){printf("%d Worng number of inputs, should be ./run int\n",argc);return 0;}
	int num_cpu = atoi(argv[1]);
	//printf("%d \n",num_cpu );
	struct cpu cpus[num_cpu];
	char dump[100];
	int time = 0;
	int i =0;
	for(i;i<4;i++){
		scanf("%s",dump);
	}
	char user[50];
	char job;
	int arrive;
	int dur;
	i = 0;
	struct node **job_list = (struct node**) malloc(sizeof(struct node));
	struct node *test;
	struct user **user_list = (struct user**) malloc(sizeof(struct user));
	int min =0;
	while(scanf("%s %c %d %d",user,&job,&arrive,&dur)>3){
		if(i==0){
			*job_list = init(user,job,arrive,dur);
			*user_list = init_USER(user,arrive);
			min=arrive;
		}
		else{
			test = init(user,job,arrive,dur);
			 insert(job_list,test);
			 insert_USER(user_list,user,arrive);
			 if(arrive < min){
			 	min = arrive;
			 }
		}
		i++;
	}
	char cpu_jobs[num_cpu];
	printf("time");
	for(i = 0;i<num_cpu;i++){
		printf("	CPU%d",i+1);
		cpu_jobs[i]='*';
	}
	printf("\n");
	time = min;
	while(*job_list != NULL){ // while there are still jobs
		struct node *cur = (struct node *) malloc(sizeof(struct node));
		cur = *job_list;
		struct node *work = (struct node *) malloc(sizeof(struct node*)); // this is one that should be worked on
		work = cur;
		while (cur != NULL){ // go through list
			if(work ==NULL ){work = cur;}
			if(cur->dur < work->dur && cur->arr <= time){ // The one that should be worked on
				//has arrived and is smallest dur
				work = cur;
			}
			if(cur->dur == 1){ // if this job is done remove it for some reason it will work on 0 so I set to 1
				struct node *tmp = (struct node *) malloc(sizeof(struct node));
				tmp =cur;
				setTime(user_list,tmp->user,time+1);
				cur = cur->next;
				pop(job_list,tmp->job);
			}

			if(cur == NULL){break;}
			cur = cur->next;
		}


		if(work!=NULL && work->dur>0){ // if you found a job
			work->dur = work->dur -1;
			printf("%d 	%c\n",time,work->job);
		}
		time++;
	}
	printf("%d 	IDLE\n", time++);
	printf("\nSummary\n");
	print_USERlist(user_list);
	delete_list(job_list);
	delete_USERlist(user_list);
}