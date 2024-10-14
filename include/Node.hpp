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
        int get_action();
        float get_cost();
        Node<State> *get_parent();
        vector<Node<State> *> expand(Problem<State> *problem);
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
    delete this->state;
}

template <typename State>
State *Node<State>::get_state()
{
    return this->state;
}

template <typename State>
int Node<State>::get_action()
{
    return this->action;
}

template <typename State>
float Node<State>::get_cost()
{
    return this->cost;
}

template <typename State>
Node<State> *Node<State>::get_parent()
{
    return this->parent;
}

template <typename State>
vector<Node<State> *> Node<State>::expand(Problem<State> *problem)
{
    vector<Node<State> *> result;
    vector<int> actions = problem->actions(this->state);

    long unsigned int i = 0;
    while (i < actions.size())
    {
        State *new_state = problem->result(this->state, actions[i]);
        Node<State> *new_node = new Node<State>(
            new_state,
            this,
            actions[i],
            this->cost + problem->path_cost(this->state, actions[i], new_state)
        );
        result.push_back(new_node);
        i++;
    }
    return result;
}

template <typename State>
class CompareNodes
{
    public:
        bool operator() (Node<State> *a, Node<State> *b)
        {
            //Hay que sumar a->h y b->h
            return a->get_cost() > b->get_cost();
        }
};