#include "datagen.h"

int check_if_word(char *argument);
int check_if_number(char *argument);

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
		else if (strncmp(argument_string, "long", 4) == 0) {
			generation_settings.type = LONG;
		}

		else if (strncmp(argument_string, "uniq", 4) == 0) {
			generation_settings.set_unique = true;
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
				generation_settings.is_min_set = true;
			}
			else {
				perror("Error: [min] stated but no number provided.");
				exit(1);
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
				generation_settings.is_max_set = true;
			}
			else {
				perror("Error: [max] stated but no number provided.");
				exit(1);
			}
		}
		else if (strncmp(argument_string, "step", 5) == 0 ||
				 strncmp(argument_string, "by", 3) == 0) {
			processed_args += 1;
			argument_string = argv[processed_args];
			if (check_if_number(argument_string)) {
				generation_settings.step = atoi(argument_string);
				generation_settings.is_step_set = true;
			}
			else {
				perror("Error: [step] stated but no number provided.");
				exit(1);
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
	int i = 0;
	if (argument[0] == '-' || argument[0] == '+') {
		i += 1;
	}
	for (; argument[i] && isdigit(argument[i]); i++) {
	}
	bool is_any_digit = (i > 1 && (argument[0] == '-' || argument[0] == '+'))
		|| (i > 0 && (argument[0] != '-' && argument[0] != '+'));
	if (argument[i] == '\0' && is_any_digit) {
		return (1);
	}
	else {
		return (0);
	}
}

