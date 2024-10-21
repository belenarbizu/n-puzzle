#include "NPuzzle.hpp"
#include "Node.hpp"
#include "Problem.hpp"
#include "BFGS.hpp"
#include <fstream>
#include <math.h>
#include <sstream>
#include <set>
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
    std::string input;
    int number = 0;

    cout << "Choose between these heuristic functions:" << endl;
    cout << "1.Manhattan distance" << endl;
    cout << "2.Euclidean distance" << endl;
    cout << "3.Hamming distance" << endl;
    cout << "Write 1, 2 or 3: ";
    cin >> input;

    int read = std::sscanf(input.c_str(), "%d", &number);

    while (!read || (number != 1 && number != 2 && number != 3))
    {
        cout << "Write 1, 2 or 3: ";
        cin >> input;

        read = std::sscanf(input.c_str(), "%d", &number);
    }

    return number;
}

int input_size()
{
    std::string input;
    int number = 0;

    cout << "What size do you want your puzzle to be?" << endl;
    cout << "Write a number between 3 and 20: ";
    cin >> input;

    int read = std::sscanf(input.c_str(), "%d", &number);

    while (!read || number < 3 || number > 20)
    {
        cout << "Write a number between 3 and 20: ";
        cin >> input;

        read = std::sscanf(input.c_str(), "%d", &number);
    }

    return number;
}

int input_shuffle()
{

    std::string input;
    int number = 0;

    cout << "How many times do you want to shuffle your puzzle?" << endl;
    cout << "Write a number between 1 and 50: ";
    cin >> input;

    int read = std::sscanf(input.c_str(), "%d", &number);

    while (!read || number < 1 || number > 50)
    {
        cout << "Write a number between 1 and 50: ";
        cin >> input;

        read = std::sscanf(input.c_str(), "%d", &number);
    }
    return number;
}

int size_puzzle(ifstream &file)
{
    int size = 0;
    int read = 0;
    string line;
    while (getline(file, line)) {
        if (line[0] == '#')
            continue;
        size_t pos = line.find('#');
        if (pos != string::npos)
        {
            line = line.substr(0, pos);
        }
        int count = 0;
        for (size_t i = 0; i < line.length(); i++)
        {
            if (line[i] >= '0' && line[i] <= '9')
            {
                count = 0;
            }
            else if (line[i] != ' ')
            {
                count++;
            }
        }
        if (count == 0)
        {
            read = sscanf(line.c_str(), "%d", &size);
        }
        if (read == 0)
        {
            cout << "Error. The file doesn't have the size of the puzzle." << endl;
            exit(EXIT_FAILURE);
        }
        else if (size < 3 || size > 20)
        {
            cout << "Error. The size has to be between 3 and 20." << endl;
            exit(EXIT_FAILURE);
        }
        else
        {
            break;
        }
    }
    return size;
}

vector<int> read_puzzle(ifstream &file)
{
    vector<int> puzzle;
    string line;
    while (getline(file, line)) {
        if (line[0] == '#')
            continue;
        size_t pos = line.find('#');
        if (pos != string::npos)
        {
            line = line.substr(0, pos);
        }
        for (size_t i = 0; i < line.length(); i++)
        {
            if (line[i] != ' ' && (line[i] < 48 || line[i] > 57))
            {
                cout << "Error. The puzzle has to be only numbers." << endl;
                exit(EXIT_FAILURE);
            }
        }
        stringstream ss(line);
        int number;
        while (ss >> number) {
            puzzle.push_back(number);
        }
    }
    if (puzzle.empty())
    {
        cout << "Error. The file doesn't have a puzzle." << endl;
        exit(EXIT_FAILURE);
    }
    return puzzle;
}

void error_puzzle(vector<int> puzzle, int size)
{
    set<int> unique_num;
    int max_num = size * size - 1;
    unsigned int puzzle_size = size * size;
    for (size_t i = 0; i < puzzle.size(); i++)
    {
        if (puzzle[i] < 0 || puzzle[i] > max_num)
        {
            cout << "Error. Wrong numbers" << endl;
            exit(EXIT_FAILURE);            
        }
        if (!(unique_num.insert(puzzle[i]).second))
        {
            cout << "Error. Duplicated numbers" << endl;
            exit(EXIT_FAILURE);
        }
    }
    if (puzzle.size() != puzzle_size)
    {
        cout << "Error. The size of the puzzle is wrong" << endl;
        exit(EXIT_FAILURE);
    }
}

NPuzzleState *error_file(char *filename)
{
    ifstream file;
    file.open(filename);
    if (!file.is_open())
    {
        cout << "Error. Can't open the file." << endl;
        exit(EXIT_FAILURE);
    }
    else if (file.peek() == EOF)
    {
        cout << "Error. The file is empty" << endl;
        exit(EXIT_FAILURE);
    }
    int size = size_puzzle(file);
    vector<int> puzzle = read_puzzle(file);
    error_puzzle(puzzle, size);
    file.close();
    return new NPuzzleState(size, puzzle.data());
}


int main(int argc, char **argv)
{
    NPuzzleState *start;
    NPuzzleState *goal;
    NPuzzleProblem *problem;

    if (argc == 2)
    {
        start = error_file(argv[1]);
    }
    else
    {
        int puzzle_size = input_size();
        start = new NPuzzleState(puzzle_size);
        int puzzle_shuffle = input_shuffle();
        start->shuffle(puzzle_shuffle*10);
    }
        int heuristic = print_input();
        goal = new NPuzzleState(start->get_n());
        start->print_map();
        goal->print_map();
        t_stats stats = {0, 0};
        problem = new NPuzzleProblem(start, goal);

        if (heuristic == 1)
        {
            Node<NPuzzleState> *goal = best_first_graph_search(problem, &stats, manhattan_distance);
            int moves = print_states(goal);
            std::cout << "Nodes represented: " << stats.nodes_represented << endl;
            std::cout << "Nodes selected: " << stats.nodes_selected << endl;
            std::cout << moves << " moves";
            while (goal)
            {
                Node<NPuzzleState> *parent = goal->get_parent();
                delete goal;
                goal = parent;
            }
        }
        else if (heuristic == 2)
        {
            Node<NPuzzleState> *goal = best_first_graph_search(problem, &stats, euclidean_distance);
            int moves = print_states(goal);
            std::cout << "Nodes represented: " << stats.nodes_represented << endl;
            std::cout << "Nodes selected: " << stats.nodes_selected << endl;
            std::cout << moves << " moves";
            while (goal)
            {
                Node<NPuzzleState> *parent = goal->get_parent();
                delete goal;
                goal = parent;
            }
        }
        else if (heuristic == 3)
        {
            Node<NPuzzleState> *goal = best_first_graph_search(problem, &stats, hamming_distance);
            int moves = print_states(goal);
            std::cout << "Nodes represented: " << stats.nodes_represented << endl;
            std::cout << "Nodes selected: " << stats.nodes_selected << endl;
            std::cout << moves << " moves";
            while (goal)
            {
                Node<NPuzzleState> *parent = goal->get_parent();
                delete goal;
                goal = parent;
            }
        }
    return 0;
}