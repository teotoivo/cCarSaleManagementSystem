#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H
#include "car_data.h"
#include <stdbool.h>

#define DEFAULT_DATA_FILE_PATH "./data.bin"

bool load_data(CarNode **head);
void save_data(CarNode *head);
bool save_changes(void);
#endif
