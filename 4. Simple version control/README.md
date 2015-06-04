===========================================================================================================================================

* Assignment 4 : Simple Version Control

* 2 solutions :
	
	A] Version_1 :
		<br>1. input 		: initial commit file that has to be created and saved elsewhere is passed as argv[1]<br>
		2. src 			: svc_version1.c<br>
		3. output 		: menu-driven version control system<br>
		4. requirements : no additional installations required<br>

		* Flow of Program:
			1. Write an initial commit (say test.txt) and save it before executing svc.c
			2. Run svc.c, pass test.txt as an argument
			3. Select option from menu, like:
			   a. Display contents of the latest version
			   b. Commit (1-delete a line, 2-append a new line at the end)
			   c. Revert to Nth version
			   d. Get latest version number
			   e. Exit 
	
		* Features and Functionalities: 
			1. Lets the user close the program and still access all the previously created versions on next execution
			2. We have created a group of every 5 successive versions and stored it in external file
			   This saves an overhead of opening every previous version file of the version we wish to revert to by using Hashing
			3. Dynamic hash tables are created as a map for knowing contents of different versions efficiently (named .maphashtab)
			4. All the intermediate versions are stored as hidden files (.filename) in the same directory 	
			5. To keep track of the latest version and number of lines in the initial commit file, external file (.bitmap) is used

	B] Version_2 :
		<br>1. input 		: a. A file which is to be commited, passed as argv[1] <br>
		 &nbsp; &nbsp;&nbsp; &nbsp;&nbsp;&nbsp; &nbsp;&nbsp; &nbsp;&nbsp;&nbsp;b. A version number to be reverted to, passed as argv[1] <br>
		2. src 			: svc_version2.c<br>
		3. output 		: A standard version control system<br>
		4. requirements : no additional installations required<br>

		* Flow of Program:
			1. Write some text in a file (say test.txt) and save it before executing svc.c
			2. Run svc.c, pass test.txt as an argument, to form the initial commit number 0
			3. Run svc repetitively by passing one of the following arguments:
			   a. The file test.txt (after making changes to the initial file i.e. either appending a new line, or deleting an existing file)
			   b. An integer, which corresponds to the version number to be reverted to (starting from 0)
				
===========================================================================================================================================
