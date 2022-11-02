/*
Author: Alysa Liann Vega
Course: CSCI-135
Instructor: Tong Yi
Date: March 7, 2022
Assignment: Memory Game Lab

This program creates a game where you flip 2 'cards' at a time until the cards match. Continue until you find all pairs.
*/

#include "MemoryGame.hpp"
#include <cstdlib> //srand, rand
#include <ctime>
#include <iomanip> //setw
#include <iostream> //std
using namespace std;

int* randomize(int numSpaces); //function to randomize layout
void swap(int* arr, int i, int j);
void displaySeparateLine(int numSpaces);

//TODO: implement by students
MemoryGame::MemoryGame(){ //default constructor,
    //set numPairs = 3, numSpaces = 2 * numPairs + 2,

    //put 3 pairs of randomly generated ints in [0, 1000) randomly in numSpaces blocks.
    //Note that 2 added after 2 * numPairs means number of two extra blocks without actual data.

    //srand(time(NULL)); //TODO: uncomment this line to see
        //different layouts of numbers in different runnings.
        //time(NULL) is the current running time.
        //use the current running time to grow random sequence
        //Since running time differs, the random sequence looks different at different running time.
    srand(1); //TODO: add this before submitting to gradescope,
        //or autograde script cannot handle random input.

    //TODO: your code here
    numPairs = 3;
    numSpaces = 2 * numPairs + 2;
    int data[numPairs];
    for (int i = 0; i < numPairs; i++){
        data[i] = rand() % 1000;
    }
    
    //In constructors, randomly assign the data in dataVector to array values[]
    int *arr = randomize(numSpaces);
    values = new string[numSpaces];
    
    for (int i = 0; i < numSpaces; i++){
        if (i < numPairs*2){
            values[arr[i]] = to_string(data[i/2]);
        }
        else values[arr[i]] = "";
    }
    delete[] arr;
}

//TODO: implement by students
MemoryGame::~MemoryGame()
{
    //When an object is no longer in need, release dynamically allocated memory by data members of the current object.
    delete[] values;
}

//TODO: implement by students
//randomize is not a member function, so there is no MemoryGame:: before function name randomize.
//Return an array of randomly allocated 0, 1, .., size-1
//In constructors, randomly assign the data in dataVector to array values
int* randomize(int size)
{
    //idea to randomize 0, 1, 2, 3, 4, 5,
    //generate a random int in [0, 6), say 3,
    //then move arr[3] to the end,
    //say, 0, 1, 2, 5, 4, 3
    //generate a random int in [0, 5), say 3 again,
    //then swap arr[3], which is 5 now, with arr[4], 
    //get 0, 1, 2, 4, 5, 3
    //generate a random int in [0, 4), say 2,
    //swap arr[2] with the current arr[3]
    //get 0, 1, 4, 2, 5, 3
    //continue to randomize arr[0..2].
    //afterwards, continue to randomize arr[0..1].
    
    int *arr = new int[size];
    for (int i = 0; i < size; i++){        //fill array arr with numbers 0 to 1
        arr[i] = i;
    }
    for (int i = size-1; i >= 0; i--){  //randomize numbers in array
        int num = rand() % (i+1);
        /*int temp = arr[i];
        arr[i] = arr[num];
        arr[num] = temp;*/
        swap(arr, i, num);
    }
    
    return arr;                            //return randomized array 0 to size-1
}

//TODO: implement by students
//int* arr means int array arr, which implies the address of the first element of array arr.
//swap arr[i] and arr[j] in array of ints arr.
void swap(int *arr, int i, int j)
{
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

//Display -----+ for numSpaces times.
//Add an extra + when for the first block (when index i is 0).
//So suppose numSpaces is 8, we get
//+-----+-----+-----+-----+-----+-----+-----+-----+
//followed by a new line.
void displaySeparateLine(int numSpaces)
{
    for (int i = 0; i < numSpaces; i++)
{
        if (i == 0)
           cout << "+";
        cout << "-----+";
    }
    cout << endl;
}

//TODO: implement by students
//display the items in values array where bShown is true.
//call displaySeparateLine()
void MemoryGame::display(bool* bShown)
{
    cout << " ";    //initial space
    //display numbers 0 through numSpaces
    for (int i = 0; i < numSpaces; i++){
        cout << setw(3) << i;
        cout << setw(3) << " ";
    }

    cout << endl;
    
    displaySeparateLine(numSpaces);
    
    //for loop, bar then num
    cout << "|";    //initial "|"
    for (int i = 0; i < numSpaces; i++){
        if (bShown[i])      //if card is flipped show num
            cout << setw(5) << values[i];
        else cout << setw(5) << "";
        cout << "|";
    }
    cout << endl;
    
    displaySeparateLine(numSpaces);
}

//TODO: implement by students
//rules for a round
//(1) pick a number, flip it
//(2) pick a second number, if the number is the same as previous pick, display the second number, otherwise, unflip the previous pick.
//(3) Finish until every pair are chosen correctly.
void MemoryGame::play()
{
    
    bool* bShown = new bool[numSpaces];
    display(bShown);
    
    int pairsFound = 0, numFlips = 0;
    int cell1, cell2;
    
    //while loop
    while (pairsFound < numPairs+1){
        cout << "Pick a cell to flip: ";
        cin >> cell1;
        while (cell1 >= numSpaces || cell1 < 0 || bShown[cell1] == true){    //repeats while cell out of bounds OR already shown
            if (bShown[cell1] == true){
                if (values[cell1] != ""){
                    cout << "The cell indexed at " << cell1 << " is shown." << endl << "Re-enter an index: ";
                    cin >> cell1;
                }
                else break;
            }
            else {
                cout << "index needs to be in range of [0, " << numSpaces-1 << "]." << endl << "Re-enter an index: ";
                cin >> cell1;
            }
        }
        numFlips++;
        bShown[cell1] = true;
        display(bShown);
        
        cout << "Pick a cell to flip: ";
        cin >> cell2;
        while (cell2 >= numSpaces || cell2 < 0 || bShown[cell2] == true){    //repeats while cell out of bounds OR already shown
            if (bShown[cell2] == true){
                if (values[cell2] != ""){
                    cout << "The cell indexed at " << cell2 << " is shown." << endl << "Re-enter an index: ";
                    cin >> cell2;
                }
                else break;
            }
            else {
                cout << "index needs to be in range of [0, " << numSpaces-1 << "]." << endl << "Re-enter an index: ";
                cin >> cell2;
            }
        }
        numFlips++;
        if (values[cell2] == values[cell1]){
            bShown[cell2] = true;
            display(bShown);
            pairsFound++;
        }
        else {
            bShown[cell1] = false;
            display(bShown);
        }
    }
    //numFlips = 32;            //BACKUP
    cout << "Congratulations! Take " << numFlips << " steps to find all matched pairs." << endl;
    delete[] bShown;
}
