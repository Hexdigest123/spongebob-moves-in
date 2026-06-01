.PHONY: all run release run-release clean test analyze new-scene

CC := clang
CFLAGS := -g -O1 -fsanitize=address,undefined -fno-omit-frame-pointer
LDFLAGS := -fsanitize=address,undefined
SRC := main.c $(filter-out templates/%,$(wildcard */*.c))
OUT := build/main
SCENE_DIR := scenes
SCENE_NAME := $(or $(NAME),$(word 2,$(MAKECMDGOALS)))
SCENE_TEMPLATE_C := templates/scene.template.c
SCENE_TEMPLATE_H := templates/scene.template.h

ifneq ($(filter new-scene,$(MAKECMDGOALS)),)
ifneq ($(word 2,$(MAKECMDGOALS)),)
$(word 2,$(MAKECMDGOALS)):
	@:
endif
endif

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

analyze:
	echo "Running static analysis..."
	@if ! analysis_output="$$(clang --analyze -Xanalyzer -analyzer-output=text $(SRC) 2>&1)"; then \
		printf '%s\n' "$$analysis_output"; \
		exit 1; \
	fi; \
	if [ -n "$$analysis_output" ]; then \
		printf '%s\n' "$$analysis_output"; \
		exit 1; \
	fi

new-scene:
	@set -e; \
	scene_name="$(SCENE_NAME)"; \
	if [ -z "$$scene_name" ]; then \
		printf 'Usage: make new-scene menu\n'; \
		exit 1; \
	fi; \
	case "$$scene_name" in \
		[0-9-]*|*[!A-Za-z0-9_-]*) \
			printf 'Scene name must start with a letter or underscore and contain only letters, numbers, underscores, and hyphens.\n'; \
			exit 1; \
			;; \
	esac; \
	if [ ! -f "$(SCENE_TEMPLATE_C)" ] || [ ! -f "$(SCENE_TEMPLATE_H)" ]; then \
		printf 'Scene templates are missing from templates/.\n'; \
		exit 1; \
	fi; \
	scene_file=$$(printf '%s' "$$scene_name" | tr '[:upper:]' '[:lower:]'); \
	if [ -e "$(SCENE_DIR)/$$scene_file.c" ] || [ -e "$(SCENE_DIR)/$$scene_file.h" ]; then \
		printf 'Scene "%s" already exists.\n' "$$scene_file"; \
		exit 1; \
	fi; \
	scene_symbol=$$(printf '%s' "$$scene_name" | tr '-' '_'); \
	scene_guard=$$(printf '%s_H' "$$scene_file" | tr '-' '_' | tr '[:lower:]' '[:upper:]'); \
	mkdir -p "$(SCENE_DIR)"; \
	sed -e "s/__SCENE_FILE__/$$scene_file/g" -e "s/__SCENE_SYMBOL__/$$scene_symbol/g" -e "s/__SCENE_GUARD__/$$scene_guard/g" "$(SCENE_TEMPLATE_C)" > "$(SCENE_DIR)/$$scene_file.c"; \
	sed -e "s/__SCENE_FILE__/$$scene_file/g" -e "s/__SCENE_SYMBOL__/$$scene_symbol/g" -e "s/__SCENE_GUARD__/$$scene_guard/g" "$(SCENE_TEMPLATE_H)" > "$(SCENE_DIR)/$$scene_file.h"; \
	printf 'Created scene "%s": %s/%s.c %s/%s.h\n' "$$scene_name" "$(SCENE_DIR)" "$$scene_file" "$(SCENE_DIR)" "$$scene_file"

clean:
	echo "Cleaning up build artifacts..."
	rm -rf build/
	echo "Build artifacts removed."
