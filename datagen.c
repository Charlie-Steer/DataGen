// REQUIREMENTS
// datagen <n> [random] numbers
// datagen [<n>] [sequential] [increasing|decreasing|random] [numbers] [[from] <min> [[to] <max>]] [by <step>]
// Read default settings from a file.
// Set default settings from program.
// Create Makefile for project.

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define DEFAULT_AMOUNT 1

typedef struct argument_data {
	int type;
	int value;
} argument_data;

enum argument_type {
	NUMBER,
	KEYWORD,
	BOOLEAN
};

enum type_of_generation {
	INTEGER
};

typedef struct generation_settings {
	int amount;
	int type;
	bool is_random;
} generation_settings;

generation_settings parse_arguments(int argc, char *argv[]);
argument_data parse_argument(char *argument);
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
		if (strncmp(argument_string, "num", 3) == 0) {
			generation_settings.type = INTEGER;
		}
		else if (strncmp(argument_string, "rand", 4) == 0) {
			generation_settings.is_random = true;
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

	if (generation_settings.amount) {
		printf("%d ", generation_settings.amount);
	}
	if (generation_settings.is_random) {
		printf("random ");
	}
	if (generation_settings.type == NUMBER) {
		char extension[2] = "\0\0";
		if (generation_settings.amount > 1) {
			extension[0] = 's';
		}
		printf("number%s.\n", extension);
	}
}
