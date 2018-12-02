/*

Snake Game with AI(Artifical Intelligence) using C++ 98.
Developed By: Aminullah Taj Muhammad, Zeeshan Anwar & Asad Tagar
Designed by: Zeeshan Anwar.
Testing By: Asad Tagar
Bug Fixed by: Aminullah Taj Muhammad

*/

#include<iostream>
#include<conio.h>
#include<windows.h>
#include<ctime>
#include<cstdlib>
using namespace std;
HANDLE hConsole;			// For Console Color

//----------- For Array Keys Code -----------------------//
enum DirectionKeyCode { KiLeft = 75, KiRight = 77, KiUp = 72, KiDown = 80, ESC = 27 };

//==================  Global Variables  ======================//
const int TableWidth = 70;    //For width of Table
const int TableHeight = 19;    //For height of Table
const int TableSides = 0;     // For table's four sides
int foodx;						//horizantal food
int foody;						//vertical food
int iScore = 0;
int CurrentDirection = KiRight;
int ilength = 5;
int iTime = 40;
bool isgame = true;
//=============================================================//

//++++++++++++++ Gotoxy Function For Co-ordinates +++++++++++++//
void gotoxy(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

class Clocation {
public:
	int x, y;
	void ShowFace(int face) {
		if (face == 0) {
			gotoxy(x, y);
			cout << "D";
		}
		else {
			gotoxy(x, y);
			cout << "\xDB";
		}
	}
	//=========Courser goes to tail and hide it=======//
	void Tail() {
		gotoxy(x, y);
		cout << " ";
	}
	void setxy(int X, int Y) {		//----------------]
		x = X;						//----------------]--------- For Set Gotoxy Values
		y = Y;						//----------------]
	}
	bool operator ==(Clocation);
};
//================ Operator For Checking Condition ===============//
bool Clocation::operator ==(Clocation temp) {
	return (x == temp.x && y == temp.y) ? true : false;
}
//===============================================================//
class CFood : public Clocation {
public:
	Clocation eat;
	void Food() {
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);               //For Color
		SetConsoleTextAttribute(hConsole, 14);
		time_t t;
		srand(time(&t));
		x = (rand() % 50) + 7;								//RANDOMLY GENERATE FOOD OF X AXIS
		y = (rand() % 10) + 3;								//RANDOMLY GENERATE FOOD OF Y AXIS
		gotoxy(x, y);
		cout << "\x01";
		eat.setxy(x, y);
	}
};
class CBigFood : public Clocation {
public:
	Clocation bigEat;
	void BigFood() {
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);               //For Color
		SetConsoleTextAttribute(hConsole, 10);
		time_t t;
		srand(time(&t));
		x = (rand() % 50) + 9;								//RANDOMLY GENERATE FOOD OF X AXIS
		y = (rand() % 10) + 6;								//RANDOMLY GENERATE FOOD OF Y AXIS
		gotoxy(x, y);
		cout << char(254);
		bigEat.setxy(x, y);
	}
	void ShowTimeForBigFood(int t) {
		if (t<10) {
			gotoxy(57, 22);
			cout << " ";
		}
		gotoxy(57, 22);
		cout << t;
	}
	void HideTime() {
		for (int a = 0; a<3; a++) {
			gotoxy(a + 57, 22);
			cout << " ";
		}
	}
	void PrintScore() {
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);               //For Color
		SetConsoleTextAttribute(hConsole, 15);
		gotoxy(7, 22);
		cout << "Score is: ";
		SetConsoleTextAttribute(hConsole, 12);
		cout << iScore;
	}
	void ShowTime() {
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);               //For Color
		SetConsoleTextAttribute(hConsole, 15);
		gotoxy(50, 22);
		cout << "Time: ";
	}
};
class CSnake : public Clocation {
public:
	Clocation s_loc[100];
	char UserInput;
	//========== Initial lenght of user snake ==========//
	void InitSnake() {
		s_loc[0].setxy(20, 7);
		s_loc[1].setxy(19, 7);
		s_loc[2].setxy(18, 7);
		s_loc[3].setxy(17, 7);
		s_loc[4].setxy(16, 7);
		s_loc[5].setxy(15, 7);
	}
	//=================================================//
	//============== Initial lenght of Computer snake  =============//
	void Comp_InitSnake(int len, int c_x, int c_y, char direction) {
		ilength = len;
		for(int i=ilength; i>=0; i--) {
			s_loc[i].setxy(i+c_x, c_y);
		}
        UserInput = direction;
	}
	//===================== Show User Snake ==============================//
	void ShowSnake() {
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);               //For Color
		SetConsoleTextAttribute(hConsole, 13);
		for (int i = 0; i<ilength; i++) {
			s_loc[i].ShowFace(i);
			s_loc[ilength].Tail();
		}
		SetConsoleTextAttribute(hConsole, 10);
	}
	//====================================================================//
	
	void ShowCompSnake() {
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);               //For Color
		SetConsoleTextAttribute(hConsole, 9);
		for (int i = 0; i<ilength; i++) {
			s_loc[i].ShowFace(i);
			s_loc[ilength].Tail();
		}
		SetConsoleTextAttribute(hConsole, 10);
	}
	
	//========== For Left Direction ===========//
	void DirLeft() {
		for (int a = ilength; a>0; a--) {
			s_loc[a].x = s_loc[a - 1].x;
			s_loc[a].y = s_loc[a - 1].y;
		}
		s_loc[0].x--;
	}
	//========================================//

	//========== For Right Direction ===========//
	void DirRight() {
		for (int b = ilength; b>0; b--) {
			s_loc[b].x = s_loc[b - 1].x;
			s_loc[b].y = s_loc[b - 1].y;
		}
		s_loc[0].x++;
	}
	//=========================================//

	//========== For Up Direction ===========//
	void DirUp() {
		for (int c = ilength; c>0; c--) {
			s_loc[c].x = s_loc[c - 1].x;
			s_loc[c].y = s_loc[c - 1].y;
		}
		s_loc[0].y--;
	}
	//=======================================//

	//========== For Down Direction ===========//
	void DirDown() {
		for (int d = ilength; d>0; d--) {
			s_loc[d].x = s_loc[d - 1].x;
			s_loc[d].y = s_loc[d - 1].y;
		}
		s_loc[0].y++;
	}
	//=========================================//

};
class CBoundary : public Clocation {
public:
	// ========= For User Hit Boundarys ============ //
	Clocation leftVerticalBoundary[TableHeight];
	Clocation RightVerticalBoundary[TableHeight];
	Clocation UpperHorizantalBoundary[TableHeight];
	Clocation LowerHorizantalBoundary[TableHeight];
	// ============================================= //
	// ======== For Computer Hit Boundarys ========= //
	Clocation Comp_leftVerticalBoundary[TableHeight];
	Clocation Comp_RightVerticalBoundary[TableHeight];
	Clocation Comp_UpperHorizantalBoundary[TableHeight];
	Clocation Comp_LowerHorizantalBoundary[TableHeight];
	// ============================================= //
	void LeftBoundary() {
		for(int i=0; i<TableHeight; i++) {
			leftVerticalBoundary[i].setxy(6,i+2);
			Comp_leftVerticalBoundary[i].setxy(6,i+2);
		}
	}
	void RightBoundary() {
		for(int i=0; i<TableHeight; i++) {
			leftVerticalBoundary[i].setxy(TableWidth,i+2);
			Comp_leftVerticalBoundary[i].setxy(TableWidth,i+2);
		}
	}
	void UpBoundary() {
		for(int i=0; i<TableWidth; i++) {
			leftVerticalBoundary[i].setxy(i+6,2);
			Comp_leftVerticalBoundary[i].setxy(i+6,2);
		}
	}
	void DownBoundary() {
		for(int i=0; i<TableWidth; i++) {
			leftVerticalBoundary[i].setxy(i+6,TableHeight);
			Comp_leftVerticalBoundary[i].setxy(i+6,TableHeight);
		}
	}
	void WelcomeScreen() {
		HANDLE hConsole;
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        system("cls");
        SetConsoleTextAttribute(hConsole, 480);        //Yellow Color Code=480
        gotoxy(23,0);
        cout<<"   Indus University (FEST)   \n"; 
        cout<<"\n";
        SetConsoleTextAttribute(hConsole, 47);     //Green & White Color Code=47
        gotoxy(19,2);
        cout<<"      Snake Game with AI in OOP using C++      "; 
        SetConsoleTextAttribute(hConsole, 8);             //Gray Color Code=8
        for (int i=6; i<18; i++) {
           gotoxy(43,i);
           cout<<'\xB3';
        }
        gotoxy(28,3);
        SetConsoleTextAttribute(hConsole, 27);             //Blue Color Code=27
        cout<<"  Semester Project  ";
        SetConsoleTextAttribute(hConsole, 12);           //Red Color Code=12
        gotoxy(1,7);
        cout<<"Submitted By: ";
        SetConsoleTextAttribute(hConsole, 12);
        gotoxy(46,8);
        cout<<"Submitted To: ";
        SetConsoleTextAttribute(hConsole, 11);          //Light Blue Color Code=11
        gotoxy(48,10);
        cout<<"Ms. Sumail Zehra";
        SetConsoleTextAttribute(hConsole, 15);              //White Color Code=15
        gotoxy(1,10);
        cout<<"(Group Leader)";
        SetConsoleTextAttribute(hConsole, 3);           //Dark Blue-Green Color Code=3
        gotoxy(16,10);
        cout<<"Aminullah Taj Muhammad";
        SetConsoleTextAttribute(hConsole, 6);            //Dark Yellow Color Code=6
        gotoxy(38,8);
        SetConsoleTextAttribute(hConsole, 15);            //White Color Code=15
        gotoxy(47,8);
        SetConsoleTextAttribute(hConsole, 3);              //Dark Blue Color Code=3
        gotoxy(16,12);
        cout<<"Asad Ali Tagar";
        SetConsoleTextAttribute(hConsole, 6);            //Dark Yellow Color Code=6
        gotoxy(38,10);
        SetConsoleTextAttribute(hConsole, 3);              //Dark Blue Color Code=3
        gotoxy(16,14);
        cout<<"Zeeshan Anwar";
        SetConsoleTextAttribute(hConsole, 3);              //Dark Blue Color Code=3
        gotoxy(16,16);
        cout<<"Abdullah Shabbir";            
		SetConsoleTextAttribute(hConsole, 8);            //Dark Yellow Color Code=8
        for (int i=0; i<79; i++) {
            gotoxy(i,18);
            cout<< char(196);
    	}
    	SetConsoleTextAttribute(hConsole, 8);            //Dark Yellow Color Code=8
        for (int i=0; i<79; i++) {
            gotoxy(i,6);
            cout<<char(196);
    	}
    	SetConsoleTextAttribute(hConsole, 14);             //Golden Code=14
		gotoxy(1,20);
		cout<<"Press 1 for Play Single player Game: ";
		gotoxy(1, 21);
    	cout<<"Press 2 for Play with computer snake Game: ";
        gotoxy(1,23);
        SetConsoleTextAttribute(hConsole, 7);             //Light White Color Code=7
        cout<<"Press Any Number to Play: ";
        //cin>>startgame;
	}
	void SnakeBoundary() {
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);               //For Color
		SetConsoleTextAttribute(hConsole, 11);
		for (int i = 0; i <= TableSides; i++) {      // --
			gotoxy(TableSides + 5, 2);				// For upper Initial Side
			cout << "\xC9";						//
		}
		for (int i = 6; i<TableWidth; i++) {       // --
			gotoxy(i, 2);                	    // For upper  horizantal Boundary
			cout << "\xCD";               	    // --
		}
		for (int i = 6; i<TableWidth; i++) {       // --
			gotoxy(i, 21);                       // For lower horizantal Boundary
			cout << "\xCD";                       // --
		}
		for (int i = 0; i <= TableSides; i++) {      // --
			gotoxy(TableWidth, 2);               // For upper Final/Last Side
			cout << "\xBB";                       // --
		}
		for (int i = 0; i<TableHeight; i++) {      // --
			gotoxy(5, i + 3);  				    // For left Height
			cout << "\xBA";                       // --
		}
		for (int i = 0; i<TableHeight; i++) {      // --
			gotoxy(70, i + 3);                     // For Right Height
			cout << "\xBA";                       // --
		}
		for (int i = 0; i <= TableSides; i++) {
			gotoxy(TableSides + 5, 21);
			cout << "\xCC" << endl;
			gotoxy(TableSides + 5, 22);        	//		]
			cout << "\xBA";						//		]--------for score boders
			gotoxy(TableSides + 5, 23);			//		]
			cout << "\xC8";
		}
		for (int i = 0; i <= TableSides; i++) {
			gotoxy(TableSides + 70, i + 21);				//last mor of table
			cout << "\xB9";
			gotoxy(TableSides + 70, 22);        	//		]
			cout << "\xBA";						//		]--------for score boders
			gotoxy(TableSides + 70, 23);			//		]
			cout << "\xBC";
		}
		for (int i = 6; i<TableWidth; i++) {
			gotoxy(i, 23);
			cout << "\xCD";
		}
	}
	void ShowGameOverScreen() {
		char cpress;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);               //For Color
		SetConsoleTextAttribute(hConsole, 11);
		for (int i = 6; i<TableWidth; i++) {       // --
			gotoxy(i, 2);                	    // For upper  horizantal Boundary
			cout << "\xCD";               	    // --
		}
		for (int i = 6; i<TableWidth; i++) {       // --
			gotoxy(i, 21);                       // For lower horizantal Boundary
			cout << "\xCD";                       // --
		}
		for (int i = 0; i <= TableSides; i++) {      // --
			gotoxy(TableSides + 5, 2);				// For upper left cornor Side
			cout << "\xC9";						//
		}
		for(int i = 1; i <= TableHeight-1; i++) {
			gotoxy(TableWidth, i+2);				// For right height
			cout << "\xBA";
		}
		for(int i = 1; i <= TableHeight-1; i++) {
			gotoxy(TableSides + 5, i+2);				// For left height
			cout << "\xBA";
		}
		for(int i = 0; i <= TableSides; i++) {
			gotoxy(TableSides + 5, TableHeight+2);				// For lower left cornor
			cout << "\xC8";
		}
		for(int i = 0; i <= TableSides; i++) {
			gotoxy(TableWidth, TableHeight+2);				// For lower right cornor
			cout << "\xBC";
		}
		for (int i = 0; i <= TableSides; i++) {      // --
			gotoxy(TableWidth, 2);               // For upper right cornor
			cout << "\xBB";                       // --
		}
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);               //For Color
		SetConsoleTextAttribute(hConsole, 14);
		gotoxy(70-48, 19-9);
		cout<<"Game Over: \n";
		gotoxy(70-49, 19-8);
		cout<<"Your Score is: ";
		SetConsoleTextAttribute(hConsole, 13);
		cout<<iScore;
		SetConsoleTextAttribute(hConsole, 14);
		gotoxy(70-50, 19-7);
		cout<<"Enter any to Again Play Game: "; cpress = getch();
		system("cls");
		SetConsoleTextAttribute(hConsole, 15);
	}

};
char DirectionOfComputer(char comp, CSnake, CFood);
int main() {

	//============= Some Important Variables ===============//
	int iCount = 0;
	int iHit = 0;
	int iHideFood = 0;
	char Choice;
	char cDirection;
	//======================================================//
	//++++++++++++++++ Objects of classes +++++++++++++++++++//
	CFood food;
	CBigFood bfood;
	CBoundary b;
	Clocation l;
	CSnake snake;
	CSnake Comp_snake;
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++//

	//========= Initialize Snake Components ================//
	b.WelcomeScreen();
	//=====================================================//
	do {
		Choice = _getch();
		if(Choice == '1') {
			system("cls");
			//b.leftVerticalBoundary;
			//b.LowerHorizantalBoundary;
			//b.RightVerticalBoundary;
			//b.UpperHorizantalBoundary;
			b.SnakeBoundary();
			food.Food();
			bfood.PrintScore();
			bfood.ShowTime();
			snake.InitSnake();
			snake.ShowSnake();
			snake.UserInput = _getch();
			while (true) {
				//======== SNAKE DIRECTIONS AND MOVEMENT ============//
				snake.ShowSnake();
				if (snake.UserInput == KiRight) {
					if (CurrentDirection != KiLeft) { snake.DirRight(); CurrentDirection = KiRight; }
					else { snake.DirLeft(); CurrentDirection = KiLeft; }
				}
				else if (snake.UserInput == KiLeft) {
					if (CurrentDirection != KiRight) { snake.DirLeft(); CurrentDirection = KiLeft; }
					else { snake.DirRight(); CurrentDirection = KiRight; }
				}
				else if (snake.UserInput == KiUp) {
					if (CurrentDirection != KiDown) { snake.DirUp(); CurrentDirection = KiUp; }
					else { snake.DirDown(); CurrentDirection = KiDown; }
				}
				else if (snake.UserInput == KiDown) {
					if (CurrentDirection != KiUp) { snake.DirDown(); CurrentDirection = KiDown; }
					else { snake.DirUp(); CurrentDirection = KiUp; }
				}
				
				snake.ShowSnake();
				Sleep(100);								// For Delay Snake 85 Milli seconds
				if(kbhit()) {
					cDirection = getch();
					if(cDirection == KiRight || cDirection == KiLeft || cDirection == KiUp || cDirection == KiDown) {
						snake.UserInput = cDirection;
					}
				}
				// ----------- Collision Condition -------------- //
				if (snake.s_loc[0].y == 2) {   			// For Collision With Upper Boundary 
					Sleep(1000);
					iHit = 1;	break;
				}
				if (snake.s_loc[0].y == TableHeight+2) {		// For Collision With Lower Boundary
					Sleep(1000);
					iHit = 1;	break;
				}
				if(snake.s_loc[0].x == 5) { 					// For Collision With Left Boundary
					Sleep(1000);
					iHit = 1;	break;
				}
				if(snake.s_loc[0].x == TableWidth) {			// For Collision With Right Boundary
					Sleep(1000);
					iHit = 1;	break;
				}
				for(int i=1; i<ilength; i++) {					//collision condition for it self
					if(snake.s_loc[0] == snake.s_loc[i]) { 
						Sleep(1000); 
						iHit = 1; 
						break; /* for loop break */ 
					}
				} // ------------ collision condition for it self ------ //
				//-------------------------------------------------//
				
				if (iHit==1) { break; /* while loop break */ }
				if (snake.s_loc[0] == food.eat) {
					iScore += 5;
					food.Food();
					iCount++;
					ilength++;
					if (iCount == 5) {
						bfood.BigFood();				//show BigFood
						iCount = 0;
						iHideFood = 1;
					}
				}
				if (iHideFood == 1) {
					bfood.ShowTimeForBigFood(iTime);
					iTime--;
					if (iTime == 0) {			// if time is end
						bfood.Tail();			// hide Big Food
						bfood.HideTime();		// hide Time
						iTime = 40;
						iHideFood = 0;
					}
				}		//BIG FOOD CONDITION
				if (snake.s_loc[0] == bfood.bigEat) {
					int randumScore = (rand() % 40);
					iScore = iScore + randumScore;
					bfood.HideTime();
					iTime = 40;
					iHideFood = 0;
				}
				for(int i=1; i<=ilength; i++) {
					if(snake.s_loc[0] == snake.s_loc[i]) { food.Food(); /* for loop break */ }
				}
				for(int i=1; i<=ilength; i++) {
					if(snake.s_loc[0] == snake.s_loc[i]) { bfood.BigFood(); /* for loop break */ }
				}
				bfood.PrintScore();
			}
		}
		//+++++++++++++++++++++++++++++++++++ Computer Vs User Snake Game +++++++++++++++++++++++++++++++//
		else if(Choice == '2') {
			system("cls");
			b.SnakeBoundary();
			snake.InitSnake();
			snake.ShowSnake();
			food.Food();
			bfood.PrintScore();
			bfood.ShowTime();
			Comp_snake.Comp_InitSnake(5, 40, 15, 75);
			Comp_snake.ShowCompSnake();
			_getch();
			while (true) {
				//============= USER SNAKE DIRECTION AND MOVEMENT ============//
				if (snake.UserInput == KiRight) {
					if (CurrentDirection != KiLeft) { snake.DirRight(); CurrentDirection = KiRight; }
					else { snake.DirLeft(); CurrentDirection = KiLeft; }
				}
				else if (snake.UserInput == KiLeft) {
					if (CurrentDirection != KiRight) { snake.DirLeft(); CurrentDirection = KiLeft; }
					else { snake.DirRight(); CurrentDirection = KiRight; }
				}
				else if (snake.UserInput == KiUp) {
					if (CurrentDirection != KiDown) { snake.DirUp(); CurrentDirection = KiUp; }
					else { snake.DirDown(); CurrentDirection = KiDown; }
				}
				else if (snake.UserInput == KiDown) {
					if (CurrentDirection != KiUp) { snake.DirDown(); CurrentDirection = KiDown; }
					else { snake.DirUp(); CurrentDirection = KiUp; }
				}
				snake.ShowSnake();
				//============================================================//
				
				//======== COMPUTER SNAKE DIRECTIONS AND MOVEMENT ============//
				switch(Comp_snake.UserInput) {
					case KiRight:
						Comp_snake.DirRight();
						break;
					case KiLeft:
						Comp_snake.DirLeft();
						break;
					case KiUp:
						Comp_snake.DirUp();
						break;
					case KiDown:
						Comp_snake.DirDown();
						break; 			
				}
				
				Comp_snake.ShowCompSnake();
				//==========================================================//
				Sleep(100);				// For Delay Snake 85 Milli seconds
				
				// same direction of snake until pressed any key from keyboard
				if(kbhit()) {
					cDirection = getch();
					if(cDirection == KiRight || cDirection == KiLeft || cDirection == KiUp || cDirection == KiDown) {
						snake.UserInput = cDirection;
					}
				}
				
				// 		!!!!!!!!!!!!!!!!!!!!   AI Of Snake Function   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!		 //
				Comp_snake.UserInput = DirectionOfComputer(Comp_snake.UserInput, Comp_snake, food);
				// 		!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!		 //
				
			//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++===//
				// ----------- Collision Condition User Snake --------------//
				if (snake.s_loc[0].y == 2) {   			// For Collision With Upper Boundary 
					Sleep(1000);
					iHit = 1;	break;
				}
				if (snake.s_loc[0].y == TableHeight+2) {		// For Collision With Lower Boundary
					Sleep(1000);
					iHit = 1;	break;
				}
				if(snake.s_loc[0].x == 5) { 					// For Collision With Left Boundary
					Sleep(1000);
					iHit = 1;	break;
				}
				if(snake.s_loc[0].x == TableWidth) {			// For Collision With Right Boundary
					Sleep(1000);
					iHit = 1;	break;
				}
				//--------------collision condition of computer snake------------------------//
				//................... for hit the up boundary ..............//
				//...
								//............... for hit the left boundary ...............//
//				if(Comp_snake.s_loc[0].x == TableHeight && Comp_snake.UserInput == KiLeft) {
//					if(food.y > snake.s_loc[0].y ) {
//						Comp_snake.UserInput = KiDown;
//					}
//					else {
//						Comp_snake.UserInput = KiUp;
//					}
//				}
				//---------------------------------------------------------------------------//
				
								//............... for hit the Right boundary ...............//
				if(Comp_snake.s_loc[0].x == TableHeight && Comp_snake.UserInput == KiRight) {
					if(food.y > snake.s_loc[0].y ) {
						Comp_snake.UserInput = KiDown;
					}
					else {
						Comp_snake.UserInput = KiUp;
					}
				}
				//---------------------------------------------------------------------------//
				
								//............... for hit the up boundary ...............//
				if(Comp_snake.s_loc[0].y == TableWidth && Comp_snake.UserInput == KiUp) {
					if(food.x > snake.s_loc[0].x ) {
						Comp_snake.UserInput = KiRight;
					}
					else {
						Comp_snake.UserInput = KiLeft;
					}
				}
				//---------------------------------------------------------------------------//
				
								//............... for hit the Down boundary ...............//
				if(Comp_snake.s_loc[0].y == TableWidth && Comp_snake.UserInput == KiDown) {
					if(food.x > snake.s_loc[0].x ) {
						Comp_snake.UserInput = KiRight;
					}
					else {
						Comp_snake.UserInput = KiLeft;
					}
				}
				//---------------------------------------------------------------------------//
				
				// ------------ collision condition for it self ------ //
				for(int i=1; i<ilength; i++) {
					if(snake.s_loc[0] == snake.s_loc[i]) { Sleep(1000); iHit = 1; break; /* for loop break */ }
				} 
				//-------------------------------------------------//
				if (Comp_snake.s_loc[0] == food.eat) {
					iScore += 5;
					food.Food();
					ilength++;
				}
				if (snake.s_loc[0] == food.eat) {
					iScore += 5;
					food.Food();
					iCount++;
					ilength++;
					if (iCount == 5) {
						bfood.BigFood();				//show BigFood
						iCount = 0;
						iHideFood = 1;
					}
				}
				if (iHideFood == 1) {
					bfood.ShowTimeForBigFood(iTime);
					iTime--;
					if (iTime == 0) {			// if time is end
						bfood.Tail();			// hide Big Food
						bfood.HideTime();		// hide Time
						iTime = 40;
						iHideFood = 0;
					}
				}		//BIG FOOD CONDITION
				if (snake.s_loc[0] == bfood.bigEat) {
					int randumScore = (rand() % 40);
					iScore = iScore + randumScore;
					bfood.HideTime();
					iTime = 40;
					iHideFood = 0;
				}
				//------------- if food generate on snake -----------------//
				for(int i=1; i<=ilength; i++) {
					if(snake.s_loc[0] == snake.s_loc[i]) { food.Food(); /* for loop break */ }
				}
				for(int i=1; i<=ilength; i++) {
					if(snake.s_loc[0] == snake.s_loc[i]) { bfood.BigFood(); /* for loop break */ }
				}
				//--------------------------------------------------------//
			}
		}
		if (iHit == 1) {
			system("cls");
			b.ShowGameOverScreen();
			isgame == false;
		}
	} while(Choice != 6); // end of first while loop (like True/False}
} // end of main function

