# incluir header 42

# Color variables
RED		= \033[1;31m
GREEN	= \033[1;32m
YELLOW	= \033[1;33m
BLUE	= \033[1;34m
WHITE	= \033[1;37m
RESET 	= \033[0m

# Executable name
NAME = btc

# Compiler options
CXX = c++
CXXFLAGS = -Werror -Wall -Wextra -std=c++98  -g #-fsanitize=address

# Paths
SRC_DIR = src/
OBJ_DIR = obj/

# Files
SRC_FILES =	main.cpp \
			BitcoinExchange.cpp \
			funcs.cpp
OBJS = $(addprefix $(OBJ_DIR), $(SRC_FILES:.cpp=.o))

#
$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	@mkdir -p $(dir $@)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

all: $(NAME)

${NAME}: $(OBJS)
	@clear
	@echo "\n$(BLUE) [Compiling] $(NAME)$(RESET)\n"
	@$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN) [Success] $(NAME) created.$(RESET)\n\n"

clean:
	@clear
	@rm -rf $(OBJS)
	@echo "\n$(RED) [Deleting] .o files ... (deleted)$(RESET)\n\n"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(GREEN) [Success] $(NAME) files ... (deleted)$(RESET)\n\n"

re: fclean all

.PHONY: clean all fclean all re
