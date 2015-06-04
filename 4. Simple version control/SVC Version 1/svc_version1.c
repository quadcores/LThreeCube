#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char bit[200]; 			// bit map of version 0 file
int initial,version=0; 		// initial->no. of lines in input text file, version-> present version
int menu();    			// generate menu for file operations
char passed_name[20];  		// file on which svc is implemented
void copy_version(char *,char *,char *);  // copy previous versions
void create_bit();		// accept version and number of lines in input text file
void create_hash(); 		// implement hashing on existing version files
void add_hash(int);		// add a new entry in the existing hash table
void copyname(char *); 		// extract name from the passed file and create version 0 file
int convert(char *);  		// extract version number and line number from hash table
int search(int ,char *,int *); // search for the version number for the givern line
void maphashtab();    		//copy the existing hash table from main memory to secondary memory file
void revert_version(int); 	// revert back to specified version number
int compare(char[], char[],int);
void calcsub(char[],char[]);
void readmaphashtab();    	// read hash table from secondary memory to main memory
typedef struct line{
	char ch[5];
	struct line *next;
}line;
typedef struct node{
	char ch;
	int x;
	struct line *next;
	struct node *next1;
}node;

node *head;

int main(int argc,char *argv[])
{
	char buff[200],filename[20],buff1[20],ch[20],prevfilename[20];
	char st[20];
	printf("\nVERSION CONTROL SYSTEM\n");
	int n,x,r,i,a,y;
	FILE *fp,*fp1[30],*fp2;
	if(argc!=2)
	{
		printf("Pass a text file through command line to Simple Version Control program \n");
		exit(0);
	}
	copyname(argv[1]);
	create_bit();
	while(1)
	{
		n=menu();

		switch(n)
		{
			case 1:
				printf(" > The lines of existing version are ::\n");
				revert_version(version);
				break;

			case 2:

				printf("\n=========================================================================\n");
				printf(" 1. Delete line from existing version                         \n");
				printf(" 2. Append a new line at the end of file                      \n");
				printf("=========================================================================\n\n");
				printf(" > Enter your option :: ");
				scanf("%d",&n);
        memset(buff,sizeof(buff),'\0');
				switch(n)
				{

					case 1:
            printf(" > Enter the line to delete :: ");
            scanf(" %[^\n]s",ch);
            copy_version("temp",ch,"delete");

            break;

					case 2:
            printf(" > Enter the line to append :: ");
            fp=fopen(".bitmap.txt","a+");
            int i=0;
            scanf(" %[^\n]s",buff);
            sprintf(prevfilename, ".%s%d.txt",passed_name,version);
            sprintf(filename, ".%s%d.txt",passed_name,++version);
            if(isupper(buff[0]))
              y=(int)buff[0]-65;
            else
              y=(int)buff[0]-97;
            add_hash(y);
            copy_version(prevfilename,filename,buff);
            fclose(fp);

            break;

          default:
						printf(" > Enter a valid option!!\n\n");
						break;
				}

				break;

			case 3:
				printf(" > Enter the version to revert back :: ");
				scanf("%d",&x);
				if(x>version || x<0)
				{
					printf(" > Error : Wrong version entered!!\n");
					break;
				}
				revert_version(x);
				break;

      case 4:
        printf(" > Latest Version Number is :: %d\n",version);
        break;

      case 5:
        fp=fopen(".bitmap.txt","w");
        maphashtab();
        fseek(fp,0,SEEK_SET);
        fprintf(fp,"%d\n",version);
        fprintf(fp,"%d\n",initial);
        fclose(fp);
        printf(" > Changes Saved Successfully! Exiting \n");
        exit(0);

        break;

      default:
        printf(" > Enter a valid option from the menu!!\n\n");
        break;
    }
	}
}

