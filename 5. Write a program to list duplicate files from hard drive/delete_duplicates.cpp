
#define line cout<<"\n===============================================================================";
#ifndef USE_FDS
#define USE_FDS 20
#endif
#define MAX 1000

#include <stdexcept>
#include <stdlib.h>
#include <unistd.h>
#include <ftw.h>
#include <time.h>
#include <iostream>
#include <map>
#include <vector>
#include <string.h>
#include <errno.h>
using namespace std;

map <string, vector<string> > Dup_Map; //Map to store key(a duplicate file's name) and values(a vector storing names of all duplicate files)
map <int, string> Dup_Names; //Map to store Sr no. and filename that has its duplicates present in the hard disk 
map <string, vector<string> > :: iterator Dup_map_Iter; //iterator over the map that has duplicates
int found = 0, choice, opt;	//flags to debug
string dir;

string Find_File_Name(string path) 
{
	//Extracts File_name from a complete_file_path

	size_t found = path.find_last_of("/");
	return path.substr(found+1);
}

void get_Dup_Names(void)
{
	map<int, string > :: iterator Dup_Iter;
	int Num_Dup1=1, Num_Dup2=0;
	vector<string> :: iterator vec_iter;

	for(Dup_map_Iter = Dup_Map.begin(); Dup_map_Iter != Dup_Map.end(); Dup_map_Iter++)
    {
    	if( (Dup_map_Iter->second).size() > 1 )	//duplicate is present for this key, so insert in map Dup_Names
    	{
    		Dup_Names.insert(pair<int, string>(Num_Dup1++, Dup_map_Iter->first));
			found=1;
    	}
    }
	
	if(found == 1)	//if duplicate is found
	{
		line
		cout<<"\nList of File names that have duplicates in specified directory:	";
		line
		cout<<"\n\n";
	
		for(Dup_Iter = Dup_Names.begin(); Dup_Iter != Dup_Names.end(); Dup_Iter++)
		{
			//list down names of duplicate files
			cout << Dup_Iter->first << ". ";
			Dup_map_Iter = Dup_Map.find(Dup_Names.at(Dup_Iter->first));	
	
			//number of duplicates found per file 
			cout << Dup_Iter->second <<"\t\t\t\t"<< Dup_map_Iter->second.size()<<" duplicates found"<<endl;
		}
		line
	}
	else
		cout<<"\n-> No duplicate found in specified directory. Exiting!"<<endl;
}

int file_entry(const char *filepath, const struct stat *info, const int typeflag, struct FTW *pathinfo) 
{
	//This function is to be run for every file entry

	string file_name = Find_File_Name(filepath); 
	string fileDel;
	vector<string> temp;

    //File
    if (typeflag == FTW_F)
    {
    	temp.push_back(filepath);
    	if( Dup_Map.insert( pair<string, vector<string> > (file_name, temp)).second == false )
    	{
    		Dup_Map.at(file_name).push_back(filepath);
    	}
    }

    //Unreadable Directory
    else if (typeflag == FTW_DNR)
    {
    	cerr << "\nDirectory " << filepath << "is unreadable!";
    }

    temp.clear(); //Clear
    return 0;
}


int print_directory_tree(const char * dirpath)
{
	//Print Directory Tree
    int result, i;

    //Invalid directory path
    if (dirpath == NULL || *dirpath == '\0')
        return errno = EINVAL;

	/*
	   ____________
	  |			  |
	  |  nftw()   |
	  |___________|

	   File_tree_walk( man nftw() ) function
	   USE_FDS -> Maximum number of directories open at a time.
	   FTW_PHYS -> Don't follow symbolic links
	   file_print -> Fuction called for each entry
	   dirpath -> Parent directory
	*/
    result = nftw(dirpath, file_entry, USE_FDS, FTW_PHYS);

    if (result >= 0)
        errno = result;
}

