#include <iostream>
#include <cstdlib>
#include <cstring>
#include<bits/stdc++.h>
#include<conio.h>
#include<stdio.h>
#include<conio.h>
#include<ctype.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
#include<string.h>
#define LEFT 1
#define RIGHT 2
#define UP 3
#define DOWN 4

using namespace std;

//This method is used to provide a particular color to elements
void textcolor(int fc,int bc=-1){
	if(fc<0 || fc>15)
		return;
	HANDLE h;
	h = GetStdHandle(STD_OUTPUT_HANDLE);
	if(bc>=0 && bc<16)
		SetConsoleTextAttribute(h,fc|bc*16);
	else
		SetConsoleTextAttribute(h,fc);
}

//This method is used to provide a particular color to elements
void textcolor(char *fc,char *bc=""){
	int x,y=16;
	char *colors[]={"Black","Blue","Green","Aqua","Red","Purple","Yellow","White","Gray",
	"LightBlue","LightGreen","LightAqua","LightRed","LightPurple","LightYellow","BrightWhite"};
	for(x=0;x<16;x++)
		if(strcmpi(colors[x],fc)==0)
			break;
	if(strlen(bc)>0)
		for(y=0;y<16;y++)
			if(strcmpi(colors[y],bc)==0)
				break;
	textcolor(x,y);
}

//This method is used to provide a particular color to elements
void textcolor(char *fc,int bc){
	int x;
	char *colors[]={"Black","Blue","Green","Aqua","Red","Purple","Yellow","White","Gray",
	"LightBlue","LightGreen","LightAqua","LightRed","LightPurple","LightYellow","BrightWhite"};
	for(x=0;x<16;x++)
		if(strcmpi(colors[x],fc)==0)
			break;
	textcolor(x,bc);
}

//This method is used to provide a particular color to elements
void textcolor(int fc,char *bc){
	int y;
	char *colors[]={"Black","Blue","Green","Aqua","Red","Purple","Yellow","White","Gray",
	"LightBlue","LightGreen","LightAqua","LightRed","LightPurple","LightYellow","BrightWhite"};
	if(strlen(bc)>0)
		for(y=0;y<16;y++)
			if(strcmpi(colors[y],bc)==0)
				break;
	textcolor(fc,y);
}

