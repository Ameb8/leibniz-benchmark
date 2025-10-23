# Compiler for C
CC = gcc

# Directories
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
BIN_DIR = bin

# Set directories for main program object files
DEBUG_OBJ_DIR = $(OBJ_DIR)/debug
RELEASE_OBJ_DIR = $(OBJ_DIR)/release

# Set naming conventions for object files
DEBUG_OBJS = $(patsubst $(SRC_DIR)/%.c,$(DEBUG_OBJ_DIR)/%.o,$(SRCS)) # src/file.c -> debug/file.o
RELEASE_OBJS = $(patsubst $(SRC_DIR)/%.c,$(RELEASE_OBJ_DIR)/%.o,$(SRCS)) # src/file.c -> release.file.o

# Benchmark directories
BENCH_DIR = benchmarks
BENCH_BIN = $(BENCH_DIR)/bin

# Java
JAVA_SRC = $(BENCH_DIR)/CalcPi.java
JAVA_CLASS = $(BENCH_BIN)/benchmarks/CalcPi.class

# C benchmark
C_BENCH_SRC = $(BENCH_DIR)/calc_pi.c
C_BENCH_EXE = $(BENCH_BIN)/calc_pi

# Go benchmark
GO_BENCH_SRC = $(BENCH_DIR)/calc_pi.go
GO_BENCH_EXE = $(BENCH_BIN)/calc_pi_go


# Main program
TARGET = $(BIN_DIR)/run
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# Flags
CFLAGS = -Wall -Wextra -I$(INC_DIR)

ifdef DEBUG 
    DEBUG_FLAGS = -DDEBUG=$(DEBUG)
else
    DEBUG_FLAGS =
endif


# Default target
.PHONY: all
all: $(TARGET) $(BIN_DIR)/run_debug $(JAVA_CLASS) $(C_BENCH_EXE) \
	$(BENCH_BIN)/calc_pi_1 $(BENCH_BIN)/calc_pi_2 $(BENCH_BIN)/calc_pi_3 \
	$(GO_BENCH_EXE)

# Build main C program
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJS) -o $@

# Normal (release) build
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJS) -o $@

# Debug build (separate objects and binary)
$(BIN_DIR)/run_debug: $(SRCS)
	@mkdir -p $(OBJ_DIR)/debug $(BIN_DIR)
	$(CC) $(CFLAGS) -DDEBUG=1 -c $(SRCS)
	$(CC) $(CFLAGS) -DDEBUG=1 $(patsubst %.c,%.o,$(SRCS)) -o $(BIN_DIR)/run_debug
	@rm -f $(patsubst %.c,%.o,$(SRCS))

# Compile main C program
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -c $< -o $@


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

$(GO_BENCH_EXE): $(GO_BENCH_SRC)
	@mkdir -p $(BENCH_BIN)
	go build -o $(GO_BENCH_EXE) $(GO_BENCH_SRC)

# Clean build artifacts
.PHONY: clean
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) $(BENCH_BIN)

