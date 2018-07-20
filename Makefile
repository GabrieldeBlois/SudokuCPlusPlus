NAME	= solver

BINPATH	=	./bin/

CC	= g++

CXX = g++

RM	= rm -f

SRCS	= ./sources/src/main.cpp

OBJS	= $(SRCS:.cpp=.o)

CPPFLAGS = -I./sources/include
CPPFLAGS += -Wall -Wextra -std=c++17 -O2



all: $(NAME)

$(NAME): $(OBJS)
	 $(CXX) $(OBJS) -o $(BINPATH)$(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
