// REQUIREMENTS
// datagen <n> [random] numbers
// OPTIONAL
// datagen <n> [random] numbers [<min>] [<max>]
// datagen <n> numbers [<min>] [<step>]

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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
	int number;
	int type;
	bool is_random;
} generation_settings;

generation_settings parse_arguments(int argc, char *argv[]);
argument_data parse_argument(char *argument);
int check_if_number(char *argument);
int check_if_word(char *argument);

int main(int argc, char *argv[]) {
	if (argc == 1) {
		//IDEA: Implement default action?
		printf("Please, introduce some argument(s).");
		return (0);
	}
	
	return (0);
}

generation_settings parse_arguments(int argc, char *argv[]) {
	for (int i = 1; i <= argc; i++) {
		parse_argument(argv[i]);
	}
}

argument_data parse_argument(char *argument_string) {
	generation_settings generation_settings; //? Problematic?
	argument_data argument;
	if (check_if_number(argument_string)) {
		argument.type = NUMBER;
		argument.value = atoi(argument_string);
	}
	else if (check_if_word(argument_string)) {
		if (strncmp(argument_string, "num", 3) == 0) {
			generation_settings.type = INTEGER;
		}
		else if (strncmp(argument_string, "rand", 4) == 0) {
			generation_settings.is_random = true;
		}
		else {
			fprintf(stderr, "Error: unrecognized keyword \"%s\"", argument_string);
			exit (1);
		}
	}
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
