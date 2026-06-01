.PHONY: all run release run-release clean test

CC := clang
CFLAGS := -g -O1 -fsanitize=address,undefined -fno-omit-frame-pointer
LDFLAGS := -fsanitize=address,undefined
SRC := main.c **/*.c
OUT := build/main

LDLIBS := \
	-lraylib -lGL -lm -lpthread -ldl -lrt -lX11 \
	-lavformat -lavcodec -lswscale -lavutil -lswresample

all:
	$(MAKE) clean
	echo "Building project..."
	mkdir -p build
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) $(LDFLAGS) $(LDLIBS)
run:
	$(MAKE) all
	./build/main

release: CFLAGS := -O2
release: LDFLAGS :=
release:
	$(MAKE) clean
	echo "Building release project..."
	mkdir -p build
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) $(LDFLAGS) $(LDLIBS)

run-release:
	$(MAKE) release
	./build/main

test: CFLAGS += -DTESTING
test: OUT := build/testing
test:
	$(MAKE) clean
	echo "Starting test suite..."
	mkdir -p build
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) $(LDFLAGS) $(LDLIBS)
	./$(OUT)
clean:
	echo "Cleaning up build artifacts..."
	rm -rf build/
	echo "Build artifacts removed."
