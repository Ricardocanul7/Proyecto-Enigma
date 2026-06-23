/**
 * EnigmaProject - Header File con todos los Enums, Constantes y Prototipos
 * 
 * Universidad Autonoma de Yucatan
 * Proyecto de Encriptacion "ENIGMA"
 */

#ifndef ENIGMA_H
#define ENIGMA_H

#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

/** Enums de Tipos de Cifrado **/
typedef enum EncryptionTypes
{
	SIMPLE = 1,
	XOR = 2,
	VIGERENE = 3,
	RUN_LENGTH = 4
} EncryptionType;

/** Valores de Teclas del Teclado (con sus ASCII) **/
#define KEY_UP       72
#define KEY_DOWN     80
#define KEY_LEFT     75
#define KEY_RIGHT    77
#define KEY_ENTER    13
#define KEY_SPACE    32
#define KEY_ESC      27

/** Tipos de Menu **/
typedef enum MenuOptions
{
	ENCRYPTION,
	DECRYPTION,
	ABOUT,
	EXIT
} MenuOption;

/** Prototipos de Funciones de Utilidad **/
void set_color_and_background(int ForgC, int BackC);
int *gotoxy(int x, int y);
void print_on_coord(COORD coord, char str[]);
void print_on_raw_coord(int x, int y, char str[]);
void string_to_uppercase(char cadena[]);
void clean_screen(void);

/** Prototipos de Pantallas **/
void draw_login_form(void);
int authentication(void);
void login_screen(void);
void draw_screen_border(void);
void main_menu(void);
int encryption_type_option_screen(void);
int decryption_type_option_screen(void);
void draw_message_input_form(void);
void loading_animation(void);
void decryption_animation(void);
void about_screen(void);
void bye_animation(void);

/** Prototipos de Iconos **/
void padlock_close_icon(void);
void padlock_open_icon(void);
void about_icon(void);
void exit_icon(void);

/** Prototipos de Algoritmos de Cifrado **/
int simple_encryption(void);
int run_length_encryption(void);
int xor_encryption(void);
int vigenere_encryption(void);

/** Prototipos de Algoritmos de Descifrado **/
int simple_decryption(void);
int run_length_decryption(void);
int xor_decryption(void);
int vigerene_decryption(void);

/** Prototipos de Funciones de Input/Archivo **/
char *input_text(void);
bool save_text_to_file(char str[]);

/* Variables Globales */
extern FILE *doc;

#endif // ENIGMA_H