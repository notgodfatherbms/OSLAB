#include <stdio.h>
#define MAX 20

/* ---------- Priority Non Preemptive ---------- */

void priority_np(int n,int at[],int bt[],int pr[])
{
int wt[MAX]={0},tat[MAX],rt[MAX],ct[MAX],done[MAX]={0};
int g[MAX],gt[MAX+1];

int time=0,count=0,k=0;

float sw=0,st=0,sr=0;

gt[0]=0;

while(count<n)
{
int idx=-1,min=9999;

for(int i=0;i<n;i++)
if(at[i]<=time && !done[i] && pr[i]<min)
{
min=pr[i];
idx=i;
}

if(idx!=-1)
{
g[k]=idx;

rt[idx]=time-at[idx];
wt[idx]=time-at[idx];

time+=bt[idx];

ct[idx]=time;
tat[idx]=ct[idx]-at[idx];

done[idx]=1;

k++;
gt[k]=time;

count++;
}
else
time++;
}

printf("\nGantt Chart:\n|");

for(int i=0;i<k;i++)
printf(" P%d |",g[i]+1);

printf("\n");

for(int i=0;i<=k;i++)
printf("%d ",gt[i]);

printf("\n\nPID AT BT CT WT TAT RT\n");

for(int i=0;i<n;i++)
{
printf("%d %d %d %d %d %d %d\n",
i+1,at[i],bt[i],ct[i],wt[i],tat[i],rt[i]);

sw+=wt[i];
st+=tat[i];
sr+=rt[i];
}

printf("\nAvg WT=%.2f\n",sw/n);
printf("Avg TAT=%.2f\n",st/n);
printf("Avg RT=%.2f\n",sr/n);
}


/* ---------- Priority Preemptive ---------- */

void priority_p(int n,int at[],int bt[],int pr[])
{
int rt_bt[MAX],wt[MAX]={0},tat[MAX],rt[MAX],ct[MAX];
int g[100],gt[100];

for(int i=0;i<n;i++)
{
rt_bt[i]=bt[i];
rt[i]=-1;
}

int time=0,complete=0,k=0;
float sw=0,st=0,sr=0;

gt[0]=0;

while(complete<n)
{
int idx=-1,min=9999;

for(int i=0;i<n;i++)
if(at[i]<=time && rt_bt[i]>0 && pr[i]<min)
{
min=pr[i];
idx=i;
}

if(idx!=-1)
{
g[k]=idx;

if(rt[idx]==-1)
rt[idx]=time-at[idx];

rt_bt[idx]--;

time++;

k++;
gt[k]=time;

if(rt_bt[idx]==0)
{
complete++;

ct[idx]=time;
tat[idx]=ct[idx]-at[idx];
wt[idx]=tat[idx]-bt[idx];
}
}
else
time++;
}

printf("\nGantt Chart:\n|");

for(int i=0;i<k;i++)
printf(" P%d |",g[i]+1);

printf("\n");

for(int i=0;i<=k;i++)
printf("%d ",gt[i]);

printf("\n\nPID AT BT CT WT TAT RT\n");

for(int i=0;i<n;i++)
{
printf("%d %d %d %d %d %d %d\n",
i+1,at[i],bt[i],ct[i],wt[i],tat[i],rt[i]);

sw+=wt[i];
st+=tat[i];
sr+=rt[i];
}

printf("\nAvg WT=%.2f\n",sw/n);
printf("Avg TAT=%.2f\n",st/n);
printf("Avg RT=%.2f\n",sr/n);
}


/* ---------- Round Robin ---------- */

void rr(int n,int at[],int bt[],int q)
{
int rt_bt[MAX],wt[MAX]={0},tat[MAX],rt[MAX],ct[MAX];
int g[100],gt[100];

for(int i=0;i<n;i++)
{
rt_bt[i]=bt[i];
rt[i]=-1;
}

int time=0,complete=0,k=0;

float sw=0,st=0,sr=0;

gt[0]=0;

while(complete<n)
{
for(int i=0;i<n;i++)
{
if(at[i]<=time && rt_bt[i]>0)
{
g[k]=i;

if(rt[i]==-1)
rt[i]=time-at[i];

if(rt_bt[i]>q)
{
time+=q;
rt_bt[i]-=q;
}
else
{
time+=rt_bt[i];

ct[i]=time;
tat[i]=ct[i]-at[i];
wt[i]=tat[i]-bt[i];

rt_bt[i]=0;
complete++;
}

k++;
gt[k]=time;
}
}
time++;
}

printf("\nGantt Chart:\n|");

for(int i=0;i<k;i++)
printf(" P%d |",g[i]+1);

printf("\n");

for(int i=0;i<=k;i++)
printf("%d ",gt[i]);

printf("\n\nPID AT BT CT WT TAT RT\n");

for(int i=0;i<n;i++)
{
printf("%d %d %d %d %d %d %d\n",
i+1,at[i],bt[i],ct[i],wt[i],tat[i],rt[i]);

sw+=wt[i];
st+=tat[i];
sr+=rt[i];
}

printf("\nAvg WT=%.2f\n",sw/n);
printf("Avg TAT=%.2f\n",st/n);
printf("Avg RT=%.2f\n",sr/n);
}


/* ---------- MAIN ---------- */

int main()
{
int n,choice,q;
int at[MAX],bt[MAX],pr[MAX];

printf("Enter number of processes: ");
scanf("%d",&n);

for(int i=0;i<n;i++)
{
printf("Enter AT BT PR for P%d: ",i+1);
scanf("%d%d%d",&at[i],&bt[i],&pr[i]);
}

printf("\n1. Priority Non Preemptive");
printf("\n2. Priority Preemptive");
printf("\n3. Round Robin");

printf("\nEnter choice: ");
scanf("%d",&choice);

switch(choice)
{
case 1:
priority_np(n,at,bt,pr);
break;

case 2:
priority_p(n,at,bt,pr);
break;

case 3:
printf("Enter Time Quantum: ");
scanf("%d",&q);
rr(n,at,bt,q);
break;

default:
printf("Invalid Choice");
}

return 0;
}
