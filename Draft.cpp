#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include<direct.h>
#include<io.h>
#include<iostream>
using namespace std;
struct node{
    char val;
    struct node *next;
    struct node *down;  //*like a 2 dimention linked list
};
class Stack {
public:
    Stack();
    bool empty()const; //this function returns if the string is empty 
    bool pop();
    bool top(Stack_entry& item); //??
    bool push(const Stack_entry& item);//??
private:
    int count;
    Stack_entry entry[maxstack]; //I guess, it's an array named entry of type Move and size 100
};
Stack::Stack()
{
    count = 0;//*count de hya el top bs bade2 men zero
}
bool Stack::push(const Stack_entry& item)//??
{
    bool outcome = success;
    if (count >= maxstack)
        return overflow;
    else
        entry[count++] = item; //if there is still space then push the "item" into element no. "count++" in "entry"
    return outcome;
}
bool Stack::pop()
{
    bool outcome = success;
    if (count == 0)
        outcome = underflow;
    else --count;
    return outcome;
}
bool Stack::top(Stack_entry& item)
{
    bool outcome = success;
    if (count == 0)
        return underflow;
    else
        item = entry[count - 1]; //count -1 as the 1st element [0] is of count 1
    return outcome;
}
bool Stack::empty()const
{ //it checks if the stack is empty or not
    bool outcome = true;
    if (count > 0) //if count >0 then it's not empty
        outcome = false; 
    return outcome;
}
