# EnigmaProject - Project Restructured

## Audit Summary

A complete audit was performed on the `EnigmaProject-ver_1.0.c` file (approximately 1700 lines).
The project presents the following organizational issues:

### Identified Problems:
- **All code is in a single file:** The 1700+ lines are in `EnigmaProject-ver_1.0.c`, which makes it difficult to:
  - Maintenance and debugging
  - Modular compilation
  - Incremental updates
  - Team collaboration

## New Project Structure

```
Proyecto-Enigma/
├── main.c                              # Entry point
├── include/
│   └── enigma.h                        # Header with enums, constants and prototypes
├── src/
│   ├── utils/
│   │   └── console.c                   # Console functions (set_color, gotoxy, print_on_coord)
│   ├── ui/
│   │   ├── screens.c                   # UI functions (login, menu, screens)
│   │   ├── icons.c                     # ASCII art icons (padlock, about, exit)
│   │   └── animations.c               # Loading and farewell animations
│   └── algorithms/
│       ├── simple.c                    # Simple encryption/decryption
│       ├── run_length.c                # Run-Length Encoding (compressor)
│       ├── xor.c                       # XOR encryption/decryption
│       └── vigenere.c                  # Vigenere encryption/decryption
├── README.md                           # This file
├── REORGANIZATION_README.md            # Migration guide
├── USUARIO para poder usar el Programa.txt  # User manual
├── Proyecto_encriptacion.pdf            # PDF documentation
├── Proyecto_Enigma_Manual_Usuario.pdf   # User manual (PDF)
└── readme-media/                       # Reference images
```

## Reorganized Files Description

### 1. **main.c** - Main File
- Program entry point
- Basic logic: login screen → main menu
- Includes only necessary declarations

### 2. **include/enigma.h** - Header File
- Contains all enums (EncryptionType, MenuOption)
- Key definitions (KEY_UP, KEY_DOWN, etc.)
- All function prototypes organized by category
- Globally declared external variables

### 3. **src/utils/console.c** - Console Utilities
- `set_color_and_background()` - Console colors
- `gotoxy()` - Console positioning
- `print_on_coord()` / `print_on_raw_coord()` - Printing
- `string_to_uppercase()` - Uppercase conversion
- `clean_screen()` - Screen clearing

### 4. **src/ui/screens.c** - Screen Interface
- `draw_login_form()` - Visual login form
- `authentication()` - USER validation (FMAT)
- `login_screen()` - Complete login screen
- `draw_screen_border()` - Decorative border with ASCII art
- `encryption_type_option_screen()` - Encryption type selection
- `decryption_type_option_screen()` - Decryption type selection
- `main_menu()` - Program main menu

### 5. **src/ui/icons.c** - Graphic Icons
- `padlock_close_icon()` - Closed padlock (encrypting)
- `padlock_open_icon()` - Open padlock (decrypting)
- `about_icon()` - "About" icon
- `exit_icon()` - "Exit" icon

### 6. **src/ui/animations.c** - Animations
- `loading_animation()` - Loading animation when encrypting
- `decryption_animation()` - Decryption animation
- `about_screen()` - Project information screen
- `bye_animation()` - Farewell animation

### 7. **src/algorithms/*.c** - Encryption/Decryption Algorithms

#### simple.c
- `simple_encryption()` - Encryption without changes
- `simple_decryption()` - Decryption without changes
- `input_text()` - Text input capture
- `save_text_to_file()` - Save to mensaje.txt

#### run_length.c (Compressor)
- `run_length_encryption()` - Run-Length Encoding
- `run_length_decryption()` - Compressor decryption

#### xor.c
- `xor_encryption()` - XOR operation encryption
- `xor_decryption()` - XOR decryption

#### vigenere.c
- `vigenere_encryption()` - Vigenere encryption
- `vigerene_decryption()` - Vigenere decryption

## Advantages of the Reorganization

| Before | After |
|--------|-------|
| 1 monolithic file of 1700 lines | ~9 modular files organized by function |
| Difficult to find specific code | Logical structure and easy to navigate |
| All-at-once compilation | Possibility of incremental compilation |
| Difficulty working in team | Multiple developers can work simultaneously |
| Complex maintenance | Localized updates without affecting the rest |

## Build Instructions

### With Microsoft Visual C++ (cl.exe):
```batch
cl main.c src/utils/console.c src/ui/screens.c src/ui/icons.c ^
src/ui/animations.c src/algorithms/simple.c src/algorithms/run_length.c ^
src/algorithms/xor.c src/algorithms/vigenere.c /Fe:EnigmaProject.exe ^
/Iinclude /Od./
```

### With Visual Studio Build:
1. Create a new empty C++ Console Application project
2. Add `main.c` as the main file
3. Add all `.c` files from `src/` and `include/`
4. Set the include path to `/include`

## Instructions to Migrate from EnigmaProject-ver_1.0.c

### Step 1: Copy the new code
- Copy all new files to the corresponding folders
- Rename `EnigmaProject-ver_1.0.c` as backup (`EnigmaProject-v1.0_backup.c`)

### Step 2: Update the include folder
Make sure VS Code recognizes the header:
```json
// .vscode/c_cpp_properties.json
{
    "includePath": ["${workspaceFolder}/include", "**/*.h"],
    // ...
}
```

### Step 3: Compile and test
- Compile with the instructions above
- Test each algorithm individually

## Important Notes

1. **Do not delete the original file immediately** - Keep it as backup until verifying everything works correctly

2. **Global functions are already declared in include/enigma.h** - It is not necessary to duplicate them in main.c or individual files

3. **The ASCII color system (95, 124, etc.)** - These are ASCII keys for the console drawing characters. Keep them intact in all files.

## Recommended Next Steps

1. Create `compile.bat` file with the complete command
2. Create `.vscode/settings.json` for IntelliSense configuration
3. Refactor code within each file if necessary
4. Add additional comments to functions
5. Create unit tests for each algorithm

---

**Project Developers:**
- Arias Morales Marvin
- Canul Flota Ricardo
- Cordova Villamil Jorge
- Pool Alvarado Marco

**Universidad Autonoma de Yucatan - 2026**
