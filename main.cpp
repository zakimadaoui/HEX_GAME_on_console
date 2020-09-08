#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <assert.h>
#include "hex_graph.h"

using namespace std;

void clearConsole()
{
#if defined _WIN32
    system("cls");
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
#elif defined (__APPLE__)
    system("clear");
#endif
}


//######################################## Main ############################################
int main()
{

    int size;
    int choice;
    bool win = false;
    int counter = 0;

    srand(time(0));

    cout << "Enter the size of the borad (min 4): ";
    cin >> size;
    assert(size >=4);

    HEX_GRAPH g(size);// create graph object

    cout << "What color do you choose ? (BLUE: 1 ; RED: 2): ";
    cin>> choice;
    assert(choice == 1 || choice == 2);
    if(choice == 1){
        g.setPlayerColor(state::BLUE);
        g.setAIcolor(state::RED);

    }
    else{
        g.setPlayerColor(state::RED);
        g.setAIcolor(state::BLUE);
    }


    cout << "Who starts first ? (YOU: 1 ; AI: 2): ";
    cin>> choice;
    assert(choice == 1 || choice == 2);
    if(choice == 2) counter = 1;

    g.printGraph();

    while(!win){


        if(counter %2 == 0) {
            int i,j;
            cout << "Enter coordinates: " << endl;
            cin >> i >> j;
            cout << endl;
            clearConsole();
            win = g.playMove(i,j,g.getPlayerColor());
            g.printGraph();
        }
        else {

            //AI move
            clearConsole();
            node* AInode = g.generateMCmove();
            win = g.playMove(AInode->x,AInode->y,g.getAIcolor());
            g.printGraph();

        }


        if(win && g.getWinner() == g.getPlayerColor()) cout << " ##### You won! #####" << endl;
        if(win && g.getWinner() == g.getAIcolor()) cout << " ##### AI won, try harder! #####" << endl;
        counter++;
    }




    return 0;
}










