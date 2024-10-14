#pragma once

#include "Node.hpp"
#include <queue>

template <typename State>
bool check_close(vector<Node<State> *> *close, Node<State> *current)
{
    (void)close;
    (void)current;
    return true;
}

template <typename State>
Node<State> *best_first_graph_search(Problem<State> *problem)
{
    std::priority_queue<Node<State> *, std::vector<Node<State> *>, CompareNodes<State> > frontier;
    vector<Node<State> *> close;

    Node<State> *init = new Node<State>(problem->init_state(), NULL, 0, 0);
    frontier.push(init);
    while (frontier.size())
    {
        //Sacamos el nodo que tenga menor coste
        Node<State> *current = frontier.top();
        frontier.pop();

        // Imprimir el estado por depurar
        std::cout << endl << "Action: " << current->get_action()
            << ", Cost: " << current->get_cost() << endl;
        current->get_state()->print_map();

        //Se comprueba si es el goal test
        if (problem->goal_test(current->get_state()))
        {
            //Copiar la lista para eliminar todo el arbol
            return current;
        }
        if (check_close(&close, current))
        {
            vector<Node<State> *> children = current->expand(problem);
            long unsigned int i = 0;
            while (i < children.size())
            {
                frontier.push(children[i]);
                i++;
            }
        }
    }
    //No tiene solucion
    return NULL;
}