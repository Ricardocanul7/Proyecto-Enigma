# Algoritmos de Cifrado

Este documento describe detalladamente los cuatro algoritmos de cifrado y descifrado implementados en el proyecto.

---

## 1. Cifrado Simple (César)

**Tipo:** Sustitución monoalfabética
**Complejidad:** Baja
**Archivo:** `src/algorithms/simple.c`

### Principio

Desplaza cada carácter del mensaje 3 posiciones hacia adelante en la tabla ASCII. Para descifrar, se realiza la operación inversa (restar 3).

### Cifrado

```
Mensaje original:  H O L A
ASCII:             72 79 76 65
+3:                75 82 79 68
Resultado:         K R O D
```

**Fórmula:** `cifrado[i] = original[i] + 3`

### Descifrado

**Fórmula:** `descifrado[i] = cifrado[i] - 3`

### Ejemplo

| Entrada | Salida |
|---------|--------|
| `HOLA`  | `KROD` |
| `hola`  | `krod` |

### Limitaciones

- Solo desplaza 3 posiciones (no es un cifrado César configurable)
- No maneja caracteres especiales de forma diferente
- Es un cifrado trivial, no apto para uso real de seguridad

---

## 2. Cifrado XOR

**Tipo:** Operación bitwise
**Complejidad:** Media
**Archivo:** `src/algorithms/xor.c`

### Principio

Opera cada bit del mensaje con una clave binaria de 8 bits usando la operación XOR (OR exclusivo):

| A | B | A XOR B |
|---|---|---------|
| 0 | 0 |    0    |
| 0 | 1 |    1    |
| 1 | 0 |    1    |
| 1 | 1 |    0    |

### Flujo del Cifrado

1. **Lectura del mensaje:** Se captura el texto a cifrar
2. **Conversión a binario:** Cada carácter se convierte a su representación binaria de 8 bits
3. **Ingreso de clave:** El usuario ingresa una clave binaria de 8 bits (ej: `10110110`)
4. **Operación XOR:** Se aplica XOR entre cada bit del mensaje y la clave
5. **Conversión a decimal:** Los resultados binarios se convierten a caracteres
6. **Guardado:** Se almacena en `mensaje.txt`

### Ejemplo

```
Carácter:  'A' (65)  →  01000001
Clave:                  10110110
XOR:                    11110111  →  247 → '˙'
```

### Flujo del Descifrado

1. Se lee el archivo `mensaje.txt`
2. Se solicita la misma clave binaria de 8 bits
3. Se aplica XOR entre cada carácter cifrado y la clave
4. El resultado es el mensaje original

### Notas

- La misma clave se usa para cifrar y descifrar (XOR es simétrico)
- El usuario debe recordar la clave para poder descifrar
- La clave debe ser exactamente de 8 bits (0s y 1s)

---

## 3. Cifrado Vigenère

**Tipo:** Sustitución polialfabética
**Complejidad:** Media
**Archivo:** `src/algorithms/vigenere.c`

### Principio

Utiliza una palabra clave de hasta 4 letras para desplazar cada carácter del mensaje. A diferencia de César, cada posición usa un desplazamiento diferente según la letra de la clave.

### Fórmula

**Cifrado:** `C[i] = (P[i] + K[i]) mod 26`
**Descifrado:** `P[i] = (C[i] - K[i] + 26) mod 26`

Donde:
- `P[i]` = posición del carácter plano (0-25 para A-Z)
- `K[i]` = posición de la letra de la clave (0-25 para A-Z)
- `C[i]` = posición del carácter cifrado

### Ejemplo

```
Mensaje:   H O L A
Clave:     K E Y
Desplaz.:  K(10) E(4) Y(24) K(10)  (repite)

H(7)  + K(10) = R(17)  →  R
O(14) + E(4)  = S(18)  →  S
L(11) + Y(24) = J(9)   →  J
A(0)  + K(10) = K(10)  →  K

Resultado: R S J K
```

### Flujo

1. Se captura el mensaje (se convierte a mayúsculas)
2. Se ingresa la clave (máximo 4 letras)
3. Se aplica la fórmula de cifrado para cada carácter alfabético
4. Los caracteres no alfabéticos se mantienen sin cambios
5. Se muestra el resultado y se guarda en `mensaje.txt`

