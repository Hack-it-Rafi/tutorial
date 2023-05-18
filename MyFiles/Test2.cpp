#include <bits/stdc++.h>
#include <conio.h>
//#include<stdlib.h>
#include <windows.h>
#include "GCost.h"
#include "HCost.h"
#include "PrintMAZE.h"
#include "IsValid.h"
#define RowNum 23
#define ColNum 75
using namespace std;

typedef struct
{
    int row;
    int column;
} location;

struct Cell
{
    int x;
    int y;
    int f;
    int g;
    int h;
}cell[RowNum*ColNum];

struct Status
{
    int open;
    int closed;
    int cellInx;
}status[RowNum+1][ColNum+1];

int getInput();

int minPath(int ux, int uy, int px, int py, char maze[RowNum][ColNum+1]);
int ghostLogic(location *ghost, location *pacman, char maze[RowNum][ColNum+1]);

void addColumn(location *ghost, int *change, int *dead, int *foodToken, char maze[RowNum][ColNum+1]);
void cutColumn(location *ghost, int *change, int *dead, int *foodToken, char maze[RowNum][ColNum+1]);
void addRow(location *ghost, int *change, int *dead, int *foodToken, char maze[RowNum][ColNum+1]);
void cutRow(location *ghost, int *change, int *dead, int *foodToken, char maze[RowNum][ColNum+1]);

