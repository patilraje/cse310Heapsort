// Assignment: ASU CSE310 HW#3 Spring 2024
// Name: Raje Patil
// ASU ID: 1231031453
// ASU Email Address: rpatil46@asu.edu
// Description: This program displays a menu of choices to a user
//              and performs the chosen task. It will keep asking a user to
//              enter the next choice until the choice of 'Q' (Quit) is entered.
//             	//---- is where you should add your own code
//********************************************************************************

#include "MaxHeap.h"
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

void printMenu();
void heapSort(MaxHeap* oneMaxHeap);

int main()
{
	char input1 = 'Z';
	int vin, newVIN;
	string model, make;
    double price;
	int capacity, index, index2 = -1;   //array capacity and index
	bool success = false;
	//int size = 0;

    Car oneCar;

	// instantiate an empty Heap
	MaxHeap* heap1 = NULL;
	printMenu();

	do {
		cout << "\nWhat action would you like to perform?" << endl;
		cin.get(input1);
		input1 = toupper(input1);
		cin.ignore(20, '\n');	//flush the buffer

		// matches one of the cases
		switch (input1)
		{
			case 'C':	//create empty Heap with the relevant capacity
				cout << "\nPlease enter the heap capacity: ";
				cin >> capacity;
				cin.ignore(20, '\n');	//flush the buffer
				heap1 = new MaxHeap(capacity);  // Dynamically allocate memory for a new MaxHeap object
				break;


			case 'D':	//delete the heap, call the destructor explicitly
				cout << "\nDelete the heap" << endl;
				//heap1->~MaxHeap();
				delete heap1;  // Use delete to free the memory allocated for the heap
				heap1 = NULL;  // Set the pointer to NULL after deleting

				//re-initialize it with capacity 5
				heap1 = new MaxHeap(5);
				break;



			case 'E':	//Extract the maximum node
                if (heap1 == NULL)
                    cout << "\nEmpty heap, can NOT extract max" << endl;
                else
                {
                    cout << "\nBefore extract heap max operation:" << endl;
					heap1->printHeap();
					heap1->extractHeapMax();
					cout << "\nAfter extract heap max operation:" << endl;
					heap1->printHeap();
                }
				break;


			case 'F':	//Find a Car
				cout << "\nEnter the car VIN you want to search: ";
				cin >> vin;
				cin.ignore(20, '\n');	//flush the buffer
				index = heap1->isFound(vin);

				if(index != -1)
				{
					cout << "\nCar with VIN: " << vin << " is found" << endl;
					break;
				}

				else
				{
					cout << "\nCar with VIN: " << vin << " is NOT found" << endl;
					break;
				}
				


			case 'I':	//Insert a Car
				cout << "\nEnter the car model: ";
				cin >> model;

				cout << "\nEnter the car make: ";
				cin >> make;

				cout << "\nEnter the car VIN: ";
				cin >> vin;
				cout << "\nEnter the car price: ";
				cin >> price;
				cin.ignore(20, '\n');	//flush the buffer

				//checking if a car with the new vin already exists in the heap
				index = heap1 -> isFound(vin);
				if(index != -1)  //if it exists it will return a value > 0 not -1
				{
					cout << "\nDuplicated Car. Not added" << endl;
					cout << "\nCar \"" << model << " " << make << "\" is NOT added" << endl;
					break;
				}

				success = heap1 -> heapInsert(vin, model, make, price);

				if(success == true)
				{
					cout << "\nCar \"" << model << " " << make << "\" is added" << endl;
				}

				else
				{
					cout << "\nCar \"" << model << " " << make << "\" is NOT added" << endl;
				}

				break;


			//INCOMPLETE
			case 'K':	//increase the vin
				cout << "\nEnter the old car VIN you want to increase: ";
				cin >> vin;
				cout << "\nEnter the new car VIN: ";
				cin >> newVIN;
				cin.ignore(20, '\n');	//flush the buffer

				if(newVIN < vin)
				{
					cout << "\nIncrease VIN error: new vin is smaller than current vin" << endl;
					break;
				}


				index = heap1 -> isFound(vin);
				if(index == -1)
				{
					cout << "\nThe old VIN you try to increase does not exist" << endl;
					break;
				}

				//checking if a car with the new vin already exists in the heap
				index2 = heap1 -> isFound(newVIN);
				if(index2 != -1)  //if it exists it will return a value > 0 not -1
				{
					cout << "\nThe new VIN you entered already exist, increase VIN operation failed" << endl;
					break;
				}

				cout << "\nBefore increase VIN operation:" << endl;
			    heap1 -> printHeap();

				// Create a new car with the updated VIN
				oneCar = heap1->getCarArr()[index];
				oneCar.vin = newVIN;

				success = heap1 -> heapIncreaseVIN(index, oneCar);
				if(success == true)
				{
					cout << "\nCar with old VIN: " << vin << " is increased to new VIN: " << newVIN << endl;
					cout << "\nAfter increase VIN operation: " << endl;
					heap1 -> printHeap();
				}

				break;


			case 'M':	//get maximum node
				if(heap1 -> getSize() == 0)
				{
					cout << "Empty heap, can NOT get max node" << endl;
					break;
				}

				cout << "\nThe maximum heap node is:" << endl;
				oneCar = heap1 -> getHeapMax();
				cout << left;
				cout << setw(8) << oneCar.vin
					<< setw(12) << oneCar.model
					<< setw(12) << oneCar.make
					<< setw(8) << fixed << setprecision(2) << oneCar.price << endl;

				break;


			case 'P':	//Print heap contents
				if(heap1 == NULL)
				{
					cout << "\nEmpty heap, no elements" << endl;
					break;
				}

				//heapSort(heap1);
				heap1 ->printHeap();
				break;


			case 'S':	//HeapSort
				cout << "\nHeap sort. Cars will be sorted in increasing order of their VINs" << endl;
				heapSort(heap1);
				break;


			case 'Q':	//Quit
				//size=0;
				delete heap1;
				break;


			case '?':	//Display Menu
				printMenu();
				break;


			default:
				cout << "Unknown action\n";
				break;
		}
	} while (input1 != 'Q');
	return 0;
}

