#include "ui.h"
#include "car_data.h"
#include <stdio.h>
#include <stdlib.h>

void clear_terminal(void) { system("clear || cls"); }

void print_header(void) {
  clear_terminal();
  printf("========================================\n");
  printf("       CAR SALES MANAGEMENT SYSTEM      \n");
  printf("========================================\n\n");
  printf("1. Add a new car\n");
  printf("2. Print profit report (sorted by profit)\n");
  printf("3. List all cars\n");
  printf("4. Search cars\n");
  printf("5. Search car by id\n");
  printf("6. Sell a car\n");
  printf("7. Backup database\n");
  printf("8. Exit\n\n");
}

int get_user_choice(void) {
  char input[MAX_STRING_LENGTH];

  printf("Enter your choice (1-8): ");

  if (fgets(input, sizeof(input), stdin) == NULL) {
    return -1;
  }

  return strtol(input, NULL, 10);
}

float get_float(void) {
  char input[MAX_STRING_LENGTH];

  if (fgets(input, sizeof(input), stdin) == NULL) {
    return -1;
  }

  return strtof(input, NULL);
}

void clear_input_buffer(void) {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

void wait_for_enter(void) {
  printf("Press enter to continue...");
  getchar();
}
