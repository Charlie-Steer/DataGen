#include "datagen.h"
#include <limits.h>
#include <time.h>
#include <assert.h>
#include <math.h>

void generate_integers(generation_settings generation_settings);
double change_range_of_value(double value, double old_min, double old_max, double new_min, double new_max);
int determine_minimum_upper_limit(const generation_settings generation_settings);
void set_numbers_by_auto_range(generation_settings generation_settings, int *number_array);
void set_numbers_in_range(generation_settings generation_settings, int *number_array);

int main(int argc, char *argv[]) {
	generation_settings generation_settings;
	if (argc == 1) {
		//IDEA: Implement default action?
		fprintf(stderr, "Please, introduce some argument(s).\n");
		return (1);
	}
	else {
		generation_settings = parse_arguments(argc, argv);
		generate_integers(generation_settings);
	}

	#if DEBUG >= 2
		DEBUG_print_generation_settings(generation_settings);
	#endif

	return (0);
}

void generate_integers(generation_settings generation_settings) {
	int *number_array = calloc(generation_settings.amount, sizeof(int));
	if (!number_array) {
		perror("Error: Failed to allocate heap memory.");
		exit(1);
	}

	if (!generation_settings.is_min_set && !generation_settings.is_max_set) {
		set_numbers_by_auto_range(generation_settings, number_array);
	}
	else {
		set_numbers_in_range(generation_settings, number_array);
	}

	for (int i = 0; i < generation_settings.amount; i++) {
		int separator = generation_settings.separator;
		if (i + 1 == generation_settings.amount) {
			separator = '\n';
		}
		printf("%d%c", number_array[i], separator);
	}

	free(number_array);
}

void set_numbers_by_auto_range(generation_settings generation_settings, int *number_array) {
	for (int i = 0; i < generation_settings.amount; i++) {
		srand(clock());
		int max = determine_minimum_upper_limit(generation_settings);
		int rand_val = change_range_of_value(
			rand(), 0, RAND_MAX, 0, max); //? Would this recreate the variable every iteration?
		number_array[i] = rand_val;
	}
}

void set_numbers_in_range(generation_settings generation_settings, int *number_array) {
	for (int i = 0; i < generation_settings.amount; i++) {
		srand(clock());
		int sign = rand();
		if (sign < RAND_MAX/2) {
			sign = -1;
		}
		else {
			assert(sign >= RAND_MAX / 2);
			sign = 1;
		}
		int value = rand() * sign - (sign == -1);
		value = change_range_of_value(
			value, -RAND_MAX - 1, RAND_MAX, generation_settings.min, generation_settings.max); //? Would this recreate the variable every iteration?
		value = floor(value);
		number_array[i] = (int)floor(value);
	}
}

double change_range_of_value(double value, double old_min, double old_max, double new_min, double new_max) {
	value = (value - old_min) / (old_max - old_min);
	value = (value * (new_max - new_min)) + new_min;
	value = floor(value);
	return (value);
}

int determine_minimum_upper_limit(const generation_settings generation_settings) {
	int amount = generation_settings.amount;
	int max = 10;

	while (amount /= 10) {
		max *= 10;
	}
	return (max);
}
