/* A Sample main function for testing the search and sort algorithms in the header file */
/* SupportFunctions.h" */


#include "SupportFunctions.h"



int main()
{

	vector<int> v2(300000);
	clock_t start, stop;
	initializeList(v2);
	printVector(v2);  // print will only print the first 10 elements, you might want to change this number.
	start = clock();  // start time
	//mergeSort(v2, 0, v2.size() - 1);
	quicksort(v2, 0, v2.size() - 1);  // run one sorting algorithm at a time.
	//insertionSort(v2);
	//shellSort(v2, 8191);
	//quicksort(v2, 0, v2.size()-1);
	//radixSort(v2);
	stop = clock() - start; // time elapsed
	printVector(v2);
	cout << "time taken was " << (double)stop / CLOCKS_PER_SEC << endl;
	cout << "Done" << endl;
	system("pause");
	return 0;
}