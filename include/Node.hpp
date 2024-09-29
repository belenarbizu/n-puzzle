using namespace std;
#pragma once

#include <iostream>
#include <vector>

class Node
{
    private:

    public:
        Node(State state, Node parent, int action, float cost);
        ~Node();

        vector<Node> expand(Problem problem);
}