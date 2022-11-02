//File name: /Users/laptopuser/Documents/courses/cs135/projects/memoryGame/MemoryGame.hpp

//header file of C++ ends with .hpp
//#ifndef … #define … #endif are called include guard.
//They can make sure a header file will not be included more than once. For example, suppose Hare and Tortoise are inherited from Animal class, then Animal.hpp is included in both Hare.hpp and Tortoise.hpp. Then when we have a competition involves Hare and Tortoise, Animal.hpp would have been included more than once, as a result, data members and function members in Animal.hpp are declared more than once, which causes compilation problem.
#ifndef _MEMORY_GAME
#define _MEMORY_GAME
#include <vector>
#include <string>
using namespace std;
class MemoryGame
{
public: //public method member, any class can use these methods
    MemoryGame(); 
       //default constructor, with 3 pairs of numbers 
       //randomly located in 8 blocks (two blocks are empty).
    //MemoryGame(int n); 
       //with n >= 3 pairs of numbers randomly located
    //MemoryGame(int n, int m);
       //with n >= 3 pairs of numbers randomly located in m space
    //MemoryGame(string *words, int size);
       //instead of randomly generated numbers,
       //pairs with words
    ~MemoryGame();
    void play();
    void display(bool* bShown); 
         //display array values, if bShown[i] is true,
         //then values[i] is displayed, where i is the index.

private: //private data members, private means that
         //only methods in this class, not other class,
         //can access or modify these data members.
    int numPairs; //numPairs of identical twin items
    int numSpaces; 
        //size of array value, besides identical twins, 
        //may contain empty string to 
        //make the problem more challenging
    string *values; 
        //a string to represent the layout of data,
        //mixed with possible empty strings.
        //Use array to access each element in const time.
};
#endif
