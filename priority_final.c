#include<stdio.h>
#include<unistd.h>
int last2,numberOfProcess;
//struct 	Process p1[numberOfProcess];  
int turn=0,k=0,finish=0;
struct Process
{
	int waiting_time;
	int priority;
	int turn_around_time;
	char processId[10];
	int burst_time;
	int temp_burst;
};
void sort(struct Process a[])
{
	int i=0,j=0;
	for(i=0;i<last2;i++)
	{
		for(j=0;j<last2;j++)
		{
			if(a[i].priority>a[j].priority)
			{
				struct Process temp;
				temp=a[i];
				a[i]=a[j];
				a[j]=temp;
			}
		}
	}
}
int empty(struct Process a[])
{
	int i=0,ans=1;
	for(i=0;i<numberOfProcess;i++)
	{
		if(a[i].burst_time!=0)	
		{
			ans=0;
			break;
		}
	}
	return ans;
}
int priority(struct Process q2[] )
{
	int empty=0,queue_quanta=0;
	while(queue_quanta<10)
	{
		int t;
		t=10 - queue_quanta;
		if(q2[k].burst_time==0) 
		{
			empty=1;
			break;
		}
		if(t>=q2[k].burst_time)
		{
			int x = q2[k].burst_time;
			turn = turn+x;
			q2[k].turn_around_time=turn;
			q2[k].waiting_time=q2[k].turn_around_time-q2[k].temp_burst;
			printf("\n\t Process Id    ::  %s\n",q2[k].processId);
			printf("\t Waiting  time ::  %d\tTurn Around time::	   %d\n",q2[k].waiting_time,q2[k].turn_around_time);
			queue_quanta+=x;
			k++;
			if(k==numberOfProcess)	
			{
				empty=1;
				break;
			}
		}
		else if(t<q2[k].burst_time)
		{
			int x=q2[k].burst_time;
			turn=turn+t; 
			q2[k].burst_time = q2[k].burst_time - t;
			queue_quanta = queue_quanta + t;
		}
	}
	return empty;
}
int main()
{
	printf("enter number of processes\n");
	scanf("%d",&numberOfProcess);
	struct Process p1[numberOfProcess];  
	struct Process q2[numberOfProcess];
	int i;
	for(i=0;i<numberOfProcess;i++)
	{
		printf("enter number process id		  	");+
		scanf("%s",&p1[i].processId);
		printf("enter number process priority 	 	");
		scanf("%d",&p1[i].priority);
		printf("enter number process burst time 	");
		scanf("%d",&p1[i].burst_time);
		p1[i].temp_burst = p1[i].burst_time ;
		printf("\n\n");
		q2[i]=p1[i];
		last2++;
	}
	sort(q2);
while(1)
{
	int prior;
//	round = roundrobin(q1);
	prior = priority(q2); 
//	fcfs_flag=  fcfs(q3);
	if(prior==1)	break;
	else continue;
}
return 0;	
}

