#include "car_operations.h"
#include "car_data.h"
#include "ui.h"
#include "utils.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool add_new_car(CarNode **head)
{
  CarNode *car_node = malloc(sizeof(CarNode));
  char input_buffer[MAX_STRING_LENGTH];

  car_node->data.id = generate_unique_id(*head);

  clear_terminal();
  printf("========================================\n");
  printf("                ADD A CAR               \n");
  printf("========================================\n\n");

  printf("Car make: ");
  get_user_input(input_buffer, MAX_STRING_LENGTH);
  strcpy(car_node->data.make, input_buffer);

  printf("Car model: ");
  get_user_input(input_buffer, MAX_STRING_LENGTH);
  strcpy(car_node->data.model, input_buffer);

  printf("Car mileage (in km): ");
  int mileage_km = get_float();
  if (mileage_km < 0)
  {
    printf("Invalid mileage\n");
    free(car_node);
    return false;
  }
  car_node->data.mileage_km = mileage_km;

  printf("Car buy date:");
  if (get_date_from_user(&car_node->data.purchase_date) == false)
  {
    free(car_node);
    return false;
  }

  printf("Car buy price (in euro): ");
  int buy_price = get_float();
  car_node->data.purchase_price = buy_price;

  printf("Has the car been sold (y/n): ");
  char hasCarBeenSold = getchar();
  clear_input_buffer();
  if (hasCarBeenSold == 'y' || hasCarBeenSold == 'Y')
  {
    car_node->data.has_been_sold = true;
    printf("Car sell date:");
    get_date_from_user(&car_node->data.selling_date);

    printf("Car sell price (in euro): ");
    int sell_price = get_float();
    car_node->data.selling_price = sell_price;
  }
  else if (hasCarBeenSold == 'n' || hasCarBeenSold == 'N')
  {
    car_node->data.has_been_sold = false;
  }
  else
  {
    printf("Invalid sold status\n");
    free(car_node);
    return false;
  }

  car_node->next = *head;
  *head = car_node;

  return true;
}

bool search_cars(CarNode *head)
{
  clear_terminal();
  printf("========================================\n");
  printf("            SEARCH FOR CARS            \n");
  printf("========================================\n\n");

  printf("Search make or model: ");
  char input_buffer[MAX_STRING_LENGTH];
  get_user_input(input_buffer, MAX_STRING_LENGTH);

  char search_term[MAX_STRING_LENGTH];
  strcpy(search_term, input_buffer);
  for (int i = 0; search_term[i]; i++)
  {
    search_term[i] = tolower(search_term[i]);
  }

  CarNode *current = head;
  int count = 0;

  printf("\nSearch Results:\n");
  printf("----------------------------------------\n");

  while (current != NULL)
  {
    char make_lower[MAX_STRING_LENGTH];
    char model_lower[MAX_STRING_LENGTH];

    strcpy(make_lower, current->data.make);
    strcpy(model_lower, current->data.model);

    for (int i = 0; make_lower[i]; i++)
    {
      make_lower[i] = tolower(make_lower[i]);
    }

    for (int i = 0; model_lower[i]; i++)
    {
      model_lower[i] = tolower(model_lower[i]);
    }

    if (strstr(make_lower, search_term) != NULL ||
        strstr(model_lower, search_term) != NULL)
    {

      printf("ID: %d\n", current->data.id);
      printf("Make: %s\n", current->data.make);
      printf("Model: %s\n", current->data.model);
      printf("Stock Status: %s\n",
             current->data.has_been_sold ? "In Stock" : "Sold");
      printf("Buy Price: $%.2f\n", current->data.purchase_price);
      if (current->data.has_been_sold)
      {
        printf("Price sold: %.2f\n", current->data.selling_price);
      }
      printf("----------------------------------------\n");
      count++;
    }

    current = current->next;
  }

  if (count == 0)
  {
    printf("No cars matching '%s' were found.\n", input_buffer);
  }
  else
  {
    printf("\nFound %d car(s) matching '%s'.\n", count, input_buffer);
  }

  printf("\nPress Enter to continue...");
  get_user_input(input_buffer, MAX_STRING_LENGTH);

  return true;
}