void runGame()
{
    int level = 1;
    char Maze[RowNum][(ColNum+1)] = {
            "###########################################################################",
            "# - - G - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - G - - #",
            "########### - - ######### - - ######### - - ################# - - #########",
            "#         # - - ######### - - ######### - - ################# - - #       #",
            "#         # - - ######### - - ######### - - ################# - - #       #",
            "#         # - - - ##### - - - - ##### - - - - - - ##### - - - - - #       #",
            "#         # - - - ##### - ### - ##### - ####### - ##### - - - - - #       #",
            "#         ##### - ##### - ### - ##### - #     # - ##### - #########       #",
            "#             # - ##### - ### - ##### - #     # - ##### - #               #",
            "#             # - ##### - ### - ##### - #     # - ##### - #               #",
            "#             # - ##### - ### - ##### - ####### - ##### - #               #",
            "#             # - - - - - - - - - - - @ - - - - - - - - - #               #",
            "#             # - ##### - ### - ##### - ####### - ##### - #               #",
            "#             # - ##### - ### - ##### - #     # - ##### - #               #",
            "#             # - ##### - ### - ##### - #     # - ##### - #               #",
            "#         ##### - ##### - ### - ##### - #     # - ##### - #########       #",
            "#         # - - - ##### - ### - ##### - ####### - ##### - - - - - #       #",
            "#         # - - - ##### - - - - ##### - - - # - - ##### - - ### - #       #",
            "#         # - - ######### - - ######### - - - - - ##### - - # # - #       #",
            "#         # - - ######### - - ######### - - # - - ##### - - # # - #       #",
            "########### - - ######### - - ######### - - # - - ##### - - ### - #########",
            "# - - G - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - G - - #",
            "###########################################################################"
            };
    while(1)
    {
        int row = 23, column = 75;
        int input = 0;
        int food = 246;
        int moveCount = 0;
        int proceed = 0;
        int dead = 0;
        int change = 0;
        int random;

        int foodToken1 = 0;
        int foodToken2 = 0;
        int foodToken3 = 0;
        int foodToken4 = 0;

        int direction = 0;
        // 1 = up
        // 2 = left
        // 3 = down
        //4 = right

        location pacman;
        pacman.row = 11;
        pacman.column = 38;

        location ghost1;
        ghost1.row = 1;
        ghost1.column = 6;

        location ghost2;
        ghost2.row = 1;
        ghost2.column = 68;

        location ghost3;
        ghost3.row = 21;
        ghost3.column = 6;

        location ghost4;
        ghost4.row = 21;
        ghost4.column = 68;

        cout<<endl<<endl<<endl<<endl<<endl<<endl;
        cout<<"                                                 Press any key";
        getch();

        system("cls");

        PrintMaze(Maze, row, column, level);

        do{
            cout<<endl;
            cout<<"                   ";
            cout<<"press (w, a, s, d) to move";
            input = getInput();

            if(input == 'w')
            {
                if((pacman.row - 1)<0 || Maze[pacman.row-1][pacman.column] == '#')
                {
                    proceed == -1;
                }
                else
                {
                    if(Maze[pacman.row-1][pacman.column] == '-')
                    {
                        Maze[pacman.row-1][pacman.column] = ' ';
                        food = food - 1;
                    }
                    if(Maze[pacman.row-1][pacman.column] == 'G')
                    {
                        Maze[pacman.row-1][pacman.column] = 'G';
                        Maze[pacman.row][pacman.column] = ' ';
                        dead = 1;
                    }
                    else
                    {
                        Maze[pacman.row-1][pacman.column] = '@';
                        Maze[pacman.row][pacman.column] = ' ';
                        pacman.row = pacman.row - 1;
                    }
                }
            }
            else if(input == 'a')
            {
                if((pacman.column-2)<0 || Maze[pacman.row][pacman.column-2] == '#')
                {
                    proceed = -1;
                }
                else
                {
                    if(Maze[pacman.row][pacman.column-2] == '-')
                    {
                        Maze[pacman.row][pacman.column-2] = ' ';
                        food = food -1;
                    }
                    if(Maze[pacman.row][pacman.column-2] == 'G')
                    {
                        Maze[pacman.row][pacman.column-2] == 'G';
                        Maze[pacman.row][pacman.column] = ' ';
                        dead = 1;
                    }
                    else
                    {
                        Maze[pacman.row][pacman.column-2] = '@';
                        Maze[pacman.row][pacman.column] = ' ';
                        pacman.column = pacman.column - 2;
                    }
                }
            }
            else if(input == 's')
            {
                if((pacman.row + 1)>row || Maze[pacman.row+1][pacman.column] == '#')
                {
                    proceed == -1;
                }
                else
                {
                    if(Maze[pacman.row+1][pacman.column] == '-')
                    {
                        Maze[pacman.row+1][pacman.column] = ' ';
                        food = food - 1;
                    }
                    if(Maze[pacman.row+1][pacman.column] == 'G')
                    {
                        Maze[pacman.row+1][pacman.column] = 'G';
                        Maze[pacman.row][pacman.column] = ' ';
                        dead = 1;
                    }
                    else
                    {
                        Maze[pacman.row+1][pacman.column] = '@';
                        Maze[pacman.row][pacman.column] = ' ';
                        pacman.row = pacman.row + 1;
                    }
                }
            }
            else if(input == 'd')
            {
                if((pacman.column+2)>75 || Maze[pacman.row][pacman.column+2] == '#')
                {
                    proceed = -1;
                }
                else
                {
                    if(Maze[pacman.row][pacman.column+2] == '-')
                    {
                        Maze[pacman.row][pacman.column+2] = ' ';
                        food = food -1;
                    }
                    if(Maze[pacman.row][pacman.column+2] == 'G')
                    {
                        Maze[pacman.row][pacman.column+2] == 'G';
                        Maze[pacman.row][pacman.column] = ' ';
                        dead = 1;
                    }
                    else
                    {
                        Maze[pacman.row][pacman.column+2] = '@';
                        Maze[pacman.row][pacman.column] = ' ';
                        pacman.column = pacman.column + 2;
                    }
                }
            }
            else if(input == 'q')
            {
                cout<<endl<<"Quit the game?"<<endl;
                cout<<"1. press 'a' to continue"<<endl;
                cout<<"2. press 'd' to quit"<<endl;
                while(1)
                {
                    input = getInput();
                    if(input == 'a')
                    {
                        proceed = -1;
                        cout<<"Game continue "<<endl;
                        break;
                    }
                    if(input == 'd')
                    {
                        return;
                    }
                }
            }
            else
            {
                proceed = -1;
            }

            if(proceed==0)
            {
                moveCount++;
            }

            if(proceed == 0&&dead == 0)
            {
                random = rand()%10;
                if(random == 0)
                {
                    addColumn(&ghost1, &change, &dead, &foodToken1, Maze);
                }
                if(random == 1)
                {
                    addRow(&ghost1, &change, &dead, &foodToken1, Maze);
                }
                if(random == 2)
                {
                    cutColumn(&ghost1, &change, &dead, &foodToken1, Maze);
                }
                if(random == 3)
                {
                    cutRow(&ghost1, &change, &dead, &foodToken1, Maze);
                }
                if(random>3&&random<7)
                {
                    if((ghost1.column - pacman.column)<0)
                    {
                        addColumn(&ghost1, &change, &dead, &foodToken1, Maze);
                    }
                    if((ghost1.column - pacman.column)>0)
                    {
                        cutColumn(&ghost1, &change, &dead, &foodToken1, Maze);
                    }
                    if((ghost1.row - pacman.row)<0)
                    {
                        addRow(&ghost1, &change, &dead, &foodToken1, Maze);
                    }
                    if((ghost1.row - pacman.row)>0)
                    {
                        cutRow(&ghost1, &change, &dead, &foodToken1, Maze);
                    }

                    if(!change)
                    {
                        addColumn(&ghost1, &change, &dead, &foodToken1, Maze);
                        cutColumn(&ghost1, &change, &dead, &foodToken1, Maze);
                        addRow(&ghost1, &change, &dead, &foodToken1, Maze);
                        cutRow(&ghost1, &change, &dead, &foodToken1, Maze);
                    }
                }
                if(random>6)
                {
                    if((ghost1.row - pacman.row)<0)
                    {
                        addRow(&ghost1, &change, &dead, &foodToken1, Maze);
                    }
                    if((ghost1.row - pacman.row)>0)
                    {
                        cutRow(&ghost1, &change, &dead, &foodToken1, Maze);
                    }
                    if((ghost1.column - pacman.column)<0)
                    {
                        addColumn(&ghost1, &change, &dead, &foodToken1, Maze);
                    }
                    if((ghost1.column - pacman.column)>0)
                    {
                        cutColumn(&ghost1, &change, &dead, &foodToken1, Maze);
                    }

                    if(!change)
                    {
                        addRow(&ghost1, &change, &dead, &foodToken1, Maze);
                        cutRow(&ghost1, &change, &dead, &foodToken1, Maze);
                        addColumn(&ghost1, &change, &dead, &foodToken1, Maze);
                        cutColumn(&ghost1, &change, &dead, &foodToken1, Maze);
                    }
                }
            }

            change = 0;

            if(proceed == 0&&dead == 0)
            {
                random = rand()%10;
                if(random == 0)
                {
                    addColumn(&ghost2, &change, &dead, &foodToken2, Maze);
                }
                if(random == 1)
                {
                    addRow(&ghost2, &change, &dead, &foodToken2, Maze);
                }
                if(random == 2)
                {
                    cutColumn(&ghost2, &change, &dead, &foodToken2, Maze);
                }
                if(random == 3)
                {
                    cutRow(&ghost2, &change, &dead, &foodToken2, Maze);
                }
                if(random>3&&random<7)
                {
                    if((ghost2.column - pacman.column)<0)
                    {
                        addColumn(&ghost2, &change, &dead, &foodToken2, Maze);
                    }
                    if((ghost2.column - pacman.column)>0)
                    {
                        cutColumn(&ghost2, &change, &dead, &foodToken2, Maze);
                    }
                    if((ghost2.row - pacman.row)<0)
                    {
                        addRow(&ghost2, &change, &dead, &foodToken2, Maze);
                    }
                    if((ghost2.row - pacman.row)>0)
                    {
                        cutRow(&ghost2, &change, &dead, &foodToken2, Maze);
                    }

                    if(!change)
                    {
                        addColumn(&ghost2, &change, &dead, &foodToken2, Maze);
                        cutColumn(&ghost2, &change, &dead, &foodToken2, Maze);
                        addRow(&ghost2, &change, &dead, &foodToken2, Maze);
                        cutRow(&ghost2, &change, &dead, &foodToken2, Maze);
                    }
                }
                if(random>6)
                {
                    if((ghost2.row - pacman.row)<0)
                    {
                        addRow(&ghost2, &change, &dead, &foodToken2, Maze);
                    }
                    if((ghost2.row - pacman.row)>0)
                    {
                        cutRow(&ghost2, &change, &dead, &foodToken2, Maze);
                    }
                    if((ghost2.column - pacman.column)<0)
                    {
                        addColumn(&ghost2, &change, &dead, &foodToken2, Maze);
                    }
                    if((ghost2.column - pacman.column)>0)
                    {
                        cutColumn(&ghost2, &change, &dead, &foodToken2, Maze);
                    }

                    if(!change)
                    {
                        addRow(&ghost2, &change, &dead, &foodToken2, Maze);
                        cutRow(&ghost2, &change, &dead, &foodToken2, Maze);
                        addColumn(&ghost2, &change, &dead, &foodToken2, Maze);
                        cutColumn(&ghost2, &change, &dead, &foodToken2, Maze);
                    }
                }
            }

            change = 0;

            if(proceed == 0&&dead == 0)
            {
                direction = ghostLogic(&ghost3, &pacman, Maze);
                if(direction == 1)
                {
                    cutRow(&ghost3, &change, &dead, &foodToken3, Maze);
                }
                else if(direction == 2)
                {
                    cutColumn(&ghost3, &change, &dead, &foodToken3, Maze);
                }
                else if(direction == 3)
                {
                    addRow(&ghost3, &change, &dead, &foodToken3, Maze);
                }
                else if(direction == 4)
                {
                    addColumn(&ghost3, &change, &dead, &foodToken3, Maze);
                }

                if(!change)
                    {
                        addColumn(&ghost3, &change, &dead, &foodToken3, Maze);
                        cutColumn(&ghost3, &change, &dead, &foodToken3, Maze);
                        addRow(&ghost3, &change, &dead, &foodToken3, Maze);
                        cutRow(&ghost3, &change, &dead, &foodToken3, Maze);
                    }

            }

            change = 0;

            if(proceed == 0&&dead == 0)
            {
                direction = ghostLogic(&ghost4, &pacman, Maze);
                if(direction == 1)
                {
                    cutRow(&ghost4, &change, &dead, &foodToken4, Maze);
                }
                else if(direction == 2)
                {
                    cutColumn(&ghost4, &change, &dead, &foodToken4, Maze);
                }
                else if(direction == 3)
                {
                    addRow(&ghost4, &change, &dead, &foodToken4, Maze);
                }
                else if(direction == 4)
                {
                    addColumn(&ghost4, &change, &dead, &foodToken4, Maze);
                }

                if(!change)
                    {
                        addColumn(&ghost4, &change, &dead, &foodToken4, Maze);
                        cutColumn(&ghost4, &change, &dead, &foodToken4, Maze);
                        addRow(&ghost4, &change, &dead, &foodToken4, Maze);
                        cutRow(&ghost4, &change, &dead, &foodToken4, Maze);
                    }

            }

            change = 0;


            if(!proceed)
            {
                system("cls");
                //cout<<endl<<"direction: "<<direction<<endl;
                PrintMaze(Maze, row, column, level);
                cout<<endl<<"Total move: "<<moveCount<<endl;
                cout<<"Score: "<<246-food<<endl;
                cout<<"Food remaining: "<<food<<endl;
            }

            if(dead)
            {
                break;
            }

            input = 0;
            proceed = 0;

        }while(food!=0);

        if(!dead)
        {
            cout<<endl<<"Horrah! You won the match!!!!!!!"<<endl;
            level++;
        }
        else
        {
            cout<<endl<<"You lost, please try again!!!!"<<endl;
        }

        if(level==2)
        {
            char board[RowNum][ColNum+1] = {
                "###########################################################################",
            "# - - G - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - G - - #",
            "# - ########### - ########### - ############# - ########### - ######### - #",
            "# - #         # - #         # - #           # - #         # - #       # - #",
            "# - #         # - #         # - #           # - #         # - #       # - #",
            "# - ########### - ########### - ############# - ########### - ######### - #",
            "# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #",
            "# - ########### - ########### - ############# - ########### - ######### - #",
            "# - #         # - #         # - #           # - #         # - #       # - #",
            "# - #         # - #         # - #           # - #         # - #       # - #",
            "# - ########### - ########### - ############# - ########### - ######### - #",
            "# - - - - - - - - - - - - - - - - - - @ - - - - - - - - - - - - - - - - - #",
            "# - ########### - ########### - ############# - ########### - ######### - #",
            "# - #         # - #         # - #           # - #         # - #       # - #",
            "# - #         # - #         # - #           # - #         # - #       # - #",
            "# - ########### - ########### - ############# - ########### - ######### - #",
            "# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #",
            "# - ########### - ########### - ############# - ########### - ######### - #",
            "# - #         # - #         # - #           # - #         # - #       # - #",
            "# - #         # - #         # - #           # - #         # - #       # - #",
            "# - ########### - ########### - ############# - ########### - ######### - #",
            "# - - G - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - G - - #",
            "###########################################################################"
            };

            for(int i=0; i<RowNum; i++)
                for(int j=0;j<ColNum+1; j++)
                Maze[i][j] = board[i][j];
            continue;
        }

        cout<<"Press any key";
        getch();

        cout<<"Do you want to play again?"<<endl;
        cout<<"1. Press 'a' to continue"<<endl;
        cout<<"2. Press 'd' to exit"<<endl;

        while(1)
        {
            input = getInput();
            if(input == 'a')
            {
                moveCount = 0;
                break;
            }
            if(input == 'd')
            {
                return;
            }
        }
    }
}

