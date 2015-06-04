#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int initial,version=0; // initial->no. of lines in input text file, version-> present version
void check_change();
char passed_name[20]; // file on which svc is implemented
void create_bit(char []); // accept version and number of lines in input text file
void copyname(char *); // extract name from the passed file and create version 0 file
void revert_version(int); // revert back to specified version number
int compare(char[], char[],int);
void accept_version();
int difference_in_files(char []);
void convert(char *);

int main(int argc,char *argv[])
{
	char st2[20],buff[20];
	char st[20];
	int disp;
	printf("\nVERSION CONTROL SYSTEM\n");
	int n,change;
	FILE *fp,*fp1[30],*fp2;

	if(argc<=1) //error handling for no command line argument passed
	{
		printf("Pass a text file OR a version number through command line to Simple Version Control program \n\n");
		exit(0);
	}

	n = check_arguement(argv[1]); //check if argument is version number or file
	if(n==2) //condition for valid file passed as an argument
	{
		convert(argv[1]); //convert the filename (eg test.txt to test) for storing in the bitmap file
		create_bit(argv[1]); //create the bitmap file
	}
	else //condition for version number passed as argument
		accept_version(); //update the global variable 'version'

  	switch(n)
	{
    	case 1:
		  	printf(" > Argument Passed is Version Number\n");
		  	disp=strToInt(argv[1]);
		  	if(disp>version || disp<0) //error handling for wrong version entered
		  	{
		   		printf(" > Error : Wrong Version Entered!! The Latest Version Number is %d\n",version);
		    	break;
		  	}
			revert_version(disp); //function called to revert to the given version
	  	    break;

    	case 2: //if argument passed is file to be commited
			copyname(argv[1]); //function called to update the passed_name variable
		  	change=difference_in_file(argv[1]); //to check if any changes are made to the input file
		  	if(change) //condition for input file changed
		 	{
		    	sprintf(st2,".%s%d.txt",passed_name,++version); //open a new version file
		    	FILE *fp2=fopen(st2,"w");
		    	sprintf(st,"%s.txt",passed_name);
		    	FILE *fp=fopen(st,"r");
		    	while(fgets(buff,sizeof(buff),fp)) //print the data of input file in the new version file
		      		fprintf(fp2,"%s",buff);
		    	fclose(fp);
		    	fclose(fp2);
		    	fp=fopen(".bitmap.txt","w"); //update the bitmap file to give the new version number
		    	fseek(fp,0,SEEK_SET);
				fprintf(fp,"%d\n",version);
				fprintf(fp,"%s\n",passed_name);
				fclose(fp);
				printf(" > File Committed! Version %d Created\n",version);
				printf(" > Changes Saved Successfully! Exiting \n");
				exit(0);
		 	}
			else if(version != 0) //if there is no change made to input file
		    	printf(" > File has Already been Committed. No Changes Found\n");
			break;
		default: //condition for wrong input given as a command line argument
			printf(" > Error : Enter a Valid Option from the Menu! Either a Filename for Commit OR a Version Number for Reverting!\n\n");
			break;
	}
}

int check_arguement(char arg[])
{
	/* this function is used to find out if the argument entered in command line
	 * is a valid argument and return if it is a version number given or a file 
	 * input :: argument passed
	 * output :: 1 = version number entered
	 *           2 = file name entered
	 */

	FILE *fp;
	int i = 0, type = 2;
	for(i=0; arg[i]!='\0'; i++)
	{
		if(arg[i] >= '0' && arg[i] <= '9')
			type = 1;
		else
		{
			fp = fopen(arg,"r"); //error handling condition for inexistent file given as input through command line
			if(fp == NULL)
			{
				printf(" > Error : File Does Not Exist! Exiting\n");
				exit(0);
			}
			fclose(fp);
			type = 2;
			break;
		}
	}
	return type; //return the type of argument, either version number or file
}

int strToInt(char arg[])
{
	/*this function is used to convert the version number entered as the
	 * command line argument, to integer giving version number
	 * input :: command line argument
	 * output :: integer conversion
	 */
	int val=0, i=0;
	
	for(i=0; arg[i] != '\0'; i++)
		val = val*10 + (arg[i]-'0');
	
	return val;
}

