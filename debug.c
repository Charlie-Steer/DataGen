#include "datagen.h"

void DEBUG_print_generation_settings(generation_settings generation_settings) {

	char extension[2] = "\0\0";

	if (generation_settings.amount) {
		printf("%d ", generation_settings.amount);
		if (generation_settings.amount > 1) {
			extension[0] = 's';
		}
	}

	if (generation_settings.order == RANDOMIZED) {
		printf("randomized ");
	}
	else if (generation_settings.order == INCREASING) {
		printf("increasing ");
	}
	else if (generation_settings.order == DECREASING) {
		printf("decreasing ");
	}

	if (generation_settings.type == INTEGER) {
		printf("integer%s ", extension);
	}
	else if (generation_settings.type == LONG) {
		printf("long%s ", extension);
	}

	if (generation_settings.type == INTEGER ||
		generation_settings.type == LONG) {
		printf("from %d, to %d, by %d.\n",
			generation_settings.min, generation_settings.max, generation_settings.step);
	}
}
