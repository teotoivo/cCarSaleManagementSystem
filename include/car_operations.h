#ifndef CAR_OPERATIONS_H
#define CAR_OPERATIONS_H

#include "car_data.h"
#include <stdbool.h>

bool add_new_car(CarNode **head);
bool search_cars(CarNode *head);
bool search_car_by_id(CarNode *head);
bool sell_car(CarNode *head);

#endif
