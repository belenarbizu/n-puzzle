#include "NPuzzle.hpp"
#include "Node.hpp"
#include "Problem.hpp"
#include "BFGS.hpp"
#include <fstream>
using namespace std;


int print_states(Node<NPuzzleState> *goal)
{
    if (goal)
    {
        int n = print_states(goal->get_parent());
        switch (goal->get_action())
        {
            case UP:
                std::cout << " ↑" << std::endl;
                break;
            case DOWN:
                std::cout << " ↓" << std::endl;
                break;
            case LEFT:
                std::cout << " ←" << std::endl;
                break;
            case RIGHT:
                std::cout << " →" << std::endl;
                break;
        }
        goal->get_state()->print_map();
        return n + 1;
    }
    return -1;
}

int main(int argc, char **argv)
{
    if (argc == 2)
    {
        ifstream file(argv[1], ifstream::in);
        file.close();
    }
    else
    {
        // Create the starting state
        int map[9] = {1, 2, 3, 8, 0, 4, 7, 6, 5};
        NPuzzleState puzzle(3, map);

        int map2[9] = {0, 2, 3, 1, 8, 4, 7, 6, 5};
        NPuzzleState puzzle2(3, map2);

        puzzle2.shuffle(20);

        t_stats stats = {0, 0};

        // Create the problem.
        NPuzzleProblem problem(&puzzle2, &puzzle);
        Node<NPuzzleState> *goal = best_first_graph_search(&problem, &stats);
        Node<NPuzzleState> *copy = goal;
        int moves = print_states(copy);
        std::cout << "Nodes represented: " << stats.nodes_represented << endl;
        std::cout << "Nodes selected: " << stats.nodes_selected << endl;
        std::cout << moves << " moves";
        goal = copy;
        while (goal)
        {
            Node<NPuzzleState> *parent = goal->get_parent();
            delete goal;
            goal = parent;
        }
    }
    return 0;
}