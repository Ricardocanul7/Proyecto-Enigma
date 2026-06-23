# AGENTS.md

## Project Overview
**Proyecto Enigma** — A C-based encryption/decryption console application developed at Universidad Autónoma de Yucatán. Provides multiple cipher algorithms (Simple, XOR, Vigenère, Run-Length) with a Windows console UI.

## Build & Run

```bash
# Build the project
make

# Clean build artifacts
make clean

# Run the compiled executable
./build/EnigmaProject.exe
```

- **Compiler:** GCC (via Makefile, `CXX = gcc`)
- **Output:** `build/EnigmaProject.exe`
- **Include path:** `include/`

## Project Structure

```
├── main.c                  # Entry point
├── include/
│   └── enigma.h            # Central header (enums, prototypes, globals)
├── src/
│   ├── algorithms/         # Cipher implementations
│   │   ├── simple.c
│   │   ├── xor.c
│   │   ├── vigenere.c
│   │   └── run_length.c
│   ├── ui/                 # Console UI (screens, icons, animations)
│   │   ├── screens.c
│   │   ├── icons.c
│   │   └── animations.c
│   └── utils/
│       └── console.c       # Console helpers (gotoxy, colors, etc.)
├── build/                  # Compiled output (.o and .exe)
├── docs/                   # Documentation and media
└── archive/                # Legacy code
```

## Code Conventions
- Language: **C (C99+)**
- All function prototypes and enums live in `include/enigma.h`
- Functions use `snake_case`
- Enums use `PascalCase` values
- Windows-specific APIs (`<windows.h>`, `<conio.h>`) are used throughout
- No external dependencies beyond the Windows C runtime

## Key Notes
- This is a **Windows-only** application (uses `windows.h`, `conio.h`, `COORD`, etc.)
- Encryption algorithms are in `src/algorithms/` — each file implements one cipher (encryption + decryption)
- UI logic is separated into `src/ui/` (screens, icons, animations)
- Console utilities (color, cursor positioning) are in `src/utils/console.c`
- When adding new files, update both `SOURCE_FILES` and the corresponding build rule in the `Makefile`
