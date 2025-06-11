# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bcheronn <bcheronn@42mulhouse.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/11 12:12:32 by nduvoid           #+#    #+#              #
#    Updated: 2025/06/11 17:55:17 by bcheronn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Big Fat Header\n

# ***************************************************** #
# *                 Configuation                      * #
# ***************************************************** #

MAKEFLAGS += --no-print-directory

# ***************************************************** #
# *                    Variables                      * #
# ***************************************************** #

NAME		:= retromfa
BONUS		:=

CC			:= cc
CFLAGS		+= -Wall -Wextra -Werror -Werror=implicit-function-declaration -MMD
DEBUGFLAGS	:= 
DIR_SRC		:= src
DIR_OBJ		:= .build
DIR_BONUS	:= 
INCLUDE_ALL	:=-Iconfig -I$(DIR_SRC)/core -I$(DIR_SRC)/display -I$(DIR_SRC)/manager -I$(DIR_SRC)/parsing -I$(DIR_SRC)/reader -I$(DIR_SRC)/utils

DIR_LIBFT	:= 
LIBFT		:= #$(DIR_LIBFT)/libft.a
DEPS		:= $(_OBJ_ALL:.o=.d)

# Here we include all the makefile.mk files
include  src/core/makefile.mk src/display/makefile.mk src/manager/makefile.mk src/parsing/makefile.mk src/reader/makefile.mk src/utils/makefile.mk
-include $(DEPS)

SRC_MAIN	:= main.c
SRC_BONUS	:=

# all object files for the modules
_OBJ_MAIN	:= $(addprefix $(DIR_OBJ)/, $(SRC_MAIN:.c=.o))
_OBJ_BONUS	:= $(addprefix $(DIR_OBJ)/, $(SRC_BONUS:.c=.o))
_OBJ_ALL		:= $(OBJ_CORE) $(OBJ_DISPLAY) $(OBJ_MANAGER) $(OBJ_PARSING) $(OBJ_READER) $(OBJ_UTILS)

# ***************************************************** #
# *                    Rules                          * #
# ***************************************************** #

.PHONY: all

all: header norm $(NAME) symbols install

# ***************************************************** #
# *                  Compiling                        * #
# ***************************************************** #

$(NAME): $(LIBFT) $(_OBJ_ALL) $(_OBJ_MAIN)
	$(CC) $(CFLAGS) $(DEBUGFLAGS) $(INCLUDE_ALL) $^ $(LIBFT) -o $(NAME) 

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c
	@mkdir -p $(DIR_OBJ)
	$(CC) $(CFLAGS) $(DEBUGFLAGS) $(INCLUDE_ALL) -c $< -o $@

# $(LIBFT):
	#@make -C $(DIR_LIBFT) NO_HEADER=true

bonus: $(LIBFT) $(_OBJ_ALL) $(_OBJ_BONUS)
	$(CC) $(CFLAGS) $(DEBUGFLAGS) $(INCLUDE_ALL) $^ $(LIBFT)  -o $(BONUS)

# ***************************************************** #
# *                    Clean Rules                    * #
# ***************************************************** #

.PHONY: clean fclean re

clean:
	rm -f $(_OBJ_ALL) $(_OBJ_MAIN) $(_OBJ_BONUS)
#@make clean -C $(DIR_LIBFT)

fclean:
	rm -rf $(DIR_OBJ)
	rm -f $(NAME) $(BONUS)
#@make fclean -C $(DIR_LIBFT)

re: fclean all

# ***************************************************** #
# *                    Debug Rules                    * #
# ***************************************************** #

.PHONY: debug debug.fsanitize debug.fs debug.pg

debug:
	$(eval DEBUGFLAGS=$(DEBUGFLAGS) -g3 -D DEBUG=1)
	@echo "\033[1;33m DEBUG MODE ACTIVATED \033[0m"

debug.fsanitize: debug
	$(eval DEBUGFLAGS=$(DEBUGFLAGS) -fsanitize=address)

debug.fs: debug.fsanitize

debug.pg:
	$(eval DEBUGFLAGS=$(DEBUGFLAGS) -pg)

# ***************************************************** #
# *                      Utils                        * #
# ***************************************************** #

.PHONY: header norm install uninstall update symbols

header:
ifeq ($(MAKELEVEL), 0)
	@echo "Big Fat Header\n"
endif

# norm:
# 	@errors=$$(norminette --use-gitignore | grep --color=always "Error"); \
# 	if [ -n "$$errors" ]; then \
# 		echo "$$errors"; \
# 		echo "\033[31m ❌ Norminette errors found \033[0m"; \
# 	else \
# 		echo "\033[1;32m ✅ Norminette Ok\033[0m"; \
# 	fi

INSTALL_DIR = $(HOME)/.local/bin

install:
	mkdir -p $(INSTALL_DIR)
	cp $(NAME) $(INSTALL_DIR)/
	chmod +x $(INSTALL_DIR)/$(NAME)
	$(call _completion)
	echo "\033[1;32m ✅ $(NAME) installed to $(INSTALL_DIR) \033[0m"; \

uninstall:
	rm -rf $(INSTALL_DIR)/$(NAME)
	echo "\033[1;32m ✅ $(NAME) uninstalled from $(INSTALL_DIR) \033[0m";

update:
	if [ -f ./auto.sh ]; then \
		echo "\033[1;33m Updating Makefile... \033[0m"; \
	else \
		echo "\033[1;31m auto.sh not found, please add the script to automate the update \033[0m"; \
		exit 1; \
	fi
	./auto.sh
	echo "\033[1;32m ✅ Makefile updated \033[0m";

.SILENT:
	@echo "\033[1;33m SILENT MODE ACTIVATED \033[0m
