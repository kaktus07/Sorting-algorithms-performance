#include<iostream>	//For reading and writing to console
#include<fstream>	//For reading and writing to file
#include<iomanip>	//For output formatting
#include<random>	//For random numbers generation
#include<chrono>	//For sorting time measurement

//CLASSES DECLARATION
class Sorting		//Parent class for all the others
	{
	public:
	Sorting();				//Default constructor of the Sorting class.
	Sorting(int size);		//Parametarized constructor of the Sorting class.
	~Sorting();				//The destructor of the Sorting class.
	void print();			//Prints the elements of the array to a file, followed by a newline character
	void randomIntegersFile(int min, int max);	//Generates a file with random integers within a specified range
	void readFromFile();	//Reads a sequance of integers from a file
	int getSize() const;	//Returns the array size (the number of integers)
	
	protected:
	void swap(int &a, int &b);	//Swaps the values of two integer variables
	int size;	//Stores array size
	int* A;		//A dynamic array pointer
	};

class Bubblesort : public Sorting
    {
    public:
    Bubblesort() : Sorting() { }				//Default constructor
    Bubblesort(int size) : Sorting(size) { }	//Parametrized constructor
    void sort();								//Sorts the elements of the array using the bubble sort algorithm.
    
    private:
    // No additional private members in the Bubblesort class.
    };

class Insertionsort : public Sorting
	{
	public:
	Insertionsort() : Sorting() { }				//Default constructor
	Insertionsort(int size) : Sorting(size) { }	//Parameterized constructor
	void sort();		//Sorts the elements of the array using the insertion sort algorithm.
	};

class Quicksort : public Sorting
    {
    public:
    Quicksort() : Sorting() { }				//Default constructor
    Quicksort(int size) : Sorting(size) { }	//Parameterized constructor
    void sort(int i, int j);				//Sorts the subarray [i, j] using the quicksort algorithm.

    private:
    int partition(int first, int last, int pivot);
    //Partition function: Rearranges the elements in the subarray [first, last], such that all elements less than the pivot are on the left, and all elements greater than or equal to the pivot are on the right.
    };
   
class Mergesort : public Sorting
    {
    public:
    Mergesort() : Sorting() { }				//Default constructor
    Mergesort(int size) : Sorting(size) { }	//Parameterized constructor
	void sort(int left, int right);			//Sorts the elements of the array using the merge sort algorithm.
    
    private:
	void mergeStandard(int left, int middle, int right);	//Performs the standard merge operation for merge sort.
	void mergeBottomUp(int left, int middle, int right);	// Performs the bottom-up merge operation for merge sort.	

    };

class Heapsort : public Sorting
    {
    public:
    Heapsort() : Sorting() { }				//Default constructor
    Heapsort(int size) : Sorting(size) { }	//Parameterized constructor
    void sort();							//Sorts the elements of the array using the heap sort algorithm.
    
	private:
	void heapify(int i, int heapSize);		// Performs the heapify operation for heap sort.
    };

//FUNCTIONS DECLARATIONS
void bubbleSort(int arraySize, int min, int max);
// Sorts an array of integers using the bubble sort algorithm.
// Parameters:
// - arraySize: The size of the array.
// - min: The minimum value for generating random integers.
// - max: The maximum value for generating random integers.
void insertionSort(int arraySize, int min, int max);
// Sorts an array of integers using the insertion sort algorithm.
// Parameters:
// - arraySize: The size of the array.
// - min: The minimum value for generating random integers.
// - max: The maximum value for generating random integers.
void quickSort(int arraySize, int min, int max);
// Sorts an array of integers using the quick sort algorithm.
// Parameters:
// - arraySize: The size of the array.
// - min: The minimum value for generating random integers.
// - max: The maximum value for generating random integers.
void mergeStandardSort(int arraySize, int min, int max);
// Sorts an array of integers using the standard merge sort algorithm.
// Parameters:
// - arraySize: The size of the array.
// - min: The minimum value for generating random integers.
// - max: The maximum value for generating random integers.
void mergeBottomUpSort(int arraySize, int min, int max);
// Sorts an array of integers using the bottom-up merge sort algorithm.
// Parameters:
// - arraySize: The size of the array.
// - min: The minimum value for generating random integers.
// - max: The maximum value for generating random integers.
void heapSort(int arraySize, int min, int max);
// Sorts an array of integers using the heap sort algorithm.
// Parameters:
// - arraySize: The size of the array.
// - min: The minimum value for generating random integers.
// - max: The maximum value for generating random integers.

