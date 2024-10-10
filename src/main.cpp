#include "NPuzzle.hpp"
#include "Node.hpp"
#include "Problem.hpp"
#include "BFGS.hpp"
using namespace std;

int main()
{
    // Create the starting state
    int map[9] = {1, 2, 3, 8, 0, 4, 7, 6, 5};
    NPuzzleState puzzle(3, map);

    int map2[9] = {0, 2, 3, 1, 8, 4, 7, 6, 5};
    NPuzzleState puzzle2(3, map2);

    // Create the problem.
    NPuzzleProblem problem(&puzzle2, &puzzle);
    Node<NPuzzleState> *goal = best_first_graph_search(&problem);
    while (goal)
    {
        goal->get_state()->print_map();
        goal = goal->get_parent();
    }
    return 0;
}