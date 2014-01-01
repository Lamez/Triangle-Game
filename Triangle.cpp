//Triangle Object
//The triangle game at cracker berrel, you have to jump a peg over another to an empty space, goal is to have one peg left.
//the user chooses the starting position.
#include <iostream>
#include <string>
#include <stdlib.h>
#include <list>
//reminder, have triangle throw exceptions when out of bounds.
using namespace std;
const int TRI_SIZE = 15;
class move{
	public:
		int from;
		int to;
		move(int from, int to){
			this->from = from;
			this->to = to;
		}
		move(){
            from = 0;
            to = 0;
		}
    friend ostream& operator << (ostream& os, const move &m){
            os << "(from: " << m.from << ", to: " << m.to << ")";
        }
};
class Triangle{
	public:
		Triangle();
		Triangle(int);
		void printMissingPegs();
		int missingPegSize();
		void printTriangle();
		int jumpPeg(int, int);
		int jumpPeg(move);
		void possibleFromPosition(int, int[4]);
        list<move> possibleFromPosition(int);
		int possibleMovesLeft();
		int countPossibleMovesFromPosition(int);
		void openPegs(int[15]);
		bool gameOver();
		bool isWinner();
		void pause();
		bool correctJump(int, int);
		//operator overloads
		// a triangle is larger if it is missing less pieces than the other triangle
		// triangles are equal if they are missing the same pieces.
		Triangle& operator = (const Triangle&);
		bool operator < (const Triangle&);
		bool operator > (const Triangle&);
		bool operator == (const Triangle&);
		bool operator <= (const Triangle&);
		bool operator >= (const Triangle&);
		friend ostream& operator << (ostream& os, const Triangle&);
	private:
		int missingPegs[15];
		int missingPegsSize;

