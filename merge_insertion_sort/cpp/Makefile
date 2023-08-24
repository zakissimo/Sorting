CC=		c++

FLAGS=	-Wall -Wextra -Werror -std=c++98 -O3

NAME=	main

SRCS=	main.cpp merge_insertion_sort.cpp

OBJS=	$(SRCS:.cpp=.o)

%.o: %.cpp
		$(CC) $(FLAGS) -c $< -o $@

$(NAME):$(OBJS)
		$(CC) $^ -o $@

all:	$(NAME)

clean:
		rm -f $(OBJS)

fclean:
		make clean
		rm -f $(NAME)

re:
		make fclean
		make

.PHONY: all clean fclean re
