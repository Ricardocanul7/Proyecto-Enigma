# Arquitectura del Proyecto

## Visión General

El proyecto sigue una arquitectura modular basada en la separación de responsabilidades: utilidades de consola, interfaz de usuario, algoritmos de cifrado y punto de entrada.

## Diagrama de Módulos

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

## Descripción de Módulos

### 1. `main.c` - Punto de Entrada

El archivo principal contiene únicamente la función `main()` que orquesta el flujo del programa:

```
main() → login_screen() → main_menu()
```

No contiene lógica de negocio ni presentación; solo coordina las llamadas a los módulos principales.

### 2. `include/enigma.h` - Header Principal

Archivo de encabezado compartido por todos los módulos. Contiene:

- **Enums:**
  - `EncryptionType` - Tipos de cifrado (SIMPLE, XOR, VIGERENE, RUN_LENGTH)
  - `MenuOption` - Opciones del menú (ENCRYPTION, DECRYPTION, ABOUT, EXIT)
- **Constantes de teclado:**
  - `KEY_UP`, `KEY_DOWN`, `KEY_LEFT`, `KEY_RIGHT`, `KEY_ENTER`, `KEY_ESC`
- **Prototipos de funciones:** Declaraciones de todas las funciones del proyecto
- **Variables globales:** `extern FILE *doc;` para manejo de archivos

### 3. `src/utils/console.c` - Utilidades de Consola

Capa de abstracción sobre la API de Windows para operaciones de consola:

| Función | Descripción |
|---------|-------------|
| `set_color_and_background()` | Establece colores de texto y fondo |
| `gotoxy()` | Posiciona el cursor en coordenadas (x, y) |
| `print_on_coord()` | Imprime texto en una estructura COORD |
| `print_on_raw_coord()` | Imprime texto en coordenadas x, y |
| `string_to_uppercase()` | Convierte una cadena a mayúsculas |
| `clean_screen()` | Limpia la pantalla (cls) |

### 4. `src/ui/screens.c` - Pantallas de Interfaz

Contiene todas las pantallas estáticas y menús navegables:

| Función | Descripción |
|---------|-------------|
| `draw_login_form()` | Dibuja el formulario visual de login |
| `authentication()` | Valida el usuario contra la constante "FMAT" |
| `login_screen()` | Loop principal de login hasta autenticación exitosa |
| `draw_screen_border()` | Dibuja el borde decorativo del programa |
| `draw_message_input_form()` | Dibuja el formulario de entrada de texto |
| `encryption_type_option_screen()` | Menú de selección de tipo de cifrado |
| `decryption_type_option_screen()` | Menú de selección de tipo de descifrado |
| `main_menu()` | Menú principal con navegación por teclado |

**Flujo de navegación del menú:**

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

### 5. `src/ui/icons.c` - Iconos ASCII Art

Iconos dibujados con caracteres especiales de código ASCII extendido:

- `padlock_close_icon()` - Candado cerrado (se muestra al seleccionar "Encriptar")
- `padlock_open_icon()` - Candado abierto (se muestra al procesar cifrado/descifrado)
- `about_icon()` - Icono decorativo de "Acerca de"
- `exit_icon()` - Icono decorativo de "Salir"

### 6. `src/ui/animations.c` - Animaciones

Animaciones de transición entre pantallas:

- `loading_animation()` - Barra de progreso al cifrar (muestra "Cifrando mensaje...")
- `decryption_animation()` - Barra de progreso al descifrar (muestra "Descifrando mensaje...")
- `about_screen()` - Animación de presentación de los desarrolladores
- `bye_animation()` - Animación de despedida con arte ASCII

### 7. `src/algorithms/*.c` - Algoritmos de Cifrado

Cada archivo contiene la implementación de un algoritmo específico:

| Archivo | Funciones | Descripción |
|---------|-----------|-------------|
| `simple.c` | `simple_encryption()`, `simple_decryption()`, `input_text()`, `save_text_to_file()` | Cifrado por sustitución (shift +3). También contiene las funciones de entrada de texto y guardado en archivo, compartidas por todos los algoritmos |
| `xor.c` | `xor_encryption()`, `xor_decryption()` | Cifrado XOR con clave binaria de 8 bits |
| `vigenere.c` | `vigenere_encryption()`, `vigerene_decryption()` | Cifrado polialfabético con clave de hasta 4 letras |
| `run_length.c` | `run_length_encryption()`, `run_length_decryption()` | Compresión Run-Length Encoding |

## Flujo General del Programa

```
┌─────────────────────────────────────────────┐
│                 ARRANQUE                    │
│                                             │
│  main() → clean_screen() → login_screen()   │
└─────────────────┬───────────────────────────┘
                  │
                  ▼
┌─────────────────────────────────────────────┐
│              PANTALLA DE LOGIN              │
│                                             │
│  draw_screen_border()                       │
│  draw_login_form()                          │
│  authentication() → fgets("FMAT")           │
│  Si incorrecto: mostrar error → reintentar  │
│  Si correcto: continuar                     │
└─────────────────┬───────────────────────────┘
                  │
                  ▼
┌─────────────────────────────────────────────┐
│              MENÚ PRINCIPAL                 │
│                                             │
│  Navegación con flechas del teclado         │
│  Iconos ASCII según opción seleccionada     │
│  Enter para seleccionar                     │
│  Esc para regresar                          │
└─────────────────┬───────────────────────────┘
                  │
      ┌───────────┼───────────┬───────────┐
      ▼           ▼           ▼           ▼
  Encriptar  Desencriptar  Acerca de   Salir
      │           │           │           │
      ▼           ▼           ▼           ▼
  Selección  Selección   Animación   Animación
  de tipo    de tipo     about       bye
      │           │
      ▼           ▼
  input_text()  Abrir mensaje.txt
      │           │
      ▼           ▼
  Algoritmo   Algoritmo
  de cifrado  de descifrado
      │           │
      ▼           ▼
  Guardar en  Mostrar en
  mensaje.txt consola
```

## Variables Globales

| Variable | Tipo | Descripción |
|----------|------|-------------|
| `doc` | `FILE *` | Puntero al archivo de texto (mensaje.txt) |

Declarada en `simple.c` y referenciada via `extern` en `enigma.h`.

## Convenciones de Código

- **Nomenclatura:** snake_case para funciones y variables
- **Archivos .c:** Incluyen `../../include/enigma.h` como ruta relativa
- **Funciones de retorno:** `1` (true) para regresar al menú, `0` (false) para continuar
- **Teclas:** Definidas como constantes `KEY_*` en el header
- **Coordenadas:** Sistema de coordenadas de consola Windows (x=columna, y=fila)
