#include "test_data.h"
#include "car_data.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void initialize_test_data(CarNode **head)
{
  srand(time(NULL));

  const char *car_makes[] = {"Toyota",   "Honda",  "Ford",  "BMW",
                             "Mercedes", "Audi",   "Volvo", "Volkswagen",
                             "Nissan",   "Hyundai"};
  const char *car_models[][5] = {
      {"Corolla", "Camry", "RAV4", "Prius", "Highlander"},
      {"Civic", "Accord", "CR-V", "Pilot", "Fit"},
      {"Focus", "Fiesta", "Mustang", "Explorer", "F-150"},
      {"3 Series", "5 Series", "X3", "X5", "i8"},
      {"C-Class", "E-Class", "S-Class", "GLC", "GLE"},
      {"A3", "A4", "Q5", "Q7", "TT"},
      {"S60", "XC60", "XC90", "V60", "S90"},
      {"Golf", "Passat", "Tiguan", "Polo", "Jetta"},
      {"Altima", "Sentra", "Rogue", "Pathfinder", "Maxima"},
      {"Elantra", "Sonata", "Tucson", "Santa Fe", "Kona"}};

  time_t now = time(NULL);
  struct tm *current_time = localtime(&now);
  int current_year = current_time->tm_year;
  int current_month = current_time->tm_mon;

  for (int i = 0; i < 10; i++)
  {
    CarNode *new_car = malloc(sizeof(CarNode));
    if (new_car == NULL)
    {
      printf("Memory allocation failed\n");
      return;
    }

    new_car->data.id = generate_unique_id(*head);

    int make_index = rand() % 10;
    int model_index = rand() % 5;

    strcpy(new_car->data.make, car_makes[make_index]);
    strcpy(new_car->data.model, car_models[make_index][model_index]);

    new_car->data.mileage_km = 5000.0 + (rand() % 145000);

    int purchase_years_ago = 1 + (rand() % 3);
    int purchase_months_ago = rand() % 12;

    new_car->data.purchase_date = *current_time;
    new_car->data.purchase_date.tm_year = current_year - purchase_years_ago;
    new_car->data.purchase_date.tm_mon =
        (current_month - purchase_months_ago + 12) % 12;
    new_car->data.purchase_date.tm_mday = 1 + (rand() % 28);

    new_car->data.purchase_price = 5000.0 + (rand() % 45000);

    new_car->data.has_been_sold = (rand() % 10) < 7;

    if (new_car->data.has_been_sold)
    {
      int sell_months_after_purchase =
          1 + (rand() % (purchase_years_ago * 12 + purchase_months_ago - 1));

      new_car->data.selling_date = new_car->data.purchase_date;
      new_car->data.selling_date.tm_mon += sell_months_after_purchase;
      while (new_car->data.selling_date.tm_mon > 11)
      {
        new_car->data.selling_date.tm_mon -= 12;
        new_car->data.selling_date.tm_year++;
      }
      new_car->data.selling_date.tm_mday = 1 + (rand() % 28);

      float profit_factor = 0.9 + ((float)rand() / (float)RAND_MAX) * 0.5;
      new_car->data.selling_price =
          new_car->data.purchase_price * profit_factor;
    }
    else
    {
      new_car->data.selling_price = 0.0;
    }

    new_car->next = *head;
    *head = new_car;
  }
}
