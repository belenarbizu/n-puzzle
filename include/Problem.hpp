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

template <typename State>
Problem<State>::Problem() {}

template <typename State>
Problem<State>::~Problem() {}

template <typename State>
vector<int> Problem<State>::actions(State state)
{
    return {};
}

template <typename State>
State Problem<State>::result(State state, int action)
{
    return state;
}

template <typename State>
bool Problem<State>::goal_test(State state)
{
    return false;
}

template <typename State>
float Problem<State>::path_cost(State init_state, int action, State final_state)
{
    return 0.0f;
}