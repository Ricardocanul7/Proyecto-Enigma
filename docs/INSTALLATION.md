# Installation Guide

## Prerequisites

### Operating System

- **Windows** (7, 8, 10 or 11)
- The program uses Windows-only APIs (`windows.h`, `conio.h`) and is not compatible with Linux or macOS

### Compiler

Option A: **GCC** (recommended)
- [MinGW-w64](https://www.mingw-w64.org/) or [MSYS2](https://www.msys2.org/)
- Make sure `gcc` is in the system PATH

Option B: **Microsoft Visual C++**
- [Visual Studio](https://visualstudio.microsoft.com/) with the "Desktop Development with C++" workload
- Use the Developer Command Prompt

## Installation

### Option 1: Build with Make (recommended)

1. Clone or download the repository:
```bash
git clone <repository-url>
cd Proyecto-Enigma
```

2. Build with make:
```bash
make
```

3. Run:
```bash
./build/EnigmaProject.exe
```

### Option 2: Compile with GCC directly

```bash
gcc -Iinclude -O2 main.c src/utils/console.c src/ui/screens.c src/ui/icons.c src/ui/animations.c src/algorithms/simple.c src/algorithms/run_length.c src/algorithms/xor.c src/algorithms/vigenere.c -o build/EnigmaProject.exe
```

### Option 3: Compile with Visual C++ (cl.exe)

From the Developer Command Prompt:

```batch
cl main.c src\utils\console.c src\ui\screens.c src\ui\icons.c src\ui\animations.c src\algorithms\simple.c src\algorithms\run_length.c src\algorithms\xor.c src\algorithms\vigenere.c /Fe:build\EnigmaProject.exe /Iinclude
```

## Verification

1. Run `build/EnigmaProject.exe`
2. The login screen will appear
3. Enter the username: **FMAT**
4. If the main menu appears correctly, the compilation was successful

## Troubleshooting

### "gcc is not recognized as an internal or external command"

GCC is not in the PATH. Solutions:
- **MinGW:** Add `C:\msys64\mingw64\bin` to the system PATH
- **MSYS2:** Use the MSYS2 terminal to compile

### "Cannot find windows.h"

The compiler does not have the Windows headers. Solutions:
- Use MinGW-w64 instead of a native Linux GCC
- In Visual Studio, make sure to install the "C++ Desktop Development" workload

### Program closes immediately

Make sure the console terminal stays open. If run from Windows Explorer, the window will close when finished. Use a command terminal to run.

### Unicode/special character errors

The program uses extended ASCII code characters for the icons. Make sure the console is set to code page 437 or UTF-8.

## Resulting File Structure

After compiling, the following will be generated:

```
Proyecto-Enigma/
├── build/
│   └── EnigmaProject.exe  <- Generated executable
├── main.c
├── Makefile
├── include/
├── src/
├── archive/
└── docs/
```

## Uninstallation

Simply delete the project folder. No files are installed on the system.
