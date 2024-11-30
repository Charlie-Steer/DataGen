#ifndef DATAGEN_H
#define DATAGEN_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define DEFAULT_AMOUNT 1

typedef struct generation_settings {
	int amount;
	enum order {
		RANDOMIZED,
		INCREASING,
		DECREASING,
	} order;
	enum type {
		INTEGER,
		LONG,
	} type;

	// For numbers
	int min;
	int max;
	int step;
	char separator;
	bool is_min_set;
	bool is_max_set;
	bool is_step_set;
	bool set_unique;
} generation_settings;

generation_settings parse_arguments(int argc, char *argv[]);
void set_numbers_in_range(generation_settings generation_settings, int *number_array);
void set_unique_numbers(int *number_array, generation_settings generation_settings);
int get_random_number_in_range(int min, int max);

void DEBUG_print_generation_settings(generation_settings generation_settings);

#endif
