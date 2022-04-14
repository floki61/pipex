NAME = pipex
FLAGS = -Wall -Wextra -Werror -g

SRCS =	utils/ft_split.c		\
		utils/ft_strjoin.c		\
		utils/get_next_line.c	\
		pipex.c					\
		utils/utils.c			\
		heredoc.c				\

all : $(NAME)

$(NAME) : $(SRCS)
	@gcc $(FLAGS) $(SRCS) -D BUFFER_SIZE=1024 -o $(NAME)

clean :
	@rm -rf $(NAME)
fclean :
	@rm -rf $(NAME)

re: fclean all