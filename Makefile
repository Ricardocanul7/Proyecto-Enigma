# Makefile - Proyecto Enigma
# Universidad Autonoma de Yucatan
# Compila la aplicacion EnigmaProject

# Detecta automaticamente el compilador disponible
CXX = gcc
INCLUDE_PATH = -Iinclude

# Directorio de salida
BUILD_DIR = build

SOURCE_FILES = \
    main.c \
    src/utils/console.c \
    src/utils/file_io.c \
    src/ui/screens.c \
    src/ui/icons.c \
    src/ui/animations.c \
    src/algorithms/simple.c \
    src/algorithms/run_length.c \
    src/algorithms/xor.c \
    src/algorithms/vigenere.c

# Archivos objeto en build/
OBJECT_FILES = $(patsubst %.c,$(BUILD_DIR)/%.o,$(SOURCE_FILES))

TARGET = $(BUILD_DIR)/EnigmaProject.exe

# Test files
TEST_SOURCE_FILES = \
    tests/test_main.c \
    tests/test_simple.c \
    tests/test_xor.c \
    tests/test_vigenere.c \
    tests/test_run_length.c

TEST_OBJECT_FILES = $(patsubst %.c,$(BUILD_DIR)/%.o,$(TEST_SOURCE_FILES))
TEST_TARGET = $(BUILD_DIR)/EnigmaTests.exe

# Regla por defecto: compila todo
all: $(TARGET)

# Crear directorio build antes de compilar
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Regla para compilar el ejecutable principal
$(TARGET): $(OBJECT_FILES) | $(BUILD_DIR)
	$(CXX) $(INCLUDE_PATH) -O2 $^ -o $@

# Reglas individuales para cada archivo fuente
$(BUILD_DIR)/main.o: main.c include/enigma.h | $(BUILD_DIR)
	$(CXX) $(INCLUDE_PATH) -c $< -o $@

$(BUILD_DIR)/src/utils/console.o: src/utils/console.c include/enigma.h | $(BUILD_DIR)
	@mkdir -p $(BUILD_DIR)/src/utils
	$(CXX) $(INCLUDE_PATH) -c $< -o $@

$(BUILD_DIR)/src/utils/file_io.o: src/utils/file_io.c include/enigma.h | $(BUILD_DIR)
	@mkdir -p $(BUILD_DIR)/src/utils
	$(CXX) $(INCLUDE_PATH) -c $< -o $@

$(BUILD_DIR)/src/ui/screens.o: src/ui/screens.c include/enigma.h | $(BUILD_DIR)
	@mkdir -p $(BUILD_DIR)/src/ui
	$(CXX) $(INCLUDE_PATH) -c $< -o $@

$(BUILD_DIR)/src/ui/icons.o: src/ui/icons.c include/enigma.h | $(BUILD_DIR)
	@mkdir -p $(BUILD_DIR)/src/ui
	$(CXX) $(INCLUDE_PATH) -c $< -o $@

$(BUILD_DIR)/src/ui/animations.o: src/ui/animations.c include/enigma.h | $(BUILD_DIR)
	@mkdir -p $(BUILD_DIR)/src/ui
	$(CXX) $(INCLUDE_PATH) -c $< -o $@

$(BUILD_DIR)/src/algorithms/simple.o: src/algorithms/simple.c include/enigma.h | $(BUILD_DIR)
	@mkdir -p $(BUILD_DIR)/src/algorithms
	$(CXX) $(INCLUDE_PATH) -c $< -o $@

$(BUILD_DIR)/src/algorithms/run_length.o: src/algorithms/run_length.c include/enigma.h | $(BUILD_DIR)
	@mkdir -p $(BUILD_DIR)/src/algorithms
	$(CXX) $(INCLUDE_PATH) -c $< -o $@

$(BUILD_DIR)/src/algorithms/xor.o: src/algorithms/xor.c include/enigma.h | $(BUILD_DIR)
	@mkdir -p $(BUILD_DIR)/src/algorithms
	$(CXX) $(INCLUDE_PATH) -c $< -o $@

$(BUILD_DIR)/src/algorithms/vigenere.o: src/algorithms/vigenere.c include/enigma.h | $(BUILD_DIR)
	@mkdir -p $(BUILD_DIR)/src/algorithms
	$(CXX) $(INCLUDE_PATH) -c $< -o $@

# Test rules
$(BUILD_DIR)/tests/%.o: tests/%.c include/enigma.h tests/test.h | $(BUILD_DIR)
	@mkdir -p $(BUILD_DIR)/tests
	$(CXX) $(INCLUDE_PATH) -c $< -o $@

$(TEST_TARGET): $(TEST_OBJECT_FILES) $(filter-out $(BUILD_DIR)/main.o,$(OBJECT_FILES)) | $(BUILD_DIR)
	$(CXX) $(INCLUDE_PATH) $^ -o $@

test: $(TEST_TARGET)
	$(TEST_TARGET)

# Limpia el directorio build
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean test
