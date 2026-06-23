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

# Run unit tests
make test
```

- **Compiler:** GCC (via Makefile, `CXX = gcc`)
- **Output:** `build/EnigmaProject.exe`
- **Tests:** `build/EnigmaTests.exe`
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
├── tests/                  # Unit tests
│   ├── test.h              # Lightweight test framework (assert macros)
│   ├── test_main.c         # Test runner entry point
│   ├── test_simple.c       # Simple cipher tests
│   ├── test_xor.c          # XOR cipher tests
│   ├── test_vigenere.c     # Vigenere cipher tests
│   └── test_run_length.c   # Run-length encoding tests
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
- Each algorithm file exposes testable pure functions (e.g., `simple_encrypt_str`, `xor_encrypt_str`) alongside the UI-coupled `_encryption()`/`_decryption()` functions
- UI logic is separated into `src/ui/` (screens, icons, animations)
- Console utilities (color, cursor positioning) are in `src/utils/console.c`
- When adding new files, update both `SOURCE_FILES`/`TEST_SOURCE_FILES` and the corresponding build rule in the `Makefile`
- Unit tests use a lightweight framework in `tests/test.h` (no external dependencies)
- To add a new test: create `tests/test_<name>.c`, declare a `void test_<name>(void)` function, add `extern` declaration in `tests/test_main.c`, and add the `.c` file to `TEST_SOURCE_FILES` in `Makefile`