int difference_in_file(char ss[])
{
	/* This function is used to check if there is a change made to the previous version of the file for commit
	* input :: the file name passed as command line
	* output :: 1 = change is made to the file
	*           0 = there is no change to the previous version
	*/
	char st[20], buff[20], buff1[20];
	int presentlines, previouslines;
	FILE *fp=fopen(ss,"r"); //open the currently passed file
	sprintf(st,".%s%d.txt",passed_name,version);
	FILE *fp1=fopen(st,"r");//open the latest version file already present
	
	for(presentlines=0;fgets(buff,sizeof(buff),fp)!=NULL;presentlines++);
	for(previouslines=0;fgets(buff1,sizeof(buff1),fp1)!=NULL;previouslines++);
	
	if(presentlines==previouslines) //if there is no change in the number of lines
		return 0;
	else
		return 1;
}

void create_bit(char st[])
{
	/*
	 * This function is used to create the bitmap.txt file which stores
	 * the latest version which is being used and the file name which is input
	 * input :: file name which is input
	 * output :: bitmap.txt file created
	*/
	char buff[20],st1[20];
	int i;
	FILE *fp=fopen(st,"r"); //check if bitmap.txt already exists
	FILE *fp1=fopen(".bitmap.txt","r");
	
	if(fp1 == NULL) //if bitmap.txt does not exist, open it in write mode
	{
		fp1 = fopen(".bitmap.txt","w");
		fprintf(fp1,"%d\n",0);
		fprintf(fp1,"%s\n",passed_name); //write the name of the file and version
		initial = i;
		version = 0;
		fclose(fp1);
	}
	else
	{
		fseek(fp1,0,SEEK_SET); // accept in int form
		fscanf(fp1,"%d",&version);
		fscanf(fp1,"%s",passed_name);
		fclose(fp1);
	}
	fclose(fp);
}

void accept_version()
{
	/*this fuction is used to retrieve the latest version from the bitmap.txt*/
	FILE *fp1=fopen(".bitmap.txt","r");
	fscanf(fp1,"%d",&version); //latest version is stored in global variable 'version'
	fscanf(fp1,"%s",passed_name); //file name is stored in global variable 'passed_name'
	fclose(fp1);
}

void copyname(char *s)
{
   /* This function is used to create the version 0 file if it does not exist
	* and store the data from input file into the version 0 file, providing the first commit
	* input :: input file
	* output :: creation of the version 0 if it doesn't exist 
	*/

	char *mystr;
	char buff[20],st[20];

	mystr=(char *)malloc(20*sizeof(char));
	strcpy(mystr,s);

	char *lastdot=(char *)malloc(20*sizeof(char));
	strcpy (passed_name, mystr);
	lastdot = strrchr (passed_name, '.'); //the extension of the file is removed while storing in the global variable passed_name

	if(lastdot != NULL)
		*lastdot = '\0';

	FILE *fp=fopen(s,"r"),*fp1;

	sprintf(st,".%s%d.txt",passed_name,0);
	fp1=fopen(st,"r");
	if(fp1==NULL) //condition for version 0 file not existing
	{
		fp1=fopen(st,"w");
		while(fgets(buff,sizeof(buff),fp))
	  		fprintf(fp1,"%s",buff);
		fclose(fp);
		fclose(fp1);
		printf(" > File Committed! Version %d Created\n",version);
	}
	else //if version 0 file already exists
	{
		if(version == 0 && difference_in_file(s) == 0)
	  		printf(" > File has Already been Committed. No Changes Found\n");
		fclose(fp);
		fclose(fp1);
	}
}

void revert_version(int ver)
{
	/*This function is used to revert to the version which is given
	* by the variable ver and print all the lines of files up till that version
	* input :: the version to revert back to
	* output :: the lines of all versions up to that function
	*/
  	char st[20],buff[20];
 	sprintf(st,".%s%d.txt",passed_name,ver);
  	FILE *fp=fopen(st,"r");
  	
	while(fgets(buff,sizeof(buff),fp))
		printf("%s",buff);
  	
	fclose(fp);
}

void convert(char *s)
{
	/* this function is used to remove the extension from the file name and store it in the global variable 'passed_name
	 * input :: file name
	 * output :: file name stored without extension in the global variable 'passed_name'
	 */
	char *mystr;
	char buff[20],st[20];
	mystr=(char *)malloc(20*sizeof(char));
	strcpy(mystr,s);
	char *lastdot=(char *)malloc(20*sizeof(char));
	strcpy (passed_name, mystr);
	lastdot = strrchr (passed_name, '.'); //remove the extension from the file
	if(lastdot != NULL)
		*lastdot = '\0';
}