void copy_version(char prevch[],char ch[],char ch1[])
{
  /*This fuction is used to create a new file version each time
   * a line is appended or deleted by the user*/
  //input :: the string appended
  //output :: the new text file giving the newest version where
  //line is appended

  char filebit[20],s[5],grpstr[20],character[3],temp[20],filename[20],buff[20],bits[20]="",list[20],bit[20];
  int y,start,i,vno,counter=0,len,verinp,a;
  FILE *fp;//=fopen(ch,"w");
  FILE *fp2;//= fopen(prevch,"r");
  FILE *fp3;
  FILE *fpgroup;

  if(strcmp(ch1,"delete") == 0)
  {
    if(isupper(ch[0]))
      y=(int)ch[0]-65;
    else
      y=(int)ch[0]-97;

    verinp=search(y,ch,&a);
    if(verinp == -1)
    {
      printf(" > Error: Line does not exist!\n");
      return;
    }
    sprintf(filename,".%s%d.txt",passed_name,++version);
    fp=fopen(filename,"w");
		fprintf(fp,"%s\n",ch1);
		memset(buff,sizeof(buff),'\0');

    if(verinp == 1) //if the line is in a version and not input file
    {
      sprintf(filename,".%s%d.txt",passed_name,version-1);

      fp3=fopen(filename,"r");

      for(i=0;i<sizeof(list);i++)
        list[i]='\0';

      fgets(list,sizeof(list),fp3);
      fgets(list,sizeof(list),fp3);

      i = initial + a;
      list[i-1]='0';
      strcat(list,"0");

      fprintf(fp,"%s",list);
      strcpy(bits,list);
      fclose(fp3);
      fclose(fp);
    }

    else //if line is in the input file
    {
      if(version == 1) //if current version is version 1
      {
        int i;
        for(i=0;i<initial;i++)
          bit[i]='1';

        bit[a-1]='0';
        strcat(bit,"0");
        fprintf(fp,"%s",bit);
        fclose(fp);
      }

      else //if current version is not version 1
      {
        sprintf(filename,".%s%d.txt",passed_name,version-1);
        fp3=fopen(filename,"r"); //open the file of previous version
        for(i=0;i<sizeof(buff);i++)
          buff[i]='\0';

        fgets(buff,sizeof(buff),fp3);
        fgets(buff,sizeof(buff),fp3);
        buff[a-1]='0';
        strcat(buff,"0");
        fprintf(fp,"%s",buff);
        fclose(fp3);
        fclose(fp);
      }
    }

   }//end of copy_version processing for delete command

  else
  {
    fp = fopen(ch,"w"); //open current version file
    fp2 = fopen(prevch,"r"); //open previous version file

    if(version-1 == 0) //if previous version = 0
    {
      while(counter < initial) //make all bits of current version to 1
      {
        bits[counter] = '1';
        counter++;
      }
      bits[counter] = '\0';
    }

    else //if previous version != 0
    {
      memset(temp,sizeof(temp),'\0');
      memset(bits,sizeof(bits),'\0');
      fgets(temp,sizeof(temp),fp2);
      fgets(bits,sizeof(bits),fp2); //second line gives bits of previous version
    }

    fclose(fp2);

    strcat(bits,"1"); //append 1 to the last position
    fprintf(fp,"%s\n%s",ch1,bits); //print bits to the current version file
    fclose(fp);
  }

  if(version % 5 == 0)
  {
    sprintf(grpstr,".grouptill%d.txt",version);
    fpgroup = fopen(grpstr,"w"); //open the grouptill file
    start = version - 4;
    for(i=start;i<=version;i++) //print all the lines corresponding
                                //bits of previous 5 versions in
                                //the group till file
    {
      if(bits[i+initial-1] == '1')
      {
        sprintf(filebit,".%s%d.txt",passed_name,i);
        fp2 = fopen(filebit,"r");
        {
          fgets(temp,sizeof(temp),fp2);
          fprintf(fpgroup,"%s",temp);
        }

        fclose(fp2);
      }
    }
    fclose(fpgroup);
  }

  printf("\n > Change Committed Successfully!\n");
}

