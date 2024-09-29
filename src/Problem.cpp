#include "Problem.hpp"

Problem::Problem(State goal) {}

Problem::~Problem() {}

vector<int> &Problem::actions()
{
    return;
}

State &Problem::result(State state, int action)
{
    return;
}

bool Problem::goal_test(State state)
{
    return;
}

float Problem::path_cost(State init_state, int action, State final_state)
{
    return;
}