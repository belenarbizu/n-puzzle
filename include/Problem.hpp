using namespace std;
#pragma once

#include <iostream>
#include <vector>

template <typename State>
class Problem
{
    private:
        State goal;
    public:
        Problem(State goal);
        ~Problem();

        vector<int> &actions();
        State &result(State state, int action);
        bool goal_test(State state);
        float path_cost(State init_state, int action, State final_state);
};

class NPuzzleProblem : Problem<MiEstado>
{
 ...
};

Problem<MiEstado> p = new NPuzzleProblem;