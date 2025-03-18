CXX				= g++
CXXFLAGS		= -std=c++20 -Wall -Wextra -Werror -MMD -MP -I./include
LDFLAGS			=

SRC_DIR			= src
INCLUDE_DIR		= include
CXXOPTS_DIR 	= cxxopts
CXXOPTS_HEADER	= $(INCLUDE_DIR)/cxxopts.hpp

BIN			= combine_files
SRCS		= $(wildcard $(SRC_DIR)/*.cpp)
OBJS		= $(SRCS:.cpp=.o)
DEPS		= $(OBJS:.o=.d)

# ANSI COLOR
RESET		= \033[0m
RED			= \033[31m
GREEN		= \033[32m
YELLOW		= \033[33m
BLUE		= \033[34m
CYAN		= \033[36m
BOLD		= \033[1m

all: cxxopts $(BIN)

$(BIN): $(OBJS)
	@echo -e "$(BLUE) Compiling project...$(RESET)"
	$(CXX) $(CXXFLAGS) -o $@ $^
	@echo -e "$(GREEN) Build complete!$(RESET)"

%.o: %.cpp
	@echo -e "$(CYAN) Compiling: $<$(RESET)"
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TEST_BIN): $(TEST_DIR)/test_text_file_combiner.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ -I./include

clean:
	@echo -e "$(RED) Cleaning object files...$(RESET)"
	rm -f $(OBJS) $(DEPS)
	@echo -e "$(GREEN) Object files cleaned!$(RESET)"

fclean: clean
	@echo -e "$(RED) Removing binaries...$(RESET)"
	rm -f $(BIN)
	@echo -e "$(GREEN) Binaries removed!$(RESET)"

re: fclean all
	@echo -e "$(YELLOW) Rebuilding project...$(RESET)"

# cxxopts 헤더 파일 존재 확인 후 다운로드 및 복사
cxxopts:
	@if [ -f "$(CXXOPTS_HEADER)" ]; then \
		echo -e "$(YELLOW) cxxopts.hpp already exists in $(INCLUDE_DIR), skipping download.$(RESET)"; \
	else \
		echo -e "$(CYAN) Checking cxxopts...$(RESET)"; \
		if [ ! -d "$(CXXOPTS_DIR)" ]; then \
			echo -e "$(CYAN) Downloading cxxopts...$(RESET)"; \
			git clone https://github.com/jarro2783/cxxopts.git cxxopts; \
		fi; \
		if [ -f "$(CXXOPTS_DIR)/include/cxxopts.hpp" ]; then \
			echo -e "$(CYAN) Copying cxxopts.hpp to $(INCLUDE_DIR)...$(RESET)";\
			mkdir -p $(INCLUDE_DIR); \
			cp $(CXXOPTS_DIR)/include/cxxopts.hpp $(INCLUDE_DIR)/cxxopts.hpp; \
		else \
			echo -e "$(RED) cxxopts.hpp not found! Check the repository structure.$(RESET)"; \
			exit 1; \
		fi; \
	fi

-include $(DEPS)

.PHONY: all clean fclean re cxxopts
