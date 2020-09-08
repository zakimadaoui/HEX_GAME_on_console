#ifndef HEX_GRAPH_H
#define HEX_GRAPH_H
#include<vector>
#include<queue>
#include"node.h"

using namespace std;

class HEX_GRAPH
{
private:

    vector<node*>         nodes;
    priority_queue<node*> openSet;
    vector<node*>         closeSet;
    int                   size;
    state                 winner = state::EMPTY;
    state                 AIcolor = state::RED;
    state                 playerColor = state::BLUE;

//-------------------------------------------------------------------------------------
    void clearSets();
    bool isPathAvailable(node* node1, node* node2);

public:

    HEX_GRAPH  (int size);
    ~HEX_GRAPH ();

    void  printGraph();
    bool  playMove(int i, int j, state s);
    node* generateMCmove(int accuracy = 1000);

    // setters and getters
    void  setAIcolor(state s){this->AIcolor = s;}
    void  setPlayerColor(state s){this->playerColor = s;}
    state getAIcolor(){return AIcolor;}
    state getPlayerColor(){return playerColor;}
    state getWinner(){return winner;}

};

#endif // HEX_GRAPH_H
