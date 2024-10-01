#pragma once
using namespace std;

#include <iostream>
#include <vector>

template <typename State>
class Problem
{
    private:
        State goal;
    public:
        Problem();
        ~Problem();

        vector<int> &actions();
        State &result(State state, int action);
        bool goal_test(State state);
        float path_cost(State init_state, int action, State final_state);
};