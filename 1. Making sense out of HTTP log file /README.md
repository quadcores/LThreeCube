===========================================================================================================================================

* Assignment 1: Making sense out of HTTP log file
 
* Solution:
	1. input file : weblog.txt
	2. src: main.py 
	3. output: output.txt, data entry in mongodb, visual aggregation results on java servlet

* Features and Functionalities: 
	1. This program generates output.txt file that contains HTTP Log Info in a proper human-readable format as a basic output
	2. ADVANCED : 
	(Installation steps follow)
	
	a. We thought of using a database to store all the entries as it would be much more feasible and efficient to store data of more than one weblog file and perform all the aggregation functions over this complete dataset. Also, this eliminates the burden on the main memory for large dataset.<br>
	b. MongoDB has been used as the backend owing to its flexible collection formats (HTTP Dataset does not follow fix format in all headers) and MapReduce functionality. This hugely increases the speed and scalability of the data storage and analysis.<br>
	c. We have used Java Servlet API to retrieve data from this MongoDB and displayed it in tabular form and pie charts. The fact that MongoDB has been used makes it easy to add any kind of filtering and aggregation queries as and when required.<br>
	d. Also, using Java Servlet facilitates use of unending web-technology resources like D3, JQuery, Bootstrap, AngularJS, etc. easily for aesthetic visual representation of data.<br>

* Additional Requirements and Installation Steps:	
	1. Install pygeoip (python library used for finding location from IP Address)
			> sudo apt-get install pip 
			> sudo pip install pygeoip
	2. Install MongoDB :
			> Run "mongo_install.bash" given in Installations and Screenshots folder
				(*Note : Run it only if MongoDB is not present on your system, else data loss might occur!) 
			OR
			> Follow steps on "http://docs.mongodb.org/manual/"		
	3. If default port of mongod is not 27017, please make appropriate changes in source code of Analytics/src/java/newpackage/Analytics.java
	4. Deploy the Analytics.war on any Java Server and run the application.
			> You may refer "https://tomcat.apache.org/tomcat-6.0-doc/deployer-howto.html" for assistance in deploying the .war

* Flow of Program:
	1. Pass weblog.txt as a command line argument to 'main.py'
	2. REGEX has been used to parse each HTTP Header based on the standard header format
	3. This 'main.py' creates a new database named 'log' in MongoDB dynamically and stores all the HTTP Data in a collection 
	   named 'http' - SCREENSHOT ATTACHED
	   (*Note : Use "> sudo service mongod start" command to start mongod server before executing this step )
	4. Also a file 'output.txt' is generated that contains all the HTTP Log Data parsed
	5. Now that all the data has been stored in MongoDB, J2EE is used to retrieve this data and render it to any Java Servlet where it can 
	   be viewed in required manner.
	6. Run any Java Servelet, for eg. Apache Tomcat
	7. Now deploy the 'Analytics.war' file on the server using normal procedure
			> You may refer "https://tomcat.apache.org/tomcat-6.0-doc/deployer-howto.html" for assistance in deploying the .war
	8. Use the web page that is loaded to get a number of statistics in visually aesthetic manner - SCREENSHOTS ATTACHED

===========================================================================================================================================
