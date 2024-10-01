#include "../include/NPuzzle.hpp"

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