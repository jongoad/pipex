SRCS			= ./srcs/child.c ./srcs/free.c ./srcs/pipex.c ./srcs/utils.c

OBJS			= $(SRCS:.c=.o)

BONUS_SRCS		= ./bonus_srcs/bonus_args.c ./bonus_srcs/bonus_child.c ./bonus_srcs/bonus_free.c ./bonus_srcs/bonus_pipes.c ./bonus_srcs/bonus_pipex.c ./bonus_srcs/bonus_utils.c

BONUS_OBJS		= $(BONUS_SRCS:.c=.o)

CC				= gcc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -I./includes/
LIBFT			= cd ../libft && make
LIBFT_INC		= ./libft/libft.a

NAME			= pipex
BONUS_NAME		= pipex_bonus

all:			$(NAME)

$(NAME):		$(OBJS)
				$(LIBFT)
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT_INC)

bonus:			$(BONUS_NAME)		

$(BONUS_NAME):	$(BONUS_OBJS)
				$(LIBFT)
				$(CC) $(CFLAGS) -o $(BONUS_NAME) $(BONUS_OBJS) $(LIBFT_INC)

clean:
				$(RM) $(OBJS) $(BONUS_OBJS)

fclean:			clean
				$(RM) $(NAME) $(BONUS_NAME)

re:				fclean $(NAME)

rebonus:		fclean $(BONUS_NAME)

.PHONY:			all clean fclean re bonus rebonus