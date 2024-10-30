#pragma once

#include "Node.hpp"
#include <queue>
#include <set>

#define A_STAR 1
#define GREEDY 2
#define UNIFORM_COST 3

typedef struct s_stats
{
    int nodes_selected;
    int nodes_represented;
} t_stats;

template <typename Comparator, typename State>
Node<State> *best_first_graph_search(Problem<State> *problem, t_stats *stats, float (*h)(State *s, State *e))
{
    std::priority_queue<Node<State> *, std::vector<Node<State> *>, Comparator > frontier;
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

        it = close.find(current);
        if (it != close.end())
        {
            if ((*it)->get_cost() > current->get_cost())
            {
                //delete *it;
                (*it)->set_parent(current->get_parent());
                (*it)->set_action(current->get_action());
                (*it)->set_cost(current->get_cost());
                //close.erase(it);
                //close.insert(current);
                delete current;
                current = *it;
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
            while (close.size())
            {
                delete *close.begin();
                close.erase(close.begin());
            }
            delete end;
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
            else
            {
                delete children[i];
            }
            i++;
        }
        children.clear();
    }
    delete end;
    return NULL;
}