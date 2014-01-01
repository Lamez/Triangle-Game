#include <iostream>
#include <stdlib.h>
#include "Triangle.cpp"
#include "LinkedList.cpp"
#include <list>
#include <stack>
using namespace std;
bool playAgain(){
    char a;
    do{
        cout << "Would you like to play again (y/n)? ";
        cin >> a;
        a = tolower(a);
    }while(a != 'y' && a != 'n');
    return a == 'y';
}
int askForStart(){
	int start;
	/* Ask for starting Position */
	Triangle t;
	do{
        cout << t << endl;
		cout << "Enter Starting Position (1-15): ";
		cin >> start;
		cout << endl;
	}while(start > 15 || start < 1);
	return start;
}
void play(){
    do{
        Triangle tri(askForStart());
        while(!tri.gameOver()){
            cout << endl << "Your are missing these pegs: ";
            tri.printMissingPegs();
            cout << "You have " << tri.possibleMovesLeft() << " possible moves." << endl << endl;
            char from, to;
            int f, t;
            do{
                cout << tri << endl;
                cout << "Enter from and to peg: ";
                cin >> f;
                cin >> t;
              /*  f = (int)from;
                t = (int)to;
                changeToInt(f);
                changeToInt(t); */
            }while(f > 15 || f < 1 || t > 15 || t < 1);
            if(tri.correctJump(f, t))
                tri.jumpPeg(f, t);
            else
                cout << endl << "::Invalid move, nothing removed::" << endl;
        }
        cout << tri << endl;
        if(tri.isWinner())
            cout << "*~You Win!~*" << endl;
        else
            cout << "Loser!" << endl;
    }while(playAgain());
    //ask to play again..
}
void printList(list<move> lst){
    for(list<move>::iterator it=lst.begin(); it != lst.end(); ++it)
        cout << *it << endl;

}
void fillMoves(Triangle t,list<move> moves[15]){
    int openPegs[15];
    t.openPegs(openPegs);
    list<move> zero(0);
    for(int i=0; i<15; i++){
        if(openPegs[i] == 1){
            moves[i] = t.possibleFromPosition(i + 1);
        }else
            moves[i] = zero;
    }
}
/*
function SolveBoard(board, listOfMoves)
    if (board is solved):
        return listOfMoves! #this is the solution

    foreach (possibleMove in board):
        listOfMoves.add(possibleMove)

        solution = SolveBoard(board, listOfMoves)
        if (solution != null):
            return solution

        listOfMoves.remove(possibleMove) # this is the backtracking part... undo and try again

    return null
*/
void solve(Triangle t, list <move> lst){

}
int main(){
    //trying to figure out how to implment the backtracking algorithm
    play();
    int s = askForStart();
    Triangle t(s);

    list<move> lst;
    move m;
    lst = t.possibleFromPosition(s);

    m = lst.back();
    cout << t << endl;
    printList(lst);
    cout << t.jumpPeg(m) << endl;
    cout << t;
    lst = t.possibleFromPosition(lst.back().from);
    m = lst.back();

    printList(lst);
    return 1;




}