		int removePeg(int);
		int removeMiddlePeg(int, int);
		void addPeg(int);
		void setup();
	protected:
		bool isMissing(int);
		string changeToHex(int);
		void printSpaces(int);

};
Triangle::Triangle(){
	this->setup();
	this->missingPegsSize = 0;
}
Triangle::Triangle(int startingPosition){
	this->setup();
	this->missingPegsSize = 0;
	this->removePeg(startingPosition);
}
int Triangle::removePeg(int p){
	this->missingPegs[p-1] = 1;
	this->missingPegsSize++;
	return p;
}
int Triangle::missingPegSize(){
	return this->missingPegsSize;
}
void Triangle::printMissingPegs(){
	int c = this->missingPegsSize; //so we don't override the value in missingPegSize
	cout << "[";
	for(int i=0; i<TRI_SIZE; i++){
		if(this->missingPegs[i] != 0){
			cout << i + 1;
			c--;
			if(c <= 0)
				break;
			else
				cout << ", ";
		}
	}
	cout << "]\n";
}
void Triangle::printTriangle(){ //this algorithm works perfect!
	int current_number = 1;
	int space_counter = 4;
	for(int i=1; i<=5; i++){
		//print spaces.
		this->printSpaces(space_counter);
		space_counter--;
		for(int j=1; j<=i; j++){
			if(isMissing(current_number))
				cout << "*";
			else if(current_number <= 9)
				cout << current_number;
			else
				cout << changeToHex(current_number);
			cout << " ";
			current_number++;
		}
		cout << endl;
	}
}
string Triangle::changeToHex(int j){ //Note: does not actually calculate hex value, but usese the notation
	string s = "";
	switch(j){
		case 10: s+= "A"; break;
		case 11: s+= "B"; break;
		case 12: s+= "C"; break;
		case 13: s+= "D"; break;
		case 14: s+= "E"; break;
		case 15: s+= "F"; break;
		default: s+= j;
	}
	return s;
}
void Triangle::pause(){
	//system("read -n1 -r -p \"Press any key to continue...\" key");
	system("pause");
}
void Triangle::printSpaces(int i){
	for(; i>0; i--)
		cout << " ";
}
bool Triangle::isMissing(int i){
	return this->missingPegs[i-1] == 1;
}
int Triangle::jumpPeg(int from, int to){
	if(this->isMissing(to)){
		if(this->correctJump(from, to)){
			this->addPeg(to);
			this->removePeg(from);
			return this->removeMiddlePeg(from, to);
		}
	}
	return 0;
}
int Triangle::jumpPeg(move m){
    return this->jumpPeg(m.from, m.to);
}
void Triangle::addPeg(int i){
	this->missingPegs[i-1] = 0;// no longer missing
	this->missingPegsSize--;
}
void Triangle::setup(){
	for(int i=0; i<TRI_SIZE; i++)
		this->missingPegs[i] = 0;
}
bool Triangle::correctJump(int from, int to){ //needs to be modified to include if middle peg is not empty
		switch(to){
		case 1:
			if(from == 4)
				return !this->isMissing(2);
			else if(from == 6)
				return !this->isMissing(3);
			else
				return false;
			break;
		case 2:
			if(from == 7)
				return !this->isMissing(4);
			else if(from == 9)
				return !this->isMissing(5);
			else
				return false;
			break;
		case 3:
			if(from == 10)
				return !this->isMissing(6);
			else if(from == 8)
				return !this->isMissing(5);
			else
				return false;
			break;
		case 4:
			if(from == 1)
				return !this->isMissing(2);
			else if(from == 6)
				return !this->isMissing(5);
			else if(from == 11)
				return !this->isMissing(7);
			else if(from == 13)
				return !this->isMissing(8);
			else
				return false;
			break;
		case 5:
			if(from == 12)
				return !this->isMissing(8);
			else if(from == 14)
				return !this->isMissing(9);
			else
				return false;
			break;
		case 6:
			if(from == 1)
				return !this->isMissing(3);
			else if(from == 4)
				return !this->isMissing(5);
			else if(from == 13)
				return !this->isMissing(9);
			else if(from == 15)
				return !this->isMissing(10);
			else
				return false;
			break;
		case 7:
			if(from == 2)
				return !this->isMissing(4);
			else if(from == 9)
				return !this->isMissing(8);
			else
				return false;
			break;
		case 8:
			if(from == 3)
				return !this->isMissing(5);
			else if(from == 10)
				return !this->isMissing(9);
			else
				return false;
			break;
		case 9:
			if(from == 2)
				return !this->isMissing(5);
			else if(from == 7)
				return !this->isMissing(8);
			else
				return false;
			break;
		case 10:
			if(from == 3)
				return !this->isMissing(6);
			else if(from == 8)
				return !this->isMissing(9);
			else
				return false;
			break;
		case 11:
			if(from == 4)
				return !this->isMissing(7);
			else if(from == 13)
				return !this->isMissing(12);
			else
				return false;
			break;
		case 12:
			if(from == 5)
				return !this->isMissing(8);
			else if(from == 14)
				return !this->isMissing(13);
			else
				return false;
		break;
		case 13:
			if(from == 4)
				return !this->isMissing(8);
			else if(from == 6)
				return !this->isMissing(9);
			else if(from == 11)
				return !this->isMissing(12);
			else if(from == 15)
				return !this->isMissing(14);
			else
				return false;
		break;
		case 14:
			if(from == 5)
				return !this->isMissing(9);
			else if(from == 12)
				return !this->isMissing(13);
			else
				return false;
			break;
		case 15:
			if(from == 6)
				return !this->isMissing(10);
			else if(from == 13)
				return !this->isMissing(14);
			else
				return false;
			break;
		default: return false;
	}
}
list<move> Triangle::possibleFromPosition(int p){
    int moves[4];
    list<move> lst;
    move m;
    possibleFromPosition(p, moves);
    for(int i=0; i<4; i++)
        if(moves[i] != -1){
            m.to = p;
            m.from = moves[i];
            lst.push_back(m);
        }

    return lst;
}
void Triangle::possibleFromPosition(int p, int lst[]){
		lst[0] = -1;
		lst[1] = -1;
		lst[2] = -1;
		lst[3] = -1;
		switch(p){
			case 1: lst[0] = 4; lst[1] = 6; break;
			case 2: lst[0] = 7; lst[1] = 9; break;
			case 3: lst[0] = 8; lst[1] = 10; break;
			case 4: lst[0] = 1; lst[1] = 6; lst[2] = 13; lst[3] = 11; break;
			case 5: lst[0] = 12; lst[1] = 14; break;
			case 6: lst[0] = 1; lst[1] = 4; lst[2] = 13; lst[3] = 15; break;
			case 7: lst[0] = 2; lst[1] = 9; break;
			case 8: lst[0]= 3; lst[1] = 10; break;
			case 9: lst[0] = 2; lst[1] = 7; break;
			case 10: lst[0] = 3; lst[1] = 8; break;
			case 11: lst[0] = 4; lst[1] = 13; break;
			case 12: lst[0] = 5; lst[1] = 14; break;
			case 13: lst[0] = 4; lst[1] = 6; lst[2] = 11; lst[3] = 15; break;
			case 14: lst[0] = 5; lst[1] = 12; break;
			case 15: lst[0] = 6; lst[1] = 13; break;
	}
}
int Triangle::countPossibleMovesFromPosition(int peg){
	int total = 0;
	if(this->missingPegsSize == 1){
		if(peg == 4 || peg == 6 || peg == 13)
			total = 4;
		else
			total = 2;
	}else{
		switch(peg){
			case 1:
				if(!this->isMissing(6) && !this->isMissing(3))
					total++;
				if(!this->isMissing(4) && !this->isMissing(2))
					total++;
				break;
			case 2:
				if(!this->isMissing(7) && !this->isMissing(4))
					total++;
				if(!this->isMissing(9) && !this->isMissing(5))
					total++;
				break;
			case 3:
				if(!this->isMissing(10) && !this->isMissing(6))
					total++;
				if(!this->isMissing(8) && !this->isMissing(5))
					total++;
				break;
			case 4:
				if(!this->isMissing(1) &&  !this->isMissing(2))
					total++;
				if(!this->isMissing(6) && !this->isMissing(5))
					total++;
				if(!this->isMissing(13) && !this->isMissing(8))
					total++;
				if(!this->isMissing(11) && !this->isMissing(7))
					total++;
				break;
			case 5:
				if(!this->isMissing(12) && !this->isMissing(8))
					total++;
				if(!this->isMissing(9) && !this->isMissing(14))
					total++;
				break;
			case 6:
				if(!this->isMissing(10) && !this->isMissing(15))
					total++;
				if(!this->isMissing(9) && !this->isMissing(13))
					total++;
				if(!this->isMissing(4) && !this->isMissing(5))
					total++;
				if(!this->isMissing(1) && !this->isMissing(3))
					total++;
				break;
			case 7:
				if(!this->isMissing(2) && !this->isMissing(4))
					total++;
				if(!this->isMissing(8) && !this->isMissing(9))
					total++;
				break;
			case 8:
				if(!this->isMissing(9) && !this->isMissing(10))
					total++;
				if(!this->isMissing(3) && !this->isMissing(5))
					total++;
				break;
			case 9:
				if(!this->isMissing(7) && !this->isMissing(8))
					total++;
				if(!this->isMissing(2) && !this->isMissing(5))
					total++;
				break;
			case 10:
				if(!this->isMissing(3) && !this->isMissing(6))
					total++;
				if(!this->isMissing(8) && !this->isMissing(9))
					total++;
				break;
			case 11:
				if(!this->isMissing(4) && !this->isMissing(7))
					total++;
				if(!this->isMissing(12) && !this->isMissing(13))
					total++;
				break;
			case 12:
				if(!this->isMissing(5) && !this->isMissing(8))
					total++;
				if(!this->isMissing(13) && !this->isMissing(14))
					total++;
				break;
			case 13:
				if(!this->isMissing(11) && !this->isMissing(12))
					total++;
				if(!this->isMissing(14) && !this->isMissing(15))
					total++;
				if(!this->isMissing(6) && !this->isMissing(9))
					total++;
				if(!this->isMissing(4) && !this->isMissing(8))
					total++;
				break;
			case 14:
				if(!this->isMissing(5) && !this->isMissing(9))
					total++;
				if(!this->isMissing(12) && !this->isMissing(13))
					total++;
				break;
			case 15:
				if(!this->isMissing(6) && !this->isMissing(10))
					total++;
				if(!this->isMissing(13) && !this->isMissing(14))
					total++;
				break;
		}
	}
	return total;
}
int Triangle::possibleMovesLeft(){
	int total = 0;
	//find the missing peg
	for(int i=0; i<TRI_SIZE; i++){
		//is this peg missing?
		if(this->missingPegs[i] == 1){//yes
			total += this->countPossibleMovesFromPosition(i+1);
		}
	}
	return total;
}
int Triangle::removeMiddlePeg(int from, int to){
	switch(to){
		case 1:
			if(from == 4)
				return this->removePeg(2);
			else if(from == 6)
				return this->removePeg(3);
			break;
		case 2:
			if(from == 7)
				return this->removePeg(4);
			else if(from == 9)
				return this->removePeg(5);
			break;
		case 3:
			if(from == 10)
				return this->removePeg(6);
			else if(from == 8)
				return this->removePeg(5);
			break;
		case 4:
			if(from == 1)
				return this->removePeg(2);
			else if(from == 6)
				return this->removePeg(5);
			else if(from == 11)
				return this->removePeg(7);
			else if(from == 13)
				return this->removePeg(8);
			break;
		case 5:
			if(from == 12)
				return this->removePeg(8);
			else if(from == 14)
				return this->removePeg(9);
			break;
		case 6:
			if(from == 1)
				return this->removePeg(3);
			else if(from == 4)
				return this->removePeg(5);
			else if(from == 13)
				return this->removePeg(9);
			else if(from == 15)
				return this->removePeg(10);
			break;
		case 7:
			if(from == 2)
				return this->removePeg(4);
			else if(from == 9)
				return this->removePeg(8);
			break;
		case 8:
			if(from == 3)
				return this->removePeg(5);
			else if(from == 10)
				return this->removePeg(9);
			break;
		case 9:
			if(from == 2)
				return this->removePeg(5);
			else if(from == 7)
				return this->removePeg(8);
			break;
		case 10:
			if(from == 3)
				return this->removePeg(6);
			else if(from == 8)
				return this->removePeg(9);
			break;
		case 11:
			if(from == 4)
				return this->removePeg(7);
			else if(from == 13)
				return this->removePeg(12);
			break;
		case 12:
			if(from == 5)
				return this->removePeg(8);
			else if(from == 14)
				return this->removePeg(13);
		break;
		case 13:
			if(from == 4)
				return this->removePeg(8);
			else if(from == 6)
				return this->removePeg(9);
			else if(from == 11)
				return this->removePeg(12);
			else if(from == 15)
				return this->removePeg(14);
		break;
		case 14:
			if(from == 5)
				return this->removePeg(9);
			else if(from == 12)
				return this->removePeg(13);
			break;
		case 15:
			if(from == 6)
				return this->removePeg(10);
			else if(from == 13)
				return this->removePeg(14);
			break;
	}
	return 0;
}
bool Triangle::gameOver(){ //return 0 for game is not over, 1 for game over
	return (this->possibleMovesLeft() == 0);
}
bool Triangle::isWinner(){
	if(this->gameOver())
		return (this->missingPegsSize == 14);
	else
		return false;
}
// Triangle  Triangle::copy(Triangle t);
Triangle &Triangle::operator = (const Triangle &t){
	Triangle temp;
	for(int i=0; i<TRI_SIZE; i++)
		missingPegs[i] = t.missingPegs[i];
	missingPegsSize = t.missingPegsSize;
	return *this;
}
bool Triangle::operator < (const Triangle &t){
	return missingPegsSize > t.missingPegsSize;
}
bool Triangle::operator > (const Triangle &t){
	return missingPegsSize < t.missingPegsSize;
}
bool Triangle::operator == (const Triangle &t){ //this one compares if they have the same missing pegs.
	bool b;
	for(int i=0; i<TRI_SIZE; i++){
		if(missingPegs[i] != t.missingPegs[i]){
			b = false;
			break;
		}else
			b = true;
	}
	return b;
}
bool Triangle::operator <= (const Triangle &t){
	return (missingPegsSize > t.missingPegsSize) || (missingPegsSize == t.missingPegsSize);
}
bool Triangle::operator >= (const Triangle &t){
	return (missingPegsSize < t.missingPegsSize) || (missingPegsSize == t.missingPegsSize);
}

void Triangle::openPegs(int pegs[15]){
		for(int i=0; i<TRI_SIZE; i++){
			if(missingPegs[i] == 1)
				pegs[i] = 1;
			else
				pegs[i] = 0;
		}
}

ostream& operator << (ostream& os, const Triangle &t){
	int current_number = 1;
	int space_counter = 4;
	Triangle temp = t;
	for(int i=1; i<=5; i++){
		//print spaces.
		temp.printSpaces(space_counter);
		space_counter--;
		for(int j=1; j<=i; j++){
			if(temp.isMissing(current_number))
				os << "*";
			else if(current_number <= 9)
				os << current_number;
			else
				os << temp.changeToHex(current_number);
			os << " ";
			current_number++;
		}
		os << endl;
	}
	return os;
}