int main ()
	{
	using namespace std;	
	int arraySize, min, max;
	cout<<"How many elements to sort? ";
	cin>>arraySize;
	cout<<"Lower limit for pseudorandom numbers generation: ";
	cin>>min;
	cout<<"Upper limit for pseudorandom numbers generation: ";
	cin>>max;
	
	int choice;
	cout<<"Provide a number 1-6 for choosing a sorting algorithm\n";
	cout<<"1 - Bubble sort\n2 - Insertion sort\n3 - Quick sort\n4 - Merge sort (standard)\n5 - Merge sort (bottom-up)\n6 - Heap sort\n";
	cin>>choice;
	
	auto startTime = chrono::high_resolution_clock::now();	//Record the start time

	switch (choice)
		{
		case 1: bubbleSort(arraySize, min ,max);		//BUBBLE SORT
		break;
		
		case 2: insertionSort(arraySize, min, max);	 	//INSERTION SORT
		break;
		
		case 3: quickSort(arraySize, min, max);			//QUICK SORT
		break;
		
		case 4: mergeStandardSort(arraySize, min, max);	//MERGE SORT (STANDARD)
		break;
		
		case 5: mergeBottomUpSort(arraySize, min, max);	//MERGE SORT (BOTTOM-UP)
		break;
		
		case 6:	heapSort(arraySize, min, max);			//HEAP SORT
		break;
		
		default: cout<<"Wrong input!\n";
				 exit(1);
		}
	
	auto endTime = chrono::high_resolution_clock::now();	//Record the end time
	auto duration = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();
    cout<<endl<<setw(40)<<left<<"Total sorting time: "<<setw(5)<<right<<duration<<" miliseconds"<<endl;
    
	return 0;
	}

//SORTING CLASSES DEFINITIONS
Sorting::Sorting()
	//Default constructor
	{
	size=10;
	A = new int[size];
	}
	
Sorting::Sorting(int size)
	//Constructor with declared array size
	{
	this -> size = size;
	A = new int[size];
	}
	
	Sorting::~Sorting()
	//Destructor
	{
	delete[] A;
	}
	
int Sorting::getSize() const
	//Returns the array size
	{
	return size;
	}

void Sorting::swap(int &a, int &b)
	//Swaps the values of two integer variables
	{
	int temp=a;
	a=b;
	b=temp;
	}

void Sorting::print()
	//Prints the elements of the array to a file, followed by a newline character
	{
	std::ofstream outputFile;
		outputFile.open("Sorted numbers.txt");
	if (outputFile.is_open())
		std::cout<<"Output file opened correctly\n";
	else
		{
		std::cout<<"Faild to open the output file\n";
		exit(1);
		}
	
	for (int i=0; i<size; i++)
		outputFile<<A[i]<<" ";
	outputFile<<std::endl;

	outputFile.close();
	}

void Sorting::randomIntegersFile(int min, int max)
	// Generates a file with random integers within a specified range
	{
	std::random_device rd;
	std::mt19937 engine(rd());
	std::uniform_int_distribution<int> distribution(min, max);
	
	std::ofstream inputFileWrite;
	inputFileWrite.open("Unsorted numbers.txt");
	if (inputFileWrite.is_open())
		std::cout<<"\nInput file for writing opened correctly.\n";
	else
		{
		std::cout<<"Faild to open the input file for writing down the data!\n";
		exit(1);
		}
	
	for (int i=0; i<size; i++)
		inputFileWrite<<distribution(engine)<<" ";
	
	std::cout<<"An input file with random numbers was generated.\n";
	inputFileWrite.close();
	}

void Sorting::readFromFile()
	// Reads a sequence of integers from a file
	{
	std::ifstream inputFileRead;
	inputFileRead.open("Unsorted numbers.txt");
	if (inputFileRead.is_open())
		std::cout<<"Input file for reading opened correctly.\n";
	else
		{
		std::cout<<"Faild to open the input file for reading the data!\n";
		exit(1);
		}
	
	int num, count=0;
	while (inputFileRead >> num)
		A[count++] = num;
	
	inputFileRead.close();
	}

void Bubblesort::sort()
	//Sorts the elements of the array using the bubble sort algorithm
	{
	for (int i=0;i<getSize(); i++)
		for (int j=0; j<getSize()-i-1; j++)
			{
			if (A[j] > A[j+1])
				swap(A[j], A[j+1]);
			}
	}