### Características

- Solo cifra letras (A-Z), otros caracteres pasan sin cambios
- La clave se repite cíclicamente sobre el mensaje
- Ambas partes (mensaje y clave) se convierten a mayúsculas

---

## 4. Run-Length Encoding (Compresión)

**Tipo:** Compresión de datos
**Complejidad:** Baja
**Archivo:** `src/algorithms/run_length.c`

### Principio

Reemplaza secuencias de caracteres repetidos consecutivos con una representación compacta: el carácter seguido del número de repeticiones.

### Formato

```
#caracternum
```

Donde:
- `#` es el delimitador
- `caractern` es el carácter que se repite
- `num` es el número de veces que se repite

### Ejemplo

```
Entrada:   AAABBBCC
Salida:    #A3#B3#C2

Entrada:   AABCDE
Salida:    #A2BCDE
```

### Algoritmo de Cifrado

```
Para cada posición i del mensaje:
  Si el carácter actual == siguiente carácter:
    Incrementar contador de repeticiones
  Si no:
    Si el carácter actual == anterior carácter:
      Escribir # + carácter + contador
      Reiniciar contador
    Si no:
      Escribir el carácter tal cual
```

### Algoritmo de Descifrado

```
Para cada carácter del mensaje cifrado:
  Si es '#':
    Leer el siguiente carácter (el que se repite)
    Leer el siguiente dígito (número de repeticiones)
    Repetir el carácter esa cantidad de veces
  Si no:
    Copiar el carácter tal cual
```

### Ejemplo Detallado

**Entrada:** `AAAABBBCDDDEEE`

**Cifrado paso a paso:**
| Paso | Carácter | Siguiente | Acción | Salida parcial |
|------|----------|-----------|--------|----------------|
| 1 | A | A | Contar | - |
| 2 | A | A | Contar | - |
| 3 | A | A | Contar | - |
| 4 | A | B | Escribir #A4 | #A4 |
| 5 | B | B | Contar | - |
| 6 | B | B | Contar | - |
| 7 | B | C | Escribir #B3 | #A4#B3 |
| 8 | C | D | Escribir C | #A4#B3C |
| 9 | D | D | Contar | - |
| 10 | D | D | Contar | - |
| 11 | D | E | Escribir #D3 | #A4#B3C#D3 |
| 12 | E | E | Contar | - |
| 13 | E | - | Escribir #E2 | #A4#B3C#D3#E2 |

**Salida:** `#A4#B3C#D3#E2`

### Limitaciones

- Solo maneja repeticiones de un solo carácter
- No comprime eficientemente patrones complejos
- El carácter `#` se usa como delimitador (no se puede comprimir directamente)

---

## Comparación de Algoritmos

| Característica | Simple | XOR | Vigenère | Run-Length |
|----------------|--------|-----|----------|------------|
| **Tipo** | Sustitución | Bitwise | Polialfabético | Compresión |
| **Clave** | Ninguna (fija +3) | Binaria (8 bits) | Texto (4 letras) | Ninguna |
| **Caracteres** | Todos | Todos | Solo A-Z | Todos |
| **Reversible** | Sí | Sí (misma clave) | Sí (misma clave) | Sí |
| **Seguridad** | Muy baja | Baja | Baja | N/A (no es cifrado) |
| **Uso original** | Ejemplo educativo | Ejemplo educativo | Ejemplo educativo | Reducción de tamaño |

## Referencias

- [Cifrado César - Wikipedia](https://es.wikipedia.org/wiki/Cifrado_C%C3%A9sar)
- [Cifrado XOR - Wikipedia](https://es.wikipedia.org/wiki/Cifrado_XOR)
- [Cifrado de Vigenère - Wikipedia](https://es.wikipedia.org/wiki/Cifrado_de_Vigen%C3%A8re)
- [Run-Length Encoding - Wikipedia](https://es.wikipedia.org/wiki/Codificaci%C3%B3n_por_longitud_de_ejecuci%C3%B3n)
