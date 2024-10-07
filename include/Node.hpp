using namespace std;
#pragma once

#include <iostream>
#include <vector>
#include "Problem.hpp"

template <typename State>
class Node
{
    private:
        State *state;
        Node<State> *parent;
        int action;
        float cost;
    public:
        Node(State *state, Node<State> *parent, int action, float cost);
        ~Node();

        State *get_state();
        vector<Node<State> > expand(Problem<State> *problem);
};

template <typename State>
Node<State>::Node(State *state, Node<State> *parent, int action, float cost)
{
    this->state = state;
    this->parent = parent;
    this->action = action;
    this->cost = cost;
}

template <typename State>
Node<State>::~Node()
{
    //delete this->state;
}

template <typename State>
State *Node<State>::get_state()
{
    return this->state;
}

template <typename State>
vector<Node<State> > Node<State>::expand(Problem<State> *problem)
{
    vector<Node<State> > result;
    // Use pointers in problem class
    vector<int> actions = problem->actions(this->state);

    int i = 0;
    while (i < actions.size())
    {
        State *new_state = problem->result(this->state, actions[i]);
        Node<State> new_node(
            new_state,
            this,
            actions[i],
            problem->path_cost(this->state, actions[i], new_state)
        );
        result.push_back(new_node);
        i++;
    }
    return result;
}