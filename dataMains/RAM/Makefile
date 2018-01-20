SRC_D = ./src/
SRC = $(SRC_D)main.cpp\

OBJ_D = ./obj/
OBJ = $(SRC:$(SRC_D)%.cpp=$(OBJ_D)%.o)

INC_D = ./include/
INC = -I$(INC_D)

CC = clang++
CFLAGS = -Wall -Wextra -Werror -g
NAME = testRAM

all : $(NAME)

$(NAME) : $(OBJ)
	@$(CC) $(CFLAGS) $(INC) -o $(NAME) $(OBJ)
	@echo "Compilation completed"

$(OBJ_D)%.o : $(SRC_D)%.cpp
	@mkdir -p $(OBJ_D)
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $<
	@echo "Object created"

clean :
	@/bin/rm -rf $(OBJ_D)
	@echo 'Object directory removed'

fclean : clean
	@/bin/rm -rf $(NAME)
	@echo 'Binary removed'

re	: fclean all
	@echo "Re done"
