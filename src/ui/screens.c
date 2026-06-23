/**
 * EnigmaProject - Funciones de Pantallas UI
 * 
 * Todas las funciones relacionadas con la interfaz gráfica de consola
 */

#include "../../include/enigma.h"

void draw_login_form(void)
{
	COORD coord;

	/** esquinas de recuadro de usuario*/
	print_on_raw_coord(29, 8, "\xC9");
	print_on_raw_coord(50, 8, "\xBB");
	print_on_raw_coord(29, 11, "\xC8");
	print_on_raw_coord(50, 11, "\xBC");

	/** draw user input box*/
	coord.Y = 8;
	do { /**left side of user box*/
		coord.Y++;
		print_on_raw_coord(29, coord.Y, "\xBA");
	} while (coord.Y != 10);

	coord.Y = 8;
	do { /**right side of user box*/
		coord.Y++;
		print_on_raw_coord(50, coord.Y, "\xBA");
	} while (coord.Y != 10);

	coord.X = 29;
	do { /**the bottom of the user box*/
		coord.X++;
		print_on_raw_coord(coord.X, 11, "\xCD");
	} while (coord.X != 49);

	coord.X = 29;
	do { /**the top of user box*/
		coord.X++;
		print_on_raw_coord(coord.X, 8, "\xCD");
	} while (coord.X != 49);

	print_on_raw_coord(24, 2, "  ___       _                    \n");
	print_on_raw_coord(24, 3, " | __>._ _ <_> ___.._ _ _  ____ \n");
	print_on_raw_coord(24, 4, " | _> |   || |/ . || Y Y |<_>  |\n");
	print_on_raw_coord(24, 5, " |___>|_|_||_|\\_. ||_|_|_|<____|\xA9\n");
	print_on_raw_coord(24, 6, "              <___:              \n");

	print_on_raw_coord(36, 13, "         ");
	print_on_raw_coord(36, 14, " USUARIO ");
	print_on_raw_coord(36, 15, "         ");

	/** set coords to place input pointer*/
	gotoxy(32, 10);
}

int authentication(void)
{
	char input_password[5];
	char static_password[5] = "FMAT"; /**USUARIO DEL PROGRAMA*/

	set_color_and_background(7, 0);
	fgets(input_password, 5, stdin);

	return strcmp(input_password, static_password); /**Comparar String si son iguales devuelve 0*/
}

void login_screen(void)
{
	const int IS_LOGGED = 0;
	int auth_response;

	do {
		set_color_and_background(50, 0);
		draw_screen_border();
		draw_login_form();
		auth_response = authentication();
		if (auth_response != IS_LOGGED)
		{
			set_color_and_background(4, 0);
			print_on_raw_coord(32, 10, "¡Incorrecto!");
			Sleep(300); /**tiempo que aparecera "¡Incorrecto!" en pantalla*/
		}

		clean_screen();
	} while (auth_response != IS_LOGGED);
	printf("\a");
}

void draw_message_input_form(void)
{
	COORD coord;

	draw_screen_border();

	for (coord.X = 2; coord.X < 77; coord.X++) { /**Sombreado Superior*/
		for (coord.Y = 2; coord.Y < 8; coord.Y++)
		{
			print_on_coord(coord, "\xB1");
		}
	}

	for (coord.Y = 8; coord.Y < 24; coord.Y++) {
		coord.X = 2;
		print_on_coord(coord, "\xB1");
	}

	for (coord.Y = 8; coord.Y < 24; coord.Y++) {
		coord.X = 76;
		print_on_coord(coord, "\xB1");
	}

	for (coord.X = 2; coord.X < 76; coord.X++) {
		coord.Y = 23;
		print_on_coord(coord, "\xB1");
	}

	print_on_raw_coord(3, 5, "         ");
	print_on_raw_coord(3, 6, " MENSAJE ");
	print_on_raw_coord(3, 7, "         ");
}

void draw_screen_border(void)
{
	COORD coord;

	/** Dibujar esquinas */
	print_on_raw_coord(1, 1, "\xC9");
	print_on_raw_coord(1, 24, "\xC8");
	print_on_raw_coord(77, 1, "\xBB");
	print_on_raw_coord(77, 24, "\xBC");

	/** Dibujo del Marco o Dorde*/

	coord.X = 1;
	do { /**lado superior*/
		coord.X++;
		print_on_raw_coord(coord.X, 1, "\xCD");
	} while (coord.X != 76);

	coord.X = 1;
	do { /**lado inferior*/
		coord.X++;
		print_on_raw_coord(coord.X, 24, "\xCD");
	} while (coord.X != 76);

	coord.Y = 1;
	do { /** lado derecho*/
		coord.Y++;
		print_on_raw_coord(77, coord.Y, "\xBA");
	} while (coord.Y != 23);

	coord.Y = 1;
	do { /** lado izquierdo*/
		coord.Y++;
		print_on_raw_coord(1, coord.Y, "\xBA");
	} while (coord.Y != 23);
}

