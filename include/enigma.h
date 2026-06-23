/**
 * EnigmaProject - Header File with all Enums, Constants and Prototypes
 *
 * Universidad Autonoma de Yucatan
 * ENIGMA Encryption Project
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

/** Buffer size for text input and processing **/
#define BUFFER_SIZE 910

/** Encryption Type Enums **/
typedef enum EncryptionTypes
{
	SIMPLE = 1,
	XOR = 2,
	VIGENERE = 3,
	RUN_LENGTH = 4
} EncryptionType;

/** Keyboard Key Values (ASCII) **/
#define KEY_UP       72
#define KEY_DOWN     80
#define KEY_LEFT     75
#define KEY_RIGHT    77
#define KEY_ENTER    13
#define KEY_SPACE    32
#define KEY_ESC      27

/** Menu Types **/
typedef enum MenuOptions
{
	ENCRYPTION,
	DECRYPTION,
	ABOUT,
	EXIT
} MenuOption;

/** Console/Utility Function Prototypes **/
void set_color_and_background(int ForgC, int BackC);
void gotoxy(int x, int y);
void print_on_coord(COORD coord, const char str[]);
void print_on_raw_coord(int x, int y, const char str[]);
void string_to_uppercase(char cadena[]);
void clean_screen(void);

/** File I/O Function Prototypes **/
char *input_text(void);
bool save_text_to_file(const char str[]);
void free_text_input(char *text);

/** Screen Function Prototypes **/
void draw_login_form(void);
int authentication(void);
void login_screen(void);
void draw_screen_border(void);
void main_menu(void);
int algorithm_option_screen(const char *title);
void draw_message_input_form(void);
void loading_animation(void);
void decryption_animation(void);
void about_screen(void);
void bye_animation(void);

/** Icon Prototypes **/
void padlock_close_icon(void);
void padlock_open_icon(void);
void about_icon(void);
void exit_icon(void);

/** Encryption Algorithm Prototypes **/
int simple_encryption(void);
int run_length_encryption(void);
int xor_encryption(void);
int vigenere_encryption(void);

/** Decryption Algorithm Prototypes **/
int simple_decryption(void);
int run_length_decryption(void);
int xor_decryption(void);
int vigenere_decryption(void);

/** Testable Algorithm Functions (pure logic, no I/O) **/
void simple_encrypt_str(const char *input, char *output, int len);
void simple_decrypt_str(const char *input, char *output, int len);
void xor_decimal_to_binary(int decimal, int binary[8]);
int xor_binary_to_decimal(const int binary[8]);
void xor_apply_key(const int binary[8], const int key[8], int result[8]);
void xor_encrypt_str(const char *input, const int key[8], char *output, int len);
void xor_decrypt_str(const char *input, const int key[8], char *output, int len);
void vigenere_encrypt_str(const char *input, const char *key, char *output, int len);
void vigenere_decrypt_str(const char *input, const char *key, char *output, int len);
int run_length_encode_str(const char *input, char *output);
int run_length_decode_str(const char *input, char *output);

#endif // ENIGMA_H
