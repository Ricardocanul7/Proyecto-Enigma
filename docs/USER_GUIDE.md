# Manual de Usuario

## Inicio

Al ejecutar `EnigmaProject.exe`, aparecerá la pantalla de login.

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
│                   USUARIO                       │
└─────────────────────────────────────────────────┘
```

1. Ingrese el usuario: **FMAT**
2. Presione **Enter**
3. Si es incorrecto, aparecerá "¡Incorrecto!" y deberá reintentar
4. Si es correcto, accederá al menú principal

## Menú Principal

```
┌─────────────────────────────────────────────────────┐
│                                                     │
│  --> Encriptar                    [icono candado]   │
│                                                     │
│      Desencriptar                 [icono candado]   │
│                                                     │
│      Acerca de                    [icono info]      │
│                                                     │
│      Salir                        [icono exit]      │
│                                                     │
└─────────────────────────────────────────────────────┘
```

### Navegación

| Tecla | Acción |
|-------|--------|
| ↑ | Mover selección hacia arriba |
| ↓ | Mover selección hacia abajo |
| Enter | Seleccionar opción |
| Esc | Regresar al menú anterior |

## Encriptar Mensaje

### Paso 1: Seleccionar tipo de cifrado

```
┌─────────────────────────────────────────────────────┐
│                                                     │
│          * SELECCIONA TIPO DE CIFRADO *             │
│                                                     │
│    --> 1.-SIMPLE            3.-VIGERENE             │
│                                                     │
│        2.-XOR               4.-RUN LENGTH           │
│                               (COMPRESOR)           │
│                                                     │
└─────────────────────────────────────────────────────┘
```

Use las teclas de dirección para navegar y **Enter** para seleccionar.

### Paso 2: Ingresar el mensaje

```
┌─────────────────────────────────────────────────────┐
│▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓│
│▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓│
│▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓│
│▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓│
│▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓│
│▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓│
│▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓│
│▓▓ MENSAJE ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓│
│▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓│
└─────────────────────────────────────────────────────┘
```

- Escriba su mensaje directamente
- El texto se muestra en pantalla mientras se escribe
- **Backspace** para borrar caracteres
- **Esc** para cancelar y regresar al menú
- **Enter** para finalizar la entrada

### Paso 3: Proceso de cifrado

Aparecerá una animación de carga mientras se procesa el mensaje.

### Paso 4: Resultado

El mensaje cifrado se muestra en pantalla y se guarda automáticamente en el archivo `mensaje.txt`.

## Desencriptar Mensaje

### Paso 1: Seleccionar tipo de descifrado

Igual que en el cifrado, seleccione el algoritmo que corresponda al que se usó para cifrar.

### Paso 2: Proceso de descifrado

- **Simple:** Lee automáticamente de `mensaje.txt`
- **XOR:** Solicita la clave binaria de 8 bits que se usó para cifrar
- **Vigenère:** Solicita la clave de texto de hasta 4 letras
- **Run-Length:** Lee automáticamente de `mensaje.txt`

### Paso 3: Resultado

El mensaje descifrado se muestra en la pantalla.

## Acerca de

Muestra información sobre los desarrolladores del proyecto con una animación de presentación.

## Salir

Muestra una animación de despedida y cierra el programa.

## Algoritmos Disponibles

| Algoritmo | Clave requerida | Archivo generado |
|-----------|-----------------|------------------|
| Simple | No | mensaje.txt |
| XOR | Sí (binaria de 8 bits) | mensaje.txt |
| Vigenère | Sí (texto, máx 4 letras) | mensaje.txt |
| Run-Length | No | mensaje.txt |

## Consejos

1. **Guarde la clave:** Si usa XOR o Vigenère, anote la clave usada para poder descifrar después
2. **Archivo mensaje.txt:** Se genera/actualiza en la misma carpeta del ejecutable
3. **Misma clave para descifrar:** Use exactamente la misma clave que usó para cifrar
4. **Caso sensible:** Vigenère convierte todo a mayúsculas automáticamente
5. **Cancelar operación:** Presione **Esc** en cualquier momento para regresar al menú

## Solución de Problemas Comunes

| Problema | Solución |
|----------|----------|
| No puedo regresar al menú | Presione **Esc** |
| No se muestra el mensaje cifrado | Verifique que existe `mensaje.txt` en la carpeta del programa |
| "ARCHIVO NO ENCONTRADO" | Asegúrese de que `mensaje.txt` está en la misma carpeta que el ejecutable |
| La pantalla queda corrupta | Ejecute `cls` en la consola o reinicie el programa |
| No funciona el cifrado Vigenère | Verifique que la clave tenga solo letras (máximo 4) |
