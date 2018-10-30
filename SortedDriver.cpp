// SortedDriver.cpp
// Ben Howe
// COSC 2030
// Lab 06

// Modified. 
// Original source:
// tom bailey   1445  25 mar 2014
// Construct sorted sequences and call functions that
//   process the sorted sequences.


#include "RandomUtilities.h"
#include "ContainerPrinting.h"
#include "winTimer.h"//CHANGE: this to unixTimer.h if on mac/linux
#include <list>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// post: a sorted vector of listSize random doubles from
//         the range minNum to maxNum has been returned.
vector<double> getNums(size_t listSize, double minNum, double maxNum)
{
	vector<double> theList;
	for (size_t i = 0; i < listSize; ++i)
	{
		theList.push_back(randReal(minNum, maxNum));
	}

	sort(begin(theList), end(theList));

	return theList;
}


// post: a sorted list of numWords words of length
//         wordLength with characters chosen randomly from
//         alphabet has been returned.
list<string> getWords(size_t numWords, size_t wordLength, string alphabet)
{
	list<string> theWords;
	for (size_t i = 0; i < numWords; ++i)
	{
		string word;
		for (size_t j = 0; j < wordLength; ++j)
		{
			word += alphabet.at(randInt(0, alphabet.size()));
		}
		theWords.push_back(word);
	}

	theWords.sort();

	return theWords;
}


// pre:  number is not empty;
//       number is sorted from smallest to largest
// post: The most isolated entry in number has been returned
double mostIsolated(vector<double> & number)
{
	
	
	// STUB  STUB  STUB

	int mi = 0; //most isolated
	double maxdiff = 0; //nearest neightbor difference
	double nextdiff = 0; //temporary difference of current and next number
	double prevdiff = 0; //temporary difference of current and previous number
	double leastdiff = 0; //temporary least difference
	for (int i = 0; i < number.size(); i++)
	{
		if (i == 0) // first element
		{
			prevdiff = -1; // there is no previous difference
		} 
		if (i == number.size() - 1)  // last element
		{
			nextdiff = -1; // there is no next difference
		}

		if (i != 0) // compare to previous
		{
			prevdiff = abs(number[i - 1] - number[i]);
		}
		if (i != number.size() - 1)// compare to next
		{
			nextdiff = abs(number[i + 1] - number[i]);
		}


		if (i == 0) //first element
		{ 
			leastdiff = nextdiff;
		}

		if (i == number.size() - 1) // last element
		{
			leastdiff = prevdiff;
		}

		if (prevdiff != -1 && nextdiff != -1) //for the case when we're not on the first or the last vector element
		{
			if (nextdiff > prevdiff) { leastdiff = prevdiff; }
			if (prevdiff > nextdiff) { leastdiff = nextdiff; }
		}




		if (leastdiff > maxdiff)
		{
			maxdiff = leastdiff;
			mi = i;

		}
	}
	return number[mi];
}


// pre:  A and B are sorted.
// post: The number of strings in A that do not occur in B
//         has been returned.
int unmatched(list<string> & A, list<string> & B)
{
	// STUB  STUB  STUB
	bool found = false; // 
	int AnotinB = 0; // keep track of no match condition

	for(std::list<string>::iterator itA = A.begin(); itA != A.end(); ++itA)
	{
		
		found = false; //reset
		for (std::list<string>::iterator itB = B.begin(); itB != B.end(); ++itB)
		{
			if (*itA == *itB)
			{
				found = true;//found a match
				break; //get out of loop
			}
		
		}
		if (found == false)
		{
			AnotinB++;
		}
		
	}
	
		
	return AnotinB;
}


int main()
{
	cout << "Find the most isolated number" << endl
		<< "-----------------------------" << endl << endl;
	while (true)
	{
		cout << "Enter size for numbers: ";
		int n = 0;
		cin >> n;
		if (n <= 0)
			break;
		cout << "Enter seed for rand: ";
		unsigned int seed;
		cin >> seed;
		srand(seed);

		// Construct a sorted list of numbers
		Timer get;
		get.start();
		vector<double> numbers = getNums(n, -n, n);
		get.stop();
		cout << "Constructed in " << get() << " seconds"
			<< endl;

		if (n < 10)
			cout << numbers << endl << endl;

		// Report a most isolated isolated number
		Timer time;
		time.start();
		double isolated = mostIsolated(numbers);
		time.stop();
		cout << "The most isolated number is "
			<< isolated << endl
			<< "calculated in " << time() << " seconds"
			<< endl << endl;
	}


	cout << endl << endl;
	cout << "Count the unmatched words" << endl
		<< "-------------------------" << endl << endl;
	while (true)
	{
		cout << "Enter size for words lists: ";
		int n = 0;
		cin >> n;
		if (n <= 0)
			break;
		cout << "Enter word length: ";
		int wordSize;
		cin >> wordSize;
		cout << "Enter alphabet: ";
		string alphabet;
		cin >> alphabet;

		cout << "Enter seed for rand: ";
		unsigned int seed;
		cin >> seed;
		srand(seed);

		// Construct two sorted vectors of words
		Timer get;
		get.start();
		list<string> A = getWords(n, wordSize, alphabet);
		list<string> B = getWords(n, wordSize, alphabet);
		get.stop();
		cout << "Constructed in " << get() << " seconds"
			<< endl;

		if (wordSize * n < 60)
		{
			cout << "A is: " << A << endl
				<< "B is: " << B << endl;
		}

		// Report the number of words in the first sorted list
		//   that are not in the second sorted list
		Timer time;
		time.start();
		int count = unmatched(A, B);
		time.stop();
		cout << count
			<< " words in A were not in B" << endl
			<< "calculated in " << time() << " seconds"
			<< endl << endl;
	}

	return 0;
}
