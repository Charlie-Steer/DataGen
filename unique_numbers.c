#include "datagen.h"

void fisher_yates_shuffle(int *number_array, int array_length);

void set_unique_numbers(int *number_array, generation_settings generation_settings) {
	int min = generation_settings.min;
	int max = generation_settings.max;

	for (int i = min; i < max; i++) {
		number_array[i - min] = i;
	}

	fisher_yates_shuffle(number_array, max - min);
}

void fisher_yates_shuffle(int *number_array, int array_length) {
	srand(clock());
	for (int i = array_length - 1; i > 0; i--) {
		int j = rand() % (i + 1);
		int temp_value = number_array[i];
		number_array[i] = number_array[j];
		number_array[j] = temp_value;
	}
}

