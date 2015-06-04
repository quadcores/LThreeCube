===========================================================================================================================================

* Assignment 3 : TCP/IP data 

* Solution:
	1. input 		: 1st parameter = PCAP/CAP test file ( runs for all 4 : arp-storm.pcap,tcp-ecn-sample.pcap,http_witp_jpegs.cap,bgp.pcap )
					  2nd parameter = output file name for info generated
	2. src 			: PCAP_parser.c ( packetread.c is included as header )
	3. output 		: DETAILED INFORMATION of all packets
					  SUMMARY at the end of the output file
					  {argv[2]}.txt is the output file that contains all these DETAILED FIELDS of the packets and SUMMARY
	4. requirements : sudo apt-get install libpcap-dev ( for C library that supports pcap - network traffic capture interface )

* Flow of Program:
	1. Open the .pcap file i.e. get a pointer to that file
	2. Iterate over and read all the packets in the file
	3. Print all the data in the packet in HEX form in the IC file, timestamp of the file follows at the end
	4. Read the IC file and convert the HEX data in appropriate form. Simple packet format used for finding out the fields 
	5. Print all this data in output file
	6. DETAILED SUMMARY for the complete PCAP file follows

===========================================================================================================================================
