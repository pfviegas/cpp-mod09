# incluir header 42

# Color variables
RED		= \033[1;31m
GREEN	= \033[1;32m
YELLOW	= \033[1;33m
BLUE	= \033[1;34m
WHITE	= \033[1;37m
RESET 	= \033[0m

# Executable name
NAME = PmergeMe

# Compiler options
CXX = c++
CXXFLAGS = -Werror -Wall -Wextra -std=c++98  -g #-fsanitize=address

# Paths
SRC_DIR = src/
OBJ_DIR = obj/

# Files
SRC_FILES =	main.cpp \
			PmergeMe.cpp
OBJS = $(addprefix $(OBJ_DIR), $(SRC_FILES:.cpp=.o))

# Compile object files
$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	@mkdir -p $(dir $@)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# Default target
all: $(NAME)

# Link executable
${NAME}: $(OBJS)
	@clear
	@echo "\n$(BLUE) [Compiling] $(NAME)$(RESET)\n"
	@$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN) [Success] $(NAME) created.$(RESET)\n\n"

# Clean object files
clean:
	@clear
	@rm -rf $(OBJS)
	@echo "\n$(RED) [Deleting] .o files ... (deleted)$(RESET)\n\n"

# Clean all files
fclean: clean
	@rm -rf $(NAME)
	@echo "$(GREEN) [Success] $(NAME) files ... (deleted)$(RESET)\n\n"

# Rebuild
re: fclean all

.PHONY: clean all fclean all re
