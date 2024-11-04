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
            this->p_x = i % n;
            this->p_y = i / n;
        }
        i++;
    }
}

int NPuzzleState::get_n()
{
    return this->n;
}

int NPuzzleState::get(int x, int y)
{
    return this->map[this->_index_of(x, y)];
}

void NPuzzleState::fill_map(int init, int n, int m)
{
    if (m == 0)
    {
        for (int i = 0; i < n*n; i++)
        {
            this->map[i] = 0;
        }
    }
    for (int i = 0; i < n - 1; i++)
    {
        this->map[this->_index_of(i + m, m)] = init + i + 1;
    }
    for (int i = 0; i < n - 1; i++)
    {
        this->map[this->_index_of(n + m - 1, i + m)] = init + n + i;
    }
    for (int i = 0; i < n - 1; i++)
    {
        this->map[this->_index_of(n + m - i - 1, n + m - 1)] = init + (n - 1) * 2 + i + 1;
    }
    for (int i = 0; i < n - 1; i++)
    {
        this->map[this->_index_of(m, n + m - i - 1)] = init + (n - 1) * 3 + i + 1;
    }
    if (n > 2)
    {
        this->fill_map(init + (n - 1) * 4, n - 2, m + 1);
    }
    else if (n > 1)
    {
        this->map[this->_index_of(m, m + 1)] = 0;
    }
}

NPuzzleState::NPuzzleState(int n)
{
    this->n = n;
    this->map = new int[n * n];
    this->fill_map(0, n, 0);
    int i = 0;
    while (i < n * n)
    {
        if (map[i] == 0)
        {
            this->p_x = i % n;
            this->p_y = i / n;
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

bool NPuzzleState::is_solvable(NPuzzleState *end)
{
    end = new NPuzzleState(*end);
    while (end->can_move_down())
        end->move_down();
    while (end->can_move_right())
        end->move_right();

    int mapping[this->n * this->n];
    for (int i = 0; i < this->n * this->n; i++)
        mapping[end->map[i]] = i;

    int inversions = 0;
    for (int i = 0; i < this->n * this->n; i++)
    {
        for (int j = i; j < this->n * this->n; j++)
        {
            if (mapping[this->map[i]] > mapping[this->map[j]]
                && this->map[i] != 0)
                inversions ++;
        }
    }

    int row = this->n - this->p_y;

    delete end;
    if (this->n % 2 && inversions % 2 == 0)
        return true;
    if (this->n % 2 == 0)
    {
        if (inversions % 2 == 1 && row % 2 == 0)
            return true;
        if (inversions % 2 == 0 && row % 2 == 1)
            return true;
    }
    return false;
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

NPuzzleState *NPuzzleProblem::goal_state()
{
    return new NPuzzleState(*this->goal);
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