void create_bit()
{
  /*This function is called in the beginning of the program
   * to get the number of lines in the initial input file and
   * the latest version number each time the program is executed*/

  char buff[20],st[20];
  int i;
  sprintf(st,".%s%d.txt",passed_name,0);
  FILE *fp=fopen(st,"r");
  FILE *fp1=fopen(".bitmap.txt","r");

  if(fp1 == NULL)
  {
    fp1 = fopen(".bitmap.txt","w");
    fprintf(fp1,"%d\n",0);
    for(i=0;fgets(buff,sizeof(buff),fp)!=NULL;i++);  // check number of lines
    fprintf(fp1,"%d\n",i);
    initial = i;
    version = 0;
    fclose(fp1);
  }

  else
  {
    fseek(fp1,0,SEEK_SET); // accept in int form
    fscanf(fp1,"%d",&version);
    //d = version;
    fscanf(fp1,"%d",&initial);
  }

  FILE *fp2=fopen(".maphashtab.txt","r");
  if(fp2==NULL)
    create_hash();
  else
    readmaphashtab();

  fclose(fp);
  fclose(fp1);
  if(fp2 != NULL)
    fclose(fp2);
}
int menu()
{
  /*This function displays the options to the user in the beginning
   *User can choose one of the option from the given menu*/
	int n;
	printf("\n=========================================================================\n");
	printf("                            CHOOSE YOUR OPERATION                           \n");
	printf(" 1. Display Contents of the Latest Version                                \n");
	printf(" 2. SVC Commit(Appends a new line OR Deletes any existing line)        \n");
	printf(" 3. SVC N(reverts back to the Nth version)                             \n");
	printf(" 4. Get Latest Version Number                                          \n");
	printf(" 5. Exit                                                               \n");
	printf("=========================================================================\n\n");
	printf(" > Enter your option :: ");
	scanf("%d",&n);
	return n;
}
void create_hash()
{
  /*This function is called in the beginning to create the
   * hash structure used to store each line in the appropriate location
   * according to the starting character of each line in the
   * input file */

  FILE *fp;
  char ch[20];
  sprintf(ch,".%s%d.txt",passed_name,0);
  fp=fopen(ch,"r"); //open the initial input file
  char ss[3],buff[20],sp;
  int i,j,k,y;
  node *temp1;

  head=(node *)malloc(sizeof(node)); //storing the first node of the
                                     //hash structure which is pointing to
                                     //the character 'a'
  head->x=0;
  head->ch='a';

  line *l=(line *)malloc(sizeof(line));
  head->next=NULL;
  head->next1=NULL;

  temp1=(node *)malloc(sizeof(node));
  temp1=head;

  for(i=2;i<=26;i++) //storing remaining nodes and the lines in respective
                     //nodes, thus creating the hash structure
  {
    node *temp;
    temp=(node *)malloc(sizeof(node));
    sp=97+i-1;
    temp->ch=sp;
    temp->x=0;
    temp->next=NULL;
    temp->next1=NULL;
    temp1->next1=temp;
    temp1=temp;
  }

  for(i=0;i<initial;i++) //
  {
    fgets(buff,sizeof(buff),fp);

    if(isupper(buff[0]))
      y=(int)buff[0]-65;
    else
      y=(int)buff[0]-97;

    line *l1;
    l=(line *)malloc(sizeof(line));
    sprintf(ss,"x%d",i+1);
    strcpy(l->ch,ss);
    l->next=NULL;

    node *temp1=head;
    for(k=0;k<y;k++)
      temp1=temp1->next1;

    if(temp1->next==NULL)
    {
      temp1->next=l;
      temp1->x++;
    }
    else
    {
      line *temp2=temp1->next;
      for(k=0;k<temp1->x-1;k++)
        temp2=temp2->next;

      temp2->next=l;
      temp1->x++;
    }
  }
  temp1=head;

  for(j=0;j<7;j++)
    temp1=temp1->next1;
  line *p=temp1->next;
}
void copyname(char *s)
{
	char *mystr;
	char buff[20],st[20];
	mystr=(char *)malloc(20*sizeof(char));
	strcpy(mystr,s);
    char *lastdot=(char *)malloc(20*sizeof(char));
    strcpy (passed_name, mystr);
    lastdot = strrchr (passed_name, '.');
    if (lastdot != NULL)
       	*lastdot = '\0';
	FILE *fp=fopen(s,"r"),*fp1;
	sprintf(st,".%s%d.txt",passed_name,0);
	fp1=fopen(st,"w");
	while(fgets(buff,sizeof(buff),fp))
		fprintf(fp1,"%s",buff);

	fclose(fp);
	fclose(fp1);
}
void add_hash(int y)
{
  /*This function adds the appended line by the user, in the
   * appropriate node in the hash structure */
  //input :: the node corresponding to the accepted string
  //in the hash structure

  char ss[3];
  int i;
  line *l,*l1;
  node *temp1;

  temp1 = (node *)malloc(sizeof(node));
  l=(line *)malloc(sizeof(line));
  sprintf(ss,"v%d",version);
  strcpy(l->ch,ss);
  l->next=NULL;
  temp1=head;

  for(i=0;i<y;i++)
    temp1=temp1->next1;

  if(temp1->next==NULL)
  {
    temp1->next=l;
    temp1->x++;
  }

  else
  {
    line *temp2=temp1->next;

    while(temp2 -> next != NULL)
      temp2=temp2->next;

    temp2->next=l;
    temp1->x++;
  }

  temp1=head;
  line *p=temp1->next;
}

