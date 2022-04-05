NAME = pipex
FLAGS = -Wall -Wextra -Werror

SRCS =	utils/ft_split.c		\
		utils/ft_strjoin.c		\
		pipex.c					\
		utils/utils.c			\

all : $(NAME)

$(NAME) : $(SRCS)
	@gcc $(FLAGS) $(SRCS) -o $(NAME)

clean :
	@rm -rf $(NAME)
fclean :
	@rm -rf $(NAME)

re: fclean all