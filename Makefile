NAME = catch_me

CC = g++

SRC = ai.cxx lin.cxx win.cxx projet.cxx

FLAGS = --std=c++11 -Wall -Wextra -pedantic

all: $(NAME)

$(NAME):
	$(CC) $(FLAGS) -o $(NAME) $(SRC)

clean:
	rm -f $(NAME) *~ #*#

re: clean all
