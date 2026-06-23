# Encryption Algorithms

This document describes in detail the four encryption and decryption algorithms implemented in the project.

---

## 1. Simple Encryption (Caesar)

**Type:** Monoalphabetic substitution
**Complexity:** Low
**File:** `src/algorithms/simple.c`

### Principle

Shifts each character of the message 3 positions forward in the ASCII table. To decrypt, the inverse operation is performed (subtract 3).

### Encryption

```
Original message:  H O L A
ASCII:             72 79 76 65
+3:                75 82 79 68
Result:            K R O D
```

**Formula:** `encrypted[i] = original[i] + 3`

### Decryption

**Formula:** `decrypted[i] = encrypted[i] - 3`

### Example

| Input | Output |
|-------|--------|
| `HOLA`  | `KROD` |
| `hola`  | `krod` |

### Limitations

- Only shifts 3 positions (not a configurable Caesar cipher)
- Does not handle special characters differently
- It is a trivial cipher, not suitable for real security use

---

## 2. XOR Encryption

**Type:** Bitwise operation
**Complexity:** Medium
**File:** `src/algorithms/xor.c`

### Principle

Operates each bit of the message with an 8-bit binary key using the XOR operation (exclusive OR):

| A | B | A XOR B |
|---|---|---------|
| 0 | 0 |    0    |
| 0 | 1 |    1    |
| 1 | 0 |    1    |
| 1 | 1 |    0    |

### Encryption Flow

1. **Message reading:** The text to encrypt is captured
2. **Binary conversion:** Each character is converted to its 8-bit binary representation
3. **Key input:** The user enters an 8-bit binary key (e.g., `10110110`)
4. **XOR operation:** XOR is applied between each bit of the message and the key
5. **Decimal conversion:** Binary results are converted to characters
6. **Saving:** Stored in `mensaje.txt`

### Example

```
Character: 'A' (65)  ->  01000001
Key:                   10110110
XOR:                   11110111  ->  247 -> '˙'
```

### Decryption Flow

1. The file `mensaje.txt` is read
2. The same 8-bit binary key is requested
3. XOR is applied between each encrypted character and the key
4. The result is the original message

### Notes

- The same key is used for encryption and decryption (XOR is symmetric)
- The user must remember the key to decrypt later
- The key must be exactly 8 bits (0s and 1s)

---

## 3. Vigenere Encryption

**Type:** Polyalphabetic substitution
**Complexity:** Medium
**File:** `src/algorithms/vigenere.c`

### Principle

Uses a keyword of up to 4 letters to shift each character of the message. Unlike Caesar, each position uses a different shift based on the key letter.

### Formula

**Encryption:** `C[i] = (P[i] + K[i]) mod 26`
**Decryption:** `P[i] = (C[i] - K[i] + 26) mod 26`

Where:
- `P[i]` = position of plaintext character (0-25 for A-Z)
- `K[i]` = position of key letter (0-25 for A-Z)
- `C[i]` = position of encrypted character

### Example

```
Message:  H O L A
Key:      K E Y
Shift:    K(10) E(4) Y(24) K(10)  (repeats)

H(7)  + K(10) = R(17)  ->  R
O(14) + E(4)  = S(18)  ->  S
L(11) + Y(24) = J(9)   ->  J
A(0)  + K(10) = K(10)  ->  K

Result: R S J K
```

### Flow

1. The message is captured (converted to uppercase)
2. The key is entered (maximum 4 letters)
3. The encryption formula is applied for each alphabetic character
4. Non-alphabetic characters remain unchanged
5. The result is displayed and saved to `mensaje.txt`

### Characteristics

- Only encrypts letters (A-Z), other characters pass through unchanged
- The key repeats cyclically over the message
- Both parties (message and key) are converted to uppercase

---

## 4. Run-Length Encoding (Compression)

**Type:** Data compression
**Complexity:** Low
**File:** `src/algorithms/run_length.c`

### Principle

Replaces repeated character sequences with a compact representation: the character followed by the number of repetitions.

### Format

```
#characternum
```

Where:
- `#` is the delimiter
- `character` is the character that repeats
- `num` is the number of times it repeats

### Example

```
Input:    AAABBBCC
Output:   #A3#B3#C2

Input:    AABCDE
Output:   #A2BCDE
```

### Encryption Algorithm

```
For each position i of the message:
  If current character == next character:
    Increment repetition counter
  Else:
    If current character == previous character:
      Write # + character + counter
      Reset counter
    Else:
      Write the character as is
```

### Decryption Algorithm

```
For each character of the encrypted message:
  If '#':
    Read next character (the one that repeats)
    Read next digit (number of repetitions)
    Repeat the character that many times
  Else:
    Copy the character as is
```

### Detailed Example

**Input:** `AAAABBBCDDDEEE`

**Step-by-step encryption:**
| Step | Character | Next | Action | Partial Output |
|------|-----------|------|--------|----------------|
| 1 | A | A | Count | - |
| 2 | A | A | Count | - |
| 3 | A | A | Count | - |
| 4 | A | B | Write #A4 | #A4 |
| 5 | B | B | Count | - |
| 6 | B | B | Count | - |
| 7 | B | C | Write #B3 | #A4#B3 |
| 8 | C | D | Write C | #A4#B3C |
| 9 | D | D | Count | - |
| 10 | D | D | Count | - |
| 11 | D | E | Write #D3 | #A4#B3C#D3 |
| 12 | E | E | Count | - |
| 13 | E | - | Write #E2 | #A4#B3C#D3#E2 |

**Output:** `#A4#B3C#D3#E2`

### Limitations

- Only handles single character repetitions
- Does not compress complex patterns efficiently
- The `#` character is used as delimiter (cannot be compressed directly)

---

## Algorithm Comparison

| Characteristic | Simple | XOR | Vigenere | Run-Length |
|----------------|--------|-----|----------|------------|
| **Type** | Substitution | Bitwise | Polyalphabetic | Compression |
| **Key** | None (fixed +3) | Binary (8 bits) | Text (4 letters) | None |
| **Characters** | All | All | Only A-Z | All |
| **Reversible** | Yes | Yes (same key) | Yes (same key) | Yes |
| **Security** | Very low | Low | Low | N/A (not encryption) |
| **Original use** | Educational example | Educational example | Educational example | Size reduction |

## References

- [Caesar Cipher - Wikipedia](https://en.wikipedia.org/wiki/Caesar_cipher)
- [XOR Cipher - Wikipedia](https://en.wikipedia.org/wiki/XOR_cipher)
- [Vigenere Cipher - Wikipedia](https://en.wikipedia.org/wiki/Vigenere_cipher)
- [Run-Length Encoding - Wikipedia](https://en.wikipedia.org/wiki/Run-length_encoding)
