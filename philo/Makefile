# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/16 17:38:32 by rpoder            #+#    #+#              #
#    Updated: 2022/08/17 22:06:07 by rpoder           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROGNAME			=	philo

INCLUDEDIR			:=	./includes
SRCDIR				:=	./src

OBJDIR				:=	./obj

SRCS				:=	main.c \
						parsing.c \
						libft-utils.c \
						threads.c \
						threads_utils.c \
						init.c \
						creates.c \
						prints.c \
						time.c \
						actions.c \
						deaths.c \
						frees.c \
						frees_utils.c \

CC					:=	cc
RM					:=	rm

CCFLAGS				:=	-Wall -Wextra -Werror

#SANITIZE			:= -fsanitize=thread -g3

NAME				:=	$(PROGNAME)

OUTDIR				:=	$(OBJDIR)

$(OUTDIR)/%.o		:	$(SRCDIR)/%.c | $(OUTDIR)
	$(CC) -c $(CCFLAGS) $(SANITIZE) -I $(INCLUDEDIR) $< -o $@

$(NAME)				:	$(addprefix $(OUTDIR)/,$(SRCS:.c=.o))
	$(CC) $(CCFLAGS) $(addprefix $(OUTDIR)/,$(SRCS:.c=.o)) $(SANITIZE) -lpthread -o $(NAME)

all					:	$(NAME)

$(OUTDIR)			:
	mkdir $(OUTDIR)

clean				:
	$(RM) -rf $(OBJDIR)

fclean				:	clean
	$(RM) -f $(PROGNAME)

re					:	fclean
	make $(NAME)

push				:
	$(MAKE) fclean
	git add *
	git status
	git commit -m "$m"
	git push origin master

.PHONY				:	all clean fclean re push