void delete_files()
{
	vector<string> :: iterator vec_iter;
	int Num_Dup = 0;
    int option = 0;
    char if_del = 'n', confirm;
    int Num_del_files = 1;
    int inner_del;
	int delete_indices[MAX], i;

	if(found == 1) //duplicates found
	{
		cout << "\nDo you wish to delete duplicates for any of these files? (Y/N) ";
		cin >> if_del;	
	}
	if(if_del == 'Y' || if_del == 'y')
	{
		cout << "\nSelect the duplicate files to delete? (Enter index number)	";
		cin >> option;

		//Vector corresponding to this key contains filepaths of duplicate files
		try 
		{
		    Dup_map_Iter = Dup_Map.find(Dup_Names.at(option));     // vector::at throws an out-of-range
		}
  		catch (const std::out_of_range& oor) 
		{
		    std::cerr << "Out of Range error!"<<endl;
			cout<<"Auto-selecting the last index!"<<endl;
		}		
		string file = Dup_map_Iter->first;

		//representing the duplicate file list in tabular form
		cout << "\n\t" << file << endl;
		for(vec_iter = (Dup_map_Iter->second).begin(); vec_iter != (Dup_map_Iter->second).end(); vec_iter++)
		{
			cout << "\t|_ " << ++Num_Dup << "] " << *vec_iter << endl ;
		}
		
		cout<<"\nNumber of files to delete (max "<<Num_Dup<<", Enter -1 to DELETE ALL, 0 to delete NONE): "<<endl;
		cin>>Num_del_files;
		
		if(Num_del_files == -1) //delete all
		{
			cout << "\nAre you sure you want to DELETE ALL the listed duplicate files? (Y/N) ";
			cin>>confirm;
			if(confirm == 'Y' || confirm == 'y')
			{
				for(i=0; i<Num_Dup; i++)
				{
					string filename = (Dup_map_Iter->second).at(i);
					string s = "rm -r \"" + filename +"\"";
			
					if(system(s.c_str()) != 0)
					    cerr<<"\nError deleting file"<<endl;
					else
					    cout<<"\nFile "<<filename<<" successfully deleted";
				}
				cout<<"\n\nDo you want to delete more files? (0/1) "<<endl;
				cin>>choice;
				if(choice == 1)
				{
					found = 0;
					Dup_Map.clear();
					Dup_Names.clear();
					switch(opt)
					{
						case 1:
							print_directory_tree("/");
							break;
						case 2:
							print_directory_tree(".");			
							break;
						case 3:
							print_directory_tree(dir.c_str());
							break;
					}
					get_Dup_Names();	//gets names of currently duplicate bearing files in map Dup_Names	
					delete_files();
				}	
			}
			else
			{
				cout<<"\nExiting! "<<endl;
				exit(0);
			}
		}
		else if(Num_del_files == 0) //delete none
		{
			choice = 2;
		}
		else if(Num_del_files <= Num_Dup)
		{
			cout<<"\nEnter the index numbers to DELETE :"<<endl;
			for(i=0; i<Num_del_files; i++)
			{
				cout<<i+1<<": ";
				cin>>delete_indices[i];
			}
			for(i=0; i<Num_del_files; i++)
			{
				string filename = (Dup_map_Iter->second).at(delete_indices[i] - 1);
				string s = "rm -r \"" + filename +"\"";
			
				if(system(s.c_str()) != 0)
				    cerr<<"\nError deleting file"<<endl;
				else
				    cout<<"\nFile "<<filename<<" successfully deleted";
			}
			cout<<"\n\nDo you want to delete more files? (0/1) "<<endl;
			cin>>choice;	
			if(choice == 1)
			{
				found = 0;
				Dup_Map.clear();
				Dup_Names.clear();
				switch(opt)
				{
					case 1:
						print_directory_tree("/");
						break;
					case 2:
						print_directory_tree(".");			
						break;
					case 3:
						print_directory_tree(dir.c_str());
						break;
				}
				get_Dup_Names();	//gets names of currently duplicate bearing files in map Dup_Names	
				delete_files();
			}	
		}
		else
		{
			choice = 2;
			cout<<"\nInvalid entry! Returning."<<endl;
			return;
		}	
	}
	else //no duplicate found OR no deletion required
	{
		cout<<"\nExiting! "<<endl;
		choice = 2;
		return;
	}
}

void select_path_to_search(void)
{
	line
	cout<<"\nSelect path to search from: \n"<<endl;
	cout<<"1. Root directory \n(May take around 3-5 minutes depending on the memory used and processor)\n2. Present Working Directory\n3. Any other (specify)\n4. Exit";
	cout<<endl;
	cin>>opt;

	switch(opt)
	{
		case 1:
			print_directory_tree("/");
			break;
		case 2:
			print_directory_tree(".");			
			break;
		case 3:
			cout<<"\nEnter the directory path to find duplicates in: ";
			cin>>dir;
			print_directory_tree(dir.c_str());
			break;
		case 4:
			cout<<"\nExiting! "<<endl;
			exit(0);
			break;
		default:
			cout<<"\nPlease re-enter a correct choice! Your new choice : ";
			cin>>opt;
			switch(opt);
	}	
}

/* Main function */
int main(int argc, char *argv[])
{
	while(1)
	{		
		select_path_to_search();
		get_Dup_Names(); //gets names of currently duplicate bearing files in map Dup_Names	
		delete_files(); 
		found = 0; 
		if(choice == 0)
		{
			cout<<"\nExiting! "<<endl;
			break;
		}
		Dup_Map.clear();
		Dup_Names.clear(); 
	}
	return EXIT_SUCCESS;
}
