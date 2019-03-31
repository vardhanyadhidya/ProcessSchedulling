#include<stdio.h>
#include<stdlib.h>
int time=0,queueTime=10,total;
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
void FCFS(struct project c[],int a)
{
	        int i;
		for(i=0;i<a;i++)
		{	
			if(c[i].Bursttime<=queueTime && c[i].arrival<=Time && c[i].Bursttime>0)
			{			
			if(c[i].start==-1)
			c[i].start=Time;
			c[i].Bursttime=0;
			Time=Time+c[i].Bursttime;
			queueTime-=c[i].Bursttime;
			if(c[i].Bursttime==0&&c[i].completion==-1)
			{
				c[i].completion=Time;
				total--;
			}
		    }
			else
			{
				if((c[i].Bursttime-queueTime>0) && c[i].arrival<=Time && c[i].Bursttime>0)
				{
				if(c[i].start==-1)
				c[i].start=Time;
				c[i].Bursttime=c[i].Bursttime-queueTime;
				Time=Time+queueTime;
				queueTime=0;
				if(c[i].brustTime==0 && c[i].completion==-1)
				{
					c[i].completion=Time;
					total--;
				}
				}
			}
		}
		queueTime=10;
}