int search(int hashline,char *ch,int *verline)
{
  /*this function searches the hash structure for the string
   * input by the user in string ch[] and returns the
   * line number and version of file where it is present*/
  //input :: variable hashline gives the node corresponding to the
  //accepted string in the hash structure
  //output :: line number and version number of the file where
  //string ch is present for deleting

  line *l;
  char h[4],*i,buff[20],filename[20],temp[20];
  int x,j,k;
  l=(line *)malloc(sizeof(line));
  node *temp1;
  FILE *fp, *fp2;

  temp1=(node *)malloc(sizeof(node));
  temp1=head;

  for(j=0;j<hashline;j++)
    temp1=temp1->next1;
  l=temp1->next;

  //for(k=0;k<temp1->x;k++)
  while(l != NULL)
  {
    strcpy(h,l->ch);
    if(h[0]=='v')
    {
      x=convert(h);
      sprintf(filename,".%s%d.txt",passed_name,x);
      fp=fopen(filename,"r");
      fgets(buff,sizeof(buff),fp);
      buff[strlen(buff)-1]='\0';

      sprintf(filename, ".%s%d.txt",passed_name,version);

      fp2 = fopen(filename,"r");
      fgets(temp,sizeof(temp),fp2);
      fgets(temp,sizeof(temp),fp2);
      fclose(fp2);

      if(strcmp(buff,ch)==0 && temp[x+initial-1] == '1')
      {
        *verline = x;
        return 1;
      }
      fclose(fp);
    }
    else
    {
      x=convert(h);
      sprintf(filename,".%s%d.txt",passed_name,0);
      fp=fopen(filename,"r");

      int j;
      for(j=0;j<x-1;j++)
        fgets(buff,sizeof(buff),fp);

      fgets(buff,sizeof(buff),fp);
      buff[strlen(buff)-1]='\0';

      if(version != 0)
      {
        sprintf(filename, ".%s%d.txt",passed_name,version);
        fp2 = fopen(filename,"r");
        fgets(temp,sizeof(temp),fp2);
        fgets(temp,sizeof(temp),fp2);
        fclose(fp2);
      }

      if((version != 0 && strcmp(buff,ch)==0 && temp[x-1] == '1') || (version == 0 && strcmp(buff,ch)==0))
      {
        *verline = x;
        return 2;
      }

      fclose(fp);
    }

    l=l->next;
  }

  return -1;
}

void maphashtab()
{
  /*this function writes the hash table in a file named
   * maphashtab.txt for further use at the time of exit */
  FILE *fp;
  int i;
  line *lptr;
  node *nptr;
  char *str;

  str = (char *)malloc(255*sizeof(char));

  fp = fopen(".maphashtab.txt","w");
  nptr = head;
  while(nptr != NULL)
  {
    for(i=0;i<255;i++)
      str[i] = '\0';

    str[0] = nptr -> ch;
    strcat(str, " ->");

    lptr = nptr -> next;
    while(lptr != NULL)
    {
   		strcat(str," ");
      	strcat(str,lptr -> ch);

      	lptr = lptr -> next;
    }

    fprintf(fp,"%s",str);
    fprintf(fp,"\n");
    nptr = nptr -> next1;
  }

  fclose(fp);
}

