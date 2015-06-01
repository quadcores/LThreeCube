#include<stdio.h>
#include<math.h>
#include<time.h>
#include<string.h>
#define no_of_simulations 10000												//number of time the experiment is to be run

void one_run(int stats[]);

int main()
{
	int i, stats[367];
	long double probability1[367], probability2 = 1.0;	//probability1 = from experiment, probability2 = from formula 
	
	printf("\nRunning the Random Experiment %d times!\n\n", no_of_simulations); 	
	for(i=0; i<no_of_simulations; i++)
	{	
		one_run(stats);
	}
	
	printf("\n_________________________________________________________________");
	printf("\n|\t\t|\t\t\t|\t\t\t|");
	printf("\n| No. of persons|     Probability 1\t|     Probability 2\t|");
	printf("\n|\t\t|(Using %d trials)\t|    (Using formula)\t|", no_of_simulations);
	printf("\n|_______________|_______________________|_______________________|");
	for(i=1; i<=366; i++)
	{
		// Calculate probability by running the Random Experiment n no. of times - will give test results.
		probability1[i] = (long double)stats[i]/(long double)no_of_simulations;
		
		// Calculate using simple probability (mathematically) to compare with test and prove.
		probability2 = probability2*(long double)(366-i+1)/(long double)366;
		
		// Print both to compare
		printf("\n|\t%d\t|\t%Lf\t|\t%Lf\t|", i, probability1[i]*100, ((long double)1-probability2)*100);
	}
	printf("\n|_______________|_______________________|_______________________|\n\n");
	return 0;
}
	
void one_run(int stats[])								//calculate if bday repeats or not for particular date in one trial
{
	int i, j, k, a[367][367];

	memset(a, 0, sizeof(a[0][0]) * 367 * 367);

	for(i=1; i<=366; i++)			
	{
		for(j=1; j<=i; j++)
		{
			k = rand()%366;								//generate random birthday date from 1 to 366
			a[i][k]++;				
			if(a[i][k]>1)								
			{
				stats[i]++;								//if already exists, notify in stats[][] and break		
				break;
			}
		}
	}
}
