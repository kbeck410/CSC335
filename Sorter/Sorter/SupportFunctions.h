/* C++ header file for searching and sorting algorithms */

#ifndef SUPPORTFUNCTIONS_H
#define SUPPORTFUNCTIONS_H

#include <iostream>
#include <ctime>
#include <sstream>
#include <vector>
using namespace std;

//function receives a vector of integer type elements by reference call
//the function initializes the vector with random integers 0 - 499
void initializeList(vector<int>& l)
{
	//srand(time(0));
	for (int i = 0; i < l.size(); i++)
		l[i] = (rand() % 500);
}


//function receives a vector of template type T
//and prints the elements of the vector
template<typename T>
void printVector(const vector<T>& l)
{
	cout << "Elements of the vector: ";
	for (int i = 0; i < 20; i++) // prints only the first 20 elements
		cout << l[i] << " ";
	cout << endl;
}

//============================= Linear Search================

//The function linearsearch receives a vector and a key to search for
//If search is successful the index of the key is returned
//If serach fails -1 is returned
template<typename T>
int linearSearch(const vector<T>& l, T key)
{
	for (int i = 0; i < l.size(); i++)
		if (l[i] == key)
			return i;  // return first instance of the key. Function terminates
	return -1;  // search failed, return index -1.
}

//==================================  Binary Search iterative

//Function receives a vector, the size of the list( really not necessay) and the key
//to search for.
//If search is successful the index of the key is returned
//If serach fails -1 is returned

template<typename T>
int BinarySearchIterative(const vector<T>& numbers, int numbersSize, T key)
{
	int low = 0;
	int mid = 0;
	int high = numbersSize - 1;
	while (high >= low)
	{
		mid = (low + high) / 2; // index of the middle element
		if (numbers[mid] < key)
			low = mid + 1;
		else if (numbers[mid] > key)
			high = mid - 1;
		else if (numbers[mid] == key)
			return mid;
	}
	return -1; // failed 
}

//========================= Binary Search  Recursive implementation ===
//Binary Search Recursive
template<typename T>
int BinarySearchRec(const vector<T>& numbers, int low, int high, T key)
{
	if (high < low)
		return -1;
	else
	{
		int mid = (low + high) / 2; // index of the middle element
		if (numbers[mid] < key)
			return BinarySearchRec(numbers, mid + 1, high, key);
		else if (numbers[mid] > key)
			return BinarySearchRec(numbers, low, mid - 1, key);
		else if (numbers[mid] == key)
			return mid;
	}
}

//========================Selection Sort===============================

//the function template selectionSort receives a vector of template type T 
//and sorts the vector.
template<typename T>
void selectionSort(vector<T>& l)
{

	for (int i = 0; i < l.size() - 1; i++)
	{
		int minIndex = i;
		for (int j = i + 1; j < l.size(); j++)
			if (l[minIndex] > l[j])
				minIndex = j;
		//swap elements in locations i and minIndex
		T temp = l[i];
		l[i] = l[minIndex];
		l[minIndex] = temp;
	}
}

//=========================== Insertion Sort ==========================

//Insertion sort receives a vector and implements the insertion sort algorithm
template<typename T>
void insertionSort(vector<T>& l)
{
	for (int i = 1; i < l.size(); i++)
	{
		int j = i;
		while (j > 0 && (l[j] < l[j - 1])) //insert the ith element into sorted list 
		{
			T temp = l[j];
			l[j] = l[j - 1];
			l[j - 1] = temp;
			j--; // move index j back
		}
	}
}

//==========================   Quicksort =====================

//partition functio is used by the quicksort
//the function receives a vector and the left and right index of the list as parameters
//partition uses the midpoint element as the pivot
template <typename T>
int partition(vector<T>& l, int i, int k)
{
	bool done = false;
	int midpoint = i + (k - i) / 2; //Pick middle value as pivot 
	T pivot = l[midpoint];
	int low = i;  // 
	int high = k;
	while (!done) {
		while (l[low] < pivot) ++low; /* Increment low while l[l] < pivot */
		while (pivot < l[high]) --high; /* Decrement high while pivot < l[h] */
		if (low >= high)
			done = true;
		else
		{
			T temp = l[low];
			l[low] = l[high];
			l[high] = temp;
			++low;   --high;
		}
	}
	return high;
}

