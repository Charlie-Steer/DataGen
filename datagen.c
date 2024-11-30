#include "datagen.h"
#include <limits.h>
#include <assert.h>
#include <math.h>

void generate_integers(generation_settings generation_settings);
double change_range_of_value(double value, double old_min, double old_max, double new_min, double new_max);
int determine_minimum_upper_limit(const generation_settings generation_settings);
void set_numbers_by_auto_range(generation_settings generation_settings, int *number_array);
void set_numbers_in_range(generation_settings generation_settings, int *number_array);
int get_random_number_in_range(int min, int max);
void print_number_array(int *number_array, int array_length, char separator);

//TODO: Make max inclusive.
//TODO: Handle min > max case.
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

//! Ensure new auto-range system replaces old in all paths.
void generate_integers(generation_settings generation_settings) {
	int *number_array;
	if (generation_settings.set_unique) {
		number_array = calloc(generation_settings.max - generation_settings.min, sizeof(int));
		if (!number_array) {
			perror("error: failed to allocate heap memory."); //? how do these work. is this the better error printing function?
			exit(1);
		}
		set_unique_numbers(number_array, generation_settings);
	}
	else {
		number_array = calloc(generation_settings.amount, sizeof(int));
		if (!number_array) {
			perror("error: failed to allocate heap memory."); //? how do these work. is this the better error printing function?
			exit(1);
		}

		set_numbers_in_range(generation_settings, number_array);
		// if (!generation_settings.is_min_set && !generation_settings.is_max_set) {
		// 	set_numbers_by_auto_range(generation_settings, number_array);
		// }
		// else {
		// 	set_numbers_in_range(generation_settings, number_array);
		// }
	}
	print_number_array(number_array, generation_settings.amount, generation_settings.separator);
	free(number_array);
}

void print_number_array(int *number_array, int array_length, char separator) {
	for (int i = 0; i < array_length; i++) {
		if (i + 1 == array_length) {
			separator = '\n';
		}
		printf("%d%c", number_array[i], separator);
	}
}
//
// void set_numbers_by_auto_range(generation_settings generation_settings, int *number_array) {
// 	for (int i = 0; i < generation_settings.amount; i++) {
// 		srand(clock());
// 		// int max = determine_minimum_upper_limit(generation_settings);
// 		int rand_val = change_range_of_value(
// 			rand(), 0, RAND_MAX, generation_settings.min, generation_settings.max); //? Would this recreate the variable every iteration?
// 		number_array[i] = rand_val;
// 	}
// }

void set_numbers_in_range(generation_settings generation_settings, int *number_array) {
	for (int i = 0; i < generation_settings.amount; i++) {
		int value = get_random_number_in_range(generation_settings.min, generation_settings.max);
		number_array[i] = value;
	}
}

int get_random_number_in_range(int min, int max) {
	srand(clock()); //! May be better to only set the seed once.
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
		value, -RAND_MAX - 1, RAND_MAX, min, max); //? Would this recreate the variable every iteration?
	return (value);
}

double change_range_of_value(double value, double old_min, double old_max, double new_min, double new_max) {
	value = (value - old_min) / (old_max - old_min);
	value = (value * (new_max - new_min)) + new_min;
	value = floor(value);
	return (value);
}
