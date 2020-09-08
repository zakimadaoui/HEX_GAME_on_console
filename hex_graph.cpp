#include <iostream>
#include <algorithm>
#include <cassert>
#include "hex_graph.h"
#include "node.h"

using namespace std;


void printDirections(){

    cout << "           RED       " << endl;
    cout << "           /         " << endl;
    cout << "BLUE <---------> BLUE" << endl;
    cout << "         /           " << endl;
    cout << "       RED           " << endl;
    cout <<  endl;
    cout <<  endl;

}

HEX_GRAPH::HEX_GRAPH(int size){

    this->size = size;
    //1- create an empty graph
    for(int i = 0 ; i< size ; i++ )
    {
        for(int j = 0 ; j< size ; j++ )
        {
            nodes.push_back(new node(i,j,state::EMPTY));
        }
    }

    //2- determin neighbors for each node, we have 9 cases
    for(int i = 0 ; i< size ; i++ )
    {
        for(int j = 0 ; j< size ; j++ )
        {

            int pos = i*size + j; //node position

            if       (i == 0 && j == 0){//top left
                nodes[pos]->neighbors.push_back(nodes[pos+1]); //next node
                nodes[pos]->neighbors.push_back(nodes[(i+1)*size +j]); // node below
            }
            else if  (i == 0 && j == size-1){//top right
                nodes[pos]->neighbors.push_back(nodes[pos-1]); //previous node
                nodes[pos]->neighbors.push_back(nodes[(i+1)*size +j]); // node below
                nodes[pos]->neighbors.push_back(nodes[(i+1)*size +j -1]); //previous to node below
            }
            else if  (i == size-1 && j == 0){//bottom left
                nodes[pos]->neighbors.push_back(nodes[pos+1]); //next node
                nodes[pos]->neighbors.push_back(nodes[(i-1)*size +j]); // node above
                nodes[pos]->neighbors.push_back(nodes[(i-1)*size +j+1]); //next to node above
            }
            else if  (i == size-1 && j == size-1){//bottom right
                nodes[pos]->neighbors.push_back(nodes[pos-1]); //prev node
                nodes[pos]->neighbors.push_back(nodes[(i-1)*size +j]); // node above
            }
            else if  (i== 0){//top edge
                nodes[pos]->neighbors.push_back(nodes[pos+1]); //next node
                nodes[pos]->neighbors.push_back(nodes[pos-1]); //previous node
                nodes[pos]->neighbors.push_back(nodes[(i+1)*size +j]); // node below
                nodes[pos]->neighbors.push_back(nodes[(i+1)*size +j -1]); //previous to node below
            }
            else if  (j== 0){//left edge
                nodes[pos]->neighbors.push_back(nodes[pos+1]); //next node
                nodes[pos]->neighbors.push_back(nodes[(i-1)*size +j]); // node above
                nodes[pos]->neighbors.push_back(nodes[(i-1)*size +j+1]); //next to node above
                nodes[pos]->neighbors.push_back(nodes[(i+1)*size +j]); // node below
            }
            else if  (j== size -1){//right edge
                nodes[pos]->neighbors.push_back(nodes[pos-1]); //previous node
                nodes[pos]->neighbors.push_back(nodes[(i-1)*size +j]); // node above
                nodes[pos]->neighbors.push_back(nodes[(i+1)*size +j]); // node below
                nodes[pos]->neighbors.push_back(nodes[(i+1)*size +j -1]); //previous to node below
            }
            else if  (i== size -1){//bottom edge
                nodes[pos]->neighbors.push_back(nodes[pos+1]); //next node
                nodes[pos]->neighbors.push_back(nodes[pos-1]); //prev node
                nodes[pos]->neighbors.push_back(nodes[(i-1)*size +j]); // node above
                nodes[pos]->neighbors.push_back(nodes[(i-1)*size +j+1]); // next to node above
            }
            //todo: add for edges too
            else{//nodes in middle of the graph
                nodes[pos]->neighbors.push_back(nodes[pos+1]);//next node
                nodes[pos]->neighbors.push_back(nodes[pos-1]);//prev node
                nodes[pos]->neighbors.push_back(nodes[(i+1)*size +j]);// node below
                nodes[pos]->neighbors.push_back(nodes[(i+1)*size +j -1]);//previous to node below
                nodes[pos]->neighbors.push_back(nodes[(i-1)*size +j]);// node above
                nodes[pos]->neighbors.push_back(nodes[(i-1)*size +j +1]);// next to node above
            }
        }
    }
}

