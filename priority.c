#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<iostream>

using namespace std;
int n;
void taketheprocess(struct process p[],int n);
void print(struct process p[],int n);
bool check(struct process p[],int total,int currently);
void aftertime(struct process p[],int totaltime,int i,int previous,int currently,struct process q[],struct process t[]);
void aftertime2(struct process p[],int n,int currently,int previous,int totaltime,struct process q[],struct process t[]);
void clone(struct process p[],struct process q[],int n);
void sortonpriority(struct process p[],int n);
struct process
{
    //tat=ct-at
    //wt=tat-bursttime
 int processno;
 int bursttime;
 int priority;
  int end=0;
int start;
int turnaroundtime;
int waitingtime;

    
};
    int minindex;  
  int minimumburst;
  int totaltime=0;
  int previous=0;
void taketheprocess(struct process p[],int n)
{
    
    
    for(int i=0;i<n;i++)
    {
        //cout<<"Enter the process no\n";
    p[i].processno=i;
    cout<<"Enter the burst time for Process no "<<i<<"\n";
    cin>>p[i].bursttime;
    }

    
    
}
void calculatewt(struct process q[],struct process t[],int n)

{
    for(int i=0;i<n;i++)
    {
     q[i].waitingtime=q[i].turnaroundtime-t[i].bursttime;   
     q[i].bursttime=t[i].bursttime;
        
    }
    
    
}
void assignthepriority(struct process p[],struct process q[],int n)
{
    /*swapping*/
    for(int i=0;i<n;i++)
    {        for(int j=i+1;j<n;j++)
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
    for(int i=0;i<n;i++)
    {
     p[i].priority=tempn--; 
    }
    //print(p,n);
 for(int i=0;i<n;i++)
 {
  q[p[i].processno].priority=p[i].priority;
 }
 
 for(int i=0;i<n;i++)
    {        for(int j=i+1;j<n;j++)
        {
            if(q[i].bursttime==q[j].bursttime && q[i].processno<q[j].processno && q[i].priority<q[j].priority)
            {
                swap(q[i].priority,q[j].priority);
            }
        }
    }
    
    
}
void clone(struct process p[],struct process q[],int n)
{
    
    
    for(int i=0;i<n;i++)
    {
        //q[i].bursttime=p[i].bursttime;
        q[i]=p[i];
    }
}
void decrement(struct process p[],int currently,int previous,int totalp)
{
 
  /*  if(currently==1)
    {cout<<"values of currently and previous are"<<currently<<previous<<"and value of totalp is"<<totalp<<"\n";
     p[currently].start=0;
     p[currently].end=totalp-1;
     p[currently].bursttime=p[currently].bursttime-(p[currently].end-p[currently].start);   
    }
    else*/
    {
  //   cout<<"values of currently and previous are"<<currently<<previous<<"and value of totalp is"<<totalp<<"\n";
     p[currently].start=p[previous].end;
     p[currently].end=totalp;
    // previous=totalp;
     //cout<<p[currently].bursttime<<"this is the burst time\n";
    p[currently].bursttime=(p[currently].bursttime)-( p[currently].end -  p[currently].start);
       // cout<<p[currently].end-p[currently].start<<"this is minus of end start for"<<p[currently].processno<<"\n";
    }
    
}
void execute(struct process p[],int currently,struct process q[],struct process t[])
{
    int i,alltime;
    int tempburst;
    //while(1)
    {
     
        
        for(i=0;i<p[currently].bursttime;)
        {
         //totaltime>=currently
         ++totaltime;
         i++;
//         p[currently].bursttime=p[currently].bursttime-i;
         ++alltime;
         if(totaltime<=n-1 && i>=p[currently].bursttime)
         {
             decrement(p,currently,previous,totaltime);
          //p[currently].end=totaltime;   
         }
         if(totaltime<=n-1 && check(p,totaltime,currently))
         {
          decrement(p,currently,previous,totaltime);
          previous=currently;
          i=0;
          currently=totaltime;
          continue;
         }
         if(totaltime<=n-1 &&  !(check(p,totaltime,currently)) && p[currently].bursttime==0)
         {
 
             if(check(p,previous,totaltime))
             {
                 int t=currently;
             currently=previous;
             previous=t;
             i=0;
             continue;
             }
             else
             {
                 previous=currently;
              currently=totaltime;
              
              if(currently>n)
         {
          break;   
         }
              continue;   
             }
         }
         
         if(totaltime>n-1)
         {
          //   cout<<"this is the value of i and currently and previous"<<i<<currently<<previous<<"\n";
          break;   
         }
         
         //i++;
            
        }
        
        
    }
    aftertime(p,totaltime,i,previous,currently,q,t);
    
}
void calculatetime(struct process p[],int n)
{
 for(int i=0;i<n;i++)
 {
    p[i].turnaroundtime=p[i].end-p[i].processno;
    
    
}

}
void sortonpriority(struct process p[],int n)
{
 for(int i=0;i<n;i++)
 {
     for(int j=i+1;j<n;j++)
     {
         if(p[i].priority<p[j].priority)
         {
          swap(p[i],p[j]);   
             
         }
     }
 }
 //print(p,n);
    
}
void aftertime(struct process p[],int totaltime,int i,int previous,int currently,struct process q[],struct process t[])

{
 
  //  while(totaltime<totalbursttime)
    {
        
     for(;i<p[currently].bursttime;i++)
     {
        
      ++totaltime;  
        
        
    
         
    }
    decrement(p,currently,previous,totaltime);
    previous=currently;
    
    
    }
    clone(p,q,n);
   // print(q,n);
    sortonpriority(p,n);
 //   cout<<"value checkkkk  prev and curr"<<previous<<currently<<"\n";
    aftertime2(p,n,currently,previous,totaltime,q,t);
    
    
    
}




void aftertime2(struct process p[],int n,int currently,int previous,int totaltime,struct process q[],struct process t[])
{
    //print(p,n);
 for(int i=0;i<n;i++)
 {
    // cout<<p[i].processno<<"processno is being generated\n";
      //cout<<p[i].bursttime<<"bursttime is being generated\n";
     currently=p[i].processno;

     //currently=i;
     if(q[currently].bursttime!=0)
     {
   //      cout<<"value which cureent is holding if this block runs is"<<currently<<"and burst"<<p[i].bursttime<<"\n";
     for(int j=0;j<q[currently].bursttime;j++)
     {
         ++totaltime;
         
     }
     //    cout<<"currently"<<currently<<"\n";
     decrement(q,currently,previous,totaltime);
     previous=currently;
         
    }
 }
calculatetime(q,n); 
calculatewt(q,t,n);
 print(q,n); //remember this to uncomment
    
    
    
}
bool check(struct process p[],int total,int currently)
{
    
    if(p[total].bursttime!=0 && p[total].priority>p[currently].priority)
    {
        
    return true;    
    
            }
    else
        return false;
}
void print(struct process p[],int n)
{
    
 for(int i=0;i<n;i++)
 {
     cout<<"\n\n";
     cout<<"  Process no  -> "<<p[i].processno<<"\n";
     cout<<"  Burst time  -> "<<p[i].bursttime<<"\n";
     cout<<"  Priority is -> "<<p[i].priority<<"\n";
    cout<<" Process  Start time  is  -> "<<p[i].start<<"\n";
    cout<<" Process End Time Is  -> "<<p[i].end<<"\n";
    cout<<" Turn Around time is  -> "<<p[i].turnaroundtime<<"\n";
    cout<<" Waiting Time is  -> "<<p[i].waitingtime<<"\n";
     
}
}
        
main()
{
    
    cout<<"Enter total no of process\n";
    cin>>n;
    
    
    
    struct process p[n+1],q[n+1],t[n+1];
  

    taketheprocess(p,n);
    clone(p,q,n);
    assignthepriority(q,p,n);
    clone(p,t,n);
   // print(t,n);
    
   // print(p,n);
  execute(p,0,q,t);
 // calculatetime(p,t,n);
 //   print(t,n);
//print(q,n);
    
 
}

    
    
    
