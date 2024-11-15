CC = clang
MODE ?= dev
DEBUG_LEVEL ?= 1
CFLAGS_dev = -DDEBUG=$(DEBUG_LEVEL) -Wall -Wextra -MMD -g
CFLAGS_prod = -DNDEBUG -Wall -Wextra -O2 -MMD
CFLAGS = $(CFLAGS_$(MODE))
NAME = datagen
RM = rm -rf
SOURCES = \
	datagen.c \
	parsing.c \
	debug.c
OBJECTS = $(SOURCES:.c=.o)
DEPENDENCIES = $(SOURCES:.c=.d)

-include $(DEPENDENCIES)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) -lm $(OBJECTS) -o $(NAME)
ifeq ($(MODE), prod)
	strip $(NAME)
endif

all: $(NAME)

clean:
	$(RM) $(OBJECTS) $(DEPENDENCIES)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
