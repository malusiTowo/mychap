##
## EPITECH PROJECT, 2019
## FTP SERVER
## File description:
## Makefile
##

UT_DIR	=	./tests/

UT_SRC	=	$(UT_DIR)parsing.c \

TEST_FILES  = 	$(SRC_FILE)parsing.c\
				$(SRC_FILE)global.c\
				$(SRC_FILE)utils.c\

TESTED = $(TEST_FILES:.c=.o)

UT	=	units

SRC_FILE = 	./src/

SRC		=	$(SRC_FILE)main.c\
			$(SRC_FILE)global.c\
			$(SRC_FILE)parsing.c\
			$(SRC_FILE)utils.c\
			$(SRC_FILE)config_socket.c\
			$(SRC_FILE)auth.c\
			$(SRC_FILE)create_headers.c\

OBJ		=	$(SRC:.c=.o)

CC		=   gcc

NAME	=	client

CFLAGS	=	-W -Wall -Wextra
CFLAGS +=   -I./includes
CFLAGS +=  -I/usr/local/opt/openssl/include

LDFLAGS	=  -lcriterion --coverage -fprofile-arcs -ftest-coverage

all:	$(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS) -lcrypto

gdb:
	$(CC) -o $(NAME) $(SRC) $(CFLAGS) -g3 -lcrypto

tests_run: $(TESTED)
	$(CC) -o $(UT) $(UT_SRC) $(TESTED) $(LDFLAGS) -I./includes
	./$(UT) --verbose
	gcovr
	gcovr -b

html: tests_run
	lcov -c --directory . --output-file main_coverage.info
	genhtml main_coverage.info --output-directory out
	google-chrome ./out/tests/index.html
	rm -rf out/
	rm -f main_coverage.info
	fclean

clean:
	rm -f $(OBJ)

fclean:	clean
		rm -f $(NAME)
		rm -f $(OBJ)
		rm -f $(UT)
		rm -f $(UT_DIR)*.gcno
		rm -f $(UT_DIR)*.gcda
		rm -f $(UT_DIR)*~
		rm -f $(SRC_DIR)*.gcno
	    rm -f $(SRC_DIR)*.gcda
	    rm -f $(SRC_DIR)*~
	    rm -f *.gcov
	    rm -f *.gcno
	    rm -f *.gcda
	    rm -f *~
		rm -rf out/
		rm -f main_coverage.info

re: 	fclean all

.PHONY: all clean fclean re tests_run html gdb