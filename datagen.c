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
int check_if_number(char *argument);
int check_if_word(char *argument);
void DEBUG_print_generation_settings(generation_settings generation_settings);

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

	DEBUG_print_generation_settings(generation_settings);
	
	return (0);
}

generation_settings parse_arguments(int argc, char *argv[]) {
	generation_settings	generation_settings;
	memset(&generation_settings, 0, sizeof(generation_settings));
	int processed_args = 1;
	char *argument_string;
	if (argc - processed_args && check_if_number(argument_string = argv[processed_args])) {
		generation_settings.amount = atoi(argument_string);
		processed_args += 1;
	}
	else {
		generation_settings.amount = DEFAULT_AMOUNT;
	}

	while (argc - processed_args && check_if_word(argument_string = argv[processed_args])) {
		if (strncmp(argument_string, "num", 3) == 0 ||
			strncmp(argument_string, "int", 3) == 0) {
			generation_settings.type = INTEGER;
		}
		else if (strncmp(argument_string, "long", 5) == 0) {
			generation_settings.type = LONG;
		}
		
		else if (strncmp(argument_string, "inc", 3) == 0) {
			generation_settings.order = INCREASING;
		}
		else if (strncmp(argument_string, "dec", 3) == 0) {
			generation_settings.order = DECREASING;
		}
		else if (strncmp(argument_string, "rand", 4) == 0) {
			generation_settings.order = RANDOMIZED;
		}

		else if (strncmp(argument_string, "min", 3) == 0 ||
				 strncmp(argument_string, "from", 5) == 0 ||
				 strncmp(argument_string, "low", 3) == 0) {
			processed_args += 1;
			argument_string = argv[processed_args];
			if (check_if_number(argument_string)) {
				generation_settings.min = atoi(argument_string);
			}
			else {
				perror("Error: [min] stated by no number provided.");
			}
		}
		else if (strncmp(argument_string, "max", 3) == 0 ||
				 strncmp(argument_string, "to", 3) == 0 ||
				 strncmp(argument_string, "until", 6) == 0 ||
				 strncmp(argument_string, "up", 2) == 0) {
			processed_args += 1;
			argument_string = argv[processed_args];
			if (check_if_number(argument_string)) {
				generation_settings.max = atoi(argument_string);
			}
			else {
				perror("Error: [max] stated by no number provided.");
			}
		}
		else if (strncmp(argument_string, "step", 5) == 0 ||
				 strncmp(argument_string, "by", 3) == 0) {
			processed_args += 1;
			argument_string = argv[processed_args];
			if (check_if_number(argument_string)) {
				generation_settings.step = atoi(argument_string);
			}
			else {
				perror("Error: [step] stated by no number provided.");
			}
		}

		else {
			fprintf(stderr, "Error: unrecognized keyword \"%s\".\n", argument_string);
			exit (1);
		}
		processed_args += 1;
	}

	return (generation_settings);
}

int check_if_word(char *argument) {
	int i;
	for (i = 0; argument[i] && isalpha(argument[i]); i++)
		;
	if (argument[i] == '\0' && i != 0) {
		return (1);
	}
	else {
		return (0);
	}
}

int check_if_number(char *argument) {
	int i;
	for (i = 0; argument[i] && isdigit(argument[i]); i++)
		;
	if (argument[i] == '\0' && i != 0) {
		return (1);
	}
	else {
		return (0);
	}
}

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
