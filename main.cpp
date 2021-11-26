#include <iostream>
#include <stdio.h>
#include <string>
#include <windows.h>
#include <conio.h>
#include <time.h>

// 방향키
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

#define START_POS_X 4
#define START_POS_Y 22
#define MAX_HP 3

using namespace std;
typedef unsigned int uint;

/*----------자료형 영역----------*/
enum {
    BLACK, DARK_BLUE, DARK_GREEN, DARK_SKYBLUE, DARK_RED, DARK_VOILET, DAKR_YELLOW,
    GRAY, DARK_GRAY, BLUE, GREEN, SKYBLUE, RED, VIOLET,YELLOW, WHITE,
};

typedef struct _position{
	int x;
	int y;
}P;

class Huddle{
	private :
		uint type; //rock, tree, bird, cloud
		P pos;
    public:
        Huddle(uint t) : type(t) {pos.x=0; pos.y=0;}
        uint get_type(){return type;}
        int get_Xpos(){return pos.x;}
        int get_Ypos(){return pos.y;}
        void set_Xpos(int val){pos.x = val;}
        void set_Ypos(int val){pos.y = val;}
};

class Player {
	private :
		uint score;
		uint hp;
		P pos;
    public:
        Player() : score(0), hp(3) {pos.x=START_POS_X; pos.y=START_POS_Y;}
        uint get_score(){return score;}
        uint get_hp(){return hp;}
        int get_Xpos(){return pos.x;}
        int get_Ypos(){return pos.y;}
        void set_score(uint s){score = s;}
        void set_hp(uint val){hp = val;}
        void set_Xpos(int val){pos.x = val;}
        void set_Ypos(int val){pos.y = val;}
        friend void Character();
        void reset(){
            score = 0;
            hp = MAX_HP;
            pos.x = START_POS_X;
            pos.y = START_POS_Y;
        }
};

class bullet{
	private :
		P pos;
};

class map{
	private :
		uint time;
};

Player playerInfo[3];
int playerNum;


/*----------함수 영역 시작----------*/
void cursor_pos(int x, int y)
{
    COORD p;
    p.X = x;
    p.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

int input_key()
{
	if (_kbhit())
		return _getch();
	return 0;
}

int input_key_dir()
{
    char c;
    if (_kbhit())
    {
        c = _getch();
        if (c == -32)
            return _getch();
    }
    return 0;
}

int MainMenu()
{
    int x = 44, y = 10;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);

    system("cls");
    cursor_pos(x, y);
    printf("=================================");
    cursor_pos(x+4, y+3);
    printf("▶  G A M E S T A R T");
    cursor_pos(x+8, y+6);
    printf("S C O R E");
    cursor_pos(x+8, y+9);
    printf("E X I T");
    cursor_pos(x, y+12);
    printf("=================================");
    printf("\n\n\n\n\n\n\n\n\n\n\n");

    int menu = 0;
    bool isSelect = FALSE;

    while(1) {
        int key = input_key_dir();
        if(key == DOWN) menu++;
        else if(key == UP) menu += 2;
        else if(key == RIGHT) isSelect = TRUE;
        else if(key == 0) continue;

        menu %= 3;

        if (menu == 0) {
            system("cls");
            cursor_pos(x, y);
            printf("=================================");
            cursor_pos(x+4, y+3);
            printf("▶  G A M E S T A R T");
            cursor_pos(x+8, y+6);
            printf("S C O R E");
            cursor_pos(x+8, y+9);
            printf("E X I T");
            cursor_pos(x, y+12);
            printf("=================================");
        }
        else if (menu == 1) {
            system("cls");
            cursor_pos(x, y);
            printf("=================================");
            cursor_pos(x+8, y+3);
            printf("G A M E S T A R T");
            cursor_pos(x+4, y+6);
            printf("▶  S C O R E");
            cursor_pos(x+8, y+9);
            printf("E X I T");
            cursor_pos(x, y+12);
            printf("=================================");
        }
        else if (menu == 2) {
            system("cls");
            cursor_pos(x, y);
            printf("=================================");
            cursor_pos(x+8, y+3);
            printf("G A M E S T A R T");
            cursor_pos(x+8, y+6);
            printf("S C O R E");
            cursor_pos(x+4, y+9);
            printf("▶  E X I T");
            cursor_pos(x, y+12);
            printf("=================================");
        }
        printf("\n\n\n\n\n\n\n\n\n\n\n");

        if (isSelect) break;
    }

    return menu;
}

