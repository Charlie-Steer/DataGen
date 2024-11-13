#ifndef DATAGEN_H
#define DATAGEN_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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
} generation_settings;

generation_settings parse_arguments(int argc, char *argv[]);
void DEBUG_print_generation_settings(generation_settings generation_settings);

#endif