void Insertionsort::sort()
	{
	//Sorts the elements of the array using the insertion sort algorithm
	for (int i=1; i<getSize(); i++)
		{
		int j=i;
		while (j > 0 && A[j-1] > A[j])
			{
			swap(A[j], A[j-1]);
			j--;
			}
		}
	}

int Quicksort::partition(int first, int last, int pivot)
	//Partitions the array into two halves and returns the index of the pivot
	{
	int i=first;
	int j=last;
	while (i<=j)
		{
		while (A[j] >= pivot && j>= first)
			j--;
		while (A[i] < pivot && i<=last)
			i++;
		if (i<j)
			{
			swap(A[i], A[j]);
			i++;
			j--;
			}
		}
	swap(A[i], A[last]);	//Move pivot to its correct position
	return i;	//By now, i is set to the sorted index position
	}

void Quicksort::sort(int i, int j)
	//Sorts the elements of the array using the quicksort algorithm
	{
	if (i<j)	//(pivotIndex != 0)
		{
		int pivotIndex = i + rand()%(j-i+1);	//Returns a random index between 'first' and 'last' (inclusive)
		swap(A[pivotIndex], A[j]); //Move the pivot to the last position
		int pivot = A[j];
		int k=partition(i, j, pivot);
		sort(i, k-1);
		sort(k+1, j);
		}
	}

void Mergesort::sort(int left, int right)
	//Sorts the elements of the array using the merge sort algorithm
	{
	if (left < right)
		{
		int middle = left + (right-left)/2;
	
		sort(left, middle);
		sort(middle+1, right);
	
		mergeBottomUp(left, middle, right);
		}
	}

void Mergesort::mergeBottomUp(int left, int middle, int right)
	//Merges two sorted subarrays into a single sorted subarray (bottom-up approach)
	{
	int i = left;
	int j = middle + 1;
	
	while (i <= middle && j <= right)
		{
		if (A[i] <= A[j])
			i++;
		else
			{
			int temp = A[j];
			for (int k = j - 1; k >= i; k--)
				A[k+1] = A[k];
			A[i] = temp;
			i++;
			middle++;
			j++;
			}
		}
	}

void Mergesort::mergeStandard(int left, int middle, int right)
	//Merges two sorted subarrays into a single sorted subarray (standard approach)
	{
	int n1 = middle - left - 1;
	int n2 = right - middle;
	
	//Create temporary arrays
	int *Left = new int[n1];
	int *Right = new int[n2];
	
	//Copy data to temporary arrays
	for (int i=0; i < n1; i++)
		Left[i] = A[left + i];
	for (int j=0; j < n2; j++)
		Right[j] = A[middle+1+j];
	
	//Merge the temporary arrays back into A
	int i=0, j=0, k=left;
	
	while (i < n1 && j < n2)
		{
		if (Left[i] < Right[j])
			{
			A[k] = Left[i];
			i++;
			}
		else
			{
			A[k] = Right[j];
			j++;
			}
		k++;
		}
	
	//Copy the remaining elements of Left[], if there are any
	while (i < n1)
		{
		A[k] = Left[i];
		i++;
		k++;
		}
	
	//Copy the remaining elements of Right[], if there are any
	while (j < n2)
		{
		A[k] = Right[j];
		j++;
		k++;
		}
	
	//Deallocate the memory used for temporary arrays
	delete[] Left;
	delete[] Right;
	}

void Heapsort::heapify(int i, int heapSize)
	//Heapify the subtree rooted at index i
	{
	int largest = i;	//Initialize largest as the root
	int left = 2*i+1;	//Left child index
	int right = 2*i+2;	//Right child index
	
	//Check if the left child is greater than the root
	if (left < heapSize && A[left] > A[largest])
		largest = left;
	
	//Check if the right child is larger than the largest so far
	if (right < heapSize && A[right] > A[largest])
		largest = right;
	
	//If the largest is not the root
	if (largest!= i)
		{
		swap(A[i], A[largest]);	
		heapify(largest, heapSize);	//Recursively heapify the affected subtree
		}
	}
	
void Heapsort::sort()
	{
	//Sorts the elements of the array using the heap sort algorithm
	int n = getSize();
	
	//Build a max heap
	for (int i = n/2 - 1; i>=0; i--)
		heapify(i, n);
	
	//Extract elements from the heap one by one
	for (int i=n-1;i>=1; i--)
		{
		swap(A[0], A[i]);	//Move the currect root (maximum element) to the end of the sorted array
		n--;				//Reduce the size of the unsorted heap by 1
		heapify(0, n);		//Call heapify on the reduced heap
		}
	}


