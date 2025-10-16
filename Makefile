# Compiler for C
CC = gcc

# Directories
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
BIN_DIR = bin

# Benchmark directories
BENCH_DIR = benchmarks
BENCH_BIN = $(BENCH_DIR)/bin

# Java
JAVA_SRC = $(BENCH_DIR)/CalcPi.java
JAVA_CLASS = $(BENCH_BIN)/benchmarks/CalcPi.class

# C benchmark
C_BENCH_SRC = $(BENCH_DIR)/calc_pi.c
C_BENCH_EXE = $(BENCH_BIN)/calc_pi

# Main program
TARGET = $(BIN_DIR)/run
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# Flags
CFLAGS = -Wall -Wextra -I$(INC_DIR)

# Default target
.PHONY: all
all: $(TARGET) $(JAVA_CLASS) $(C_BENCH_EXE) \
	$(BENCH_BIN)/calc_pi_1 $(BENCH_BIN)/calc_pi_2 $(BENCH_BIN)/calc_pi_3

# Build main C program
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJS) -o $@

# Compile each C source file
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile Java benchmark
$(JAVA_CLASS): $(JAVA_SRC)
	@mkdir -p $(BENCH_BIN)
	javac -d $(BENCH_BIN) $(JAVA_SRC)

# Compile C benchmarks
$(C_BENCH_EXE): $(C_BENCH_SRC)
	@mkdir -p $(BENCH_BIN)
	$(CC) $(C_BENCH_SRC) -o $(C_BENCH_EXE)

$(BENCH_BIN)/calc_pi_1: $(C_BENCH_SRC)
	@mkdir -p $(BENCH_BIN)
	$(CC) $(CFLAGS) -O1 $< -o $@

$(BENCH_BIN)/calc_pi_2: $(C_BENCH_SRC)
	@mkdir -p $(BENCH_BIN)
	$(CC) $(CFLAGS) -O2 $< -o $@

$(BENCH_BIN)/calc_pi_3: $(C_BENCH_SRC)
	@mkdir -p $(BENCH_BIN)
	$(CC) $(CFLAGS) -O3 $< -o $@


# Clean build artifacts
.PHONY: clean
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) $(BENCH_BIN)

