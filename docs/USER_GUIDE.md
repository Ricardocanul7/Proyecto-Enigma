# User Manual

## Start

When you run `build/EnigmaProject.exe`, the login screen will appear.

### Login

```
┌─────────────────────────────────────────────────┐
│                                                 │
│           ___       _                           │
│          | __>._ _ <_> ___.._ _ _  ____         │
│          | _> |   || |/ . || Y Y |<_>  |        │
│          |___>|_|_||_|\_. ||_|_|_|<____|©       │
│                       <___:                     │
│                                                 │
│         ┌─────────────────────┐                 │
│         │                     │                 │
│         │      FMAT           │                 │
│         └─────────────────────┘                 │
│                   USER                          │
└─────────────────────────────────────────────────┘
```

1. Enter the username: **FMAT**
2. Press **Enter**
3. If incorrect, "Incorrect!" will appear and you must retry
4. If correct, you will access the main menu

## Main Menu

```
┌─────────────────────────────────────────────────────┐
│                                                     │
│  --> Encrypt                     [padlock icon]     │
│                                                     │
│      Decrypt                     [padlock icon]     │
│                                                     │
│      About                       [info icon]        │
│                                                     │
│      Exit                        [exit icon]        │
│                                                     │
└─────────────────────────────────────────────────────┘
```

### Navigation

| Key | Action |
|-----|--------|
| Up Arrow | Move selection up |
| Down Arrow | Move selection down |
| Enter | Select option |
| Esc | Return to previous menu |

## Encrypt Message

### Step 1: Select encryption type

```
┌─────────────────────────────────────────────────────┐
│                                                     │
│          * SELECT ENCRYPTION TYPE *                 │
│                                                     │
│    --> 1.-SIMPLE            3.-VIGENERE             │
│                                                     │
│        2.-XOR               4.-RUN LENGTH           │
│                               (COMPRESSOR)          │
│                                                     │
└─────────────────────────────────────────────────────┘
```

Use the arrow keys to navigate and **Enter** to select.

### Step 2: Enter the message

```
┌─────────────────────────────────────────────────────┐
│▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓│
│▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓│
│▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓│
│▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓│
│▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓│
│▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓│
│▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓│
│▓▓ MESSAGE ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓│
│▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓│
└─────────────────────────────────────────────────────┘
```

- Type your message directly
- The text is displayed on screen as you type
- **Backspace** to delete characters
- **Esc** to cancel and return to menu
- **Enter** to finish input

### Step 3: Encryption process

A loading animation will appear while the message is processed.

### Step 4: Result

The encrypted message is displayed on screen and automatically saved to the file `mensaje.txt`.

## Decrypt Message

### Step 1: Select decryption type

Same as encryption, select the algorithm that corresponds to the one used for encryption.

### Step 2: Decryption process

- **Simple:** Automatically reads from `mensaje.txt`
- **XOR:** Requests the 8-bit binary key used for encryption
- **Vigenere:** Requests the text key of up to 4 letters
- **Run-Length:** Automatically reads from `mensaje.txt`

### Step 3: Result

The decrypted message is displayed on the screen.

## About

Shows information about the project developers with a presentation animation.

## Exit

Shows a farewell animation and closes the program.

## Available Algorithms

| Algorithm | Required Key | Generated File |
|-----------|--------------|----------------|
| Simple | No | mensaje.txt |
| XOR | Yes (8-bit binary) | mensaje.txt |
| Vigenere | Yes (text, max 4 letters) | mensaje.txt |
| Run-Length | No | mensaje.txt |

## Tips

1. **Save the key:** If using XOR or Vigenere, write down the key used so you can decrypt later
2. **mensaje.txt file:** Generated/updated in the same folder as the executable
3. **Same key for decryption:** Use exactly the same key you used for encryption
4. **Case sensitive:** Vigenere converts everything to uppercase automatically
5. **Cancel operation:** Press **Esc** at any time to return to the menu

## Common Troubleshooting

| Problem | Solution |
|---------|----------|
| I can't return to the menu | Press **Esc** |
| Encrypted message not displayed | Verify that `mensaje.txt` exists in the program folder |
| "FILE NOT FOUND" | Make sure `mensaje.txt` is in the same folder as the executable |
| Screen appears corrupted | Run `cls` in the console or restart the program |
| Vigenere encryption not working | Verify that the key has only letters (maximum 4) |
