#ifndef CAR_DATA_H
#define CAR_DATA_H

#include <stdbool.h>
#include <time.h>

#define MAX_STRING_LENGTH 100
#define MAX_CAR_DATA 100

typedef struct
{
  int id;
  char make[MAX_STRING_LENGTH];
  char model[MAX_STRING_LENGTH];
  struct tm purchase_date;
  struct tm selling_date;
  float mileage_km;
  float purchase_price;
  float selling_price;
  bool has_been_sold;
} CarData;

typedef struct CarNode
{
  CarData data;
  struct CarNode *next;
} CarNode;

typedef int (*CompareFunc)(const CarData *a, const CarData *b);

void free_cars(CarNode *head);
int generate_unique_id(CarNode *head);

#endif
