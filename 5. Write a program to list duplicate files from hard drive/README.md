===========================================================================================================================================

* Assignment 5 : Write a program to list duplicate files from hard drive

* Solution:
	1. input 		: choice of directory to run the code on (auto-menu driven)
	2. src 			: delete_duplicates.cpp
	3. output 		: i) list of all duplicate files in the given directory path and sud-directories
					  ii) an option to delete specific files is given to user
	4. requirements : no additional installations required

* Flow of Program:
	1. Select the directory to search for duplicates
	2. Display all the duplicates sequentially (pre-order recursive traversal used)
	3. If you wish to delete one or more duplicate files, select the index
	4. Repeat steps 1, 2, 3 till user wishes to exit

* Logic:
	1. Pass the directory to search for duplicates to function 'nftw(3)'		(ftw stands for 'file tree walk') 
	2. nftw(3) is present in 'ftw.h'. It walks through the directory tree that is located under the directory dirpath, and calls fn()
	3. Duplicate finding logic is used in the fn() passed to nftw()
   	4. Duplicate file names are stored in a map where Filename is the key and Vector of strings is the value
	   Vector contains addresses of duplicate files
	5. If user wants to delete any of these files, take the required input, traverse over the vector and delete these files
	6. Repeat steps 1-5 till user wishes to exit

===========================================================================================================================================
