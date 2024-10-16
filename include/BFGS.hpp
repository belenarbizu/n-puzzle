#pragma once

#include "Node.hpp"
#include <queue>

typedef struct s_stats
{
    int nodes_selected;
    int nodes_represented;
} t_stats;

template <typename State>
Node<State> *best_first_graph_search(Problem<State> *problem, t_stats *stats, float (*h)(State *s, State *e))
{
    std::priority_queue<Node<State> *, std::vector<Node<State> *>, CompareNodes<State> > frontier;
    vector<Node<State> *> close;
    State *end = problem->goal_state();

    Node<State> *init = new Node<State>(problem->init_state(), NULL, 0, 0);
    init->set_h(h, end);
    frontier.push(init);
    while (frontier.size())
    {
        Node<State> *current = frontier.top();
        stats->nodes_selected += 1;
        frontier.pop();
        close.push_back(current);

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
            while (close.size())
            {
                Node<State> *n = close.back();
                delete n;
                close.pop_back();
            }
            return path;
        }
        vector<Node<State> *> children = current->expand(problem);
        long unsigned int i = 0;
        while (i < children.size())
        {
            children[i]->set_h(h, end);
            frontier.push(children[i]);
            i++;
        }
    }
    return NULL;
}