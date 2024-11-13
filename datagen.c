#include "datagen.h"

int main(int argc, char *argv[]) {
	generation_settings generation_settings;
	if (argc == 1) {
		//IDEA: Implement default action?
		fprintf(stderr, "Please, introduce some argument(s).\n");
		return (1);
	}
	else {
		generation_settings = parse_arguments(argc, argv);
	}

	#ifdef DEBUG
		DEBUG_print_generation_settings(generation_settings);
	#endif

	return (0);
}

void generate_integers(generation_settings generation_settings) {
	int number_array[generation_settings.amount];

	for (int i = 0; i < generation_settings.amount; i++) {
		number_array[i] = random();
	}

	for (int i = 0; i < generation_settings.amount; i++) {
		printf("%d", number_array[i]);
	}
	
}

int generate_random_integer() {
	int value = random();
	return (value);
}
