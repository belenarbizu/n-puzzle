#pragma once

#include "Node.hpp"
#include <queue>
#include <set>

typedef struct s_stats
{
    int nodes_selected;
    int nodes_represented;
} t_stats;

template <typename State>
Node<State> *best_first_graph_search(Problem<State> *problem, t_stats *stats, float (*h)(State *s, State *e))
{
    std::priority_queue<Node<State> *, std::vector<Node<State> *>, CompareNodes<State> > frontier;
    std::set<Node<State> *, EqualNodes<State> > close;
    State *end = problem->goal_state();
    typename std::set<Node<State> *>::iterator it;

    Node<State> *init = new Node<State>(problem->init_state(), NULL, 0, 0);
    init->set_h(h, end);
    frontier.push(init);
    while (frontier.size())
    {
        Node<State> *current = frontier.top();
        stats->nodes_selected += 1;
        frontier.pop();
        //close.insert(current);

        it = close.find(current);
        if (it != close.end())
        {
            if ((*it)->get_cost() > current->get_cost())
            {
                delete *it;
                close.erase(it);
                close.insert(current);
            }
            else
            {
                delete current;
                continue;
            }
        }
        if (problem->goal_test(current->get_state()))
        {
            stats->nodes_represented = frontier.size() + close.size();
            Node<State> *path = new Node<State>(*current);
            while (frontier.size())
            {
                Node<State> *n = frontier.top();
                delete n;
                frontier.pop();
            }
            /*while (close.size())
            {
                Node<State> *n = close.back();
                delete n;
                close.pop_back();
            }*/
            return path;
        }
        vector<Node<State> *> children = current->expand(problem);
        long unsigned int i = 0;
        while (i < children.size())
        {
            it = close.find(children[i]);
            if ((it != close.end() && (*it)->get_cost() > children[i]->get_cost()) || it == close.end())
            {
                children[i]->set_h(h, end);
                frontier.push(children[i]);
            }
            i++;
        }
    }
    return NULL;
}