void readmaphashtab()
{
	/*This function is used to read the maphashtab file and
   * update the node and the line structures so that each time
   * the code is executed, it remains updated with the newest
   * version*/

  FILE *fp;
	char st[20],*p;

	fp=fopen(".maphashtab.txt","r");

	p=(char *)malloc(5*sizeof(char));
	node *temp,*temp1;

	head=(node *)malloc(sizeof(node));
	line *lp,*lp1;
	int ctr=0,i;

  //read the first line from the maphashtab file
  //to initialize the head node and the line in the first node
	fgets(st,sizeof(st),fp);
	for(p=strtok(st," \n");p!=NULL;p=strtok(NULL," \n"))
	{
		if(ctr==0)
		{
      head->ch=p[0];
      head->next1=NULL;
      head->next=NULL;
    }

    else if(ctr==1)
    {
      ctr++;
      continue;
    }

    else
    {

      lp1=(line *)malloc(sizeof(line));
      strcpy(lp1->ch,p);
      lp1->next=NULL;
      if(ctr==2)
      {
        head->next=lp1;
        lp=lp1;
      }

      else
      {
        lp->next=lp1;
        lp=lp1;
      }
    }

    ctr++;
  }

  head->x=ctr-2;
  temp=head;

  //for each remaining line from the maphashtab function, store the
  //node and the line information to create the hashtable function
  //dynamically
  while(fgets(st,sizeof(st),fp))
  {
    temp1=(node *)malloc(sizeof(node));
    ctr=0;
    for(p=strtok(st," \n");p!=NULL;p=strtok(NULL," \n"))
    {
      if(ctr==0)
      {
        temp1->ch=p[0];
        temp1->next1=NULL;
        temp1->next=NULL;
      }

      else if(ctr==1)
      {
        ctr++;
        continue;
      }

      else
      {

        lp1=(line *)malloc(sizeof(line));
        strcpy(lp1->ch,p);
        lp1->next=NULL;
        if(ctr==2)
        {
          temp1->next=lp1;
          lp=lp1;
        }

        else
        {
          lp->next=lp1;
          lp=lp1;
        }
      }
      ctr++;
    }

    temp1->x=ctr-1;
    temp->next1=temp1;
    temp=temp1;
  }

  fclose(fp);
}

