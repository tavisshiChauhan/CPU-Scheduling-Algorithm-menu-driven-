#include<iostream>
#include <climits>
#include<math.h>
#include<string.h>
using namespace std;

int wt[100],bt[100],at[100],tat[100],n,p[100];
int temp1,temp2,temp3,sqt,avg;
int twt = 0, ttat = 0;

void input()
{
    cout << "Enter the no of processes" << endl;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        p[i] = i + 1;
    }
    cout << "Enter the arrival time" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "Arrival time of process p[" << i+1 <<"] :  ";
        cin >> at[i];
        cout << endl;
    }
    cout << "Enter the burst time" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "burst time of process p[" << i+1 <<"] :  ";
        cin >> bt[i];
        cout << endl;
    }
}

void FirstComeFirstServe(){
    int service_time[n];
	service_time[0] = at[0];
	wt[0] = 0;

	for (int i = 1; i < n ; i++)
	{
		service_time[i] = service_time[i-1] + bt[i-1];

		wt[i] = service_time[i] - at[i];

		if (wt[i] < 0)
			wt[i] = 0;
	}
    for (int i = 0; i < n ; i++)
		tat[i] = bt[i] + wt[i];
    cout << "Processes " << " Burst Time " << " Arrival Time "
		<< " Waiting Time " << " Turn-Around Time "
		<< " Completion Time \n";
	int total_wt = 0, total_tat = 0;
	for (int i = 0 ; i < n ; i++)
	{
		total_wt = total_wt + wt[i];
		total_tat = total_tat + tat[i];
		int compl_time = tat[i] + at[i];
		cout << " " << i+1 << "\t\t" << bt[i] << "\t\t"
			<< at[i] << "\t\t" << wt[i] << "\t\t "
			<< tat[i] << "\t\t " << compl_time << endl;
	}

	cout << "Average waiting time = "
		<< (float)total_wt / (float)n;
	cout << "\nAverage turn around time = "
		<< (float)total_tat / (float)n;
 }

