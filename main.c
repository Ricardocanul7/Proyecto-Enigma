/**
 * EnigmaProject - Main Entry Point
 *
 * Universidad Autonoma de Yucatan
 * ENIGMA Encryption Project
 *
 * To compile use: cl main.c /Fe:EnigmaProject.exe /Iinclude /Osrc
 */

#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include "include/enigma.h"

/** Utility Functions **/
void set_color_and_background(int ForgC, int BackC);
int *gotoxy(int x, int y);
void print_on_coord(COORD coord, char str[]);
void print_on_raw_coord(int y, int x, char str[]);
void string_to_uppercase(char cadena[]);
void clean_screen(void);

/** Screen Functions **/
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

/** Graphic Icons **/
void padlock_close_icon(void);
void padlock_open_icon(void);
void about_icon(void);
void exit_icon(void);

/** Simple Encryption/Decryption Algorithms **/
int simple_encryption(void);
int run_length_encryption(void);
int xor_encryption(void);
int vigenere_encryption(void);

/** Animations (optional - can be moved to a separate file) **/
void loading_animation(void);
void decryption_animation(void);
void about_screen(void);
void bye_animation(void);

int main(void)
{
	clean_screen();

	/** Start Login Screen */
	login_screen();

	/** Main Menu Screen */
	main_menu();

	return 0;
}