//This method is used to set the position to a particular coordinate
void gotoxy(int x, int y)
{
 COORD coord;
 coord.X = x;
 coord.Y = y;
 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//This method is used to draw the texts on the screen
void getup(){
	HANDLE hout;
	CONSOLE_CURSOR_INFO cursor;
	hout = GetStdHandle(STD_OUTPUT_HANDLE);
	cursor.dwSize=1;
	cursor.bVisible=false;
	SetConsoleCursorInfo(hout, &cursor);
	system("mode con:cols=80 lines=25");
	system("title Snake Game");
	system("cls");
	textcolor("Yellow");
	printf("\n  %c",218);
	int x;
	for(x=0;x<75;x++)
		printf("%c",196);
	printf("%c  ",191);
	for(x=0;x<17;x++){
		gotoxy(2,x+2);
		printf("%c",179);
		gotoxy(78,x+2);
		printf("%c ",179);
	}
	printf("  %c",192);
	for(x=0;x<75;x++)
		printf("%c",196);
	printf("%c  ",217);
	printf(" %c",218);
	for(x=0;x<21;x++)
	printf("%c",196);
	printf("%c\n",191);
	printf("  %cPress Enter to Replay%c\n",179,179);
	printf("  %c",192);
	for(x=0;x<21;x++)
		printf("%c",196);
	printf("%c",217);

	gotoxy(59,20);
	printf("%c",218);
	for(x=0;x<18;x++)
		printf("%c",196);
	printf("%c",191);
	gotoxy(59,21);
	printf("%c SCORE : 100      %c",179,179);
	gotoxy(59,22);
	printf("%c STATUS: Playing  %c",179,179);
	gotoxy(59,23);
	printf("%c",192);
	for(x=0;x<18;x++)
		printf("%c",196);
	printf("%c",217);
	gotoxy(32,21);
	printf("Eat the food #");
	gotoxy(32,22);
	printf("Press 'space' to Pause");
	textcolor(7);
}

//This method is used to update the score variable on the right side down screen
void score(int sc){
	gotoxy(69,21);
	printf("%6d",sc*10);
}

//This method is used to update the status variable which is initially set to playing on the right side down screen
void status(char *s,int c=7){
	gotoxy(69,22);
	textcolor(c);
	int x;
	for(x=0;x<strlen(s);x++)
		printf("%c",s[x]);
	for(;x<8;x++)
		printf(" ");
	textcolor(7);
}

void upmove(int a[4][4])
{
	int i,j,li,ri;			//li-left index		// ri-right index		//i,j taken for loops  
	for(j=0;j<4;j++)
	{
		li=0,ri=j;
		for(i=1;i<4;i++)
		{
			if(a[i][j]!=0)
			{
				if(a[i-1][j]==0 || a[i-1][j]==a[i][j])
				{
					if(a[li][ri]==a[i][j])
					{
						a[li][ri]*=2;
						a[i][j]=0;
					}
					else
					{
						if(a[li][ri]==0)
						{
							a[li][ri]=a[i][j];
							a[i][j]=0;
						}
						else
						{
							a[++li][ri]=a[i][j];
							a[i][j]=0;
						}
					}
				}
				else li++;
			}
		}
	}
}

void downmove(int a[4][4])
{
	int i,j,li,ri;
	for(j=0;j<4;j++)
	{
		li=3,ri=j;
		for(i=2;i>=0;i--)
		{
			if(a[i][j]!=0)
			{
				if(a[i+1][j]==0 || a[i+1][j]==a[i][j])
				{
					if(a[li][ri]==a[i][j])
					{
						a[li][ri]*=2;
						a[i][j]=0;
					}
					else
					{
						if(a[li][ri]==0)
						{
							a[li][ri]=a[i][j];
							a[i][j]=0;
						}
						else
						{
							a[--li][ri]=a[i][j];
							a[i][j]=0;
						}
					}
				}
				else li--;
			}
		}
	}
}

void leftmove(int a[4][4])
{
	int i,j,li,ri;
	for(i=0;i<4;i++)
	{
		li=i,ri=0;
		for(j=1;j<4;j++)
		{
			if(a[i][j]!=0)
			{
				if(a[i][j-1]==0 || a[i][j-1]==a[i][j])
				{
					if(a[li][ri]==a[i][j])
					{
						a[li][ri]*=2;
						a[i][j]=0;
					}
					else
					{
						if(a[li][ri]==0)
						{
							a[li][ri]=a[i][j];
							a[i][j]=0;
						}
						else
						{
							a[li][++ri]=a[i][j];
							a[i][j]=0;
						}
					}
				}
				else ri++;
			}
		}
	}
}

void rightmove(int a[4][4])
{
	int i,j,li,ri;
	for(i=0;i<4;i++)
	{
		li=i,ri=3;
		for(j=2;j>=0;j--)
		{
			if(a[i][j]!=0)
			{
				if(a[i][j+1]==0 || a[i][j+1]==a[i][j])
				{
					if(a[li][ri]==a[i][j])
					{
						a[li][ri]*=2;
						a[i][j]=0;
					}
					else
					{
						if(a[li][ri]==0)
						{
							a[li][ri]=a[i][j];
							a[i][j]=0;
						}
						else
						{
							a[li][--ri]=a[i][j];
							a[i][j]=0;
						}
					}
				}
				else ri--;
			}
		}
	}
}

void addblock(int a[4][4])
{
	int li,ri;
	srand(time(0));
	while(1)
	{
		li=rand()%4;
		ri=rand()%4;
		if(a[li][ri]==0)
		{
			a[li][ri]=pow(2,li%2 + 1);
			break;
		}
	}

}

void disp(int a[4][4])
{
	cout<<"\n\t\tPress Esc anytime to quit the game";
	cout<<"\n\n\n\n";
	int i,j;
	for(i=0;i<4;i++)
	{
		cout<<"\t\t\t\t-----------------\n\t\t\t\t";
		for(j=0;j<4;j++)
		{
			if(a[i][j]==0) cout<<"|   ";
			else
				cout<<"| "<<a[i][j]<<" ";
		}
		cout<<"|"<<endl;
	}
	cout<<"\t\t\t\t-----------------\n";
}

int check(int tmp[4][4],int a[4][4])
{
	int fl=1,i,j;
	for(i=0;i<4;i++)
    	for(j=0;j<4;j++)
    		if(tmp[i][j]!=a[i][j])
    		{
    			fl=0;
    			break;
			}
	return fl;
}

int checkover(int a[4][4])
{
	int fl=0,gl=0,i,j;
	for(i=0;i<4;i++)
    	for(j=0;j<4;j++)
    		if(a[i][j]==0)
    		{
    			fl=1;
				break;	
			}
			
	for(i=0;i<3;i++)
    	for(j=0;j<3;j++)
    		if(a[i+1][j]==a[i][j] || a[i][j+1]==a[i][j])
    		{
    			gl=1;
    			break;
			}
			
	if(fl || gl) return 1;
	else return 0;
}

const int N = 9;

bool isSafe(int board[N][N], int row, int col, int num) {
    // Check if 'num' is already in the same row
    for (int i = 0; i < N; i++)
        if (board[row][i] == num)
            return false;

    // Check if 'num' is already in the same column
    for (int i = 0; i < N; i++)
        if (board[i][col] == num)
            return false;

    // Check if 'num' is already in the same 3x3 box
    int boxRowStart = row - row % 3;
    int boxColStart = col - col % 3;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i + boxRowStart][j + boxColStart] == num)
                return false;

    return true;
}