// AI of Computer Snake  //
char DirectionOfComputer(char CompKey, CSnake Comp_snake, CFood food) {
	int dif_x = food.x - Comp_snake.s_loc[0].x;
	int dif_y = food.y - Comp_snake.s_loc[0].y;
	// DIRECTION FOR FORWARD FOOD //
//-----------------------------------------------------------------------------//	
	// direction for right & up //
	if(Comp_snake.UserInput == KiRight && dif_x>0 && dif_y<0) {
		CompKey = KiRight;
	}
	if(Comp_snake.s_loc[0].x == food.x && CompKey == KiRight && dif_y<0 ) {
		CompKey = KiUp;
	}
	// direction for right & down //
	if(CompKey == KiRight && dif_x>0 && dif_y>0) {
		CompKey = KiRight;
	}
	if(Comp_snake.s_loc[0].x == food.x && CompKey == KiRight && dif_y>0) {
		CompKey = KiDown;
	}
	// direction for left & up //
	if(CompKey == KiLeft && dif_x<0 && dif_y<0 ) {
		CompKey = KiLeft;
	}
	if(Comp_snake.s_loc[0].x == food.x && CompKey == KiLeft && dif_y<0) {
		CompKey = KiUp;
	}
	// direction for left & down //
	if(CompKey == KiLeft && dif_x<0 && dif_y>0) {
		CompKey = KiLeft;
	}
	if(Comp_snake.s_loc[0].x == food.x && CompKey == KiLeft && dif_y>0) {
		CompKey = KiDown;
	}
	// direction for up & right //
	if(CompKey == KiUp && dif_x>0 && dif_y<0) {
		CompKey = KiUp;
	}
	if(Comp_snake.s_loc[0].y == food.y && CompKey == KiUp && dif_x>0) {
		CompKey = KiRight;
	}
	// direction for up & left //
	if(CompKey == KiUp && dif_x<0 && dif_y<0) {
		CompKey = KiUp;
	}
	if(Comp_snake.s_loc[0].y == food.y && CompKey == KiUp && dif_x<0) {
		CompKey = KiLeft;
	}
	// direction for down & right //
	if(CompKey == KiDown && dif_x>0 && dif_y<0) {
		CompKey = KiDown;
	}
	if(Comp_snake.s_loc[0].y == food.y && CompKey == KiDown && dif_x>0) {
		CompKey = KiRight;
	}
	// direction for down & left //
	if(CompKey == KiDown && dif_x<0 && dif_y>0) {
		CompKey = KiDown;
	}
	if(Comp_snake.s_loc[0].y == food.y && CompKey == KiDown && dif_x<0) {
		CompKey = KiLeft;
	}
//--------------------------------------------------------------------------------//
	// DIRECTION FOR BACKWARD //
//--------------------------------------------------------------------------------//
	// direction for right & up //
	if(Comp_snake.UserInput == KiRight && dif_x<0 && dif_y<0) {
		CompKey = KiUp;
	}
	if(Comp_snake.s_loc[0].y == food.y && CompKey == KiUp && dif_x<0 ) {
		CompKey = KiLeft;
	}
	// direction for right & down //
	if(CompKey == KiRight && dif_x<0 && dif_y>0) {
		CompKey = KiDown;
	}
	if(Comp_snake.s_loc[0].y == food.y && CompKey == KiDown && dif_x<0) {
		CompKey = KiLeft;
	}
	// direction for left & up //
	if(CompKey == KiLeft && dif_x>0 && dif_y<0 ) {
		CompKey = KiUp;
	}
	if(Comp_snake.s_loc[0].y == food.y && CompKey == KiUp && dif_x>0) {
		CompKey = KiRight;
	}
	// direction for left & down //
	if(CompKey == KiLeft && dif_x>0 && dif_y>0) {
		CompKey = KiDown;
	}
	if(Comp_snake.s_loc[0].y == food.y && CompKey == KiDown && dif_x>0) {
		CompKey = KiRight;
	}
	// direction for up & right //
	if(CompKey == KiUp && dif_x>0 && dif_y>0) {
		CompKey = KiRight;
	}
	if(Comp_snake.s_loc[0].x == food.x && CompKey == KiRight && dif_y>0) {
		CompKey = KiDown;
	}
	// direction for up & left //
	if(CompKey == KiUp && dif_x<0 && dif_y>0) {
		CompKey = KiLeft;
	}
	if(Comp_snake.s_loc[0].x == food.x && CompKey == KiLeft && dif_y>0) {
		CompKey = KiDown;
	}
	// direction for down & right //
	if(CompKey == KiDown && dif_x>0 && dif_y<0) {
		CompKey = KiRight;
	}
	if(Comp_snake.s_loc[0].x == food.x && CompKey == KiRight && dif_y<0) {
		CompKey = KiUp;
	}
	// direction for down & left //
	if(CompKey == KiDown && dif_x<0 && dif_y<0) {
		CompKey = KiLeft;
	}
	if(Comp_snake.s_loc[0].x == food.x && CompKey == KiLeft && dif_y<0) {
		CompKey = KiUp;
	}
//--------------------------------------------------------------------------------//
	return CompKey;
} 
