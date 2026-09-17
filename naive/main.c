#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Option {
  char name[9];
  int value;
};

struct Option options[] = {{.name = "Rock", .value = 1},
                           {.name = "Paper", .value = 2},
                           {.name = "Scissors", .value = 3}};

int length_options = sizeof(options) / sizeof(options[0]);

int player_score = 0;
int my_score = 0;

int round_number = 0;

void printScores(void) {
  printf("\nPlayer: %d", player_score);
  printf("\nComputer: %d\n", my_score);
}

void printOptions(void) {
  int i;
  printf("\nSelect Option:\n");
  for (i = 0; i < length_options; i++) {
    printf("%d. %s \n", options[i].value, options[i].name);
  }
  printf("\n");
}

int check_rules(int player_option, int my_option) {
  switch (player_option) {

  case 0:
    if (my_option == 0) {
      return 0;
    } else if (my_option == 1) {
      return 1;
    } else {
      return -1;
    }
    break;

  case 1:
    if (my_option == 0) {
      return -1;
    } else if (my_option == 1) {
      return 0;
    } else {
      return 1;
    }
    break;

  case 2:
    if (my_option == 0) {
      return 1;
    } else if (my_option == 1) {
      return -1;
    } else {
      return 0;
    }
    break;

  default:
    return 0;
  }
}

void update_score(int winner_int) {
  switch (winner_int) {
  case -1:
    player_score += 1;
    break;
  case 1:
    my_score += 1;
    break;
  default:
    return;
  }
}

void declare_round_winner(int player_option, int my_option) {
  switch (check_rules(player_option, my_option)) {
  case -1:
    update_score(-1);
    printf("\nYou win this round.\n");
    break;
  case 0:
    printf("\nDraw\n");
    break;
  case 1:
    update_score(1);
    printf("\nI win this round.\n");
    break;
  default:
    return;
  }
}

void declare_overall_winner() {
  if (player_score > my_score) {
    printf("\nPlayer wins the game!");
  } else {
    printf("\nI win the game!");
  }
}

struct timespec start, end;


int main(void) {
  srand(time(NULL));
  int random_int = (rand() % ((length_options + 1) - 1)) + 1;

  int option;

  printf("Let's play Rock Paper Scissors!\n");
  printf("First to 3 points wins!\n");

  while ((option != 1 && option != 2 && option != 3) ||
         (player_score != 3 && my_score != 3)) {

    round_number += 1;

    printf("\n===============\n");

    printf("Round %d\n", round_number);

    printScores();

    printOptions();

    scanf("%d", &option);

    if (option == 0 || option > length_options) {

      printf("\nPlease select a number ranging from 1 to 3 according to your "
             "desired option.\n\n");

    } else {

      printf("\nYou picked %s\n", options[option - 1].name);

      printf("I picked %s\n", options[random_int - 1].name);

      declare_round_winner((option - 1), (random_int - 1));
    }
    printf("\n===============\n");
  }

  printScores();
  declare_overall_winner();

  return 0;
}
