// C Program to Implement Safety Algorithm- (Banker's Algorithm- Deadlock Avoidance Algorithm) 
//This algo Prints whether the given system state is in SAFE state or UNSAFE state. If safe, then prints the SAFE SEQUENCE

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

struct process_info
{
    int max[10];
    int allocated[10];
    int need[10];
};

int no_of_process,no_of_resources;

//Take the input 
void input(struct process_info process[],int available[])
{
    //Fill array of Structure
    for(int i=0;i<no_of_process;i++)
    {
      printf("Enter process[%d] info\n",i);
      printf("Enter Maximum Need: ");
      for(int j=0;j<no_of_resources;j++)
        scanf("%d",&process[i].max[j]);
      printf("Enter No. of Allocated Resources for this process: ");
      for(int j=0;j<no_of_resources;j++)
      {
        scanf("%d",&process[i].allocated[j]); 
        //calculate need/future need 
        process[i].need[j]= process[i].max[j] - process[i].allocated[j];
      }
    }
    printf("Enter Available Resources: ");
    for(int i=0;i<no_of_resources;i++)
    {
      scanf("%d",&available[i]);
    }
}

//Print the Info in Tabular Form
void showTheInfo(struct process_info process[])
{
    printf("\nPID\tMaximum\t\tAllocated\tNeed\n");
    for(int i=0;i<no_of_process;i++)
    {
        printf("P[%d]\t",i);
        for(int j=0;j<no_of_resources;j++)
           printf("%d ",process[i].max[j]);
        printf("\t\t");
        for(int j=0;j<no_of_resources;j++)
           printf("%d ",process[i].allocated[j]); 
        printf("\t\t");
        for(int j=0;j<no_of_resources;j++)
           printf("%d ",process[i].need[j]);
        printf("\n");

    }
}

//Apply safety algo
bool applySafetyAlgo(struct process_info process[],int available[],int safeSequence[])
{
   bool finish[no_of_process];
   int work[no_of_resources];  
   for(int i=0;i<no_of_resources;i++)
   {
      work[i]=available[i];      
   }
   for(int i=0;i<no_of_process;i++)
     finish[i]=false;    
   bool proceed=true;
   int k=0;
   while(proceed)
   {
     proceed=false;
     for(int i=0;i<no_of_process;i++)
     {    
         bool flag=true;
         //Find Index i
         
         if(finish[i]==false)
         {
           
           for(int j=0;j<no_of_resources;j++)
           {
             //if Need <= Work
             if(process[i].need[j] <= work[j])
             {
               continue;
             }
             else
             {
               flag=false;  // implies that the current process need > work
               break;
             }
           }
           if(flag==false)
             continue;    //check for next process
          
          //If we get Index i(or process i), update work  
          for(int j=0;j<no_of_resources;j++)   
            work[j]=work[j]+ process[i].allocated[j];
          finish[i]=true;
          safeSequence[k++]=i;
          proceed=true;    // tells that we got atleast one process in safe state, we can proceed
          
         }
       }//end of outer for loop

     } // end of while

     //check finish array
     int i;
     for( i=0;i<no_of_process&&finish[i]==true;i++)
     {
       continue;
     }
     //If all processes are completed, then return true
     if(i==no_of_process)
      return true;
     else
      return false;
}

//Checks if we State is safe or not
bool isSafeState(struct process_info process[],int available[],int safeSequence[])
{
     
    if(applySafetyAlgo(process,available,safeSequence)==true)
      return true;
    return false;
   
}

int request_resources(int customer_no, int request[], struct process_info process[], int available[], int safeSequence[])
{

for(int i = 0; i < no_of_resources; i++)
{
    //printf("z");
    if(request[i] > process[customer_no].need[i])
    {
       // printf("a");
        return 0;
    }
    else if (request[i] > available[i])
    {
       // printf("b");
        printf("Must wait for allocation release");
        return 0;
    }
    else
    {
        //printf("c");
        available[i] -= request[i];
        process[customer_no].allocated[i] += request[i];
        process[customer_no].need[i] -= request[i];
    }
    
}

return isSafeState(process, available, safeSequence);

}


int release_resources(int customer_no, int release[], struct process_info process[], int available[])
{

for(int i = 0; i < no_of_resources; i++)
{
    if(release[i] > process[customer_no].allocated[i])
    {
        return 0;
    }

}

for(int i = 0; i < no_of_resources; i++)
{
    
        available[i] += release[i];
        process[customer_no].allocated[i] -= release[i];
        process[customer_no].need[i] += release[i];
    
}

return 1;

}


int main()
{
    

    printf("Enter No of Process\n");
    scanf("%d",&no_of_process);
    printf("Enter No of Resource Instances in system\n");
    scanf("%d",&no_of_resources);
    int available[no_of_resources];
    int safeSequence[no_of_process];
    //Create Array of Structure to store Processes's Informations
    struct process_info process[no_of_process];

    int customer_no;
    int request[no_of_resources];
   
    printf("***********Enter details of processes*************\n");
    //Take the Input
    input(process,available);

      char ch = 'y';
      char ch1[2];

      while(ch == 'y')
      {
          scanf("%s",ch1);
          scanf("%d",&customer_no);
          for(int i = 0; i < no_of_resources; i++)
            {
          scanf("%d",&request[i]);
            }

           // printf("%s", ch1);
          if(ch1[0] == 'R' && ch1[1] == 'Q')
          {
              //printf("tset");
                if(request_resources(customer_no,request, process,available,safeSequence))
                {

                printf("\nSystem is in SAFE State\n");
                printf("Safe Sequence is: ");
                for(int i=0;i<no_of_process;i++)
                printf("P[%d] ",safeSequence[i]);
                printf("1\n");
                  printf("\nAvailable Resources: \n");
                 for(int i = 0; i < no_of_resources; i++)
                  {
                      printf("%d ",available[i]);
                  }
                  printf("\n");
                }
                else
                printf("0\n");
          }
          else
          {
              if(release_resources(customer_no,request,process,available))
              {
                  printf("\nSuccessfully released resources from P%d\n",customer_no);
                  printf("\nAvailable Resources: \n");
                  for(int i = 0; i < no_of_resources; i++)
                  {
                      printf("%d ",available[i]);
                  }
                  printf("\n");
              }
              else
              {
                  printf("\nFailed to release resources (tried to release more than what was allocated.)");
              }
          }
      }

    return 0;
}