void revert_version(int ver)
{
  /*This function is used to revert to the version which is given
   * by the variable ver and print all the lines of files
   * up till that version*/
  //input :: the version to revert back to
  //output :: the lines of all versions up to that function
	int i,start,startbit,j,flag = 0;
	FILE *fp,*fp2,*fpgroup,*fpini,*fploop;
	char filename[20],s[5],buff[20],bitscur[20],bitsfive[20],ch[20];
	sprintf(ch,".%s%d.txt",passed_name,0);
	if(ver == 0) //if version entered by user is the initial input file
	{
		fp = fopen(ch,"r");
		for(i=0;i<initial;i++)
		{
			fgets(buff,sizeof(buff),fp);
			printf("%s",buff);
		}
		fclose(fp);
		return;
	}

	sprintf(filename,".%s%d.txt",passed_name,ver); //open the file of the asked version
	fp = fopen(filename,"r");

	fgets(buff,sizeof(buff),fp);
	fgets(bitscur,sizeof(bitscur),fp); //get the bitmap of current version
                                    //in the variable bitscur
	fclose(fp);

	if(ver>=5) //to check if the grouptill file can be applied
	{
		i=0;
		while(ver-i >= 5)
		{
			i = i+5;

			sprintf(filename,".%s%d.txt",passed_name,i); //open each grouptill five
                                        //of number less than the current asked
                                        //version
			fp2 = fopen(filename,"r");

			fgets(buff,sizeof(buff),fp2);
			fgets(bitsfive,sizeof(bitsfive),fp2);
			fclose(fp2);

			if(flag == 0)
			{
				fpini = fopen(ch,"r"); //print each line of initial file
				{
					j=0;
					while(j < initial)
					{
						if(bitscur[j] == '1')
						{
							fgets(buff,sizeof(buff),fpini);
							printf("%s", buff);
						}

						else
							fgets(buff,sizeof(buff),fpini);

						j++;
					}
					flag = 1;
				}
				fclose(fpini);
			}

			if(compare(bitscur,bitsfive,i) == 0) //compare the bitmap of the
                                           //grouptill file and required
                                           //version file, if equal, open the
                                           //file and print all lines of the
                                           //file.
			{
				sprintf(filename,".grouptill%d.txt",i);
				fpgroup = fopen(filename,"r");

				while(fgets(buff,sizeof(buff),fpgroup))
					printf("%s", buff);
			}

			else
			{
				start = i-4;
				startbit = start + initial - 1;
				while(start <= i)
				{
					if(bitscur[startbit] == '1')
					{
						sprintf(filename,".%s%d.txt",passed_name,start);
						fploop = fopen(filename,"r");
						fgets(buff,sizeof(buff),fploop);
						printf("%s", buff);
						fclose(fploop);
					}
					startbit++;
					start++;
				}
			}
		}

		if(ver - i < 5)
		//conditions for the appending lines from remaining
		//versions after the grouptill functions
		{
			start = i+1;
			startbit = start + initial - 1;

			while(start <= ver)
			{
				if(bitscur[startbit] == '1')
				{
					sprintf(filename,".%s%d.txt",passed_name,start);

					fploop = fopen(filename,"r");
					fgets(buff,sizeof(buff),fploop);
					printf("%s", buff);
					fclose(fploop);
				}
				startbit++;
				start++;
			}

		}

	}

	else if (ver < 5)
	//condition for the version to revert to be less than 5
	{
		fpini = fopen(ch,"r");
		{
			j=0;
			while(j < initial)
			{

				if(bitscur[j] == '1')
				{
					fgets(buff,sizeof(buff),fpini);
					printf("%s", buff);
				}

				else
					fgets(buff,sizeof(buff),fpini);
				j++;
			}
		}

		fclose(fpini);

		start = 1;
		startbit = initial;
		while(bitscur[startbit] != '\0')
		{
			if(bitscur[startbit] == '1')
			{
				sprintf(filename,".%s%d.txt",passed_name,start);

				fploop = fopen(filename,"r");
				fgets(buff,sizeof(buff),fploop);
				printf("%s", buff);
				fclose(fploop);
			}
			startbit++;
			start++;
		}
	}
}

int convert(char *ch)
{
	/*this function is used to convert the file version number in string
	to integer*/
	//input :: file version in string
	//output :: file format in integer
	char st[4];
	int i,j=0;

	for(i=1;ch[i]!='\0';i++)
		st[j++]=ch[i];

	st[j]='\0';
	i=atoi(st);

	return i;
}

int compare(char bitscur[20],char bitsfive[20],int five)
{
	/*This function is used to compare the bitmap of current file given by bitscur,
	with the bitmap of the group file given by bitsfive*/
	//input :: current file bitmap, group file bitmap, version number of group file
	//output :: 0 if bitmap matches, -1 if bitmap doesn't match
	int i,j,start,startbitcur,startbitfive;

	start = five-4;
	startbitcur = start + initial - 1;
	startbitfive = strlen(bitsfive) - 5;

	for(i=0;i<5;i++)
	{
		if(bitscur[startbitcur] != bitsfive[startbitfive])
			return -1;
		startbitcur++;
		startbitfive++;
	}

	return 0;
}

void calcsub(char sub[20],char str[20])
{
	/*this function is used to calculate the substring to find
	out the version number from the file name*/
	//input :: file name to find the version number
	//output :: version number of the file
	int i,j;

	i=0;
	while(str[i] > 'a' && str[i] < 'z')
		i++;

	j=0;
	while(str[i] != '.')
	{
		sub[j] = str[i];
		i++;
		j++;
	}

	sub[j] = '\0';
}
