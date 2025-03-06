#include "car_data.h"
#include "car_operations.h"
#include "reports.h"
#include "test_data.h"
#include "ui.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
  srand(time(NULL));
  CarNode *head = NULL;
  int choice;

  initialize_test_data(&head);

  while (1)
  {
    print_header();
    choice = get_user_choice();

    switch (choice)
    {
    case 1:
      if (!add_new_car(&head))
      {
        wait_for_enter();
      }
      else
      {
        clear_terminal();
        printf("Car added\n");
        wait_for_enter();
      }
      break;
    case 2:
      print_profit_report(&head);
      break;
    case 3:
      list_all_cars(head);
      break;
    case 4:
      search_cars(head);
      break;
    case 5:
      search_car_by_id(head);
      break;
    case 6:
      sell_car(head);
      break;
    case 7:
      break;
    case 8:
      free_cars(head);
      return EXIT_SUCCESS;
      break;
    default:
      printf("\nInvalid choice try again.\n");
      wait_for_enter();
      break;
    }
  }
  free_cars(head);
}
