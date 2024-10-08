#include "NPuzzle.hpp"
#include "Node.hpp"
#include "Problem.hpp"
using namespace std;

int main_1()
{
    int map[9] = {4, 5, 6, 1, 0, 2, 3, 7, 8};
    int map2[9] = {4, 5, 6, 1, 2, 0, 3, 7, 8};
    NPuzzleState puzzle(3, map);
    NPuzzleState puzzle2(3, map2);
    puzzle.print_map();
    puzzle2.print_map();
    if (puzzle == puzzle2)
        std::cout << "Iguales";
    else
        std::cout << "Diferentes";
    return 0;
}

template <typename State>
void this_is_a_fake_search_algorithm(Problem<State> *problem)
{
    // The algorithm only depends on the abstraction of the problem and the
    // state, therefore it can be used with any implementation of the problem.

    // Create the root node
    Node<State> *root = new Node<State>(problem->init_state(),
        NULL, 0, 0);

    // Expand the root node
    vector<Node<State> *> children = root->expand(problem);

    // Iterate children
    int i = 0;
    while (i < children.size())
    {
        std::cout << endl << "Action: " << children[i]->get_action()
            << ", Cost: " << children[i]->get_cost() << endl;

        // The print_map method is specific to the NPuzzleState, we don't care
        // because this is a fake algorithm just to ilustrate the abstraction.
        // In the real implementation of the algorithm we will only rely on
        // the methods exposed by the Problem interface.
        children[i]->get_state()->print_map();
        i++;
    }

    // Kill the father
    delete root;

    // Also kill the rest of the family
    i = 0;
    while (i < children.size())
    {
        delete children[i];
        i++;
    }
}

int main()
{
    // Create the starting state
    int map[9] = {1, 2, 3, 8, 0, 4, 7, 6, 5};
    NPuzzleState puzzle(3, map);

    // Create the problem.
    NPuzzleProblem problem(&puzzle, &puzzle);

    // Run the algorithm (It may return something)
    this_is_a_fake_search_algorithm(&problem);
}