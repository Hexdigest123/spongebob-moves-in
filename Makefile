.PHONY: all run clean test

all:
	$(MAKE) clean
	echo "Building project..."
	mkdir build
	gcc main.c -o build/main -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
run:
	./build/main
test:
	$(MAKE) clean
	echo "Starting test suite..."
	mkdir build
	gcc main.c -o build/main -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -DTESTING
	$(MAKE) run
clean:
	echo "Cleaning up build artifacts..."
	rm -rf build/
	echo "Build artifacts removed."