void printBoard(int grid[N][N]) {

    system("cls");
    cout << "\t\t\t<================================================================================>" << endl;
    cout << "\t\t\t|                        WELCOME TO SUDOKU Game!                                 |" << endl;
    cout << "\t\t\t|       Fill in the missing numbers(represented by 0) to solve the puzzle.       |" << endl;
    cout << "\t\t\t<================================================================================>" << endl;
    for (int row = 0; row < N; row++){
      for (int col = 0; col < N; col++){
         if(col == 3 || col == 6)
            cout << " | ";
         cout << grid[row][col] <<" ";
      }
      if(row == 2 || row == 5){
         cout << endl;
         for(int i = 0; i<N; i++)
            cout << "---";
      }
      cout << endl;
   }
}


bool solveSudoku(int board[N][N], int row, int col) {
    // If all cells are filled, the puzzle is solved
    if (row == N - 1 && col == N)
        return true;

    // Move to the next row if the current column is N
    if (col == N) {
        row++;
        col = 0;
    }

    // Skip the cells that already have a value
    if (board[row][col] != 0)
        return solveSudoku(board, row, col + 1);

    // Try filling the current cell with a number from 1 to 9
    for (int num = 1; num <= 9; num++) {
        if (isSafe(board, row, col, num)) {
            board[row][col] = num;

            if (solveSudoku(board, row, col + 1))
                return true;

            board[row][col] = 0;
        }
    }
    return false;
}

bool isSolvedCompletely(int grid[N][N]){
    for (int row = 0; row < N; row++)
        for (int col = 0; col < N; col++)
            if (grid[row][col] == 0)
                return false;

    return true;
}

void playGame(int board[N][N]){
    int ch;
    int row, col, num;
    while(true){
        printBoard(board);
        cout << endl << endl;
        cout << "Unable to solve? Enter -1 as row, col and num to view the solved sudoku."<<endl;
        cout << "Enter row: ";
        cin >> row;
        cout << "Enter column: ";
        cin >> col;
        cout << "Enter number: ";
        cin >> num;

        if(row == -1 || col == -1 || num == -1){
            solveSudoku(board, 0, 0);
            printBoard(board);
            cout << endl;
            cout << "Better luck next time!!!" << endl;
            return;
        }
        if (isSolvedCompletely(board))
            break;
        row--;
        col--;
        if (!isSafe(board, row, col, num)) {
            cout << "Invalid move. Try again." << endl;
            continue;
        }
        board[row][col] = num;
    }

    // Check if the user has solved it correctly or not
    bool solved = true;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] == 0) {
                solved = false;
                break;
            }
        }
    }

    if (solved) {
        cout << "Congratulations! You have solved the puzzle." << endl;
        printBoard(board);
    }
    else {
        cout << "Puzzle not solved. Better luck next time." << endl;
    }

}