//*****************************************************
//Given a max heap, we want to sort it in increasing order according to Car VIN, put the
//sorting result inside another array and print it out
// Swap two Car objects
void swapCars(Car& car1, Car& car2) 
{
    Car temp = car1;
    car1 = car2;
    car2 = temp;
}

// Given a max heap, we want to sort it in increasing order according to Car VIN
void heapSort(MaxHeap* oneMaxHeap) 
{
    int n = oneMaxHeap->getSize();
    Car* arr = oneMaxHeap->getCarArr();
    int originalsize = n;   //to preserve the original size

    // Build a max heap from the input data
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        oneMaxHeap->heapify(i);
    }

    // One by one extract an element from the heap
    for (int i = n - 1; i > 0; i--)
    {
        // Move the current root to the end
        swapCars(arr[0], arr[i]);
        --n;
        oneMaxHeap -> setSize(n);
        // Call heapify on the reduced heap
        oneMaxHeap->heapify(0);

    }

    //finally after this for loop we reduce the size of heap by 1 thus removing the cout of root
    --n;
    oneMaxHeap -> setSize(n);

    // Print the sorted array
    for (int i = 0; i < originalsize; i++)
    {
        // Printing car details
    	cout << left;
    	cout << setw(8) << arr[i].vin
    	     << setw(12) << arr[i].model
    	     << setw(12) << arr[i].make
    	     << setw(8) << fixed << setprecision(2) << arr[i].price << endl;

    }
}



//**The function displays the menu to a user**
void printMenu()
{
	cout << "Choice\t\tAction\n";
	cout << "------\t\t------\n";
	cout << "C\t\tCreate a heap\n";
	cout << "D\t\tDelete the heap\n";
	cout << "E\t\tExtract max node\n";
	cout << "F\t\tFind a Car by VIN\n";
	cout << "I\t\tInsert a Car\n";
	cout << "K\t\tIncrease the VIN\n";
	cout << "M\t\tGet the max node\n";
	cout << "P\t\tPrint the heap\n";
	cout << "S\t\tHeap Sort\n";
	cout << "Q\t\tQuit\n";
	cout << "?\t\tDisplay Help\n\n";
}