/** Función de ingreso de texto - movida a utils/string_handler.c */
char *input_text(void);

/** Pantalla de opción de encriptación */
int encryption_type_option_screen(void)
{
	COORD coord;
	coord.X = 20;
	coord.Y = 8;

	char pressed_key;
	int option;
	bool exit = false;

	do {
		clean_screen();
		draw_screen_border();

		print_on_raw_coord(26, 4, "* SELECCIONA TIPO DE CIFRADO *");
		print_on_raw_coord(24, 8,"1.-SIMPLE");
		print_on_raw_coord(24, 12,"2.-XOR");
		print_on_raw_coord(45, 8,"3.-VIGERENE");
		print_on_raw_coord(45, 12,"4.-RUN LENGTH");
		print_on_raw_coord(45, 13," (COMPRESOR)");

		print_on_coord(coord, "-->");

		pressed_key = getch();
		if (pressed_key == KEY_DOWN) {
			if (coord.Y < 12) {
				coord.Y += 4;
			} else {
				coord.Y = 8;
			}
		}

		if (pressed_key == KEY_UP) {
			if (coord.Y > 8) {
				coord.Y -= 4;
			} else {
				coord.Y = 12;
			}
		}

		if ((pressed_key == KEY_RIGHT) || (pressed_key == KEY_LEFT)) {
			if (coord.X < 41) {
				coord.X += 21;
			} else {
				coord.X = 20;
			}
		}

		if (pressed_key == KEY_ESC) { /** si presiona la tecla ESC pasa valor 5 y regresa a menu */
			option = 5;
			exit = true;
		}

		if (pressed_key == KEY_ENTER) {
			exit = true;

			if ((coord.X == 20) && (coord.Y == 8)) {
				option = SIMPLE;
			}
			if ((coord.X == 20) && (coord.Y == 12)) {
				option = XOR;
			}
			if ((coord.X == 41) && (coord.Y == 8)) {
				option = VIGERENE;
			}
			if ((coord.X == 41) && (coord.Y == 12)) {
				option = RUN_LENGTH;
			}
		}
	} while (exit != true);

	return option;
}

/** Pantalla de opción de descifrado */
int decryption_type_option_screen(void)
{
	COORD coord;
	coord.X = 20;
	coord.Y = 8;

	char pressed_key;
	int option;
	bool exit = false;

	do {
		clean_screen();
		draw_screen_border();

		print_on_raw_coord(26, 4,"* SELECCIONA TIPO DE DESCIFRADO *");
		print_on_raw_coord(24, 8,"1.-SIMPLE");
		print_on_raw_coord(24, 12,"2.-XOR");
		print_on_raw_coord(45, 8,"3.-VIGERENE");
		print_on_raw_coord(45, 12,"4.-RUN LENGTH");
		print_on_raw_coord(45, 13," (COMPRESOR)");

		print_on_coord(coord, "-->");

		pressed_key = getch();
		if (pressed_key == KEY_DOWN) {
			if (coord.Y < 12) {
				coord.Y += 4;
			} else {
				coord.Y = 8;
			}
		}

		if (pressed_key == KEY_UP) {
			if (coord.Y > 8) {
				coord.Y -= 4;
			} else {
				coord.Y = 12;
			}
		}

		if ((pressed_key == KEY_RIGHT) || (pressed_key == KEY_LEFT)) {
			if (coord.X < 41) {
				coord.X += 21;
			} else {
				coord.X = 20;
			}
		}

		if (pressed_key == KEY_ESC) { /** si presiona la tecla ESC pasa valor 5 y regresa a menu */
			option = 5;
			exit = true;
		}

		if (pressed_key == KEY_ENTER) {
			exit = true;

			if ((coord.X == 20) && (coord.Y == 8)) {
				option = SIMPLE;
			}
			if ((coord.X == 20) && (coord.Y == 12)) {
				option = XOR;
			}
			if ((coord.X == 41) && (coord.Y == 8)) {
				option = VIGERENE;
			}
			if ((coord.X == 41) && (coord.Y == 12)) {
				option = RUN_LENGTH;
			}
		}
	} while (exit != true);

	return option;
}

