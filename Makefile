
#declarations
#variables
CUR_DIR = $(shell pwd)
NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -Iinclude -Isrcs -pthread

#sources
#VPATH = sources:include
#INCLUDES = philosophers.h
SRCS =	main.c \
		parsing_01.c \
		parsing_02.c \
		parsing_03_mtx.c \
		init_philosophers.c \
		dining.c \
		routine.c \
		routine_one.c \
		is_dead.c \
		all_full.c \
		time.c \
		msg.c \
		cleanup.c \
		ft_calloc.c \
		ft_atoi.c \
		ft_isdigit.c \
		ft_putchar_fd.c

#variable substitution		
OBJS = $(SRCS:%.c=obj/%.o)

#This target depends on $(NAME), making it the default target to build everything.
all: $(NAME)

#to create a program:
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@
	@echo -- prog created, try it by using ./philo

# %.o rule will compile one .c file to its correspondig object (.o) file: without this rule it would not update correctly
# automatic variables: $@ = the file name of the target of the rule, $< = the name of the prerequisite
# -p (parent option): This option tells mkdir to create the directory and any necessary parent directories if they do not already exist. It also suppresses error messages if the directory already exists.
# $(@D) is a special variable: if target is a file located in some directory, $(@D) will extract just the directory path from the target, 
# otherwise If the target doesn’t include a directory (i.e., it's in the current directory), $(@D) expands to . (representing the current directory).
$(OBJS): obj%.o : srcs%.c 
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

#clean: This target removes the object files ($(OFILES)).
#f: "force" -->prevents the command from prompting for confirmation
clean:
	@rm -rf obj
	@echo -- Deleting All .o

# fclean: this target depends on clean. Once all object files are deleted, this rule will delete the created executable / the compiled binary ('$(NAME)') 
fclean: clean
	@rm -f $(NAME)
	@echo -- Deleting executables

#This target depends on fclean and all, effectively cleaning and rebuilding the project.
re: fclean all

#This line specifies that the listed targets (all, clean, fclean, re) are phony targets, meaning they don't represent actual files, and should always be considered out-of-date, triggering their recipes to be executed.
.PHONY: all clean fclean re
