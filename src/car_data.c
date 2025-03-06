#include "car_data.h"
#include <stdlib.h>

void free_cars(CarNode *head)
{
  CarNode *current = head;
  CarNode *next;
  while (current != NULL)
  {
    next = current->next;
    free(current);
    current = next;
  }
}

int generate_unique_id(CarNode *head)
{
  int new_id;
  bool id_exists;

  do
  {
    new_id = 1000 + rand() % 9000;

    id_exists = false;
    CarNode *current = head;
    while (current != NULL)
    {
      if (current->data.id == new_id)
      {
        id_exists = true;
        break;
      }
      current = current->next;
    }
  } while (id_exists);

  return new_id;
}
