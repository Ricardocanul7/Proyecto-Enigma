# Guía de Instalación

## Requisitos Previos

### Sistema Operativo

- **Windows** (7, 8, 10 o 11)
- El programa usa API exclusivas de Windows (`windows.h`, `conio.h`) y no es compatible con Linux o macOS

### Compilador

Opción A: **GCC** (recomendado)
- [MinGW-w64](https://www.mingw-w64.org/) o [MSYS2](https://www.msys2.org/)
- Asegurarse de que `gcc` esté en el PATH del sistema

Opción B: **Microsoft Visual C++**
- [Visual Studio](https://visualstudio.microsoft.com/) con trabajo de carga "Desarrollo de Escritorio con C++"
- Usar el símbolo del sistema de Developer

## Instalación

### Opción 1: Compilar con Make (recomendado)

1. Clonar o descargar el repositorio:
```bash
git clone <url-del-repositorio>
cd Proyecto-Enigma
```

2. Compilar con make:
```bash
make
```

3. Ejecutar:
```bash
./build/EnigmaProject.exe
```

### Opción 2: Compilar con GCC directamente

```bash
gcc -Iinclude -O2 main.c src/utils/console.c src/ui/screens.c src/ui/icons.c src/ui/animations.c src/algorithms/simple.c src/algorithms/run_length.c src/algorithms/xor.c src/algorithms/vigenere.c -o build/EnigmaProject.exe
```

### Opción 3: Compilar con Visual C++ (cl.exe)

Desde el símbolo del sistema de Developer:

```batch
cl main.c src\utils\console.c src\ui\screens.c src\ui\icons.c src\ui\animations.c src\algorithms\simple.c src\algorithms\run_length.c src\algorithms\xor.c src\algorithms\vigenere.c /Fe:build\EnigmaProject.exe /Iinclude
```

## Verificación

1. Ejecutar `build/EnigmaProject.exe`
2. Aparecerá la pantalla de login
3. Ingresar el usuario: **FMAT**
4. Si el menú principal aparece correctamente, la compilación fue exitosa

## Solución de Problemas

### "gcc no se reconoce como comando"

GCC no está en el PATH. Soluciones:
- **MinGW:** Agregar `C:\msys64\mingw64\bin` al PATH del sistema
- **MSYS2:** Usar la terminal MSYS2 para compilar

### "No se puede encontrar windows.h"

El compilador no tiene los headers de Windows. Soluciones:
- Usar MinGW-w64 en lugar de un GCC nativo de Linux
- En Visual Studio, asegurarse de instalar el trabajo de carga "C++ Desktop Development"

### El programa se cierra inmediatamente

Verificar que la terminal de consola se mantenga abierta. Si se ejecuta desde el explorador de Windows, la ventana se cerrará al terminar. Usar una terminal de comandos para ejecutar.

### Errores de Unicode/caracteres especiales

El programa usa caracteres de código ASCII extendido para los iconos. Asegurarse de que la consola esté configurada con la página de códigos 437 o UTF-8.

## Estructura de Archivos Resultante

Después de compilar, se generará:

```
Proyecto-Enigma/
├── build/
│   └── EnigmaProject.exe  ← Ejecutable generado
├── main.c
├── Makefile
├── include/
├── src/
├── archive/
└── docs/
```

## Desinstalación

Simplemente eliminar la carpeta del proyecto. No se instalan archivos en el sistema.
