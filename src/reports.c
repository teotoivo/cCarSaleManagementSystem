#include "reports.h"
#include "car_data.h"
#include "ui.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void list_all_cars(CarNode *head)
{
  clear_terminal();
  printf("====================================================================="
         "=========="
         "========================================\n");
  printf("                                          CAR INVENTORY LIST         "
         "          "
         "                                      \n");
  printf("====================================================================="
         "=========="
         "========================================\n");
  printf("%-10s %-15s %-15s %-15s %-15s %-15s %-15s %-15s %-15s\n", "ID",
         "Make", "Model", "Purchase Date", "Sell Date", "Mileage", "Buy Price",
         "Sell Price", "Status");
  printf("---------------------------------------------------------------------"
         "----------"
         "----------------------------------------\n");

  if (head == NULL)
  {
    printf("\nNo cars in inventory.\n\n");
  }
  else
  {
    CarNode *current = head;
    char purchase_date_str[12];
    char sell_date_str[12];
    int car_count = 0;
    float total_investment = 0.0;
    float total_revenue = 0.0;
    float total_profit = 0.0;
    int sold_count = 0;

    while (current != NULL)
    {
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
        sold_count++;
        total_revenue += current->data.selling_price;
        total_profit +=
            (current->data.selling_price - current->data.purchase_price);
      }
      else
      {
        strcpy(sell_date_str, "N/A");
      }

      total_investment += current->data.purchase_price;

      printf("%-10d %-15s %-15s %-15s %-15s %-15.1f €%-14.2f ",
             current->data.id, current->data.make, current->data.model,
             purchase_date_str, sell_date_str, current->data.mileage_km,
             current->data.purchase_price);

      if (current->data.has_been_sold)
      {
        printf("€%-14.2f %-15s\n", current->data.selling_price, "Sold");
      }
      else
      {
        printf("%-15s %-15s\n", "N/A", "In Stock");
      }

      current = current->next;
      car_count++;
    }

    printf("-------------------------------------------------------------------"
           "------------"
           "----------------------------------------\n");
    printf("Total Cars: %d (Sold: %d, In Stock: %d)\n", car_count, sold_count,
           car_count - sold_count);
    printf("Total Investment: €%.2f | Total Revenue: €%.2f | Total Profit: "
           "€%.2f\n",
           total_investment, total_revenue, total_profit);
  }

  printf("====================================================================="
         "=========="
         "========================================\n\n");
  wait_for_enter();
}

void print_profit_report(CarNode **head)
{
  *head = insertionSort(*head, compare_profits_desending);

  clear_terminal();
  printf("====================================================================="
         "=========="
         "========================================\n");
  printf("                                          CAR PROFIT RAPORT         "
         "          "
         "                                      \n");
  printf("====================================================================="
         "=========="
         "========================================\n");
  printf("%-10s %-15s %-15s %-15s %-15s %-15s %-15s\n", "ID", "Make", "Model",
         "Buy Price", "Sell Price", "Status", "Profit");
  printf("---------------------------------------------------------------------"
         "----------"
         "----------------------------------------\n");

  if (head == NULL)
  {
    printf("\nNo cars in inventory.\n\n");
  }
  else
  {
    CarNode *current = *head;
    int car_count = 0;
    float total_investment = 0.0;
    float total_revenue = 0.0;
    float total_profit = 0.0;
    int sold_count = 0;

    while (current != NULL)
    {
      total_investment += current->data.purchase_price;

      printf("%-10d %-15s %-15s €%-14.2f ", current->data.id,
             current->data.make, current->data.model,
             current->data.purchase_price);

      if (current->data.has_been_sold)
      {
        printf("€%-14.2f %-15s €%-14.2f\n", current->data.selling_price, "Sold",
               current->data.selling_price - current->data.purchase_price);
        total_revenue += current->data.selling_price;
        total_profit +=
            current->data.selling_price - current->data.purchase_price;
        sold_count += 1;
      }
      else
      {
        printf("%-15s %-15s %-15s\n", "N/A", "In Stock", "N/A");
      }

      current = current->next;
      car_count++;
    }

    printf("-------------------------------------------------------------------"
           "------------"
           "----------------------------------------\n");
    printf("Total Cars: %d (Sold: %d, In Stock: %d)\n", car_count, sold_count,
           car_count - sold_count);
    printf("Total Investment: €%.2f | Total Revenue: €%.2f | Total Profit: "
           "€%.2f\n",
           total_investment, total_revenue, total_profit);
  }

  printf("====================================================================="
         "=========="
         "========================================\n\n");
  wait_for_enter();
}