//-------------------------------------------------------------------------------------
HEX_GRAPH::~HEX_GRAPH(){//deallocate memory after finishing
    for(node* n: nodes) delete n;
}
//-------------------------------------------------------------------------------------

void HEX_GRAPH::printGraph()
{

    printDirections();

    string connections = "\\ ";
    string spaces = "";
    for(int i = 0; i< size-1; i++){
        connections+="/ \\ ";
    }

    for(int i = 0 ; i< size ; i++ ){
        cout << spaces;
        for(int j = 0 ; j< size ; j++ ){
            string node_state = "*";
            if(nodes[i*size + j]->st == state::RED) node_state = "R";
            else if(nodes[i*size + j]->st == state::BLUE) node_state = "B";

            cout << node_state;
            if(j != (size-1)) cout << " - ";
        }
        cout << endl;
        spaces += " ";
        if(i != size-1) cout << spaces << connections << endl;
        spaces += " ";

    }
    cout << endl;
}
//-------------------------------------------------------------------------------------
bool HEX_GRAPH::playMove(int i, int j, state s)
{

    /*
         * after move is played,
         *  check: if hexes from same color exist on both corresponding edges
         *      check whether there is a path between each same colored point
         *      from one edge with another one in the other edge. whenerver a path
         *      is available return true, and a player wins
         *
         *      else return false, and the game continues
         */

    assert(i< size && j< size);

    int pos = i*size +j;
    if(nodes[pos]->st == state::EMPTY && (i< size && j< size)) { //if node is not used already, then use it
        nodes[pos]->st = s;
        vector<node*> rightEdgeList;
        vector<node*> leftEdgeList;
        vector<node*> topEdgeList;
        vector<node*> bottomEdgeList;

        //remember rules:
        /* top and bottom  edge are RED
             * right and left edges are blue
             */

        for(int i =0; i< size; i++)
        {
            for(int j =0; j< size; j++)
            {
                if(i == 0 && nodes[i*size +j]->st == state::RED) topEdgeList.push_back(nodes[i*size +j]);
                if(i == size-1 && nodes[i*size +j]->st == state::RED) bottomEdgeList.push_back(nodes[i*size +j]);
                if(j == 0 && nodes[i*size +j]->st == state::BLUE) leftEdgeList.push_back(nodes[i*size +j]);
                if(j == size-1 && nodes[i*size +j]->st == state::BLUE) rightEdgeList.push_back(nodes[i*size +j]);
            }
        }


        if (s == state::RED && !topEdgeList.empty() && !bottomEdgeList.empty())
        {
            for(node* nt: topEdgeList)
            {
                for(node* nb : bottomEdgeList)
                {
                    if(isPathAvailable(nt,nb)) {
                        winner = state::RED;
                        clearSets();// do not forget to clear sets after exploring a path
                        return true;
                    }
                    clearSets();// do not forget to clear sets after exploring a path
                }
            }
        }

        if (s == state::BLUE && !rightEdgeList.empty() && !leftEdgeList.empty())
        {
            for(node* nr: rightEdgeList)
            {
                for(node* nl : leftEdgeList)
                {
                    if(isPathAvailable(nr,nl)) {
                        winner = state::BLUE;
                        clearSets();// do not forget to clear sets after exploring a path
                        return true;
                    }
                    clearSets();// do not forget to clear sets after exploring a path
                }
            }
        }
    }
    else{
        printGraph();
        int i2,j2;
        cout << "invalid move !" << endl;
        cout << "Enter other coordinates: "  << endl;
        cin >> i2>> j2;
        return playMove(i2,j2,s); // recurse till move is correct
    }


    return false;
}
//-------------------------------------------------------------------------------------

