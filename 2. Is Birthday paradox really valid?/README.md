===========================================================================================================================================

* Assignment 2: Is Birthday paradox really valid?

* Solution:
	1. input 		: none (Verifies for 1 to 366 persons on its own, default 10000 runs for high accuracy)
	2. src 			: bdayparadox_verified.c 
	3. output 		: stdout
	4. requirements : no additional installations required

* Flow of Program:
	1. Calculate probability by running the Birthday Paradox Random Experiment n no. of times - will give test results. (n = 10000 default)
	2. Calculate using simple probability formulae (mathematically)
	3. Print both results in tabular form to compare them and prove

* Logic:
	1. Generating random b'day between day 1 to 366 and assigning to people
	2. Marking 1 for each repetition occured in respective array index
	3. Run steps 1, 2 for persons = 1 to 366 (as 366 persons gives 100% chance of repetition is known)
	4. Run steps 1, 2, 3 for 10000 times and calculate probability 
	5. Calculate probability for the same sample space using simple probability formulae (mathematically)
	6. Present in tabular form side-by-side for easy comparison

===========================================================================================================================================
