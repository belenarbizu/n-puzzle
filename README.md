# n-puzzle
In this project, my goal was to develop a program capable of solving the N-puzzle game using the A* search algorithm. The game consists of a square board of size N x N, with tiles numbered from 1 to (N*N)-1 and one empty cell. The challenge is to find a valid sequence of moves to reach the final state, known as the "snail solution" where the tiles are arranged in a specific spiral pattern depending on the board size. I implemented a solution that supports various puzzle sizes, from smaller boards like 3x3 to larger ones, ensuring the program remains efficient and avoids excessive solving times.<br/>
<br/>
The program handles both randomly generated initial states and custom configurations specified in an input file. It includes three heuristic functions: Manhattan distance, Euclidean distance and Hamming distance. The program provides detailed output, including the time and space complexity, the number of moves required, and the sequence of states leading to the solution. It also accounts for unsolvable puzzles, notifying the user when no solution exists. As a bonus, I implemented configurations for g(x) and h(x) to run uniform-cost and greedy searches, allowing for exploration of different solving strategies.<br/>
<br/>
This project not only deepened my understanding of search algorithms and heuristics but also challenged me to optimize resource management for handling large puzzle sizes.<br/>
<br/>
Project done with plopez-b
