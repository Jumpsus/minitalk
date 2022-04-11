# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pratanac <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/10 22:22:51 by pratanac          #+#    #+#              #
#    Updated: 2022/04/11 00:10:27 by pratanac         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minitalk

CLIENT = client

SERVER = server

$(NAME) : all

all : $(CLIENT) $(SERVER)

$(CLIENT):
	@gcc -Wall -Werror -Wextra utils.c client.c -o client
	@echo "Client Programming is Created !!"

$(SERVER):
	@gcc -Wall -Werror -Wextra utils.c server.c -o server
	@echo "Server Programming is Created !!"

clean:
	@echo "Nothing to Clean!!"

fclean:
	@rm -rf client
	@echo "rm -rf client"
	@rm -rf server
	@echo "rm -rf server"

re: fclean all

bonus: re all

.PHONY: $(NAME) all clean fclean re $(CLIENT) $(SERVER)