bool search_car_by_id(CarNode *head)
{
  clear_terminal();
  printf("========================================\n");
  printf("            SEARCH CAR BY ID           \n");
  printf("========================================\n\n");

  printf("Enter car ID: ");
  char input_buffer[MAX_STRING_LENGTH];
  get_user_input(input_buffer, MAX_STRING_LENGTH);

  int search_id = strtol(input_buffer, NULL, 10);

  if (search_id <= 0)
  {
    printf("\nInvalid ID. Please enter a valid number.\n");
    wait_for_enter();
    return false;
  }

  CarNode *current = head;
  bool found = false;

  while (current != NULL)
  {
    if (current->data.id == search_id)
    {
      found = true;

      char purchase_date_str[12];
      char sell_date_str[12];

      sprintf(purchase_date_str, "%02d/%02d/%d",
              current->data.purchase_date.tm_mday,
              current->data.purchase_date.tm_mon + 1,
              current->data.purchase_date.tm_year + 1900);

      if (current->data.has_been_sold)
      {
        sprintf(sell_date_str, "%02d/%02d/%d",
                current->data.selling_date.tm_mday,
                current->data.selling_date.tm_mon + 1,
                current->data.selling_date.tm_year + 1900);
      }
      else
      {
        strcpy(sell_date_str, "N/A");
      }

      printf("\n========================================\n");
      printf("            CAR DETAILS                \n");
      printf("========================================\n\n");

      printf("%-20s: %d\n", "ID", current->data.id);
      printf("%-20s: %s\n", "Make", current->data.make);
      printf("%-20s: %s\n", "Model", current->data.model);
      printf("%-20s: %s\n", "Purchase Date", purchase_date_str);
      printf("%-20s: %.1f km\n", "Mileage", current->data.mileage_km);
      printf("%-20s: €%.2f\n", "Purchase Price", current->data.purchase_price);

      if (current->data.has_been_sold)
      {
        printf("%-20s: %s\n", "Selling Date", sell_date_str);
        printf("%-20s: €%.2f\n", "Selling Price", current->data.selling_price);
        float profit =
            current->data.selling_price - current->data.purchase_price;
        printf("%-20s: €%.2f\n", "Profit", profit);
        printf("%-20s: %s\n", "Status", "Sold");
      }
      else
      {
        printf("%-20s: %s\n", "Selling Date", "N/A");
        printf("%-20s: %s\n", "Selling Price", "N/A");
        printf("%-20s: %s\n", "Profit", "N/A");
        printf("%-20s: %s\n", "Status", "In Stock");
      }

      break;
    }
    current = current->next;
  }

  if (!found)
  {
    printf("\nNo car with ID %d was found.\n", search_id);
  }

  printf("\n");
  wait_for_enter();
  return true;
}

bool sell_car(CarNode *head)
{
  clear_terminal();
  printf("========================================\n");
  printf("              SELL A CAR               \n");
  printf("========================================\n\n");

  printf("Enter the ID of the car to sell: ");
  char input_buffer[MAX_STRING_LENGTH];
  get_user_input(input_buffer, MAX_STRING_LENGTH);

  int car_id = strtol(input_buffer, NULL, 10);

  CarNode *current = head;
  bool found = false;

  while (current != NULL)
  {
    if (current->data.id == car_id)
    {
      found = true;

      if (current->data.has_been_sold)
      {
        printf("\nThis car has already been sold.\n");
        wait_for_enter();
        return false;
      }

      printf("\nSelling date:\n");
      get_date_from_user(&current->data.selling_date);

      printf("Selling price (in euro): ");
      float selling_price = get_float();

      current->data.selling_price = selling_price;
      current->data.has_been_sold = true;

      float profit = current->data.selling_price - current->data.purchase_price;

      printf("\nCar ID %d sold for €%.2f (Profit: €%.2f)\n", current->data.id,
             current->data.selling_price, profit);

      wait_for_enter();
      return true;
    }
    current = current->next;
  }

  if (!found)
  {
    printf("\nNo car with ID %d was found.\n", car_id);
    wait_for_enter();
  }

  return false;
}
