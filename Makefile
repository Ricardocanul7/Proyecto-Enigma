# Makefile - Proyecto Enigma
# Universidad Autónoma de Yucatán
# Compila la aplicación EnigmaProject

# Detecta automáticamente el compilador disponible
# Si tienes gcc instalado, usará gcc. Si no, usarás cl.exe (Visual C++)
CXX = gcc
INCLUDE_PATH = -Iinclude
SOURCE_FILES = \
    main.c \
    src/utils/console.c \
    src/ui/screens.c \
    src/ui/icons.c \
    src/ui/animations.c \
    src/algorithms/simple.c \
    src/algorithms/run_length.c \
    src/algorithms/xor.c \
    src/algorithms/vigenere.c

TARGET = EnigmaProject

# Regla por defecto: compila todo
all: $(TARGET)

# Regla para compilar el ejecutable principal (gcc/g++)
$(TARGET): $(SOURCE_FILES)
	$(CXX) $(INCLUDE_PATH) -O2 $^ -o $@

# Reglas individuales para cada archivo fuente
src/utils/console.o: src/utils/console.c include/enigma.h
	$(CXX) $(INCLUDE_PATH) -c $< -o $@

src/ui/screens.o: src/ui/screens.c include/enigma.h
	$(CXX) $(INCLUDE_PATH) -c $< -o $@

src/ui/icons.o: src/ui/icons.c include/enigma.h
	$(CXX) $(INCLUDE_PATH) -c $< -o $@

src/ui/animations.o: src/ui/animations.c include/enigma.h
	$(CXX) $(INCLUDE_PATH) -c $< -o $@

src/algorithms/simple.o: src/algorithms/simple.c include/enigma.h
	$(CXX) $(INCLUDE_PATH) -c $< -o $@

src/algorithms/run_length.o: src/algorithms/run_length.c include/enigma.h
	$(CXX) $(INCLUDE_PATH) -c $< -o $@

src/algorithms/xor.o: src/algorithms/xor.c include/enigma.h
	$(CXX) $(INCLUDE_PATH) -c $< -o $@

src/algorithms/vigenere.o: src/algorithms/vigenere.c include/enigma.h
	$(CXX) $(INCLUDE_PATH) -c $< -o $@

main.o: main.c include/enigma.h
	$(CXX) $(INCLUDE_PATH) -c $< -o $@

# Limpia todos los archivos objeto y el ejecutable (para gcc)
clean:
	rm -f $(TARGET) *.o *.obj *.dll.a .libs

# Limpia completo  
distclean: clean
	rm -rf src/*.o include/*.o *.o

# Dependencias de cabecera
include/enigma.h:
	mkdir include
	touch include/enigma.h

.PHONY: all clean distclean