int main()
{
    system("cls");
    runGame();

    return 0;
}

int getInput()
{
    int x;
    x = getch();
    return x;
}

int minPath(int ux, int uy, int px, int py, char maze[RowNum][ColNum+1])
{
    if(ux==px&&uy==py)
        return 0;

    for(int i=0; i<RowNum; i++)
    {
        for(int j=0; j<ColNum; j++)
        {
            status[i][j].open = false;
            status[i][j].closed = false;
            status[i][j].cellInx = -1;
        }
    }

    int cell_inx = 0, counter = 0;

    status[ux][uy].open = true;
    status[ux][uy].cellInx = cell_inx;

    cell[cell_inx].x = ux;
    cell[cell_inx].y = uy;
    cell[cell_inx].g = gcost(0);
    cell[cell_inx].h = hcost(ux, uy, px, py, maze);
    cell[cell_inx].f = cell[cell_inx].g + cell[cell_inx].h;

    int curNodeInx = cell_inx;
    int minFcost = INT_MAX;
    int minHcost = cell[cell_inx].h;
    counter++;
    while(counter>0)
    {
        for(int i=1; i<=cell_inx; i++)
        {
            if(status[cell[i].x][cell[i].y].open == true)
            {
                int curF = cell[i].f;
                int curH = cell[i].h;

                if(curF<minFcost||(curF==minFcost&&curH<minHcost))
                {
                    minFcost = curF;
                    minHcost = curH;
                    curNodeInx = i;
                }
            }
        }

        int X, Y;
        X= cell[curNodeInx].x;
        Y = cell[curNodeInx].y;

        status[X][Y].open = false;
        status[X][Y].closed = true;
        counter = counter-1;

        if(X==px&&Y==py)
        {
            return minFcost;
        }
        else
        {
            if(isValid(X-1, Y)&&status[X-1][Y].closed!=true&&maze[X-1][Y]!='#')
            {
                if(status[X-1][Y].cellInx != -1)
                {
                    int g = gcost(cell[curNodeInx].g+1);
                    int h = hcost(X-1, Y, px, py, maze);
                    int f = g+h;

                    if(cell[status[X-1][Y].cellInx].f>f)
                    {
                        cell[status[X-1][Y].cellInx].f = f;
                        cell[status[X-1][Y].cellInx].g = g;
                        cell[status[X-1][Y].cellInx].h = h;
                    }
                }
                else if(status[X-1][Y].open == false)
                {
                    cell_inx = cell_inx+1;
                    counter++;

                    status[X-1][Y].open = true;
                    status[X-1][Y].cellInx = cell_inx;

                    cell[cell_inx].x = X-1;
                    cell[cell_inx].y = Y;
                    cell[cell_inx].g = gcost(cell[curNodeInx].g+1);
                    cell[cell_inx].h = hcost(X-1, Y, px, py, maze);
                    cell[cell_inx].f = cell[cell_inx].g+cell[cell_inx].h;
                }
            }

            if(isValid(X+1, Y)&&status[X+1][Y].closed!=true&&maze[X+1][Y]!='#')
            {
                if(status[X+1][Y].cellInx != -1)
                {
                    int g = gcost(cell[curNodeInx].g+1);
                    int h = hcost(X+1, Y, px, py, maze);
                    int f = g+h;

                    if(cell[status[X+1][Y].cellInx].f>f)
                    {
                        cell[status[X+1][Y].cellInx].f = f;
                        cell[status[X+1][Y].cellInx].g = g;
                        cell[status[X+1][Y].cellInx].h = h;
                    }
                }
                else if(status[X+1][Y].open == false)
                {
                    cell_inx = cell_inx+1;
                    counter = counter+1;

                    status[X+1][Y].open = true;
                    status[X+1][Y].cellInx = cell_inx;

                    cell[cell_inx].x = X+1;
                    cell[cell_inx].y = Y;
                    cell[cell_inx].g = gcost(cell[curNodeInx].g+1);
                    cell[cell_inx].h = hcost(X+1, Y, px, py, maze);
                    cell[cell_inx].f = cell[cell_inx].g+cell[cell_inx].h;
                }
            }

            if(isValid(X, Y-2)&&status[X][Y-2].closed!=true&&maze[X][Y-2]!='#')
            {
                if(status[X][Y-2].cellInx != -1)
                {
                    int g = gcost(cell[curNodeInx].g+1);
                    int h = hcost(X, Y-2, px, py, maze);
                    int f = g+h;

                    if(cell[status[X][Y-2].cellInx].f>f)
                    {
                        cell[status[X][Y-2].cellInx].f = f;
                        cell[status[X][Y-2].cellInx].g = g;
                        cell[status[X][Y-2].cellInx].h = h;
                    }
                }
                else if(status[X][Y-2].open == false)
                {
                    cell_inx = cell_inx+1;
                    counter = counter +1;

                    status[X][Y-2].open = true;
                    status[X][Y-2].cellInx = cell_inx;

                    cell[cell_inx].x = X;
                    cell[cell_inx].y = Y-2;
                    cell[cell_inx].g = gcost(cell[curNodeInx].g+1);
                    cell[cell_inx].h = hcost(X, Y-2, px, py, maze);
                    cell[cell_inx].f = cell[cell_inx].g+cell[cell_inx].h;
                }
            }

            if(isValid(X, Y+2)&&status[X][Y+2].closed!=true&&maze[X][Y+2]!='#')
            {
                if(status[X][Y+2].cellInx != -1)
                {
                    int g = gcost(cell[curNodeInx].g+1);
                    int h = hcost(X, Y+2, px, py, maze);
                    int f = g+h;

                    if(cell[status[X][Y+2].cellInx].f>f)
                    {
                        cell[status[X][Y+2].cellInx].f = f;
                        cell[status[X][Y+2].cellInx].g = g;
                        cell[status[X][Y+2].cellInx].h = h;
                    }
                }
                else if(status[X][Y+1].open == false)
                {
                    cell_inx = cell_inx+2;
                    counter = counter +2;

                    status[X][Y+2].open = true;
                    status[X][Y+2].cellInx = cell_inx;

                    cell[cell_inx].x = X;
                    cell[cell_inx].y = Y+2;
                    cell[cell_inx].g = gcost(cell[curNodeInx].g+1);
                    cell[cell_inx].h = hcost(X, Y+2, px, py, maze);
                    cell[cell_inx].f = cell[cell_inx].g+cell[cell_inx].h;
                }
            }

        }
    }
    return minFcost;
}

