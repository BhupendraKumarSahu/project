#include<stdio.h>
#include<unistd.h>
int last1,last2,last3,numberOfProcess;
int quanta=1,turn=0,j=0,finish=0;
struct Process
{
	int waiting_time;
	int priority;
	int turn_around_time;
	char processId[10];
	int burst_time;
	int temp_burst;
};
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
		printf("\nprocess burst  %d\n",q1[j].burst_time);
		
		if(q1[j].burst_time>0 && q1[j].burst_time<=4 )
		{
		//	printf("\nif one\n");
			int t;
			t=10-queue_quanta;
		//	printf("\n t ::::%d\n",t);
			if(t>=q1[j].burst_time || t>=4)
			{
				int ab=q1[j].burst_time;
				printf("\nprocess done\n");
				turn=turn+q1[j].burst_time;
				q1[j].burst_time=0;
				
				q1[j].turn_around_time=turn;
				q1[j].waiting_time = q1[j].turn_around_time-q1[j].temp_burst;
			//	printf("\nwaiting time:  %d\nturnaround time:    %d\n",q1[j].waiting_time,q1[j].turn_around_time) ;
				queue_quanta=queue_quanta+ab;
				//printf("\nqueue_quanta    %d\n",queue_quanta);
				finish++;j++;
			//	printf("\n done something\n");
			}
			else 
			{
				
			//	printf("\n else\n");
				q1[j].burst_time=q1[j].burst_time-t;
				turn=turn+t;
				//q1[i].turn_around_time=turn;
				
			 queue_quanta+=t;
				//printf("\nqueue_quanta    %d\n",queue_quanta);

			}
		}
		else if(q1[j].burst_time>4)
		{
				//printf("\n done again something\n");
			int t;
			t=10-queue_quanta;
			if(t>=4)
			{
				//printf("\n  something\n");
				//printf("\n1.  %d\n",q1[j].burst_time);
				q1[j].burst_time=q1[j].burst_time-4;
			//	printf("\n2.  %d\n",q1[j].burst_time);
				turn=turn+4;
				//printf("\n3...  %d\n",q1[j].burst_time);
				queue_quanta+=4;   j++;
			//	printf("\nqueue_quanta    %d\n",queue_quanta);
				//printf("\n 5... %d\n",q1[j].burst_time);
				//q1[i].turn_around_time=turn;
				//printf("\n4.... %d\n",q1[j].burst_time);
			}
			else 
			{
				//printf("\n %d\n",queue_quanta);
				//printf("\n doething\n");
				q1[j].burst_time=q1[j].burst_time-t;
				turn=turn+t;
				queue_quanta=queue_quanta+t;
				//printf("\nqueue_quanta    %d\n",queue_quanta);
					j++;
			}
		}
	//	printf("end of the code");
	}
	return ans;
}
int main()
{
	printf("enter number of processes\n");
	scanf("%d",&numberOfProcess);
	struct 	Process p1[numberOfProcess];  
	struct Process q1[numberOfProcess];
	struct Process q2[numberOfProcess];
	struct Process q3[numberOfProcess];
	int i;
	for(i=0;i<numberOfProcess;i++)
	{
		//printf("enter number process id		  	");+
		//scanf("%s",&p1[i].processId);
		printf("enter number process priority 	 	");
		scanf("%d",&p1[i].priority);
		printf("enter number process burst time 	");
		scanf("%d",&p1[i].burst_time);
		p1[i].temp_burst = p1[i].burst_time;
		printf("\n\n");
		if(p1[i].priority>0 && p1[i].priority<=5)	
		{
			q3[last3]=p1[i];
			last3++;
			printf("\nadded in q3\n");
		}
		else if(p1[i].priority>5 && p1[i].priority<=10)
		{
			q2[last2]=p1[i];
			last2++;
			printf("\nadded in q2\n");

		}
		else if(p1[i].priority>10 && p1[i].priority<=15)
		{
			q1[last1]=p1[i];
			last1++;
			printf("\nadded in q1\n");			
		}
	}
	while(1)
	{
		if(!roundrobin(q1))  
		{
			printf("\n while loop continue\n");
			continue;
		}
		else    break;	
	} 
for(i=0;i<numberOfProcess;i++)
{
	printf("\nwaiting time:  %d\nturnaround time:    %d    ",q1[i].waiting_time,q1[i].turn_around_time) ;
}
return 0;}
