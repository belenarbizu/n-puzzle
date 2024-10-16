#include "NPuzzle.hpp"
#include "Node.hpp"
#include "Problem.hpp"
#include "BFGS.hpp"
#include <fstream>
#include <math.h>
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

float heuristico_tonto(NPuzzleState *s, NPuzzleState *e)
{
    (void) s;
    (void) e;
    return 0;
}

float manhattan_distance(NPuzzleState *s, NPuzzleState *e)
{
    float distance = 0;

    for (int row_s = 0; row_s < s->get_n(); row_s ++)
    {
        for (int col_s = 0; col_s < s->get_n(); col_s ++)
        {
            int value_s = s->get(col_s, row_s);

            if (value_s == 0)
                continue;

            for (int row_e = 0; row_e < s->get_n(); row_e ++)
            {
                for (int col_e = 0; col_e < s->get_n(); col_e ++)
                {
                    int value_e = e->get(col_e, row_e);

                    if (value_e == value_s)
                    {
                        distance += std::abs(row_s - row_e);
                        distance += std::abs(col_s - col_e);
                    }
                }
            }
        }
    }

    return distance;
}

float euclidean_distance(NPuzzleState *s, NPuzzleState *e)
{
    float distance = 0;

    for (int row_s = 0; row_s < s->get_n(); row_s ++)
    {
        for (int col_s = 0; col_s < s->get_n(); col_s ++)
        {
            int value_s = s->get(col_s, row_s);

            if (value_s == 0)
                continue;

            for (int row_e = 0; row_e < s->get_n(); row_e ++)
            {
                for (int col_e = 0; col_e < s->get_n(); col_e ++)
                {
                    int value_e = e->get(col_e, row_e);

                    if (value_e == value_s)
                    {
                        float row_value = (row_s - row_e) * (row_s - row_e);
                        float col_value = (col_s - col_e) * (col_s - col_e);
                        distance += sqrt(row_value + col_value);
                    }
                }
            }
        }
    }

    return distance;
}

float hamming_distance(NPuzzleState *s, NPuzzleState *e)
{
    float distance = 0;

    for (int row_s = 0; row_s < s->get_n(); row_s ++)
    {
        for (int col_s = 0; col_s < s->get_n(); col_s ++)
        {
            int value_s = s->get(col_s, row_s);
            int value_e = e->get(col_s, row_s);

            if (value_s == 0)
                continue;

            if (value_e != value_s)
            {
                distance += 1;
            }
        }
    }

    return distance;
}

int print_input()
{
    char number;
    cout << "Choose between these heuristic functions:" << endl;
    cout << "1. " << endl;
    cout << "2. " << endl;
    cout << "3. " << endl;
    cout << "Write 1, 2 or 3: ";
    cin >> number;
    int hfn = int(number);
    while (hfn < 49 || hfn > 51)
    {
        cout << "Write 1, 2 or 3: ";
        cin >> number;
        hfn = int(number);
    }
    return hfn;
}

int input_size()
{
    char number;
    cout << "What size do you want your puzzle to be?" << endl;
    cout << "Write a number between 3 and 20: ";
    cin >> number;
    int size = number - '0';
    while (size < 3 || size > 20)
    {
        cout << "Write a number between 3 and 20: ";
        cin >> number;
        size = number - '0';
    }
    return size;
}

int input_shuffle()
{
    int number;
    cout << "How many times do you want to shuffle your puzzle?" << endl;
    cout << "Write a number between 1 and 50: ";
    cin >> number;
    int shuffle = number ;
    cout << shuffle << endl;
    while (shuffle < 1 || shuffle > 50)
    {
        cout << "Write a number between 1 and 50: ";
        cin >> number;
        shuffle = number - '0';
    }
    return shuffle;
}

void error_file(char *filename)
{
    ifstream file;
    file.open(filename);
    if (!file.is_open())
    {
        //Error abriento el archivo
    }
    else
    {
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    }
}

int main(int argc, char **argv)
{
    if (argc == 2)
    {
        error_file(argv[1]);
    }
    else
    {
        int heuristic = print_input();
        int puzzle_size = input_size();
        int puzzle_shuffle = input_shuffle();
        switch (heuristic)
        {
        case 49:
            /* hf 1 */
            break;
        case 50:
            /* hf 2 */
            break;
        case 51:
            /* hf 3 */
            break;
        default:
            break;
        }

        // Create the starting state
        //int map[9] = {1, 2, 3, 8, 0, 4, 7, 6, 5};
        NPuzzleState puzzle(puzzle_size);

        //int map2[9] = {0, 2, 3, 1, 8, 4, 7, 6, 5};
        NPuzzleState puzzle2(puzzle_size);

        puzzle2.shuffle(puzzle_shuffle);

        t_stats stats = {0, 0};

        // Create the problem.
        NPuzzleProblem problem(&puzzle2, &puzzle);
        Node<NPuzzleState> *goal = best_first_graph_search(&problem, &stats, manhattan_distance);
        //int moves = print_states(goal);
        std::cout << "MANHATTAN: " << endl;
        std::cout << "Nodes represented: " << stats.nodes_represented << endl;
        std::cout << "Nodes selected: " << stats.nodes_selected << endl;
        //std::cout << moves << " moves";
        while (goal)
        {
            Node<NPuzzleState> *parent = goal->get_parent();
            delete goal;
            goal = parent;
        }

        stats = {0, 0};
        goal = best_first_graph_search(&problem, &stats, euclidean_distance);
        std::cout << "EUCLIDEAN: " << endl;
        std::cout << "Nodes represented: " << stats.nodes_represented << endl;
        std::cout << "Nodes selected: " << stats.nodes_selected << endl;
        while (goal)
        {
            Node<NPuzzleState> *parent = goal->get_parent();
            delete goal;
            goal = parent;
        }

        stats = {0, 0};
        goal = best_first_graph_search(&problem, &stats, hamming_distance);
        std::cout << "HAMMING: " << endl;
        std::cout << "Nodes represented: " << stats.nodes_represented << endl;
        std::cout << "Nodes selected: " << stats.nodes_selected << endl;
        while (goal)
        {
            Node<NPuzzleState> *parent = goal->get_parent();
            delete goal;
            goal = parent;
        }

        stats = {0, 0};
        goal = best_first_graph_search(&problem, &stats, heuristico_tonto);
        std::cout << "TONTO: " << endl;
        std::cout << "Nodes represented: " << stats.nodes_represented << endl;
        std::cout << "Nodes selected: " << stats.nodes_selected << endl;
        while (goal)
        {
            Node<NPuzzleState> *parent = goal->get_parent();
            delete goal;
            goal = parent;
        }
    }
    return 0;
}