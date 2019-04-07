#include<stdio.h>
#include<unistd.h>
int last1,last2,last3,numberOfProcess;
int turn=0,k=0,j=0,l=0,finish=0;
struct Process
{
	int waiting_time;
	int priority;
	int turn_around_time;
	int burst_time;
	int temp_burst;
	char processId[10];
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
int roundrobin(struct Process q1[])
{
	int queue_quanta=0;
	int ans=0;
	while(queue_quanta<10)
	{
		if(finish==numberOfProcess) 
		{	
			ans=1;
			break;
		}
		if(empty(q1)) 
		{
			ans=1;
			break;
		}
		if(j==numberOfProcess	) j=0;
		while(1)
		{
			if(q1[j].burst_time==0) 
			{
				j++;
				if(j==numberOfProcess	) j=0;
			}
			else break;
		}
		if(q1[j].burst_time>0 && q1[j].burst_time<=4 )
		{
			int t;
			t=10-queue_quanta;
			if(t>=q1[j].burst_time || t>=4)
			{
				int ab=q1[j].burst_time;
				turn=turn+q1[j].burst_time;
				q1[j].burst_time=0;
				q1[j].turn_around_time=turn;
				q1[j].waiting_time = q1[j].turn_around_time-q1[j].temp_burst;
				printf("\n\tProcess Id    ::  %s\n",q1[j].processId);
				printf("\tWaiting time  ::  %d\tTurn Around time:    %d\n",q1[j].waiting_time,q1[j].turn_around_time) ;
				queue_quanta=queue_quanta+ab;
				finish++;j++;
			}
			else 
			{
				q1[j].burst_time=q1[j].burst_time-t;
				turn=turn+t;
			 queue_quanta+=t;
			}
		}
		else if(q1[j].burst_time>4)
		{
			int t;
			t=10-queue_quanta;
			if(t>=4)
			{
				q1[j].burst_time=q1[j].burst_time-4;
				turn=turn+4;
				queue_quanta+=4;   j++;
			}
			else 
			{
				q1[j].burst_time=q1[j].burst_time-t;
				turn=turn+t;
				queue_quanta=queue_quanta+t;
					j++;
			}
		}
	}
	return ans;
}
int fcfs(struct Process q3[] )
{
	int empty=0,queue_quanta=0;
	while(queue_quanta<10)
	{
		if(q3[l].burst_time==0) 
		{
			empty=1;
			break;
		}
		int t;
		t=10 - queue_quanta;
		if(t>=q3[l].burst_time)
		{
			int x = q3[l].burst_time;
			turn = turn+x;
			q3[l].turn_around_time=turn;
			q3[l].waiting_time=q3[l].turn_around_time-q3[l].temp_burst;
			printf("\n\t Process Id   ::  %s\n",q3[l].processId);
			printf("\t Waiting time ::  %d\tTurn Around time::	%d\n",q3[l].waiting_time,q3[l].turn_around_time);
			queue_quanta+=x;
			l++;
			if(l==numberOfProcess)	
			{
				empty=1;
				break;
			}
		}
		else if(t<q3[l].burst_time)
		{
			int x=q3[l].burst_time;
			turn=turn+t; 
			q3[l].burst_time = q3[l].burst_time - t;
			queue_quanta = queue_quanta + t;
		}
	
	}
	return empty;
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
			printf("\t Waiting  time  ::  %d\tTurn Around time::	   %d\n",q2[k].waiting_time,q2[k].turn_around_time);
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
	int i;
	printf("enter number of processes::\t\t");
	scanf("%d",&numberOfProcess);
	struct Process p1[numberOfProcess]; 
	struct Process q1[numberOfProcess];
	struct Process q2[numberOfProcess];
	struct Process q3[numberOfProcess];
	for(i=0;i<numberOfProcess;i++)
	{
		q1[i].burst_time=q1[i].temp_burst=0;	
		q2[i].burst_time=q2[i].temp_burst=0;	
		q3[i].burst_time=q3[i].temp_burst=0;	
	}
	for(i=0;i<numberOfProcess;i++)
	{
		printf("\nenter number process id\t\t\t");
		scanf("%s",&p1[i].processId);
		printf(" enter number process priority\t\t");
		scanf("%d",&p1[i].priority);
		printf(" enter number process burst time\t");
		scanf("%d",&p1[i].burst_time);
		printf("\n");
		p1[i].temp_burst = p1[i].burst_time ;
		if(p1[i].priority>0 && p1[i].priority<=5)	
		{
			q3[last3]=p1[i];
			last3++;
			printf("added in q3\n");
		}
		else if(p1[i].priority>5 && p1[i].priority<=10)
		{
			q2[last2]=p1[i];
			last2++;
			printf("added in q2\n");
		}
		else if(p1[i].priority>10 )
		{
			q1[last1]=p1[i];
			last1++;
			printf("added in q1\n");			
		}
	}
	sort(q2);
while(1)
{
	int round,prior,fcfs_flag;
	round = roundrobin(q1);
	prior = priority(q2);
	fcfs_flag=  fcfs(q3);
	if(round==1 && prior==1 && fcfs_flag==1)	break;
	else continue;
}
return 0;
}
