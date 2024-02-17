// Assignment: ASU CSE310 HW#3 Spring 2024
// Your Name: Raje Patil
// ASU ID: 1231031453
// ASU Email address: rpatil46@asu.edu
// Description: Header file for max heap that has all the functions for heapsort and priority queue functions.
//				a newly added function apart from the structure was setSize that alters the size of the array while
//				heapifying to implement a heapsort.
//********************************************************
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

//Each Car will have a unique Vin
struct Car
{
	string model, make;
	int vin;        //Vehicle Identification Number
	double price;
};

//class MaxHeap represents a max heap that contains Car objects. The underline data structure
//is a one dimensional array of Cars.
class MaxHeap
{
private:
	struct Car* carArr;	//an array of Cars
	int capacity, size;

public:
	MaxHeap(int capacity);
	~MaxHeap();

	Car* getCarArr();
	int getSize();
	void setSize(int newSize);  //new addition
	int getCapacity();
	int isFound(int aVin);
	bool heapIncreaseVIN(int index, Car oneCarWithNewVIN);
	bool heapInsert(int vin, string model, string make, double price);
	void heapify(int index);
	Car getHeapMax();
	void extractHeapMax();
	int leftChild(int parentIndex);
	int rightChild(int parentIndex);
	int parent(int childIndex);
	void printHeap();
};

//Constructor to dynamically allocate memory for a heap with the specified capacity
MaxHeap::MaxHeap(int capacity) 
{
	// Initialize the class member variable 'capacity'
    this->capacity = capacity; 
    // Initialize the class member variable 'size' to 0
    this->size = 0;        

    // Dynamically allocate memory for the heap array
    carArr = new Car[this->capacity];  // Allocate memory for an array of 'Car' objects
}


//Destructor
//Before termination, the destructor is called to free the associated memory occupied by the heap.
//and prints the number of nodes deleted by it.
MaxHeap::~MaxHeap()
{
	delete[] carArr;
	cout << "\nThe number of deleted cars is: " << size << endl;
}


//This is the accessor of the instance variable carArr
Car* MaxHeap::getCarArr()
{
	return carArr;
}


//return current size of the heap
int MaxHeap::getSize()
{
	return size;
}

//to reset the size of heap if required (for heapsort)
void MaxHeap::setSize(int newSize)
{
	this -> size = newSize;
}

//get the dynamic array container capacity
int MaxHeap::getCapacity()
{
	return capacity;
}


//if the car with the vin exists return its index
int MaxHeap::isFound(int aVin)
{
	for(int i=0; i<size; i++)
	{
		if(carArr[i].vin == aVin)
		{
			return i;
		}
	}

	return -1;
}

//increase the Car's VIN located at the specific index
bool MaxHeap::heapIncreaseVIN(int index, Car oneCarWithNewVIN)
{
    if (index >= size)
    {
        cout << "\nIncrease VIN error: index out of range" << endl;
        return false;
    }

    // Add new car at index
    carArr[index] = oneCarWithNewVIN;

    // Check if the parent is less than the child (and ensure index > 0)
    while (index > 0 && carArr[parent(index)].vin < carArr[index].vin)
    {
        //buffer holds the parent while exchanging these two nodes (parent is smaller, child is larger)
        Car buffer = carArr[parent(index)];
        carArr[parent(index)] = carArr[index];
        carArr[index] = buffer;
        index = parent(index);  // Move up to the parent
    }

    return true;
}


//insert new car in heap
bool MaxHeap::heapInsert(int vin, string model, string make, double price)
{
	//check if the heap is at capacity & double it if required
	if (size == capacity)
	{
		//double the capacity and dynamically reallocate memory
		MaxHeap::capacity *= 2;
		Car* newCarArr = new Car[capacity];

		//copy existing elements to the new array
		for (int i = 0; i < size; ++i)
		{
			newCarArr[i] = carArr[i];
		}

		//delete the old array and update the pointer
		delete[] carArr;
		carArr = newCarArr;

		// Display a message indicating the new capacity
		cout << "\nReach the capacity limit, double the capacity now." << endl;
		cout << "\nThe new capacity now is " << capacity << endl;
	}

	//create a dummy car to add to the heap
	Car dummyCar;
	dummyCar.vin = -10000;
	dummyCar.model = "";
	dummyCar.make = "";
	dummyCar.price = 0.0;

	// Create a new Car object with the given information
	Car newCar;
	newCar.vin = vin;
	newCar.model = model;
	newCar.make = make;
	newCar.price = price;

	// Update the size
	++size;

	// Insert the new Car object at the rightmost position in the last level
	carArr[size-1] = dummyCar;

	// "Float" the new Car object up to maintain the max-heap property
	bool flag = heapIncreaseVIN(size-1, newCar);
	//when the new car is inserted, delete the dummy car
	return flag;
}


void MaxHeap::heapify(int index)
{
	int leftChildIndex = leftChild(index);
	int rightChildIndex = rightChild(index);
	int largest = index;

	// Compare with left child based on VIN
	if (leftChildIndex < size && carArr[leftChildIndex].vin > carArr[largest].vin)
	{
		largest = leftChildIndex;
	}

	// Compare with right child based on VIN
	if (rightChildIndex < size && carArr[rightChildIndex].vin > carArr[largest].vin) {
		largest = rightChildIndex;
	}

	// If the largest is not the current index, swap and recursively heapify the affected subtree
	if (largest != index) {
		std::swap(carArr[index], carArr[largest]);
		heapify(largest);  // Recursively heapify the affected subtree
	}
}

//return root which has the max vin
Car MaxHeap::getHeapMax()
{
	return carArr[0];
}


//remove the root which is the max vin
void MaxHeap::extractHeapMax()
{
    if (size < 1)
    {
        cout << "Heap underflow";
        return;
    }

    Car max = carArr[0];
    carArr[0] = carArr[size - 1];
    carArr[size - 1] = max;  //swap root with the leaf node
    --size;
    //delete max;
    heapify(0);  //heapify the leaf node
    //return max;
}



//returns left child of the parent
int MaxHeap::leftChild(int parentIndex)
{
	return (2 * parentIndex) + 1;
}

//returns right side of the parent
int MaxHeap::rightChild(int parentIndex)
{
	return (2 * parentIndex) + 2;
}


// Returns parent of a child node
int MaxHeap::parent(int childIndex)
{
    return (childIndex-1) / 2;
}


//prints the heap in order
void MaxHeap::printHeap()
{
	if(MaxHeap::size==0)
	{
		cout << "\nEmpty heap, no elements" << endl;
	}

	else
	{
		cout << "\nHeap capacity = " << capacity << endl;
		cout << "\nHeap size = " << size << endl;
		cout << endl;  // Add an empty line

		for(int i=0; i<=MaxHeap::size-1; i++)
		{
			cout << left;
			cout << setw(8) <<  carArr[i].vin
					<< setw(12) << carArr[i].model
					<< setw(12) << carArr[i].make
					<< setw(8) << fixed << setprecision(2) << carArr[i].price << endl;
		}
	}

}
