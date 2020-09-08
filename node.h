#ifndef NODE_H
#define NODE_H
#include<vector>
#include<queue>

using namespace std;

enum state :short{ RED, BLUE, EMPTY};

class node
{
public:
    int             x,y;
    state           st;
    vector<node*>   neighbors;
    int             blueScore = 0;
    int             redScore = 0;

//-------------------------------------------------------------------------------------
    node(int x,int y,state st):x(x),y(y),st(st){}
    bool belongsTo(vector<node*> &nodes);
    bool belongsTo(priority_queue<node*>& q);
    void increseScore();
    void reset();
};

template<state s>
struct compareNodes //struct for custom comparision to use in sort()
{
    inline bool operator() (node* n1,node* n2)
    {
        if(s == state::BLUE) return n1->blueScore > n2->blueScore;
        else return n1->redScore > n2->redScore;

    }
};

#endif // NODE_H
