#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SIZE_X 10
#define SIZE_Y 10

char SYM_LIVE = '*';
char SYM_FREE = ' ';

char world[SIZE_X][SIZE_Y];
char new_world[SIZE_X][SIZE_Y];

void
init()
{
  int i, j;

  for (i = 0; i < SIZE_X; i++) {
    for (j = 0; j < SIZE_Y; j++) {
      world[i][j] = SYM_FREE;
    }
  }

  /* glider */
  world[1][3] = SYM_LIVE;
  world[2][1] = SYM_LIVE;
  world[2][3] = SYM_LIVE;
  world[3][2] = SYM_LIVE;
  world[3][3] = SYM_LIVE;
}

void
render()
{
  int i, j;

  for (i = 0; i < SIZE_X; i++) {
    for (j = 0; j < SIZE_Y; j++) {
      printf("%c  ", world[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

int
count_live_cell(int i, int j)
{
  int k, l;
  int live_cell;

  live_cell = 0;

  for (k = i - 1; k < (i + 2); k++) {
    for (l = j - 1; l < (j + 2); l++) {
      if (k != i || l != j) {
        if (world[k][l] == SYM_LIVE) {
          live_cell++;
        } 
      }
    }
  }

  return live_cell;
}

void
copy_world_into_new_world()
{
  int i, j;

  for (i = 0; i < SIZE_X; i++) {
    for (j = 0; j < SIZE_Y; j++) {
      new_world[i][j] = world[i][j];
    }
  }
}

void
copy_new_world_into_world()
{
  int i, j;

  for (i = 0; i < SIZE_X; i++) {
    for (j = 0; j < SIZE_Y; j++) {
      world[i][j] = new_world[i][j];
    }
  }
}

void
tick()
{
  int i, j;
  int k, l;
  int live_cell;

  /* remember world state */
  copy_world_into_new_world();

  for (i = 1; i < SIZE_X - 1; i++) {
    for (j = 1; j < SIZE_Y - 1; j++) {
      live_cell = count_live_cell(i, j);

      if (world[i][j] == SYM_LIVE) {
        /* 1. a live cell with fewer than two live neighbors dies */
        if (live_cell < 2) {
          new_world[i][j] = SYM_FREE;
        }

        /* 2. a live cell with more than three live neighbors also dies */
        if (live_cell > 3) {
          new_world[i][j] = SYM_FREE;
        }

        /* 3. a live cell with exactly two or three live neighbors lives */
        if (live_cell == 2 || live_cell == 3) {
          /* do nothing */
        }
      }

      if (world[i][j] == SYM_FREE) {
        /* 4. a dead cell with exactly three live neighbors becomes alive */
        if (live_cell == 3) {
          new_world[i][j] = SYM_LIVE;
        }
      }
    }
  }

  /* update world state */
  copy_new_world_into_world();
}

int
main(void)
{
  init();

  while (1) {
    render();
    tick();
    sleep(1);
  }

  return 0;
}