int ghostLogic(location *ghost, location *pacman, char maze[RowNum][ColNum+1])
{
    int gX = ghost->row;
    int gY = ghost->column;

    int pX = pacman->row;
    int pY = pacman->column;

    int loc1 = gX-1;
    int loc2 = gY-2;
    int loc3 = gX +1;
    int loc4 = gY + 2;

    int a = INT_MAX;
    int b = INT_MAX;
    int c = INT_MAX;
    int d = INT_MAX;

    int mini;

    cout<<endl;
    if(loc1>0&&maze[loc1][gY]!='#')
        a = minPath(loc1, gY, pX, pY, maze);
        cout<<"w: "<<a<<endl;
    if(loc2>0&&maze[gX][loc2]!='#')
        b = minPath(gX, loc2, pX, pY, maze);
        cout<<"a: "<<b<<endl;
    if(loc3<RowNum&&maze[loc3][gY]!='#')
        c = minPath(loc3, gY, pX, pY, maze);
        cout<<"s: "<<c<<endl;
    if(loc4<ColNum&&maze[gX][loc4]!='#')
        d = minPath(gX, loc4, pX, pY, maze);
        cout<<"d: "<<d<<endl;

    if(a<=b&&a<=c&&a<=d)
        {
            mini = 1;
            if(a==b)
            {
                if(hcost(loc1, gY, pX, pY, maze)<hcost(gX, loc2, pX, pY, maze))
                    mini = mini;
                else mini = 2;
            }
            if(a==c)
            {
                if(hcost(loc1, gY, pX, pY, maze)<hcost(loc3, gY, pX, pY, maze))
                    mini = mini;
                else mini = 3;
            }
            if(a==d)
            {
                if(hcost(loc1, gY, pX, pY, maze)<hcost(gX, loc4, pX, pY, maze))
                    mini = mini;
                else mini = 4;
            }

            return mini;
        }
    else if(b<=a&&b<=c&&b<=d)
        {
             mini = 2;
            if(b==a)
            {
                if(hcost(gX, loc2, pX, pY, maze)<hcost(loc1, gY, pX, pY, maze))
                    mini = mini;
                else mini = 1;
            }
            if(b==c)
            {
                if(hcost(gX, loc2, pX, pY, maze)<hcost(loc3, gY, pX, pY, maze))
                    mini = mini;
                else mini = 3;
            }
            if(b==d)
            {
                if(hcost(gX, loc2, pX, pY, maze)<hcost(gX, loc4, pX, pY, maze))
                    mini = mini;
                else mini = 4;
            }

            return mini;
        }
    else if(c<=a&&c<=b&&c<=d)
        {
            mini = 3;
            if(c==a)
            {
                if(hcost(loc3, gY, pX, pY, maze)<hcost(loc1, gY, pX, pY, maze))
                    mini = mini;
                else mini = 1;
            }
            if(b==c)
            {
                if(hcost(loc3, gY, pX, pY, maze)<hcost(gX, loc2, pX, pY, maze))
                    mini = mini;
                else mini = 2;
            }
            if(b==d)
            {
                if(hcost(loc3, gY, pX, pY, maze)<hcost(gX, loc4, pX, pY, maze))
                    mini = mini;
                else mini = 4;
            }

            return mini;
        }
    else if(d<=a&&d<=b&&d<=c)
        {
            mini = 4;
            if(d==a)
            {
                if(hcost(gX, loc4, pX, pY, maze)<hcost(loc1, gY, pX, pY, maze))
                    mini = mini;
                else mini = 1;
            }
            if(d==b)
            {
                if(hcost(gX, loc4, pX, pY, maze)<hcost(gX, loc2, pX, pY, maze))
                    mini = mini;
                else mini = 2;
            }
            if(d==c)
            {
                if(hcost(gX, loc4, pX, pY, maze)<hcost(loc3, gY, pX, pY, maze))
                    mini = mini;
                else mini = 3;
            }

            return mini;
        }
}

