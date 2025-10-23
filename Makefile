# Compiler for C
CC = gcc

# Directories
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
BIN_DIR = bin

# Identify source files to compile
SRCS = $(wildcard $(SRC_DIR)/*.c) 

# Set directories for main program Debug and release builds
DEBUG_OBJ_DIR = $(OBJ_DIR)/debug
RELEASE_OBJ_DIR = $(OBJ_DIR)/release

# Set naming conventions for object files
DEBUG_OBJS = $(patsubst $(SRC_DIR)/%.c,$(DEBUG_OBJ_DIR)/%.o,$(SRCS)) # src/file.c -> debug/file.o
RELEASE_OBJS = $(patsubst $(SRC_DIR)/%.c,$(RELEASE_OBJ_DIR)/%.o,$(SRCS)) # src/file.c -> release/file.o

# Benchmark directories
BENCH_DIR = benchmarks
BENCH_BIN = $(BENCH_DIR)/bin

# Java benchmark files
JAVA_SRC = $(BENCH_DIR)/CalcPi.java
JAVA_CLASS = $(BENCH_BIN)/benchmarks/CalcPi.class

# C benchmark files
C_BENCH_SRC = $(BENCH_DIR)/calc_pi.c
C_BENCH_EXE = $(BENCH_BIN)/calc_pi

# Go benchmark files
GO_BENCH_SRC = $(BENCH_DIR)/calc_pi.go
GO_BENCH_EXE = $(BENCH_BIN)/calc_pi_go

# Compile Flags for C builds
CFLAGS = -Wall -Wextra -I$(INC_DIR)

# Targets for binaries
.PHONY: all
all: $(BIN_DIR)/run $(BIN_DIR)/run_debug $(JAVA_CLASS) $(C_BENCH_EXE) \
	$(BENCH_BIN)/calc_pi_1 $(BENCH_BIN)/calc_pi_2 $(BENCH_BIN)/calc_pi_3 \
	$(GO_BENCH_EXE)

# Build release object files
$(BIN_DIR)/run: $(RELEASE_OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(RELEASE_OBJS) -o $@

# Build release binary
$(RELEASE_OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(RELEASE_OBJ_DIR)
	$(CC) $(CFLAGS) -DDEBUG=0 -c $< -o $@

# Build debug object files
$(BIN_DIR)/run_debug: $(DEBUG_OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(DEBUG_OBJS) -o $@

# Build debug binary
$(DEBUG_OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(DEBUG_OBJ_DIR)
	$(CC) $(CFLAGS) -DDEBUG=1 -c $< -o $@

# Compile Java benchmark
$(JAVA_CLASS): $(JAVA_SRC)
	@mkdir -p $(BENCH_BIN)
	javac -d $(BENCH_BIN) $(JAVA_SRC)

# Compile Go benchmark
$(GO_BENCH_EXE): $(GO_BENCH_SRC)
	@mkdir -p $(BENCH_BIN)
	go build -o $(GO_BENCH_EXE) $(GO_BENCH_SRC)

# Compile C benchmark
$(C_BENCH_EXE): $(C_BENCH_SRC)
	@mkdir -p $(BENCH_BIN)
	$(CC) $(C_BENCH_SRC) -o $(C_BENCH_EXE)

# Compile C benchmark with -O1
$(BENCH_BIN)/calc_pi_1: $(C_BENCH_SRC)
	@mkdir -p $(BENCH_BIN)
	$(CC) $(CFLAGS) -O1 $< -o $@

# Compile C benchmark with -O2
$(BENCH_BIN)/calc_pi_2: $(C_BENCH_SRC)
	@mkdir -p $(BENCH_BIN)
	$(CC) $(CFLAGS) -O2 $< -o $@

# Compile C benchmark with -O3
$(BENCH_BIN)/calc_pi_3: $(C_BENCH_SRC)
	@mkdir -p $(BENCH_BIN)
	$(CC) $(CFLAGS) -O3 $< -o $@

# Clean build artifacts
.PHONY: clean
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) $(BENCH_BIN)

