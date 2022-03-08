NAME	=	so_long

NAME_B	=	so_long_bonus

SRCS	=	check_close_map_exit_player_collectible_other_symbols.c \
			draw.c \
			filling_lines.c \
			init.c \
			key_press.c \
			main.c \
			get_next_line/get_next_line.c

SRCS_B	=	check_close_map_exit_player_collectible_other_symbols_bonus.c \
			check_move_to_exit.c \
			continue_bonus.c \
			draw_bonus.c \
			filling_lines.c \
			init_bonus.c \
			key_press_bonus.c \
			main.c \
			string_movements_put_bonus.c \
			get_next_line/get_next_line.c

OBJS	=	$(SRCS:%.c=%.o)

OBJS_B	=	$(SRCS_B:%.c=%.o)

CC 		=	gcc

RM		=	rm -f

FLAGS 	=	-Wall -Wextra -Werror -Imlx_linux -Lmlx_linux

all:		${NAME}

${NAME}:	${OBJS} so_long.h
			cd libft && make
			cd ..
			${CC} ${FLAGS} -g -o ${NAME} ${OBJS} libft/libft.a -lmlx -lXext -lX11

${NAME_B}:	${OBJS_B} so_long_bonus.h
			cd libft && make
			cd ..
			${CC} ${FLAGS} -g -o ${NAME_B} ${OBJS_B} libft/libft.a  -lmlx -lXext -lX11

clean:
			cd libft && make clean
			${RM} ${OBJS} && ${RM} ${OBJS_B}

fclean:		clean
			cd libft && make fclean
			${RM} $(NAME) && ${RM} $(NAME_B)

bonus:		${NAME_B}
			
re:			fclean all

.PHONY:		all clean fclean re