/** Pantalla principal de menú */
void main_menu(void)
{
	COORD coord;
	coord.X = 5;
	coord.Y = 8;

	int encryption_type;
	bool exit = false;
	bool go_back = false;
	int menu_index = 0;
	char pressed_key; /** valores capturados por teclas de navegacion */

	do {
		clean_screen();

		/*********************************************************/
		/** Se imprime Un dibujo representando la opcion marcada */
		if (coord.Y == 8) {
			padlock_close_icon();
		}
		if (coord.Y == 11) {
			padlock_open_icon();
		}
		if (coord.Y == 14) {
			set_color_and_background(9, 0); /**Color Azul*/
			about_icon();
		}
		if (coord.Y == 17) {
			set_color_and_background(4, 0); /**Color Rojo*/
			exit_icon();
		}
		/*********************************************************/
		set_color_and_background(50, 0); /** establecer color de nuevo porque acabo de limpiar la pantalla*/
		draw_screen_border();

		print_on_raw_coord(10, 8, "Encriptar");
		print_on_raw_coord(17, 11, "Desencriptar");
		print_on_raw_coord(24, 14, "Acerca de");
		print_on_raw_coord(31, 17, "Salir");

		print_on_coord(coord, "-->");

		pressed_key = getch();
		if (pressed_key == -32) {
			pressed_key = getch();
		}
		if (pressed_key == KEY_DOWN) {
			if (coord.Y < 17) {
				coord.Y += 3;
				coord.X += 7;
				menu_index++;
			} else {
				coord.Y = 8;
				coord.X = 5;
				menu_index = 0;
			}
		}
		if (pressed_key == KEY_UP) {
			if (coord.Y > 8) {
				coord.Y -= 3;
				coord.X -= 7;
				menu_index--;
			} else {
				coord.Y = 17;
				coord.X = 26;
				menu_index = 3;
			}
		}
		if (pressed_key == KEY_ENTER) {
			set_color_and_background(50, 0);
			if (menu_index == ENCRYPTION)
			{
				clean_screen();
				encryption_type = encryption_type_option_screen();
				clean_screen();
				switch (encryption_type)
				{
				case SIMPLE:
					draw_message_input_form();
					go_back = simple_encryption();
					if (go_back == true)
					{
						break;
					}
					printf("\n\n\t\t   Pulsa una tecla para regresar al menu");
					getch();
					break;
				case XOR:
					draw_message_input_form();
					go_back = xor_encryption();
					if (go_back == true)
					{
						break;
					}
					printf("\n\n\t\t   Pulsa una tecla para regresar al menu");
					getch();
					break;
				case VIGERENE:
					draw_message_input_form();
					go_back = vigenere_encryption();
					if (go_back == true)
					{
						break;
					}
					printf("\n\n\t\t   Pulsa una tecla para regresar al menu");
					getch();
					break;
				case RUN_LENGTH:
					draw_message_input_form();
					go_back = run_length_encryption();
					if (go_back == true)
					{
						break;
					}
					printf("\n\n\t\t   Pulsa una tecla para regresar al menu");
					getch();
					break;
				case 5:
					break;
				default:
					printf("Error");
				}
			}
			if (menu_index == DECRYPTION)
			{
				clean_screen();
				gotoxy(13, 13);
				encryption_type = decryption_type_option_screen();
				clean_screen();
				switch (encryption_type)
				{
				case SIMPLE:
					decryption_animation();
					clean_screen();
					go_back = simple_decryption();
					if (go_back == true)
					{
						printf("\n\nPresione una tecla para salir");
						getch();
						break;
					}
					printf("\n\nPresione una tecla para salir");
					getch();
					break;
				case XOR:
					go_back = xor_decryption();
					if (go_back == true)
					{
						break;
					}
					printf("\n\nPresione una tecla para salir");
					getch();
					break;
				case VIGERENE:
					go_back = vigerene_decryption();
					if (go_back == true)
					{
						break;
					}
					printf("\n\nPresione una tecla para salir");
					getch();
					break;
				case RUN_LENGTH:
					decryption_animation();
					clean_screen();
					go_back = run_length_decryption();
					if (go_back == true)
					{
						printf("\n\nPresione una tecla para salir");
						getch();
						break;
					}
					printf("\n\nPresione una tecla para salir");
					getch();
					break;
				case 5:
					break;
				default:
					printf("Error");
				}
			}
			if (menu_index == ABOUT)
			{
				clean_screen();
				about_screen();
				getch();
			}
			if (menu_index == EXIT)
			{
				clean_screen();
				bye_animation();
				exit = true;
			}
		}

	} while (exit == false);
}