//CLASS FUNCTIONS DEFINITIONS
void bubbleSort(int arraySize, int min, int max)
	{
	using namespace std;

	//Create an instance of Bubblesort class
	Bubblesort Bubble(arraySize);
	Bubble.randomIntegersFile(min, max);
	Bubble.readFromFile();
	
	auto startTime = chrono::high_resolution_clock::now();	//Record the start time
	Bubble.sort();
	auto endTime = chrono::high_resolution_clock::now();	//Record the end time
	auto duration = chrono::duration_cast<chrono::microseconds>(endTime - startTime).count();

	Bubble.print();
    cout<<setw(40)<<left<<"Bubble sort sorting time: "<<setw(5)<<right<<duration<<" microseconds"<<endl;
    }
   
void insertionSort(int arraySize, int min, int max)
	{
	using namespace std;

    //Create an instance of Insertionsort class
	Insertionsort Insertion(arraySize);
	Insertion.randomIntegersFile(min, max);
	Insertion.readFromFile();
	
	auto startTime = chrono::high_resolution_clock::now();	//Record the start time
	Insertion.sort();
	auto endTime = chrono::high_resolution_clock::now();	//Record the end time
	auto duration = chrono::duration_cast<chrono::microseconds>(endTime - startTime).count();

	Insertion.print();
   std:: cout<<setw(40)<<left<<"Insertion sort sorting time: "<<setw(5)<<right<<duration<<" microseconds"<<endl;
	}

void quickSort(int arraySize, int min, int max)
	{
	using namespace std;

    //Create an instance of Quicksort class
	Quicksort Quick(arraySize);
	Quick.randomIntegersFile(min, max);
	Quick.readFromFile();
	
	auto startTime = chrono::high_resolution_clock::now();	//Record the start time
	Quick.sort(0, Quick.getSize() - 1);
	auto endTime = chrono::high_resolution_clock::now();	//Record the end time
	auto duration = chrono::duration_cast<chrono::microseconds>(endTime - startTime).count();

	Quick.print();
	std::cout<<setw(40)<<left<<"Quick sort sorting time: "<<setw(5)<<right<<duration<<" microseconds"<<endl;
	}

void mergeStandardSort(int arraySize, int min, int max)
	{
	using namespace std;
	
    //Create an instance of Mergesort class
	Mergesort MergeStd(arraySize);
	MergeStd.randomIntegersFile(min, max);
	MergeStd.readFromFile();
	
	auto startTime = chrono::high_resolution_clock::now();	//Record the start time
	MergeStd.sort(0, MergeStd.getSize() - 1);
	auto endTime = chrono::high_resolution_clock::now();	//Record the end time
	auto duration = chrono::duration_cast<chrono::microseconds>(endTime - startTime).count();

	MergeStd.print();
	std::cout<<setw(40)<<left<<"Merge sort (standard) sorting time: "<<setw(5)<<right<<duration<<" microseconds"<<endl;
	}

void mergeBottomUpSort(int arraySize, int min, int max)
	{
	using namespace std;
	
    //Create an instance of Mergesort class
	Mergesort MergeBottomUp(arraySize);
	MergeBottomUp.randomIntegersFile(min, max);
	MergeBottomUp.readFromFile();
	
	auto startTime = chrono::high_resolution_clock::now();	//Record the start time
	MergeBottomUp.sort(0, MergeBottomUp.getSize() - 1);
	auto endTime = chrono::high_resolution_clock::now();	//Record the end time
	auto duration = chrono::duration_cast<chrono::microseconds>(endTime - startTime).count();

	MergeBottomUp.print();
	std::cout<<setw(40)<<left<<"Merge sort (bottom-up) sorting time: "<<setw(5)<<right<<duration<<" microseconds"<<endl;
	}

void heapSort(int arraySize, int min, int max)
	{
	using namespace std;
	
    //Create an instance of Heapsort class
	Heapsort Heap(arraySize);
	Heap.randomIntegersFile(min, max);
	Heap.readFromFile();
	
	auto startTime = chrono::high_resolution_clock::now();	//Record the start time
	Heap.sort();
	auto endTime = chrono::high_resolution_clock::now();	//Record the end time
	auto duration = chrono::duration_cast<chrono::microseconds>(endTime - startTime).count();

	Heap.print();
	std::cout<<setw(40)<<left<<"Heap sort sorting time: "<<setw(5)<<right<<duration<<" microseconds"<<endl;
	}
