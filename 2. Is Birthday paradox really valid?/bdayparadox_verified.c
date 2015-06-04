#include<stdio.h>
#include<math.h>
#include<time.h>
#include<string.h>

void one_run(int stats[]);

int main()
{
	int i, stats[367], choice = 0;
	long double probability1[367], probability2 = 1.0;	//probability1 = from experiment, probability2 = from formula
	int no_of_simulations = 10000;						//number of time the experiment is to be run 

	printf("\nNumber of trials is %d currently. Do you want to change it? (0/1)  \n", no_of_simulations);
	scanf("%d", &choice);
	
	if(choice == 1)
	{
		printf("\nEnter the number of times you wish to run the experiment : ");
		scanf("%d", &no_of_simulations);
	}

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

	printf("\n*Note : The accuracy increases with increase in number of trials.\n\t10000 runs gives sufficiently accurate answer.\n\nCheck & compare for 23rd and 70th entry as 'The Birthday Paradox' says that \nprobability of repetition touches 50%% with 23 people and 99.9%% with 70 people. \n\n");
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
