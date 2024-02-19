CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -fno-asm -pedantic -MMD -MP
LFLAGS = -lm

BUILD_DIR = bin
OBJ_DIR = obj
TARGET = $(BUILD_DIR)/main # Replace 'program' with your actual program name
COMPILE_COMMANDS_FILE= compile_commands.json

# Automatically find source files
SRC_FILES := $(shell find src -type f -name '*.c')
# Transform source file paths to object file paths
OBJ_FILES := $(SRC_FILES:src/%.c=$(OBJ_DIR)/%.o)
# Generate dependency file paths
DEP_FILES := $(OBJ_FILES:.o=.d)

# Deduce the directories from OBJ_FILES
OBJ_DIRS := $(sort $(dir $(OBJ_FILES)))

# Info
$(info source files: $(SRC_FILES))
$(info object files: $(OBJ_FILES))
$(info dependency files: $(DEP_FILES))

# Default target
all: scaffold $(TARGET)

# Scaffold rule for creating necessary directories
.PHONY: scaffold
scaffold:
	@echo "Creating necessary directories..."
	@mkdir -p $(BUILD_DIR) $(OBJ_DIRS)

# Ensure target directory exists before linking
$(TARGET): $(OBJ_FILES)
	@echo "Linking..."
	$(CC) $(LFLAGS) $(OBJ_FILES) -o $@

# Compile source files into object files and generate dependency files
$(OBJ_DIR)/%.o: src/%.c | scaffold
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# Include dependency files if they exist
-include $(DEP_FILES)

# Phony targets for cleaning up
.PHONY: clean
clean:
	@echo "Cleaning..."
	@rm -rf $(BUILD_DIR) $(OBJ_DIR)

# Avoid cleaning dependency files in a separate clean-dep target to keep the Makefile simple