void playSnakeGame() {
    	getup();
	register int flow,size,i,xb,yb;
	int speed,restart=1,tmp,xpos[100],ypos[100],scr;
	srand(time(NULL));
	while(true){
		if(restart){
			status("Playing",10);
			for(int k=1;k<75;k+=2)
				for(int j=0;j<17;j++){
					gotoxy(k+3,j+2);
					printf(" ");
				}
			size=5;
			speed=200;
			scr=0;
			score(scr);
			flow=RIGHT;
			xpos[0]=20;
			for(i=0;i<size;i++){
				xpos[i]=xpos[0]-i*2;
				ypos[i]=10;
			}
			for(i=0;i<size;i++){
				gotoxy(xpos[i],ypos[i]);
				printf("*");
			}
			for(tmp=1;true;){
				do{
					xb=rand()%75+3;
				}while(xb%2!=0);
				yb=rand()%17+2;
				for(i=0;i<size;i++)
					if(xb==xpos[i] && yb==ypos[i]){
						tmp=0; break;
					}
				if(tmp)
					break;
			}
			gotoxy(xb,yb);
			textcolor("lightred");
			printf("#");
			textcolor(7);
			restart=0;
		}
		while(!kbhit() && !restart)	{
			if(xpos[0]==xb && ypos[0]==yb){
				for(tmp=1;true;){
					do{
						xb=rand()%75+3;
					}while(xb%2!=0);
					yb=rand()%17+2;
					for(i=0;i<size;i++)
						if(xb==xpos[i] && yb==ypos[i]){
							tmp=0; break;
						}
					if(tmp)
						break;
				}
				gotoxy(xb,yb);
				textcolor("lightred");
				printf("#");
				textcolor(7);
				size++;
				scr++;
				speed-=3;
				score(scr);
			}
			gotoxy(xpos[size-1],ypos[size-1]);
			for(i=size-1;i>0;i--){
				xpos[i]=xpos[i-1];
				ypos[i]=ypos[i-1];
			}
			switch(flow){
				case RIGHT :xpos[i]+=2; break;
				case LEFT :	xpos[i]-=2; break;
				case UP :	ypos[i]-=1; break;
				case DOWN :	ypos[i]+=1;
			}
			tmp=1;
			for(i=1;i<size;i++)
				if(xpos[i]==xpos[0] && ypos[i]==ypos[0]){
					tmp=0;
					break;
				}
			if(xpos[0]>76 || xpos[0]<4 || ypos[0]<2 ||ypos[0]>18)
				tmp=0;
			if(tmp){
				printf(" ");
				gotoxy(xpos[0],ypos[0]);
				printf("O");
				gotoxy(xpos[1],ypos[1]);
				printf("*");
			}
			else{
				textcolor("LIGHTRED");
				printf("*");
				gotoxy(xpos[1],ypos[1]);
				printf("O");
				for(i=2;i<size;i++){
					gotoxy(xpos[i],ypos[i]);
					printf("*");
				}
				textcolor(7);
				status("GameOver",12);
				restart=1;
				getch();
			}
			//delay(speed);
			Sleep(speed);
		}
		char ch=getch();
		switch(tolower(ch)){
			case 'x' : 	system("cls");
//						return 0;
			case ' ' : status("Paused");
						while(true){
							char z=getch();
							if(z=='x')
//								return 0;
							if(z==' ')
								break;
						}
						status("Playing",10);
						break;
			case -32: {
				char chh=getch();
				if(chh==72 && flow!=DOWN)
					flow=UP;
				else if(chh==80 && flow!=UP)
					flow=DOWN;
				else if(chh==75 && flow!=RIGHT)
					flow=LEFT;
				else if(chh==77 && flow!=LEFT)
					flow=RIGHT;
				break;
			}
		}
	}
    
}

