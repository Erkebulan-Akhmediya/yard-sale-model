CC = gcc
CFLAGS = -O2 -I C:\raylib\w64devkit\include
LDFLAGS = -L C:\raylib\w64devkit\lib -lraylib -lopengl32 -lgdi32 -lwinmm

SRCS = $(wildcard viz/*.c)
OBJS = $(SRCS:.c=.o)
TARGET = viz.exe

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LDFLAGS)

viz/%.o: viz/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del /Q viz\*.o $(TARGET)

.PHONY: clean