node* HEX_GRAPH::generateMCmove(int accuracy)//generate a more using monty carlo technique
{

    /*
         * put avilable moves in a list (a node has two scores one for red and one for blue) **
         * shuffle list**
         * fill half with blue, half with red (+1 depends on first player)
         * check for path
         * increase winner score
         * after 1000 iteratons take move with highest winning score in AI color
         * reset All scores to 0
         * return chosen move
         *
         */

    vector<node*> availableNodes;
    for(auto n: nodes) if(n->st == state::EMPTY) availableNodes.push_back(n);

    if(availableNodes.size() == 1) return availableNodes[0]; // game ended, no need to compute

    for(int i = 0; i< accuracy; i++)// make 1000 or more iterations to get a good probability
    {
        random_shuffle(availableNodes.begin(),availableNodes.end()); //shuffle

        for(unsigned int j = 0; j<availableNodes.size(); j++)// fill with colors
        {
            if(j<(availableNodes.size()/2) ) availableNodes[j]->st = AIcolor;
            else availableNodes[j]->st = playerColor;
        }


        //check for a path
        vector<node*> rightEdgeList;
        vector<node*> leftEdgeList;
        for(int i =0; i< size; i++){// get blue hexes on both edges
            for(int j =0; j< size; j++){
                if(j == 0 && nodes[i*size +j]->st == state::BLUE) leftEdgeList.push_back(nodes[i*size +j]);
                if(j == size-1 && nodes[i*size +j]->st == state::BLUE) rightEdgeList.push_back(nodes[i*size +j]);
            }
        }


        bool pathfound = false; //path from west to south found or not?
        for(node* nr: rightEdgeList){
            for(node* nl : leftEdgeList){
                if(isPathAvailable(nr,nl)) {
                    pathfound = true;
                    clearSets();// do not forget to clear sets after exploring a path
                    break;
                }
                clearSets();// do not forget to clear sets after exploring a path
            }
            if(pathfound) break;
        }


        if(pathfound){// blue wins
            for(auto n : availableNodes)
                if(n->st == BLUE) n->increseScore();
        }
        else{// blue looses, so red must be the winner
            for(auto n : availableNodes)
                if(n->st == RED) n->increseScore();
        }
    }




    node* bestNode;
    //sort nodes such that the one with the highest score is on top
    if(AIcolor == BLUE) sort(availableNodes.begin(), availableNodes.end(), compareNodes<BLUE>());
    else sort(availableNodes.begin(), availableNodes.end(), compareNodes<RED>());

    //retrieve node with highest score
    bestNode = availableNodes[0];

    // reset to state before prob calculation
    for(auto n : availableNodes) n->reset();

    return bestNode;
}


bool HEX_GRAPH::isPathAvailable(node* node1, node* node2)
{
    /* Algo
     * 1- add current node to close set
     * 2- look for same color neigbors that are not in close set nor in open
     * 3- if finish node is a neigbor a player won and a path is available, so return true
     * 4- else add neigbors to openSet
     * 5- if openset empty return false
     * 6- else take first element from open set,
     * 7 - pop it and findpath from that node to finish
     */


    closeSet.push_back(node1);

    for(node* n: node1->neighbors) //populate open set
    {
        if(n == node2) return true; // path found! a player won!
        if(n->st == node1->st && !n->belongsTo(openSet) && !n->belongsTo(closeSet)){
            openSet.push(n);// add to open set if it is not in there or not in close set
        }
    }
    if(openSet.size() == 0)
        return false; //no path found
    else{//explore nodes in open set
        node* temp = openSet.top();
        openSet.pop();
        return isPathAvailable(temp, node2);
    }
}

void HEX_GRAPH::clearSets()
{
    closeSet.clear();
    while(!openSet.empty())openSet.pop();
}
