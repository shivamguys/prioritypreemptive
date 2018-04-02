#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<iostream>
using namespace std;
int n;
void taketheprocess(struct process p[],int n);
void print(struct process p[],int n);
struct process
{
 int processno;
 int bursttime;
 int priority;
 
 
    
};
    int minindex;  
  int minimumburst;
void taketheprocess(struct process p[],int n)
{
    
    
    for(int i=1;i<=n;i++)
    {
        //cout<<"Enter the process no\n";
    p[i].processno=i;
    cout<<"Enter the burst time for Process no "<<i<<"\n";
    cin>>p[i].bursttime;
    }

    
    
}
void assignthepriority(struct process p[],struct process q[],int n)
{
    /*swapping*/
    for(int i=1;i<n;i++)
    {        for(int j=i+1;j<=n;j++)
        {
            if(p[i].bursttime>p[j].bursttime)
            {
            //    cout<<"true";
                swap(p[i].bursttime,p[j].bursttime);
                swap(p[i].processno,p[j].processno);
            }
            /*else if(p[i].bursttime==p[j].bursttime)
            {
                break;
            }*/
        }
    }
    
    
    /*swapping*/
    int tempn=n;
    for(int i=1;i<=n;i++)
    {
     p[i].priority=tempn--; 
    }
    //print(p,n);
 for(int i=1;i<=n;i++)
 {
  q[p[i].processno].priority=p[i].priority;
 }
 
 for(int i=1;i<n;i++)
    {        for(int j=i+1;j<=n;j++)
        {
            if(q[i].bursttime==q[j].bursttime && q[i].processno<q[j].processno && q[i].priority<q[j].priority)
            {
                swap(q[i].priority,q[j].priority);
            }
        }
    }
    
    
}
void print(struct process p[],int n)
{
    
 for(int i=1;i<=n;i++)
 {
     cout<<"Process no"<<p[i].processno<<"\n";
     cout<<"Burst time"<<p[i].bursttime<<"\n";
     cout<<"Priority is"<<p[i].priority<<"\n\n\n";
 }
}
void clone(struct process p[],struct process q[],int n)
{
    
    
    for(int i=1;i<=n;i++)
    {
        //q[i].bursttime=p[i].bursttime;
        q[i]=p[i];
    }
}

void calculatenextmintime(struct process p[],int n)
{
 minindex=1;  
   minimumburst=p[1].bursttime;
 for(int i=2;i<=n;i++)
 {
     if(p[i].bursttime<minimumburst)
     {
     
         minimumburst=p[i].bursttime;
     minindex=i;
         
    }
     
 }
    
}
        
main()
{
    
    cout<<"Enter total no of process\n";
    cin>>n;
    
    
    
    struct process p[n+1],q[n+1];
  

    taketheprocess(p,n);
    clone(p,q,n);
    assignthepriority(q,p,n);
  
  print(p,n);
    
 
}

    
    
    
