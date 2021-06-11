CC = gcc
CFLAG = -Wall -Wextra -Werror

TARGET = pipex
SRC = main.c error.c ft_split.c ft_strjoin.c
OBJ = $(SRC:.c=.o)

$(NAME) : all

all : $(TARGET)

$(TARGET) : $(OBJ)
	      $(CC) $(CFLAG) -o $(TARGET) $(OBJ)

$(OBJ) : $(SRC)
	   $(CC) $(CFLAG) -c $(SRC)

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(TARGET)

re : fclean all

.PHONY : clean fclean re all