void addColumn(location *ghost, int *change, int *dead, int *foodToken, char maze[RowNum][ColNum+1])
{
    if(*change == 0)
    {
        if((ghost->column)>ColNum || maze[ghost->row][ghost->column+2] == '#'|| maze[ghost->row][ghost->column+2] == 'G')
        {}
        else
        {
            if(maze[ghost->row][ghost->column+2] == '@')
            {
                *dead = 1;
            }

            if(*foodToken)
            {
                maze[ghost->row][ghost->column] = '-';
            }
            else
            {
                maze[ghost->row][ghost->column] = ' ';
            }

            if(maze[ghost->row][ghost->column+2] == '-')
            {
                *foodToken = 1;
            }
            else
            {
                *foodToken = 0;
            }

            maze[ghost->row][ghost->column+2] = 'G';
            ghost->column = ghost->column+2;
            *change = 1;
        }
    }
}

void cutColumn(location *ghost, int *change, int *dead, int *foodToken, char maze[RowNum][ColNum+1])
{
    if(*change == 0)
    {
        if((ghost->column)>ColNum || maze[ghost->row][ghost->column-2] == '#'|| maze[ghost->row][ghost->column-2] == 'G')
        {}
        else
        {
            if(maze[ghost->row][ghost->column-2] == '@')
            {
                *dead = 1;
            }

            if(*foodToken)
            {
                maze[ghost->row][ghost->column] = '-';
            }
            else
            {
                maze[ghost->row][ghost->column] = ' ';
            }

            if(maze[ghost->row][ghost->column-2] == '-')
            {
                *foodToken = 1;
            }
            else
            {
                *foodToken = 0;
            }

            maze[ghost->row][ghost->column-2] = 'G';
            ghost->column = ghost->column-2;
            *change = 1;
        }
    }
}
void addRow(location *ghost, int *change, int *dead, int *foodToken, char maze[RowNum][ColNum+1])
{
    if(*change == 0)
    {
        if((ghost->row + 1)>RowNum || maze[ghost->row+1][ghost->column] == '#' || maze[ghost->row+1][ghost->column] == 'G')
        {}
        else
        {
            if(maze[ghost->row+1][ghost->column] == '@')
            {
                *dead = 1;
            }

            if(*foodToken)
            {
                maze[ghost->row][ghost->column] = '-';
            }
            else
            {
                maze[ghost->row][ghost->column] = ' ';
            }

            if(maze[ghost->row+1][ghost->column] == '-')
            {
                *foodToken = 1;
            }
            else
            {
                *foodToken = 0;
            }

            maze[ghost->row+1][ghost->column] = 'G';
            ghost->row = ghost->row+1;
            *change = 1;
        }
    }
}

