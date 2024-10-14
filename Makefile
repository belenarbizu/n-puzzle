

FLAGS			=	-g -I./include -Wall -Werror -Wextra

COMPILER 		=	g++

NAME			=	npuzzle

HEADERS			=	include/Node.hpp \
					include/NPuzzle.hpp \
					include/Problem.hpp

SRCS			=	src/main.cpp \
					src/NPuzzle.cpp

BINS			=	$(addprefix bin/, $(SRCS:.cpp=.o))

all:			${NAME}

bin/%.o: %.cpp ${HEADERS}
	@mkdir -p $(dir $@)
	${COMPILER} ${FLAGS} -c $< -o $@

${NAME}: ${BINS}
	${COMPILER} ${FLAGS} ${BINS} -o $@

clean:
	@rm -rf ${BINS} bin/

fclean:	clean

re:		fclean all

valgrind:	${NAME}
	valgrind --leak-check=full ./${NAME}


.PHONY: all clean fclean re
