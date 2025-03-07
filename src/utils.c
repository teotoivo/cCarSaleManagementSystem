#include "utils.h"
#include "car_data.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

bool get_user_input(char *buffer, size_t size) {
  if (buffer == NULL || size <= 0) {
    return false;
  }

  if (fgets(buffer, size, stdin) == NULL) {
    return false;
  }

  char *newLine = strchr(buffer, '\n');
  if (newLine != NULL) {
    *newLine = '\0';
  } else {
    while (getchar() != '\n')
      ;
  }

  return true;
}

bool get_date_from_user(struct tm *date) {
  char input[11];
  time_t now = time(NULL);

  struct tm *local = localtime(&now);
  date->tm_year = local->tm_year;
  date->tm_mon = local->tm_mon;
  date->tm_mday = local->tm_mday;

  printf("Enter a date (24:1:2025) or press Enter for today: ");
  fgets(input, sizeof(input), stdin);

  if (strlen(input) > 1) {
    int day, month, year;
    if (sscanf(input, "%d:%d:%d", &day, &month, &year) == 3) {
      date->tm_year = year - 1900;
      date->tm_mon = month - 1;
      date->tm_mday = day;
    } else {
      printf("Invalid date format.");
      return false;
    }
  }

  return true;
}

void stringToLower(char *str) {
  for (int i = 0; str[i]; i++) {
    str[i] = tolower(str[i]);
  }
}

bool stringContains(const char *str, const char *substr) {
  if (str == NULL || substr == NULL) {
    return false;
  }

  char strLower[strlen(str) + 1];
  strcpy(strLower, str);
  stringToLower(strLower);

  char substrLower[strlen(substr) + 1];
  strcpy(substrLower, substr);
  stringToLower(substrLower);

  return strstr(strLower, substrLower) != NULL;
}

CarNode *insertionSort(CarNode *head, CompareFunc compare) {
  if (head == NULL || head->next == NULL) {
    return head;
  }

  CarNode *sorted = NULL;
  CarNode *current = head;

  while (current != NULL) {
    CarNode *next = current->next;

    if (sorted == NULL || compare(&sorted->data, &current->data) >= 0) {
      current->next = sorted;
      sorted = current;
    } else {
      CarNode *temp = sorted;

      while (temp->next != NULL &&
             compare(&temp->next->data, &current->data) < 0) {
        temp = temp->next;
      }
      current->next = temp->next;
      temp->next = current;
    }
    current = next;
  }
  return sorted;
}

int compare_profits_desending(const CarData *a, const CarData *b) {
  if (!a->has_been_sold && !b->has_been_sold)
    return 0;
  if (a->has_been_sold && !b->has_been_sold)
    return -1;
  if (b->has_been_sold && !a->has_been_sold)
    return 1;

  int profit_a = a->selling_price - a->purchase_price;
  int profit_b = b->selling_price - b->purchase_price;

  return profit_b - profit_a;
}

void delete_char(char *str, char c) {
  int read_index = 0;
  int write_index = 0;

  while (str[read_index] != '\0') {
    if (str[read_index] != c) {
      str[write_index] = str[read_index];
      write_index++;
    }
    read_index++;
  }
  str[write_index] = '\0';
}
