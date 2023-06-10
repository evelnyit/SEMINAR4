# SEMINAR4
The maze runner game is a text-based game in which the player's objective is to run through a maze. The maze is randomly generated using Depth First Search Algorithm. The maze is represented by a grid of cells, with walls blocking certain paths. The player starts at a designated position and must reach the goal by moving up, down, left or right. The player can only move along open paths and cannot move through walls. The game ends when the player reaches the goal position.

Function descriptions:
init_maze(int n): Initializes the maze by setting all cells to be walls.
print_maze(int n): Prints the current state of the maze, including the player's position and the goal position.
isGoalCell(Point p, int n): Checks if a given position is the goal position in the maze.
dfs(Point p, int n): Performs a depth-first search algorithm to generate the maze. It carves paths through the walls to create a solvable maze.
create_maze(int n): Initializes the maze, generates the maze using the depth-first search algorithm, ensures the goal is accessible, and sets the player's starting position.
main(): The main function of the program. It handles user input, moves the player within the maze, checks if the player has reached the goal, and prints the maze after each move.

Prompts used are:
"Act as a senior C programmer, expert in code quality and best practices. Write the maze runner game in done in C using the Depth First algorithm to make a randomized maze. 
The code must meet the following points:
- The game ends when the player reaches the end  
- There must be a path to complete the game"

ChatGPT provided a code that compiled correctly, but there were some bugs: Player P and goal G were surrounded by walls. Therefore, the player could not move and the goal could not be reached, i.e. the game never ended. I wrote the following instruction to fix this:

"There is an error in the create_maze() and dfs() function. Player P is between walls, so no movement is possible. The same is true for goal G, it is not reachable. "

To solve these issues, ChatGPT provided the following modifications:

In the create_maze() function, the line 'player = point(0, 0);' was corrected to set the player's starting coordinates to (1, 1) as follows:
player.x = 1;
player.y = 1;

In the dfs() function, made the goal (G) accessible by carving paths around it. These lines were added to clear cells adjacent to the goal:
maze[n - 2][n - 3] = PATH;
maze[n - 3][n - 2] = PATH;

These modifications allowed the player to start in an open space and ensure that the goal is reachable. 