void GameStart()
{
    int x = 46, y = 10;
    system("cls");
    cursor_pos(x, y);
    printf("=============================");
    cursor_pos(x+4, y+3);
    printf("▶  P L A Y E R  1");
    cursor_pos(x+8, y+6);
    printf("P L A Y E R  2");
    cursor_pos(x+8, y+9);
    printf("P L A Y E R  3");
    cursor_pos(x, y+12);
    printf("=============================");
    printf("\n\n\n\n\n\n\n\n\n\n\n");

    bool isSelect = FALSE;

    while(1) {
        int key = input_key_dir();
        if (key == DOWN) playerNum++;
        else if (key == UP) playerNum += 2;
        else if (key == RIGHT) isSelect = TRUE;
        else if (key == 0) continue;

        playerNum %= 3;

        if (playerNum == 0) {
            system("cls");
            cursor_pos(x, y);
            printf("=============================");
            cursor_pos(x+4, y+3);
            printf("▶  P L A Y E R  1");
            cursor_pos(x+8, y+6);
            printf("P L A Y E R  2");
            cursor_pos(x+8, y+9);
            printf("P L A Y E R  3");
            cursor_pos(x, y+12);
            printf("=============================");
        }
        else if (playerNum == 1) {
            system("cls");
            cursor_pos(x, y);
            printf("=============================");
            cursor_pos(x+8, y+3);
            printf("P L A Y E R  1");
            cursor_pos(x+4, y+6);
            printf("▶  P L A Y E R  2");
            cursor_pos(x+8, y+9);
            printf("P L A Y E R  3");
            cursor_pos(x, y+12);
            printf("=============================");
        }
        else if (playerNum == 2) {
            system("cls");
            cursor_pos(x, y);
            printf("=============================");
            cursor_pos(x+8, y+3);
            printf("P L A Y E R  1");
            cursor_pos(x+8, y+6);
            printf("P L A Y E R  2");
            cursor_pos(x+4, y+9);
            printf("▶  P L A Y E R  3");
            cursor_pos(x, y+12);
            printf("=============================");
        }
        printf("\n\n\n\n\n\n\n\n\n\n\n");

        if (isSelect) break;
    }
}

void Count3sec()
{
    int x = 54, y = 11;
    system("cls");
    cursor_pos(x, y++);
    printf("■■■■■■");
    cursor_pos(x, y++);
    printf("          ■");
    cursor_pos(x, y++);
    printf("          ■");
    cursor_pos(x, y++);
    printf("          ■");
    cursor_pos(x, y++);
    printf("          ■");
    cursor_pos(x, y++);
    printf("■■■■■■");
    cursor_pos(x, y++);
    printf("          ■");
    cursor_pos(x, y++);
    printf("          ■");
    cursor_pos(x, y++);
    printf("          ■");
    cursor_pos(x, y++);
    printf("          ■");
    cursor_pos(x, y++);
    printf("■■■■■■");
    printf("\n\n\n\n\n\n\n\n\n\n\n");
    Sleep(1000);

    system("cls");
    y = 11;
    cursor_pos(x, y++);
    printf("■■■■■■");
    cursor_pos(x, y++);
    printf("          ■");
    cursor_pos(x, y++);
    printf("          ■");
    cursor_pos(x, y++);
    printf("          ■");
    cursor_pos(x, y++);
    printf("          ■");
    cursor_pos(x, y++);
    printf("■■■■■■");
    cursor_pos(x, y++);
    printf("■");
    cursor_pos(x, y++);
    printf("■");
    cursor_pos(x, y++);
    printf("■");
    cursor_pos(x, y++);
    printf("■");
    cursor_pos(x, y++);
    printf("■■■■■■");
    printf("\n\n\n\n\n\n\n\n\n\n\n");
    Sleep(1000);

    system("cls");
    x = 55, y = 11;
    cursor_pos(x, y++);
    printf("  ■■");
    cursor_pos(x, y++);
    printf("    ■");
    cursor_pos(x, y++);
    printf("    ■");
    cursor_pos(x, y++);
    printf("    ■");
    cursor_pos(x, y++);
    printf("    ■");
    cursor_pos(x, y++);
    printf("    ■");
    cursor_pos(x, y++);
    printf("    ■");
    cursor_pos(x, y++);
    printf("    ■");
    cursor_pos(x, y++);
    printf("    ■");
    cursor_pos(x, y++);
    printf("    ■");
    cursor_pos(x, y++);
    printf("■■■■■");
    printf("\n\n\n\n\n\n\n\n\n\n\n");
    Sleep(1000);
}

