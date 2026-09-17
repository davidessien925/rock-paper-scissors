#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int player_score = 0;
int computer_score = 0;

struct Option {
  char name[9];
  int value;
};

struct Option options[] = {{.name = "Rock", .value = 1},
                           {.name = "Paper", .value = 2},
                           {.name = "Scissors", .value = 3}};

int options_length = sizeof(options) / sizeof(options[0]);

void print_options(void) {
  printf("\nSelect your option:\n");
  int i;
  for (i = 0; i < options_length; i++) {
    printf("%d. %s\n", options[i].value, options[i].name);
  };
  printf("\n");
}

int rules_matrix[3][3] = {{0, -1, 1}, {1, 0, -1}, {-1, 1, 0}};

int check_rules_matrix(int x, int y) {
  int outcome = rules_matrix[x][y];
  return outcome;
};

void print_scores(void) {
  printf("\nPlayer: %d\n", player_score);
  printf("CPU: %d\n", computer_score);
}

void update_scores(int outcome) {
  switch (outcome) {
  case 1:
    computer_score += 1;
    printf("\nI won this round!\n");
    break;
  case -1:
    player_score += 1;
    printf("\nYou won this round!\n");
    break;
  default:
    printf("\nDraw\n");
    break;
  }
}

void declare_round_winner(int c_option, int p_option) {
  update_scores(check_rules_matrix(c_option, p_option));
};

void declare_overall_winner(void) {
  print_scores();
  if (player_score > computer_score) {
    printf("\nYou win the game!\n");
  } else {
    printf("\nI win the game!\n");
  }
}

struct timespec start, end;

int main(void) {
  srand(time(NULL));

  int player_option;

  printf("\nHello Gamers!!\n\n");

  printf("Let's play Rock Paper Scissors!!\n\n");

  printf("First to 3 points wins!!\n\n");

  printf("This game was made by David Essien, aka EternalZero or just Zero for "
         "short, the name is a work in progress.\n\n");

  while (player_score < 3 && computer_score < 3) {

    int random_integer = rand() % ((options_length + 1) - 1) + 1;

    printf("\n============================\n");

    print_scores();

    print_options();

    scanf("%d", &player_option);

    if (player_option == 0 || player_option > options_length) {
      printf("\nPlease select a number ranging from 1 to 3 according to your "
             "desired option.\n\n");
    } else {
      printf("\nYou picked %s \n", options[player_option - 1].name);
      printf("I picked %s \n", options[random_integer - 1].name);

      declare_round_winner(random_integer - 1, player_option - 1);
    }
    printf("\n============================\n");
  }

  declare_overall_winner();
}
