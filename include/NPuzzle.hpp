#pragma once

#include <cstring>
#include <stdlib.h>
#include <time.h>
#include "Problem.hpp"

#define DOWN 1
#define UP 2
#define LEFT 3
#define RIGHT 4

class NPuzzleState
{
    private:
        int *map;
        int n;
        int p_x, p_y;
        void fill_map(int init, int n, int m);
    public:
        NPuzzleState();
        NPuzzleState(int n, int *map);
        NPuzzleState(int n);
        NPuzzleState(NPuzzleState &s);
        ~NPuzzleState();
        bool operator==(const NPuzzleState& puzzle);

        void _swap(int a, int b);
        int _index_of(int x, int y);
        void shuffle(int n);
        int get_n();
        int get(int x, int y);

        void move_up();
        void move_down();
        void move_left();
        void move_right();

        bool is_solvable(NPuzzleState *end);

        bool can_move_up();
        bool can_move_down();
        bool can_move_left();
        bool can_move_right();

        void print_map();
};

class NPuzzleProblem: public Problem<NPuzzleState>
{
    private:
        NPuzzleState *init;
        NPuzzleState *goal;
    public:
        NPuzzleProblem(NPuzzleState *init_state, NPuzzleState *final_state);
        ~NPuzzleProblem();

        vector<int> actions(NPuzzleState *state);
        NPuzzleState *result(NPuzzleState *state, int action);
        NPuzzleState *init_state();
        NPuzzleState *goal_state();
        bool goal_test(NPuzzleState *state);
        float path_cost(NPuzzleState *init_state, int action,
            NPuzzleState *final_state);
};