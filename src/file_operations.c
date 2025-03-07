#include "file_operations.h"
#include "car_data.h"
#include "ui.h"
#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t get_file_size(const char *filename) {
  FILE *fptr;
  fptr = fopen(filename, "rb");
  if (fptr == NULL) {
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }

  fseek(fptr, 0, SEEK_END);
  size_t file_size = ftell(fptr);
  fclose(fptr);

  return file_size;
}

bool load_data(CarNode **head) {
  char filename[FILENAME_MAX] = DEFAULT_DATA_FILE_PATH;

  FILE *fptr = fopen(filename, "rb");
  if (fptr == NULL) {
    // Check if the error was "No such file or directory"
    if (errno == ENOENT) {
      // File doesn't exist, create it
      fptr = fopen(filename, "wb"); // Open in write binary mode to create
      if (fptr == NULL) {
        perror("Error creating file");
        exit(EXIT_FAILURE);
      }
      fclose(fptr);                 // Close immediately after creating
      fptr = fopen(filename, "rb"); // Reopen in read binary mode
      if (fptr == NULL) {
        perror("Error reopening file for reading");
        exit(EXIT_FAILURE);
      }
      printf("Data file created.\n");
      wait_for_enter();
    } else {
      perror("Error opening file");
      exit(EXIT_FAILURE);
    }
  }

  *head = NULL;
  CarNode *tail = NULL;
  CarData temp_data;

  while (fread(&temp_data, sizeof(CarData), 1, fptr) == 1) {
    CarNode *new_node = (CarNode *)malloc(sizeof(CarNode));

    new_node->data = temp_data;
    new_node->next = NULL;

    if (*head == NULL) {
      *head = new_node;
      tail = new_node;
    } else {
      tail->next = new_node;
      tail = new_node;
    }
  }

  if (!feof(fptr) && ferror(fptr)) {
    perror("Error reading from file");
    fclose(fptr);
    return false;
  }

  fclose(fptr);
  return true;
}

void save_data(CarNode *head) {
  char filename[FILENAME_MAX] = DEFAULT_DATA_FILE_PATH;

  FILE *fptr = fopen(filename, "wb");
  if (fptr == NULL) {
    perror("Error reading file");
    exit(EXIT_FAILURE);
  }

  CarNode *current = head;
  while (current != NULL) {
    if (fwrite(&(current->data), sizeof(CarData), 1, fptr) != 1) {
      perror("Error writing to file\n");
      fclose(fptr);
      exit(EXIT_FAILURE);
    }
    current = current->next;
  }
  fclose(fptr);
  printf("Data saved succesfully\n");
  wait_for_enter();
}

bool save_changes(void) {
  printf("Do you want to save changes (y/n): ");
  char response = getchar();
  clear_input_buffer();

  if (response == 'y' || response == 'Y') {
    return true;
  } else if (response == 'n' || response == 'N') {
    return false;
  } else {
    printf("Invalid choice\n");
    wait_for_enter();
    clear_terminal();
    return save_changes();
  }
}