//QuickSort function 
template <typename T>
void quicksort(vector<T>& l, int i, int k)
{
	int j = 0;
	if (i >= k)     //Base case
		return;
	j = partition(l, i, k);
	/* Recursively sort low and high partitions */
	quicksort(l, i, j);
	quicksort(l, j + 1, k);
}
//==============================  Shell Sort ===============
//function is utilized in shellsort
template <typename T>
void insertionSortInterleaved(vector<T>& l, int startIndex, int gap)
{
	int i = 0;
	int j = 0;
	int temp = 0;  // Temporary variable for swap
	for (i = startIndex + gap; i < l.size(); i = i + gap)
	{
		j = i;
		while (j - gap >= startIndex && l[j] < l[j - gap])
		{
			temp = l[j];
			l[j] = l[j - gap];
			l[j - gap] = temp;
			j = j - gap;
		}
	}
}


//ShellSort makes call to insertionSortInterleaved for each sublist
template <typename T>
void shellSort(vector<T>& l, int initialGapValue) {
	for (int gapValue = initialGapValue; gapValue >= 1; gapValue /= 2)  //initialGapValue should be a (power of 2) - 1.
	{
		for (int i = 0; i < gapValue; i++)
			insertionSortInterleaved(l, i, gapValue);
	}
}


//=============================  Radix Sort =================
// Returns the length, in number of digits, of value
int RadixGetLength(int value)
{
	if (value == 0)
		return 1;
	int digits = 0;
	while (value != 0)
	{
		digits = digits + 1;
		value = value / 10;
	}
	return digits;
}

// Returns the maximum length, in number of digits, out of all elements in the array
int RadixGetMaxLength(vector<int> l)
{
	int maxDigits = 0;
	for (int i = 0; i < l.size(); i++)
	{
		int digitCount = RadixGetLength(l[i]);
		if (digitCount > maxDigits)
			maxDigits = digitCount;
	}
	return maxDigits;
}



void radixSort(vector<int>& l)
{

	// Find the max length, in number of digits
	int  maxDigits = RadixGetMaxLength(l);
	vector<vector<int> > buckets(10);
	// Start with the least significant digit
	int pow10 = 1;
	for (int digitIndex = 0; digitIndex < maxDigits; digitIndex++)
	{
		for (int i = 0; i < l.size(); i++)
		{
			int bucketIndex = abs(l[i] / pow10) % 10; // 654; 
			buckets[bucketIndex].push_back(l[i]);
		}
		int arrayIndex = 0;
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < buckets[i].size(); j++)
				l[arrayIndex++] = buckets[i][j];
		}
		pow10 = 10 * pow10;
		for (int i = 0; i < 10; i++)
			buckets[i].clear();
	}
}
//===========================  Merge Sort ===============

//The merge function merges a two sorted lists
template<typename T>
void merge(vector<T>& l, int i, int j, int k) {
	// Create temporary array mergedNumbers
	// Initialize position variables
	vector<T> mergedNumbers(k - i + 1);
	int leftPos = i;
	int rightPos = j + 1;
	// Add smallest element to merged numbers
	int mergePos = 0;
	while (leftPos <= j && rightPos <= k)
	{
		if (l[leftPos] <= l[rightPos])
		{
			mergedNumbers[mergePos] = l[leftPos];
			++leftPos;
		}
		else
		{
			mergedNumbers[mergePos] = l[rightPos];
			++rightPos;
		}
		++mergePos;
	}
	// If left partition not empty, add remaining elements
	while (leftPos <= j)
	{
		mergedNumbers[mergePos] = l[leftPos];
		++leftPos;
		++mergePos;
	}

	// If right partition not empty, add remaining elements
	while (rightPos <= k)
	{
		mergedNumbers[mergePos] = l[rightPos];
		++rightPos;
		++mergePos;
	}

	// Copy merge number back to numbers
	for (mergePos = 0; mergePos < mergedNumbers.size(); ++mergePos)
	{
		l[i + mergePos] = mergedNumbers[mergePos];
	}
}

//merge sort function
template<typename T>
void mergeSort(vector<T>& l, int i, int k)
{
	int j = 0;
	if (i < k)
	{
		j = (i + k) / 2;   // Find the midpoint in the partition
		// Recursively sort left and right partitions
		mergeSort(l, i, j);
		mergeSort(l, j + 1, k);
		// Merge left and right partition in sorted order
		merge(l, i, j, k);

	}
}

#endif