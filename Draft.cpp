#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include<direct.h>
#include<io.h>
#include<iostream>
using namespace std;
#define Stack_entry Move
#define maxstack 100
const int n = 3;
int P;//*player win indicator
int draw = 0;
class Move {//move de el move rl ha3melha ta2reebn?
public:
    int row;
    int col;
    int pos;
};
struct node {
    char val;
    struct node* next;
    struct node* down;  //like a 2 dimension linked list
};
class Stack {
public:
    Stack();
    bool empty()const; //this function returns if the string is empty 
    bool pop();
    bool top(Stack_entry& item); //assigning a reference 
    bool push(const Stack_entry& item);//assigining a reference 
private:
    int count;
    Stack_entry entry[maxstack]; //it is an array named entry of type Move and size 100
};
class Board {
public:
    bool done();
    bool is_ok(Move step); //checks if the move is valid
    void print(struct node* arr[]); //prints the board
    int legal_moves(Stack& moves);
private:
    int square[3][3];
    int moves_done;
};
Stack::Stack()
{
    count = 0;// count de hya el top bs bade2 men zero
}
bool Stack::push(const Stack_entry& item)
{
    bool outcome = true;
    if (count >= maxstack)
        return false;
    else
        entry[count++] = item; //if there is still space then push the "item" into element no. "count++" in "entry"
    return outcome;
}
bool Stack::pop()
{
    bool outcome = true;
    if (count == 0)
        outcome = false;
    else --count;
    return outcome;
}
bool Stack::top(Stack_entry& item)
{
    bool outcome = true;
    if (count == 0)
        return false;
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
void initializeBoard(struct node* arr[]) {
    int i, j;
    struct node* newNode, * ptr;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            newNode = new node();
            newNode->next = NULL;//*kda ana 3amlt node gdeeda w khaltha fadya w mesh betshawer 3ala 7aga y3ni ll men node wa7da
            newNode->down = NULL;
            newNode->val = ' ';
            if (j == 0) {//*awel node f kol row
                arr[i] = newNode;//*bakhali awel element hya el ll el fadya kda ana khadt el kan newnode byshawer 3aleih w 2a2dar akhali nn teshwar 3ala 7aga tany
                ptr = arr[i];//*bakhalai el pointer yeshawer 3aleiha
            }
            else {//*ana kda akeni ba3mel 2d array bs awel coloumn array well tale3 menha ll 3shan akmel ba2eit el array
                ptr->next = newNode;
                ptr = ptr->next;
            }
        }
    }
    //down pointer
    for (j = 0; j < n - 1; j++) {//*j-1 3shan akher row mafeesh 7aga ta7to awaslo biha
        ptr = arr[j];//*kda ana ba link kol el element el fel array b b3d
        newNode = arr[j + 1];
        for (i = 0; i < n; i++) {
            ptr->down = newNode;
            ptr = ptr->next;
            newNode = newNode->next;
        }
    }
}
//prints the board
void Board:: print(struct node* arr[]) {//**ba3dein
    int i, j, k;
    struct node* ptr;
    for (k = 0; k < n; k++) {
        cout << (" ---------------");
    }
    cout << ("\n");
    for (i = 0; i < n; i++) {

        cout << ("|");
        for (k = 0; k < n; k++) {
            cout << ("               |");
        }
        cout << ("\n");
        cout << ("|");
        for (k = 0; k < n; k++) {
            cout << ("               |");
        }
        cout << ("\n");

        ptr = arr[i];
        for (j = 1; j <= n; j++) {
            if (ptr->val == ' ') {
                cout << ("|\t%d\t", i * n + j);
            }
            else {
                if (ptr->val == 'X') {
                    cout << ("|");
                    cout << ("\t%c\t", ptr->val);
                }
                else {
                    cout << ("|");
                    cout << ("\t%c\t", ptr->val);
                }
            }
            ptr = ptr->next;
        }
        cout << ("|");
        cout << ("\n");


        cout << ("|");
        for (k = 0; k < n; k++) {
            cout << ("               |");
        }
        cout << ("\n");
        cout << ("|");
        for (k = 0; k < n; k++) {
            cout << ("               |");
        }
        cout << ("\n");
        for (k = 0; k < n; k++) {
            cout << (" ---------------");
        }
        cout << ("\n");

    }
}
bool Board::is_ok(Move step)
/**Judging whether this step is feasible**/
{
    if (step.row >= 0 && step.row < 3 && step.col >= 0 && step.col < 3
        && square[step.row][step.col] == 0)
        return true;
    else return false;
}
Move getposition(Move new_move) {
    new_move.row = (new_move.pos - 1) / n;
    new_move.col = (new_move.pos - 1) % n;
    return new_move;
}
int input(struct node* arr[], int pl) {
    Move step;
    bool x = true;
    cout << ("Enter a number to place your symbol there: ");
    cin >> step.pos;
    step = getposition(step);
        struct node* ptr;
    if (!is_ok(step))
    {
        cout << ("Invalid position\n");
        input(arr, pl);
    }
    ptr = arr[step.row];
    for (step.pos = 0; step.pos != step.col; step.pos++) {
        ptr = ptr->next;
    }
    if (pl % 2 == 1) {//*player1
        ptr->val = 'X';
    }
    else {
        ptr->val = 'O';//*player2
        //increments the draw counter
        draw++;//*3shan awel ema draw de tewsal le n*n byb2a draw
    }
    return draw;//??
}