void cutRow(location *ghost, int *change, int *dead, int *foodToken, char maze[RowNum][ColNum+1])
{
    if(*change == 0)
    {
        if((ghost->row - 1)>RowNum || maze[ghost->row-1][ghost->column] == '#' || maze[ghost->row-1][ghost->column] == 'G')
        {}
        else
        {
            if(maze[ghost->row-1][ghost->column] == '@')
            {
                *dead = 1;
            }

            if(*foodToken)
            {
                maze[ghost->row][ghost->column] = '-';
            }
            else
            {
                maze[ghost->row][ghost->column] = ' ';
            }

            if(maze[ghost->row-1][ghost->column] == '-')
            {
                *foodToken = 1;
            }
            else
            {
                *foodToken = 0;
            }

            maze[ghost->row-1][ghost->column] = 'G';
            ghost->row = ghost->row-1;
            *change = 1;
        }
    }
}

/*
Maze[0][] =  "###########################################################################";
            Maze[1][] =  "# - - G - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - G - - #";
            Maze[2][] =  "# - ########### - ########### - ############# - ########### - ######### - #";
            Maze[3][] =  "# - #         # - #         # - #           # - #         # - #       # - #";
            Maze[4][] =  "# - #         # - #         # - #           # - #         # - #       # - #";
            Maze[5][] =  "# - ########### - ########### - ############# - ########### - ######### - #";
            Maze[6][] =  "# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #";
            Maze[7][] = "# - ########### - ########### - ############# - ########### - ######### - #";
            Maze[8][] = "# - #         # - #         # - #           # - #         # - #       # - #";
            Maze[9][] = "# - #         # - #         # - #           # - #         # - #       # - #";
            Maze[10][] = "# - ########### - ########### - ############# - ########### - ######### - #";
            Maze[11][] = "# - - - - - - - - - - - - - - - - - - @ - - - - - - - - - - - - - - - - - #";
            Maze[12][] =  "# - ########### - ########### - ############# - ########### - ######### - #";
            Maze[13][] = "# - #         # - #         # - #           # - #         # - #       # - #";
            Maze[14][] = "# - #         # - #         # - #           # - #         # - #       # - #";
            Maze[15][] = "# - ########### - ########### - ############# - ########### - ######### - #";
            Maze[16][] = "# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #";
            Maze[17][] = "# - ########### - ########### - ############# - ########### - ######### - #";
            Maze[18][] = "# - #         # - #         # - #           # - #         # - #       # - #";
            Maze[19][] = "# - #         # - #         # - #           # - #         # - #       # - #";
            Maze[20][] = "# - ########### - ########### - ############# - ########### - ######### - #";
            Maze[21][] = "# - - G - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - G - - #";
            Maze[22][] = "###########################################################################";
            */
