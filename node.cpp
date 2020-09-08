#include "node.h"

//-------------------------------------------------------------------------------------
bool node::belongsTo(vector<node*> &nodes)
{
    for(node* n : nodes)
    {
        if(n == this) return true;
    }
    return false;
}
//-------------------------------------------------------------------------------------
bool node::belongsTo(priority_queue<node*>& q) //overloaded method for use with queues
{
    priority_queue<node*> copyQ = q;
    for(unsigned int i=0; i< copyQ.size(); i++)
    {
        if(this == copyQ.top()) return true;
        copyQ.pop();
    }
    return false;
}
//-------------------------------------------------------------------------------------
void node::increseScore()
{
    if(st == state::BLUE) blueScore++;
    else redScore++;
}
//-------------------------------------------------------------------------------------
void node::reset()
{
    blueScore = 0;
    redScore = 0;
    st = state::EMPTY;
}
