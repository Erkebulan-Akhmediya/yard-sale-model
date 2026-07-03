# Choose which module to build: make MODULE=viz  or  make MODULE=sim
MODULE ?= viz

CC = gcc
ifeq ($(MODULE),viz)
CFLAGS = -O2 -I C:\raylib\w64devkit\include
LDFLAGS = -L C:\raylib\w64devkit\lib -lraylib -lopengl32 -lgdi32 -lwinmm
else
CFLAGS = -O2
LDFLAGS =
endif
CFLAGS += -Wall -Wextra

SRCS = $(filter-out $(MODULE)/bst_test.c,$(wildcard $(MODULE)/*.c))
OBJS = $(SRCS:.c=.o)
TARGET = $(MODULE).exe

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LDFLAGS)

$(MODULE)/%.o: $(MODULE)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all viz sim clean
all: viz sim

viz:
	$(MAKE) MODULE=viz

sim:
	$(MAKE) MODULE=sim

clean:
	del /Q viz\*.o sim\*.o