#include<stdio.h>
#include<stdlib.h>
int time=0,queuetime=10,total;
struct Project
{
	int id;
	int start;
	int priority;
	int Bursttime;
	int value;
    int completion;
	int arrival;
};
void FCFS(struct Project c[],int a)
{
	        int i;
		for(i=0;i<a;i++)
		{	
			if(c[i].Bursttime<=queuetime && c[i].arrival<=time && c[i].Bursttime>0)
			{			
			if(c[i].start==-1)
			c[i].start=time;
			c[i].Bursttime=0;
			time=time+c[i].Bursttime;
			queuetime-=c[i].Bursttime;
			if(c[i].Bursttime==0&&c[i].completion==-1)
			{
				c[i].completion=time;
				total--;
			}
		    }
			else
			{
				if((c[i].Bursttime-queuetime>0) && c[i].arrival<=time && c[i].Bursttime>0)
				{
				if(c[i].start==-1)
				c[i].start=time;
				c[i].Bursttime=c[i].Bursttime-queuetime;
				time=time+queuetime;
				queuetime=0;
				if(c[i].Bursttime==0 && c[i].completion==-1)
				{
					c[i].completion=time;
					total--;
				}
				}
			}
		}
		queuetime=10;
}
int PALGO(struct Project c[],int a,int remaining)
{
	int small;
	int i;
	while(remaining!=0&&queuetime>0)
	{
	    small=a;
	    for(i=0;i<a;i++)
	    {	
	        if(c[i].arrival<=time && c[i].priority<c[small].priority && c[i].Bursttime>0)
	        {	
	            small=i;
	        }
	    }
	    if(c[small].start==-1)
	    {
	        c[small].start=time;
	    }
	    queuetime-=1;
	    c[small].Bursttime-=1;
	    if(c[small].Bursttime==0&&c[small].completion==-1)
	    {
	        c[small].completion=time;
	        total--;
	        remaining--;
	    }
	    time+=1;
	}
	queuetime=10;
}
void ROUNDROBIN(struct Project c[],int queueNo)
{		
		int timeQuantum=10;
		int i;
		for( i=0;i<queueNo;i++)
		{	
			if(timeQuantum<=queuetime&&c[i].arrival<=time)
			{
			if(c[i].start==-1)
			{
			c[i].start=time;
			}
			if(c[i].Bursttime>=timeQuantum)
			{
			c[i].Bursttime=c[i].Bursttime-timeQuantum;
			time=time+timeQuantum;
			queuetime-=timeQuantum;
			}
			if(c[i].Bursttime<timeQuantum&&c[i].Bursttime>0) 
			{
			time=time+c[i].Bursttime;
			queuetime-=c[i].Bursttime;
			c[i].Bursttime=0;
			}
			if(c[i].Bursttime==0&&c[i].completion==-1)
			{
				c[i].completion=time;
				total--;
			}
			}
		}
		queuetime=10;
}
int main()
{	
    int n,i,rr=0,pr=0,fcfs=0;
    int m=0;
	printf("-----------------------------------------*****************************************------------------------------------------------\n");
	printf("\t\t\t\tENTER NUMBER OF PROCESSES: ");
	scanf("%d",&n);
	total=n;
	struct Project ps[n];
    for(i=0;i<n;i++)
    {
    	printf("PROCESS %d :\n",i+1);
		ps[i].id=i+1;
		printf("Enter the Arrival time: ");
    	scanf("%d",&ps[i].arrival);
    	printf("Enter the priority 1 for Round Robin, 2 for First Come First Serve or 3 for Priority: ");
    	scanf("%d",&ps[i].priority);
    	if(ps[i].priority==1)
		rr++;
		else if(ps[i].priority==2)
		fcfs++;
		else if(ps[i].priority==3)
		pr++;
		printf("Enter burst time: ");
    	scanf("%d",&ps[i].Bursttime);	
		ps[i].value=ps[i].Bursttime;
		ps[i].start=-1;
    	ps[i].completion=-1;
	}
	int rrid=0,prid=0,fcfsid=0;
	struct Project roundqueue[rr],priorqueue[pr+1],fcfsqueue[fcfs];
	for(i=0;i<n;i++)
	{
		if(ps[i].priority==1)
		{
			roundqueue[rrid]=ps[i];
			rrid++;
		}
		else if(ps[i].priority==2)
		{
			fcfsqueue[fcfsid]=ps[i];
			fcfsid++;
		}
		else if(ps[i].priority==3)
		{
			priorqueue[prid]=ps[i];
			prid++;
		}
	}
	int remain=pr;
	while(total>0)
	{
		ROUNDROBIN(roundqueue,rr);
		remain=PALGO(priorqueue,pr,remain);
		FCFS(fcfsqueue,fcfs);
	}
	printf("Process Id\tArrival time\tBrust time\tStarting time\tTurn Around time\tPriority\n");
	int qu[n],st[n],pry[n];
	int j=0;
	double att,awt;
	for(i=0;i<rr;i++)
	{
		printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n",roundqueue[i].id,roundqueue[i].arrival,roundqueue[i].value,roundqueue[i].start,roundqueue[i].completion,roundqueue[i].priority);
		qu[j]=roundqueue[i].id;
		st[j]=roundqueue[i].start;
		pry[j]=roundqueue[i].priority;
		j++;
		att+=roundqueue[i].completion;
		awt+=roundqueue[i].completion-roundqueue[i].arrival;
	}
	for(i=0;i<fcfs;i++)
	{
		printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n",fcfsqueue[i].id,fcfsqueue[i].arrival,fcfsqueue[i].value,fcfsqueue[i].start,fcfsqueue[i].completion,fcfsqueue[i].priority);
		qu[j]=fcfsqueue[i].id;
                st[j]=fcfsqueue[i].start;
                pry[j]=fcfsqueue[i].priority;
                j++;
		att+=fcfsqueue[i].completion;
		awt+=fcfsqueue[i].completion-fcfsqueue[i].arrival;

	}
	for(i=0;i<pr;i++)
	{
		printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n",priorqueue[i].id,priorqueue[i].arrival,priorqueue[i].value,priorqueue[i].start,priorqueue[i].completion,priorqueue[i].priority);
		qu[j]=priorqueue[i].id;
                st[j]=priorqueue[i].start;
                pry[j]=priorqueue[i].priority;
                j++;
		att+=priorqueue[i].completion;
		awt+=priorqueue[i].completion-priorqueue[i].arrival;

	}
	printf("Gantt Chart\nStart");

	for(i=0;i<n;i++)
	{
		for(int j=i+1;m<n;m++)
		{
			if(st[i]>st[j])
			{
				st[i]=st[i]+st[j];
				st[j]=st[i]-st[j];
				st[i]=st[i]-st[j];
				qu[i]=qu[i]+qu[j];
                                qu[j]=qu[i]-qu[j];
                                qu[i]=qu[i]-qu[j];
				pry[i]=pry[i]+pry[j];
                                pry[j]=pry[i]-pry[j];
                                pry[i]=pry[i]-pry[j];

			}
		}
		printf(" --> Process %d ",qu[i]);
	}
	printf("\nAverage Turn-Around time = %.2f",att/n);
	printf("\nAverage Waiting time = %.2f\n",awt/n);
}