void ShortestJobFirst()
{
	float wavg=0,tavg=0,tsum=0,wsum=0;
 	int i,j,temp,sum=0,ta=0;
	 for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
		if(at[i]<at[j])
		{
		temp=p[j];
		p[j]=p[i];
		p[i]=temp;

		temp=at[j];
		at[j]=at[i];
		at[i]=temp;

		temp=bt[j];
		bt[j]=bt[i];
		bt[i]=temp;
		}
	}
}
    int btime=0,min,k=1;
    for(j=0;j<n;j++)
    {
        btime=btime+bt[j];
        min=bt[k];
    for(i=k;i<n;i++)
    {
        if (btime>=at[i] && bt[i]<min)
        {
            temp=p[k];
            p[k]=p[i];
            p[i]=temp;
            temp=at[k];
            at[k]=at[i];
            at[i]=temp;
            temp=bt[k];
            bt[k]=bt[i];
            bt[i]=temp;
        }
    }
        k++;
    }
    wt[0]=0;
    for(i=1;i<n;i++)
    {
        sum=sum+bt[i-1];
        wt[i]=sum-at[i];
        wsum=wsum+wt[i];
    }
    for(i=0;i<n;i++)
    {
        ta=ta+bt[i];
        tat[i]=ta-at[i];
        tsum=tsum+tat[i];
    }
    cout<<"Process\tArrival Time\tBurst Time\tWaiting Time\tTurn Around Time"<<endl;
    for(i=0;i<n;i++)
    {
        cout<<i+1<<"\t\t"<<at[i]<<"\t\t"<<bt[i]<<"\t\t"<<wt[i]<<"\t\t"<<tat[i]<<endl;
    }
	cout << "Average waiting time = "
		<< wsum/n<<endl;
	cout << "\nAverage turn around time = "
		<< (float)tsum / (float)n;
 }

 void ShortestRemainingJobFirst()
 {
    for (int i = 0; i < n; i++)
   tat[i] = bt[i] + wt[i];  
   int rt[n];
   for (int i = 0; i < n; i++)
   rt[i] = bt[i];
   int complete = 0, t = 0, minm = INT_MAX;
   int shortest = 0, finish_time;
   bool check = false;
   while (complete != n) {
      for (int j = 0; j < n; j++) {
         if ((at[j] <= t) && (rt[j] < minm) && rt[j] > 0) {
            minm = rt[j];
            shortest = j;
            check = true;
         }
      }
      if (check == false) {
         t++;
         continue;
      }
      rt[shortest]--;
      minm = rt[shortest];
      if (minm == 0)
         minm = INT_MAX;
         if (rt[shortest] == 0) {
            complete++;
            check = false;
            finish_time = t + 1;
            wt[shortest] = finish_time -bt[shortest] -at[shortest];
            if (wt[shortest] < 0)
               wt[shortest] = 0;
         }
         t++;
   }
   cout << "Processes " << " Burst time " << " Waiting time " << " Turn around time\n";
   for (int i = 0; i < n; i++) {
      twt = twt + wt[i];
      ttat = ttat + tat[i];
      cout << " " << p[i] << "\t\t" << bt[i] << "\t\t " << wt[i] << "\t\t " << tat[i] << endl;
   }
   cout << "\nAverage waiting time = " << (float)twt / (float)n; cout << "\nAverage turn around time = " << (float)ttat / (float)n;
}

 void RoundRobin()
 {
	int i, total = 0, x, counter = 0, time_quantum;
  	int wait_time = 0, turnaround_time = 0, temp[100];
	x=n;
	for(i = 0; i < n; i++)
  	{
		temp[i] = bt[i];
  	}
      cout<<"\nEnter Time Quantum:\t";
  	cin>>time_quantum;
    cout<<"\nProcess ID\t\tBurst Time\t Turnaround Time\t Waiting Time\n";
  	for(total = 0, i = 0; x != 0;)
  	{
    		if(temp[i] <= time_quantum && temp[i] > 0)
    		{
      			total = total + temp[i];
      			temp[i] = 0;
      			counter = 1;
    		}
    		else if(temp[i] > 0)
    		{
      			temp[i] = temp[i] - time_quantum;
      			total = total + time_quantum;
    		}
    		if(temp[i] == 0 && counter == 1)
    		{
      			x--;
                 cout<<"Process["<<i+1<<"]\t\t"<<bt[i]<<"\t\t"<<total - at[i]<<"\t\t\t"<<total - at[i] - bt[i]<<endl;
      			wait_time = wait_time + total - at[i] - bt[i];
      			turnaround_time = turnaround_time + total - at[i];
      			counter = 0;
    		}
    		if(i == n - 1)
      		{
			i = 0;
		}
    		else if(at[i + 1] <= total)
      		{
			i++;
		}
    		else
      		{
			i = 0;
		}
	}

        cout << "Average waiting time = "
		<< (float)wait_time / (float)n;
	    cout << "\nAverage turn around time = "
		<< (float)turnaround_time / (float)n;
 }

 

 int main(){
     cout << endl;
    cout << "CPU Scheduling Algorithms" << endl;
    cout << endl;
    int chooseScheduler;
    input();
    cout << "\nChoose A Scheduling Algorithm \n\n1) First Come First Serve \n2) Shortest Job First \n3) ShortestRemainingJobFirst \n4) Round Robin \n"
         << endl;
    cin >> chooseScheduler;
    switch (chooseScheduler)
    {
    case (1):
        FirstComeFirstServe();
        break;
    case (2):
        ShortestJobFirst();
        break;
    case (3):
        ShortestRemainingJobFirst();
        break;
    case (4):
        RoundRobin();    
        break;
    default:
    cout << "Enter a valid number between 1 to 5";
    break;
    }
 }
