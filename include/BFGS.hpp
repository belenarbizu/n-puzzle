#pragma once

#include "Node.hpp"

template <typename State>
bool check_close(vector<Node<State> *> *close, Node<State> *current)
{
    return true;
}

template <typename State>
Node<State> *best_first_graph_search(Problem<State> *problem)
{
    vector<Node<State> *> frontier;
    vector<Node<State> *> close;

    Node<State> *init = new Node<State>(problem->init_state(), NULL, 0, 0);
    frontier.push_back(init);
    while (frontier.size())
    {
        //Sacamos el nodo que tenga menor coste
        Node<State> *current = frontier.back();
        frontier.pop_back();

        // Imprimir el estdao por depurar
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
            frontier.insert(frontier.begin(), children.begin(), children.end());
        }
    }
    //No tiene solucion
    return NULL;
}