# EnigmaProject - Estructura Reorganizada del Proyecto

## Resumen de la Auditoría

Se realizó una auditoría completa al archivo `EnigmaProject-ver_1.0.c` (aproximadamente 1700 líneas). 
El proyecto presenta los siguientes problemas de organización:

### Problemas Identificados:
- **Todo el código está en un solo archivo:** Los 1700+ líneas están en `EnigmaProject-ver_1.0.c`, lo que dificulta:
  - Mantenimiento y depuración
  - Compilación modular
  - Actualización incremental
  - Colaboración en equipo

## Nueva Estructura del Proyecto

```
Proyecto-Enigma/
├── main.c                              # Punto de entrada (entry point)
├── include/
│   └── enigma.h                        # Header con enums, constantes y prototipos
├── src/
│   ├── utils/
│   │   └── console.c                   # Funciones de consola (set_color, gotoxy, print_on_coord)
│   ├── ui/
│   │   ├── screens.c                   # Funciones UI (login, menu, pantallas)
│   │   ├── icons.c                     # Iconos ASCII art (padlock, about, exit)
│   │   └── animations.c                # Animaciones de carga y despedida
│   └── algorithms/
│       ├── simple.c                    # Cifrado/descifrado tipo simple
│       ├── run_length.c                # Run-Length Encoding (compresor)
│       ├── xor.c                       # Cifrado/descifrado XOR
│       └── vigenere.c                  # Cifrado/descifrado Vigenère
├── README.md                           # Este archivo
├── REORGANIZATION_README.md            # Guía de migración
├── USUARIO para poder usar el Programa.txt  # Manual del usuario
├── Proyecto_encriptacion.pdf            # Documentación PDF
├── Proyecto_Enigma_Manual_Usuario.pdf   # Manual del usuario (PDF)
└── readme-media/                       # Imágenes de referencia
```

## Descripción de los Archivos Reorganizados

### 1. **main.c** - Archivo Principal
- Punto de entrada del programa
- Lógica básica: pantalla de login → menú principal
- Incluye solo las declaraciones necesarias

### 2. **include/enigma.h** - Header File
- Contiene todos los enums (EncryptionType, MenuOption)
- Definiciones de teclas (KEY_UP, KEY_DOWN, etc.)
- Todos los prototipos de funciones organizados por categoría
- Variables globales declaradas externamente

### 3. **src/utils/console.c** - Utilidades de Consola
- `set_color_and_background()` - Colores del consola
- `gotoxy()` - Posicionamiento en la consola
- `print_on_coord()` / `print_on_raw_coord()` - Impresión
- `string_to_uppercase()` - Conversión a mayúsculas
- `clean_screen()` - Limpieza de pantalla

### 4. **src/ui/screens.c** - Interfaz de Pantallas
- `draw_login_form()` - Formulario de login visual
- `authentication()` - Validación del USUARIO (FMAT)
- `login_screen()` - Pantalla completa de login
- `draw_screen_border()` - Borde decorativo con ASCII art
- `encryption_type_option_screen()` - Selección de tipo de cifrado
- `decryption_type_option_screen()` - Selección de tipo de descifrado
- `main_menu()` - Menú principal del programa

### 5. **src/ui/icons.c** - Iconos Gráficos
- `padlock_close_icon()` - Candado cerrado (cifrando)
- `padlock_open_icon()` - Candado abierto (descifrando)
- `about_icon()` - Icono "Acerca de"
- `exit_icon()` - Icono "Salir"

### 6. **src/ui/animations.c** - Animaciones
- `loading_animation()` - Animación de carga al cifrar
- `decryption_animation()` - Animación de descifrado
- `about_screen()` - Pantalla de información del proyecto
- `bye_animation()` - Animación de despedida

### 7. **src/algorithms/*.c** - Algoritmos de Cifrado/Descifrado

#### simple.c
- `simple_encryption()` - Encriptación sin cambios
- `simple_decryption()` - Descifrado sin cambios  
- `input_text()` - Captura de texto de entrada
- `save_text_to_file()` - Guardado en mensaje.txt

#### run_length.c (Compresor)
- `run_length_encryption()` - Run-Length Encoding
- `run_length_decryption()` - Descifrado del compresor

#### xor.c
- `xor_encryption()` - Cifrado con operación XOR
- `xor_decryption()` - Descifrado con XOR

#### vigenere.c
- `vigenere_encryption()` - Cifrado Vigenère
- `vigerene_decryption()` - Descifrado Vigenère

## Ventajas de la Reorganización

| Antes | Después |
|-------|---------|
| 1 archivo monolítico de 1700 líneas | ~9 archivos modulares organizados por función |
| Difícil encontrar código específico | Estructura lógica y fácil de navegar |
| Compilación del todo junto | Posibilidad de compilación incremental |
| Dificultad para trabajar en equipo | Múltiples desarrolladores pueden trabajar simultáneamente |
| Mantenimiento complejo | Actualizaciones localizadas sin afectar el resto |

## Instrucciones de Compilación

### Con Microsoft Visual C++ (cl.exe):
```batch
cl main.c src/utils/console.c src/ui/screens.c src/ui/icons.c ^
src/ui/animations.c src/algorithms/simple.c src/algorithms/run_length.c ^
src/algorithms/xor.c src/algorithms/vigenere.c /Fe:EnigmaProject.exe ^
/Iinclude /Od./
```

### Con Build de Visual Studio:
1. Crear nuevo proyecto C++ Console Application vacía
2. Agregar `main.c` como archivo principal
3. Agregar todos los archivos `.c` de `src/` y `include/`
4. Establecer la ruta del include a `/include`

## Instrucciones para Migrar desde EnigmaProject-ver_1.0.c

### Paso 1: Copiar el nuevo código
- Copie todos los nuevos archivos en las carpetas correspondientes
- Renombre `EnigmaProject-ver_1.0.c` como backup (`EnigmaProject-v1.0_backup.c`)

### Paso 2: Actualizar la carpeta de include
Asegúrese de que VS Code reconozca el header:
```json
// .vscode/c_cpp_properties.json
{
    "includePath": ["${workspaceFolder}/include", "**/*.h"],
    // ...
}
```

### Paso 3: Compilar y probar
- Compile con las instrucciones arriba
- Pruebe cada algoritmo individualmente

## Notas Importantes

1. **No eliminar el archivo original inmediatamente** - Manténgalo como backup hasta verificar que todo funcione correctamente

2. **Las funciones globales ya están declaradas en include/enigma.h** - No es necesario duplicarlas en main.c o archivos individuales

3. **El sistema de colores ASCII (95, 124, etc.)** - Estas son las claves ASCII para los caracteres de dibujo del consola. Mantenerlos intactos en todos los archivos.

## Próximos Pasos Recomendados

1. ✅ Crear archivo `compile.bat` con el comando completo
2. Crear `.vscode/settings.json` para configuración de IntelliSense
3. Refactorizar código dentro de cada archivo si es necesario
4. Añadir comentarios adicionales a las funciones
5. Crear tests unitarios para cada algoritmo

---

**Desarrolladores del Proyecto:**
- Arias Morales Marvin
- Canul Flota Ricardo  
- Cordova Villamil Jorge
- Pool Alvarado Marco

**Universidad Autónoma de Yucatán - 2026**