void Score()
{
    string name[] = {"Player1", "Player2", "Player3"};
    int ranking[] = {0, 1, 2};
    int x = 45, y = 10;

    //sort(); ranking을 sort

    system("cls");
    cursor_pos(x, y);
    printf("=============================");
    cursor_pos(x+5, y+3);
    cout << "1st    " << name[ranking[0]] << "   " << playerInfo[ranking[0]].get_score();
    cursor_pos(x+5, y+6);
    cout << "2nd    " << name[ranking[1]] << "   " << playerInfo[ranking[1]].get_score();
    cursor_pos(x+5, y+9);
    cout << "3th    " << name[ranking[2]] << "   " << playerInfo[ranking[2]].get_score();
    cursor_pos(x, y+12);
    printf("=============================");
    printf("\n\n\n\n\n\n\n\n\n\n\n");

    while(1) {
        int key = input_key_dir();
        if(key == 0) continue;
        else break;
    }
}

void Character(Player myplay)
{
    int x = myplay.get_Xpos(), y = myplay.get_Ypos();
    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DARK_GRAY);
    cursor_pos(x+6, y++);
    printf("■■■");
    cursor_pos(x+4, y++);
    printf("■");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DARK_BLUE);
    printf("■■■");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DARK_GRAY);
    printf("■");
    cursor_pos(x+2, y++);
    printf("■");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DARK_BLUE);
    printf("■■■■■");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DARK_GRAY);
    printf("■");
    cursor_pos(x+2, y++);
    printf("■");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DARK_BLUE);
    printf("■■■■");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DARK_GRAY);
    printf("■■");
    cursor_pos(x, y++);
    printf("■■");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DARK_BLUE);
    printf("■■■");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DARK_GRAY);
    printf("■");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DARK_SKYBLUE);
    printf("■■");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DARK_GRAY);
    printf("■");
    cursor_pos(x, y++);
    printf("■■");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DARK_BLUE);
    printf("■■■■");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DARK_GRAY);
    printf("■■");
    cursor_pos(x, y++);
    printf("■■");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DARK_BLUE);
    printf("■■■■■");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DARK_GRAY);
    printf("■");
    cursor_pos(x, y++);
    printf("■■");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DARK_BLUE);
    printf("■■■■■");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DARK_GRAY);
    printf("■");
    cursor_pos(x+2, y++);
    printf("■");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DARK_BLUE);
    printf("■■");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DARK_GRAY);
    printf("■");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DARK_BLUE);
    printf("■■");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DARK_GRAY);
    printf("■");
    cursor_pos(x+2, y++);
    printf("■");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DARK_BLUE);
    printf("■");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DARK_GRAY);
    printf("■  ■");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DARK_BLUE);
    printf("■");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DARK_GRAY);
    printf("■");
    cursor_pos(x+3, y++);
    printf("■■    ■■");
    //system("pause");
}

