#include "../include/NPuzzle.hpp"
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

int main()
{
    int map[9] = {1, 2, 3, 8, 0, 4, 7, 6, 5};
    NPuzzleState puzzle(3, map);
    NPuzzleProblem problem(puzzle, puzzle);
    vector<int> actions = problem.actions(puzzle);
    int i = 0;
    while (i < actions.size())
    {
        std::cout << actions[i];
        i++;
    }
}