int isGameOver(struct node* arr[]) {
    int gameOver, i, j;
    struct node* ptr;
    char values[n];//*array to
    //Horizontal Check
    for (i = 0; i < n; i++)
    {
        gameOver = 1;
        ptr = arr[i];
        for (j = 0; j < n; j++) {//* akhadt el values beta3t awel row kolo w 7atetha f array lwa7do
            values[j] = ptr->val;
            ptr = ptr->next;
        }
        //checing if row is equal
        for (j = 0; j < n - 1; j++) {
            if (values[j] == ' ' || values[j + 1] == ' ') {//*lw fi ay wa7da fadya yeb2a maksebesh
                gameOver = 0;
                break;
            }
            else if (values[j] != values[j + 1]) {//*aw lw fi ay wa7da mesh zy el b3dha matnfa3sh
                gameOver = 0;
                break;
            }
        }
        if (gameOver == 1) {
            playerWins(values[j]);//*bab3at X aw O 7asab meen el keseb
            return gameOver;
        }
    }
    //Vertical Check
    for (i = 0; i < n; i++) {
        ptr = arr[0];
        for (j = 0; j < i; j++) {
            ptr = ptr->next;
        }
        gameOver = 1;
        for (j = 0; j < n; j++) {
            values[j] = ptr->val;//*hya hya bs akhat coloumn
            ptr = ptr->down;
        }
        //checking if column is equal
        for (j = 0; j < n - 1; j++) {
            if (values[j] == ' ' || values[j + 1] == ' ') {
                gameOver = 0;
                break;
            }
            if (values[j] != values[j + 1]) {
                gameOver = 0;
                break;
            }
        }
        if (gameOver == 1) {
            playerWins(values[j]);
            return gameOver;
        }
    }
    //leading Diagonal
    for (i = 0; i < n; i++) {
        gameOver = 1;
        ptr = arr[i];
        for (j = 0; j < i; j++) {//*rakam el row hwa rakan el element el hatetakhed fel diagonal
            ptr = ptr->next;
        }
        values[i] = ptr->val;//*kda value fiha el diagonal
        //checking if leading diagonal is equal
        for (j = 0; j < n - 1; j++) {
            if (values[j] == ' ' || values[j + 1] == ' ') {
                gameOver = 0;
                break;
            }
            if (values[j] != values[j + 1]) {
                gameOver = 0;
                break;
            }
        }
        if (gameOver == 1) {
            playerWins(values[j]);
            return gameOver;
        }
    }
    //other Diagonal
    for (i = n - 1; i >= 0; i--) {//bada2t men akher row
        gameOver = 1;
        ptr = arr[n - i - 1];
        for (j = 0; j < i; j++) {
            ptr = ptr->next;
        }
        values[n - i - 1] = ptr->val;
        //checking if non-leading diagonal is equal
        for (j = 0; j < n - 1; j++) {
            if (values[j] == ' ' || values[j + 1] == ' ') {
                gameOver = 0;
                break;
            }
            if (values[j] != values[j + 1]) {
                gameOver = 0;
                break;
            }
        }
        if (gameOver == 1) {
            playerWins(values[j]);
            return gameOver;
        }
    }
    return gameOver;
}
bool Board::done()
/**Judging whether the game is over**/
{
    return (moves_done == 9 || isGameOver(arr));//moves_done = draw
}
//indicates which player wins
void playerWins(char c) {
    if (c == 'X') {
        P = 1;
    }
    else {
        P = 2;
    }
}
/////////////////////////////////////////////////////////////////////////////////////////
    int main()
    {

    }
