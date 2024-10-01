#pragma once

#include <cstring>
#include "Problem.hpp"

class NPuzzleState
{
    private:
        int *map;
        int n;
        int p_x, p_y;

    public:
        NPuzzleState(int n, int *map);
        NPuzzleState(NPuzzleState &s);

        void _swap(int a, int b);
        int _index_of(int x, int y);

        void move_up();
        void move_down();
        void move_left();
        void move_right();
};

class NPuzzleProblem: Problem<NPuzzleState>
{

};