# Project Architecture

## Overview

The project follows a modular architecture based on separation of concerns: console utilities, user interface, encryption algorithms and entry point.

## Module Diagram

```
                    ┌─────────────┐
                    │   main.c    │
                    │  (Entry)    │
                    └──────┬──────┘
                           │
              ┌────────────┼────────────┐
              │            │            │
              ▼            ▼            ▼
        ┌──────────┐ ┌──────────┐ ┌──────────┐
        │ screens.c│ │animations│ │ icons.c  │
        │   (UI)   │ │   (.c)   │ │  (UI)    │
        └────┬─────┘ └──────────┘ └──────────┘
             │
    ┌────────┼────────────────┐
    │        │                │
    ▼        ▼                ▼
┌────────┐┌────────┐   ┌──────────┐
│simple.c││xor.c   │   │vigenere.c│
│(alg+IO)││(alg)   │   │  (alg)   │
└────┬───┘└────┬───┘   └────┬─────┘
     │         │            │
     └─────────┼────────────┘
               │
               ▼
        ┌──────────────┐
        │ console.c    │
        │ (Utilities)  │
        └──────────────┘
```

## Module Description

### 1. `main.c` - Entry Point

The main file contains only the `main()` function that orchestrates the program flow:

```
main() → login_screen() → main_menu()
```

It contains no business logic or presentation; it only coordinates calls to the main modules.

### 2. `include/enigma.h` - Main Header

Header file shared by all modules. Contains:

- **Enums:**
  - `EncryptionType` - Encryption types (SIMPLE, XOR, VIGERENE, RUN_LENGTH)
  - `MenuOption` - Menu options (ENCRYPTION, DECRYPTION, ABOUT, EXIT)
- **Keyboard constants:**
  - `KEY_UP`, `KEY_DOWN`, `KEY_LEFT`, `KEY_RIGHT`, `KEY_ENTER`, `KEY_ESC`
- **Function prototypes:** Declarations of all project functions
- **Global variables:** `extern FILE *doc;` for file handling

### 3. `src/utils/console.c` - Console Utilities

Abstraction layer over the Windows API for console operations:

| Function | Description |
|----------|-------------|
| `set_color_and_background()` | Sets text and background colors |
| `gotoxy()` | Positions cursor at coordinates (x, y) |
| `print_on_coord()` | Prints text using a COORD structure |
| `print_on_raw_coord()` | Prints text at x, y coordinates |
| `string_to_uppercase()` | Converts a string to uppercase |
| `clean_screen()` | Clears the screen (cls) |

### 4. `src/ui/screens.c` - Interface Screens

Contains all static screens and navigable menus:

| Function | Description |
|----------|-------------|
| `draw_login_form()` | Draws the visual login form |
| `authentication()` | Validates username against the "FMAT" constant |
| `login_screen()` | Main login loop until successful authentication |
| `draw_screen_border()` | Draws the decorative program border |
| `draw_message_input_form()` | Draws the text input form |
| `encryption_type_option_screen()` | Encryption type selection menu |
| `decryption_type_option_screen()` | Decryption type selection menu |
| `main_menu()` | Main menu with keyboard navigation |

**Menu navigation flow:**

```
main_menu()
    ├── ENCRYPTION → encryption_type_option_screen()
    │       ├── SIMPLE → simple_encryption()
    │       ├── XOR → xor_encryption()
    │       ├── VIGERENE → vigenere_encryption()
    │       └── RUN_LENGTH → run_length_encryption()
    ├── DECRYPTION → decryption_type_option_screen()
    │       ├── SIMPLE → simple_decryption()
    │       ├── XOR → xor_decryption()
    │       ├── VIGERENE → vigerene_decryption()
    │       └── RUN_LENGTH → run_length_decryption()
    ├── ABOUT → about_screen()
    └── EXIT → bye_animation()
```

### 5. `src/ui/icons.c` - ASCII Art Icons

Icons drawn with extended ASCII special characters:

- `padlock_close_icon()` - Closed padlock (shown when selecting "Encrypt")
- `padlock_open_icon()` - Open padlock (shown when processing encryption/decryption)
- `about_icon()` - Decorative "About" icon
- `exit_icon()` - Decorative "Exit" icon

### 6. `src/ui/animations.c` - Animations

Screen transition animations:

- `loading_animation()` - Progress bar when encrypting (shows "Encrypting message...")
- `decryption_animation()` - Progress bar when decrypting (shows "Decrypting message...")
- `about_screen()` - Developer presentation animation
- `bye_animation()` - Farewell animation with ASCII art

### 7. `src/algorithms/*.c` - Encryption Algorithms

Each file contains the implementation of a specific algorithm:

| File | Functions | Description |
|------|-----------|-------------|
| `simple.c` | `simple_encryption()`, `simple_decryption()`, `input_text()`, `save_text_to_file()` | Substitution cipher (shift +3). Also contains text input and file saving functions shared by all algorithms |
| `xor.c` | `xor_encryption()`, `xor_decryption()` | XOR encryption with 8-bit binary key |
| `vigenere.c` | `vigenere_encryption()`, `vigerene_decryption()` | Polyalphabetic encryption with key of up to 4 letters |
| `run_length.c` | `run_length_encryption()`, `run_length_decryption()` | Run-Length Encoding compression |

## General Program Flow

```
┌─────────────────────────────────────────────┐
│                  START                      │
│                                             │
│  main() → clean_screen() → login_screen()   │
└─────────────────┬───────────────────────────┘
                  │
                  ▼
┌─────────────────────────────────────────────┐
│              LOGIN SCREEN                   │
│                                             │
│  draw_screen_border()                       │
│  draw_login_form()                          │
│  authentication() → fgets("FMAT")           │
│  If incorrect: show error → retry           │
│  If correct: continue                       │
└─────────────────┬───────────────────────────┘
                  │
                  ▼
┌─────────────────────────────────────────────┐
│              MAIN MENU                      │
│                                             │
│  Navigation with keyboard arrows            │
│  ASCII icons per selected option            │
│  Enter to select                            │
│  Esc to return                              │
└─────────────────┬───────────────────────────┘
                  │
      ┌───────────┼───────────┬───────────┐
      ▼           ▼           ▼           ▼
   Encrypt    Decrypt      About       Exit
      │           │           │           │
      ▼           ▼           ▼           ▼
  Selection  Selection   Animation   Animation
  of type    of type     about       bye
      │           │
      ▼           ▼
  input_text()  Open mensaje.txt
      │           │
      ▼           ▼
  Encryption  Decryption
  algorithm   algorithm
      │           │
      ▼           ▼
  Save to     Show on
  mensaje.txt console
```

## Global Variables

| Variable | Type | Description |
|----------|------|-------------|
| `doc` | `FILE *` | Pointer to text file (mensaje.txt) |

Declared in `simple.c` and referenced via `extern` in `enigma.h`.

## Code Conventions

- **Naming:** snake_case for functions and variables
- **.c files:** Include `../../include/enigma.h` as relative path
- **Return values:** `1` (true) to return to menu, `0` (false) to continue
- **Keys:** Defined as `KEY_*` constants in the header
- **Coordinates:** Windows console coordinate system (x=column, y=row)
- **Build:** Object files and executable are generated in `build/`, excluded from repository via `.gitignore`
- **Backup:** Original monolithic source code is kept in `archive/` as reference