void play2048Game() {
    // ... (2048 game logic)
    cout<<"\n\n\n\n\t\t\t2048 GAME\n\n\n\t\tPress any key to continue";
	getch();
	system("cls");
	int i1,i2,i3,i4,i,j;
	int a[4][4]={0},tmp[4][4]={0};
	srand(time(0));
	i1=rand()%4;
	i2=rand()%4;
	while(1)
	{
		i3=rand()%4;
		i4=rand()%4;
		if(i3!=i1 && i4!=i2) break;
	}
	a[i1][i2]=2;
	a[i3][i4]=4;
	disp(a);
	
	int ch;
	while (1)
    {
    	for(i=0;i<4;i++)
    		for(j=0;j<4;j++)
    			tmp[i][j]=a[i][j];
    	ch=getch();
    	system("cls");
    	if(ch==72) upmove(a);
    	if(ch==80) downmove(a);
    	if(ch==75) leftmove(a);
    	if(ch==77) rightmove(a);
		if(ch==27) break;
		
		if(!check(tmp,a))
			addblock(a);
		disp(a);
			
		if(!checkover(a))
		{
			cout<<"\n\n\t\t\tGAME OVER!!\n\n\n";
			getch();
			break;
		}	
	}
//	return 0;
}

void playSudokuGame() {
    // ... (Sudoku game logic)
     system("title Sudoku Game ");
    system("color B0");
    int board[N][N] = {
        {3, 0, 6, 5, 0, 8, 4, 0, 0},
        {5, 2, 0, 0, 0, 0, 0, 0, 0},
        {0, 8, 7, 0, 0, 0, 0, 3, 1},
        {0, 0, 3, 0, 1, 0, 0, 8, 0},
        {9, 0, 0, 8, 6, 3, 0, 0, 5},
        {0, 5, 0, 0, 9, 0, 6, 0, 0},
        {1, 3, 0, 0, 0, 0, 2, 5, 0},
        {0, 0, 0, 0, 0, 0, 0, 7, 4},
        {0, 0, 5, 2, 0, 6, 3, 0, 0}
    };

    cout << "\t\t\t<================================================================================>" << endl;
    cout << "\t\t\t|                        WELCOME TO SUDOKU Game!                                 |" << endl;
    cout << "\t\t\t|       Fill in the missing numbers(represented by 0) to solve the puzzle.       |" << endl;
    cout << "\t\t\t<================================================================================>" << endl;

    while (true) {

        int choice;
        cout << endl << endl;
        cout << "\t\t[1] Solve the Sudoku" << endl;
        cout << "\t\t[2] Unable to solve? View the solved Sudoku" << endl;
        cout << "\t\t[3] Exit" << endl;
        cout << "\t\tEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                playGame(board);
                break;
            case 2:
                if (solveSudoku(board, 0, 0))
                {
                    cout << "Completely Solved Sudoku is: "<< endl;
                    cout << endl << endl;
                    for (int row = 0; row < N; row++){
                        for (int col = 0; col < N; col++){
                            if(col == 3 || col == 6)
                                cout << " | ";
                            cout << board[row][col] <<" ";
                        }
                        if(row == 2 || row == 5){
                            cout << endl;
                            for(int i = 0; i<N; i++)
                                cout << "---";
                        }
                        cout << endl;
                    }
                    cout << endl;
                    cout << "Better luck next time!!!" << endl;
                }
                else
                    cout << "No solution found" << endl;
                break;
            case 3:
                exit(0);
            default:
                cout << "Invalid choice" << endl;
        }
//    return 0;
}
}
int main()
{
    while (true) {
        system("cls");
        cout << "Welcome to the Game Hub!" << endl;
        cout << "Choose a game to play:" << endl;
        cout << "1. Snake" << endl;
        cout << "2. 2048" << endl;
        cout << "3. Sudoku" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                playSnakeGame();
                break;
            case 2:
                play2048Game();
                break;
            case 3:
                playSudokuGame();
                break;
            case 4:
                cout << "Exiting... Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Please select again." << endl;
                break;
        }
        cout << "Press any key to continue..." << endl;
        _getch(); // Wait for a key press before continuing
    }

    return 0;
}

