#pragma once
using namespace std;

#include <iostream>
#include <vector>

template <typename State>
class Problem
{
    public:
        Problem();
        ~Problem();

        virtual vector<int> actions(State *state) = 0;
        virtual State *result(State *state, int action) = 0;
        virtual State *init_state() = 0;
        virtual bool goal_test(State *state) = 0;
        virtual float path_cost(State *init_state, int action,
            State *final_state) = 0;
};

template <typename State>
Problem<State>::Problem() {}

template <typename State>
Problem<State>::~Problem() {}

/*
template <typename State>
vector<int> Problem<State>::actions(State *state)
{
    return {};
}

template <typename State>
State *Problem<State>::result(State *state, int action)
{
    return NULL;
}

template <typename State>
State *Problem<State>::init_state()
{
    return NULL;
}

template <typename State>
bool Problem<State>::goal_test(State *state)
{
    return false;
}

template <typename State>
float Problem<State>::path_cost(State *init_state, int action, State *final_state)
{
    return 0.0f;
}*/
