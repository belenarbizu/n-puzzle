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

        virtual vector<int> actions(State state);
        virtual State result(State state, int action);
        virtual bool goal_test(State state);
        virtual float path_cost(State init_state, int action, State final_state);
};
