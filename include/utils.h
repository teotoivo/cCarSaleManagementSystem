#ifndef UTILS_H
#define UTILS_H

#include "car_data.h"
#include <stdbool.h>
#include <time.h>

bool get_user_input(char *buffer, size_t size);
bool get_date_from_user(struct tm *date);
void stringToLower(char *str);
bool stringContains(const char *str, const char *substr);
CarNode *insertionSort(CarNode *head, CompareFunc compare);
int compare_profits_desending(const CarData *a, const CarData *b);
void delete_char(char *str, char c);

#endif
