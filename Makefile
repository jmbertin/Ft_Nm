UP = "\033[A"
CLEAR = "\033[K"

NAME	= ft_nm
SRCS	= main.c \
			ft_check.c \
			ft_nm32.c \
			ft_nm64.c \
			ft_struct_tools.c \
			ft_tools.c \
			ft_define_symbol.c \

LIBFT_A = libft.a
LIBFT_DIR = Libft/
LIBFT  = $(addprefix $(LIBFT_DIR), $(LIBFT_A))

OBJS	= ${SRCS:.c=.o}
CC = gcc
FLAGS = -Wall -Wextra -Werror -lssl -lcrypto -g
INCLUDE = -I includes/

all : ${NAME}

.c.o :
		@${CC} ${FLAGS} -c $< -o $@ ${INCLUDE}
		@echo $(UP)$(CLEAR)"\033[0;93mCompiling ${NAME} : $@ \033[0;39m"

${NAME}	: ${OBJS}
		@make -C $(LIBFT_DIR)
		@${CC} -o ${NAME} ${OBJS} ${INCLUDE} $(LIBFT) ${FLAGS}
		@echo $(UP)$(CLEAR)"\033[0;92m${NAME} compiled !\033[0;39m"

clean :
		@make -C $(LIBFT_DIR) clean
		@rm -f ${OBJS}
		@echo "\033[0;92m${NAME} objects files cleaned.\033[0;39m"

fclean : clean
		@make -C $(LIBFT_DIR) fclean
		@rm -f ${NAME}
		@echo "\033[0;92m${NAME} cleaned.\033[0;39m"

re : fclean all
		@echo "\033[0;92m${NAME} cleaned and rebuilded.\033[0;39m"
