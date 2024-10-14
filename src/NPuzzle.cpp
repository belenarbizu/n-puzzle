#include "NPuzzle.hpp"

NPuzzleState::NPuzzleState(int n, int *map)
{
    this->n = n;
    this->map = new int[n * n];
    memcpy(this->map, map, sizeof(int) * n * n);
    int i = 0;
    while (i < n * n)
    {
        if (map[i] == 0)
        {
            this->p_x = i % 3;
            this->p_y = i / 3;
        }
        i++;
    }
}

NPuzzleState::NPuzzleState(NPuzzleState &s)
{
    this->n = s.n;
    this->map = new int[this->n * this->n];
    std::memcpy(this->map, s.map, sizeof(int) * this->n * this->n);
    this->p_x = s.p_x;
    this->p_y = s.p_y;
}

NPuzzleState::NPuzzleState()
{
    n = 0;
    map = nullptr;
    p_x = 0;
    p_y = 0;
}

NPuzzleState::~NPuzzleState()
{
    delete[] map;
}

bool NPuzzleState::operator==(const NPuzzleState& puzzle)
{
    for (int row = 0; row < this->n; row++)
    {
        for (int col = 0; col < this->n; col++)
        {
            if (!(this->map[this->_index_of(col, row)]
                == puzzle.map[this->_index_of(col, row)]))
                return false;
        } 
    } 
    return true;
}

void NPuzzleState::_swap(int a, int b)
{
    int tmp = this->map[a];
    this->map[a] = this->map[b];
    this->map[b] = tmp;
}

int NPuzzleState::_index_of(int x, int y)
{
    return x + this->n * y;
}

void NPuzzleState::shuffle(int n)
{
    int i = 0;
    srand(time(NULL));
    while (i < n)
    {
        int random = rand() % 4 + 1;
        try
        {
            switch (random)
            {
                case 1:
                    move_down();
                    break;
                case 2:
                    move_up();
                    break;
                case 3:
                    move_left();
                    break;
                case 4:
                    move_right();
                    break;
                default:
                    break;
            }
        }
        catch (exception& e)
        {
            i--;
        }
        i++;
    }
}

void NPuzzleState::move_up()
{
    if (this->p_y == 0)
        throw runtime_error("Can't move up");
    this->_swap(
        this->_index_of(this->p_x, this->p_y),
        this->_index_of(this->p_x, this->p_y - 1)
        );
    this->p_y -= 1;
}

void NPuzzleState::move_down()
{
    if (this->p_y == this->n - 1)
        throw runtime_error("Can't move down");
    this->_swap(
        this->_index_of(this->p_x, this->p_y),
        this->_index_of(this->p_x, this->p_y + 1)
        );
    this->p_y += 1;
}

void NPuzzleState::move_left()
{
    if (this->p_x == 0)
        throw runtime_error("Can't move left");
    this->_swap(
        this->_index_of(this->p_x, this->p_y),
        this->_index_of(this->p_x - 1, this->p_y)
        );
    this->p_x -= 1;
}

void NPuzzleState::move_right()
{
    if (this->p_x == this->n - 1)
        throw runtime_error("Can't move right");
    this->_swap(
        this->_index_of(this->p_x, this->p_y),
        this->_index_of(this->p_x + 1, this->p_y)
        );
    this->p_x += 1;
}

bool NPuzzleState::can_move_up()
{
    if (this->p_y == 0)
        return false;
    return true;
}

bool NPuzzleState::can_move_down()
{
    if (this->p_y == this->n - 1)
        return false;
    return true;
}

bool NPuzzleState::can_move_left()
{
    if (this->p_x == 0)
        return false;
    return true;
}

bool NPuzzleState::can_move_right()
{
    if (this->p_x == this->n - 1)
        return false;
    return true;
}

void NPuzzleState::print_map()
{
    for (int row = 0; row < this->n; row++)
    {
        for (int col = 0; col < this->n; col++)
        {
            int cell = this->map[this->_index_of(col, row)];
            std::cout << cell << " ";
        }
        std::cout << std::endl;
    } 
}

NPuzzleProblem::NPuzzleProblem(NPuzzleState *init_state,
    NPuzzleState *final_state)
{
    this->init = init_state;
    this->goal = final_state;
}

NPuzzleProblem::~NPuzzleProblem() {}

vector<int> NPuzzleProblem::actions(NPuzzleState *state)
{
    std::vector<int> actions;

    if (state->can_move_down())
        actions.push_back(DOWN);

    if (state->can_move_up())
        actions.push_back(UP);

    if (state->can_move_left())
        actions.push_back(LEFT);

    if (state->can_move_right())
        actions.push_back(RIGHT);

    return actions;
}

NPuzzleState *NPuzzleProblem::result(NPuzzleState *state, int action)
{
    NPuzzleState *new_state = new NPuzzleState(*state);

    if (action == UP)
        new_state->move_up();

    if (action == DOWN)
        new_state->move_down();

    if (action == LEFT)
        new_state->move_left();

    if (action == RIGHT)
        new_state->move_right();

    return new_state;
}

NPuzzleState *NPuzzleProblem::init_state()
{
    return new NPuzzleState(*this->init);
}

bool NPuzzleProblem::goal_test(NPuzzleState *state)
{
    if (*this->goal == *state)
        return true;
    return false;
}

float NPuzzleProblem::path_cost(NPuzzleState *init_state, int action,
    NPuzzleState *final_state)
{
    (void)init_state;
    (void)action;
    (void)final_state;
    return 1;
}