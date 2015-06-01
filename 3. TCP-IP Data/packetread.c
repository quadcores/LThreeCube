/*
This program is included in the PCAP_parser.c program and does the work of parsing the .cap/.pcap files in the intermediate file.
Input : .cap/.pcap files
Output : "ic.txt" file that contains hexadecimal equivalent of the PCAP dump file for each packet.
*/

#include <stdio.h>
#include <string.h>
#include <pcap.h>
#include <stdlib.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

unsigned long sec_diff = 0;
int getmonth(int year, unsigned long *days);
int getyear(unsigned long *days);
void time_format_change(unsigned long ts, unsigned long tus, FILE* fp_info);
struct pcap_pkthdr header;

int parse(char* fp_pcap)
{
	//this function parses the pcap file and converts the dump into hexadecimal form
	//input : pcap input file
	//output : hexadecimal form of the information in an intermediate file
	int i, temp = 0;
	char err[PCAP_ERRBUF_SIZE]; //a buffer used to store the error messages
	FILE* fp_ic; //the intermediate code used for processing
	unsigned long current_ts = 0; //used to store the timestamp in seconds
	unsigned long current_tus = 0; //used to store the microseconds used in combination with seconds
	unsigned long first_time, last_time; //the initial and final values of timestamp in seconds
	const u_char *packet; //each packet of transaction is stored
	pcap_t *pcap_id; //id of each packet
	
	pcap_id = pcap_open_offline(fp_pcap, err); //function used to open the pcap file given by fp_pcap

	if(pcap_id == NULL) //condition for invalid input of file
	{
		return 1;
	}
	fp_ic = fopen("ic.txt", "w"); //opening the intermediate code file
	if(fp_ic == NULL) //condition for failure of open
	{
		return 2;
	}
		
	while(packet = pcap_next(pcap_id, &header))	//pcap_next is the iterator over packets, used to read each packet from file
	{	
		temp++;
		if(temp==1)
		{
			first_time = (header.ts.tv_sec)+(header.ts.tv_usec/1e6); //calculation of the time in seconds for the first packet
		}
		for(i=0;i<header.len;i++)
		{
			fprintf(fp_ic, "%02x ", packet[i]);	//parse packet into hex format and store in intermediate file
		}
		current_ts = header.ts.tv_sec; //the time of capture of packet in seconds is found in the header of the packet
	    current_tus = header.ts.tv_usec; //the time of capture of packet in microseconds is found in the header of the packet
	    time_format_change(current_ts, current_tus, fp_ic); //function called to convert the timestamp into a proper format
	
		fprintf(fp_ic, "\n"); //print each packet in the intermediate file
	}
	last_time = (current_ts) + (current_tus/1e6); //calculation of the time in seconds for the last packet
	sec_diff = last_time-first_time; //variable sec_diff is used to store the entire session duration
	return 0;
}

void time_format_change(unsigned long ts, unsigned long tus, FILE* fp_ic)
{
	//used to convert the format of timestamp into YYYY/MM/DD, HH:MM:SS
	//input : timestamp in seconds and microseconds
	//output : timestamp in proper format 
	unsigned long mil,days,t,sec,hr,min; 
	int year, month, date;
	t = ts;
	days = ts/86400; //calculate number of days since epoch
	ts %= 86400;
	hr = ts/3600; //calculate number hours in the day
	ts = ts%3600; 
	min = ts/60; //calculate number of minutes in the given hour
	sec = ts%60; //calculate the number of seconds in the minute
	mil = tus/1000; //calculate the number of milliseconds 

	year = getyear(&days); //function used to calculate the year of transaction
	month = getmonth(year,&days); //function used to calculate month of the year of transaction
	date = days; 

	fprintf(fp_ic, "%d-%d-%d %lu:%lu:%lu.%lu", year,month,date,hr,min,sec,mil); //store the timestamp in proper format in the intermediate file
}

int getyear(unsigned long *days) 
{
	//used to get the year from the number of days since epoch
	//input : number of days since epoch
	//output : the year since epoch
	int i,year = 1970,tempdays = 0;
	for(i=year,tempdays=0;*days - tempdays > 365; i++)
	{
		if((i % 4 == 0) && (i % 400 != 0)) //condition for leap year
			tempdays = tempdays + 366;
		else
			tempdays = tempdays + 365;
	}
	year = i;
	*days = *days - tempdays;

	return year;
}

int getmonth(int year, unsigned long *days)
{
	//used to get the month from the year and days since epoch
	//input : the year and number of days in that year
	//output : the month in the year since epoch
	int temp,i,month,tempdays;
	for(i=1,tempdays = 0;*days - tempdays > 30; i++)
	{
		temp = *days - tempdays;
		if(((i==1) || (i==3) || (i==5) || (i==7) || (i==8) || (i==10) || (i==12))&&(temp<30)) //condition for months with 30 days
			break;
		else if((i==2) && (year % 4)==0 && (temp < 29)) //condition for the month february in a leap year
			break;
		else if((i==2) && (year % 4)!=0 && (temp < 28)) //condition for the month february in a normal year
			break;
		else if(temp < 31) 
			break;
		if((i == 1) || (i == 3) || (i == 5) || (i == 7) || (i == 8) || (i == 10) || (i == 12))
			tempdays = tempdays + 31;
		else if (i == 2)
		{
			if((year % 4 == 0) && (year % 400!=0))
				tempdays = tempdays + 29;
			else
				tempdays = tempdays + 28;
		}
		else
			tempdays = tempdays + 30;
	}	

	month = i;
	*days = *days - tempdays;
	return month;
}