void Rock(int posX)
{
    int x = posX, y = 30;
    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DARK_GRAY);
    cursor_pos(x+2, y++);
    printf("■■");
    cursor_pos(x, y++);
    printf("■■■■");
    cursor_pos(x, y++);
    printf("■■■■");
    cursor_pos(x, y++);
    printf("■■■■");
    //system("pause");
}

void Tree(int posY)
{
    int x = START_POS_X, y = posY;
    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DARK_GREEN);
    cursor_pos(x+3, y++);
    printf("■■");
    cursor_pos(x+2, y++);
    printf("■■■");
    cursor_pos(x+1, y++);
    printf("■■■■");
    cursor_pos(x, y++);
    printf("■■■■■");
    cursor_pos(x, y++);
    printf("■■■■■");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DAKR_YELLOW);
    cursor_pos(x+2, y++);
    printf("■■");
    cursor_pos(x+2, y++);
    printf("■■");
    cursor_pos(x+2, y++);
    printf("■■");
    //system("pause");
}

void Bird(int posX)
{
    int x = posX, y = 5;
    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GRAY);
    cursor_pos(x+2, y++);
    printf("■        ■");
    cursor_pos(x, y++);
    printf("■  ■    ■  ■");
    cursor_pos(x+6, y++);
    printf("■■");
    cursor_pos(x+6, y++);
    printf("■■");
    //system("pause");
}

void GameOver()
{
    int x = 37, y = 10;
    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);

    //GAME
    cursor_pos(x, y++);
    printf("■■■■      ■■      ■      ■    ■■■■");
    cursor_pos(x, y++);
    printf("■          ■    ■    ■■  ■■    ■");
    cursor_pos(x, y++);
    printf("■  ■■    ■■■■    ■  ■  ■    ■■■■");
    cursor_pos(x, y++);
    printf("■    ■    ■    ■    ■      ■    ■");
    cursor_pos(x, y++);
    printf("■■■■    ■    ■    ■      ■    ■■■■");

    //OVER
    y += 2;
    cursor_pos(x, y++);
    printf("■■■■    ■      ■    ■■■■    ■■■");
    cursor_pos(x, y++);
    printf("■    ■     ■    ■     ■          ■    ■");
    cursor_pos(x, y++);
    printf("■    ■      ■  ■      ■■■■    ■■■");
    cursor_pos(x, y++);
    printf("■    ■       ■■       ■          ■   ■");
    cursor_pos(x, y++);
    printf("■■■■        ■        ■■■■    ■    ■");
    printf("\n\n\n\n\n\n\n\n\n\n\n");
    system("pause");
}

int Playing()
{
    char jump_type = 0; //no jump state
    int jump_size = 8, jump_cnt = 0;
    bool down = false;

    while(1){
        int key = input_key_dir();

        if(key == UP){
            if(jump_type == 0)
                jump_type = 1;

            else if(jump_type == 1){
                jump_type = 2;
                jump_cnt = 0;
                down = false;
            }
        }

        if(jump_type){
            jump_cnt++;

            if(down)
                playerInfo[playerNum].set_Ypos(playerInfo[playerNum].get_Ypos() + 1);
            else
                playerInfo[playerNum].set_Ypos(playerInfo[playerNum].get_Ypos() - 1);

            if(jump_cnt == jump_size){
                if(!down){
                    Character(playerInfo[playerNum]);
                    down = true;
                    jump_cnt = 0;
                }
            }

            if(playerInfo[playerNum].get_Ypos() == START_POS_Y){
                jump_cnt = 0;
                jump_type = 0;
                down = false;
            }
        }

        Character(playerInfo[playerNum]);
    }

    return playerInfo[playerNum].get_score();
}

int main()
{
    system("mode con:cols=120 lines=35"); //가로, 세로

    while(1)
    {
        int gameScore = 0;

        switch (MainMenu()){
            case 0 : GameStart(); Count3sec(); gameScore = Playing(); GameOver(); break;
            case 1 : Score(); break;
            case 2 : system("cls"); return 0;
        }
    }
    return 0;
}
