#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 21
#define WALL '#'
#define PATH '.'
#define PLAYER 'P'
#define GOAL 'G'
#define TRUE 1
#define FALSE 0

typedef struct {
    int x, y;
} Point;

Point player;

char maze[MAX_SIZE][MAX_SIZE];

void init_maze(int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            maze[i][j] = WALL;
        }
    }
}

void print_maze(int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == player.x && j == player.y) {
                printf("%c ", PLAYER);
            } else if (i == n - 2 && j == n - 2) {
                printf("%c ", GOAL);
            } else {
                printf("%c ", maze[i][j]);
            }
        }
        printf("\n");
    }
}

int isGoalCell(Point p, int n) {
    if (p.x == n - 2 && p.y == n - 2) return TRUE;
    return FALSE;
}


void dfs(Point p, int n) {
    maze[p.x][p.y] = PATH;

    Point dirs[4] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}}; // directions: right, left, down, up
    int order[4] = {0, 1, 2, 3}; // order of directions to try

    // Randomly shuffle the order of directions
    for (int i = 0; i < 4; ++i) {
        int j = rand() % 4;
        int tmp = order[i];
        order[i] = order[j];
        order[j] = tmp;
    }

    // Try each direction in the shuffled order
    for (int i = 0; i < 4; ++i) {
        Point next = {p.x + 2*dirs[order[i]].x, p.y + 2*dirs[order[i]].y};
        if (next.x > 0 && next.y > 0 && next.x < n - 1 && next.y < n - 1 && maze[next.x][next.y] == WALL && !isGoalCell(next, n)) {
            // Carve a path between the current cell and the next cell
            maze[p.x + dirs[order[i]].x][p.y + dirs[order[i]].y] = PATH;
            maze[next.x][next.y] = PATH;
            // Recursively generate maze from the next cell
            dfs(next, n);
        }
    }
}

void create_maze(int n) {
    init_maze(n);
    Point start = {1, 1};
    dfs(start, n);
    maze[n - 2][n - 2] = PATH; // Ensure goal is a path
    // Ensure area around the goal is cleared
    maze[n - 2][n - 3] = PATH;
    maze[n - 3][n - 2] = PATH;
    player.x = 1;
    player.y = 1;
}

int main() {
    srand(time(NULL));
    int n;

    printf("Enter maze size (NxN): ");
    scanf("%d", &n);

    // Ensure odd dimension for the maze
    if (n % 2 == 0) n++;
    if (n > MAX_SIZE) n = MAX_SIZE;

    create_maze(n);
    print_maze(n);

    while (1) {
        char command;
        printf("\nEnter command (w/a/s/d for up/left/down/right): ");
        scanf(" %c", &command);  // The space before %c is to eat any leftover \n from the input.

        Point next_move = player;
        if (command == 'w') next_move.x--;
        else if (command == 'a') next_move.y--;
        else if (command == 's') next_move.x++;
        else if (command == 'd') next_move.y++;
        else continue;  // if the input isn't one of these, just ignore it

        if (maze[next_move.x][next_move.y] == PATH) {
            player = next_move;
            print_maze(n);

            // Check if player reached the goal right after the player moved.
            if (player.x == n - 2 && player.y == n - 2) {
                printf("\nCongratulations! You've reached the end of the maze!\n");
                break;
            }
        } else {
            printf("\nInvalid move! Try again.\n");
        }
    }

    return 0;
}
