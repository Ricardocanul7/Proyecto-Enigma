/**
Universidad Autonoma de Yucatan
*Proyecto de Encriptacion "ENIGMA"*

INTEGRANTES: 
-Ricardo Canul Flota
-Rodrigo Cordova Villamil
-Marco Pool Alvarado
-Marvin Arias Morales
*/

#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

FILE *doc; /** doc es la variable usada para el archivo txt que se guardara en el proceso de cifrado*/

/* Screens */
void main_menu();		   /**Diseño del Menu interactivo de inicio del programa*/
void draw_screen_border(); /**Diseño del Marco del programa*/
void draw_login_form();	   /** recuadro de usuario y logotipo de ENIGMA*/
void login_screen();
int encryption_type_option_screen();
int decryption_type_option_screen();
void draw_message_input_form();
char *input_text();	 /**Estructura para ingresar datos de cadena para cada tipo de encriptado... no sera funcion*/
void about_screen(); /** Info+Animacion de la seccion Acerca de */

/* Animations */
void loading_animation();	 /** Animacion de Cargando(CIFRANDO) */
void decryption_animation(); /** Animacion Descifrado */
void bye_animation();

/* Actions */
int authentication(); /**Compara el usuario que se ingresa del teclado con el de la constante*/
int open_file();	  /** abrir texto para descifrar */
bool save_text_to_file(char str[]);
void clean_screen();

/* Utils */
void set_color_and_background(int ForgC, int BackC);
int *gotoxy(int x, int y);
void print_on_coord(COORD coord, char str[]);
void print_on_raw_coord(int y, int x, char str[]);
void string_to_uppercase(char cadena[]);

/** Algoritmos De Cifrado **************/
int simple_encryption();	 /***/
int run_length_encryption(); /***/
int xor_encryption();		 /***/
int vigerene_encryption();	 /***/
/***************************************/

/** Algoritmos De Descifrado ***********/
int simple_decryption();	 /***/
int run_length_decryption(); /***/
int xor_decryption();		 /***/
int vigerene_decryption();	 /***/
/***************************************/

/** ICONOS *****************************/
void padlock_close_icon(); /***/
void padlock_open_icon();  /***/
void about_icon();		   /***/
void exit_icon();		   /***/
/***************************************/

/* Enums */
enum EncryptionTypes
{
	SIMPLE = 1,
	XOR = 2,
	VIGERENE = 3,
	RUN_LENGTH = 4
} EncryptionTypes;

enum KeyboardKeys
{
	KEY_UP = 72,
	KEY_DOWN = 80,
	KEY_LEFT = 75,
	KEY_RIGHT = 77,
	KEY_ENTER = 13,
	KEY_SPACE = 32,
	KEY_ESC = 27,
} KeyboardKeys;

enum MenuOptions
{
	ENCRYPTION,
	DECRYPTION,
	ABOUT,
	EXIT
} MenuOptions;

void set_color_and_background(int ForgC, int BackC)
{
	WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
}

int *gotoxy(int x, int y) /** funcion para acceder a coordenadas del plano */
{
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hcon, dwPos);
	return 0;
}

void print_on_coord(COORD coord, char str[]){
	gotoxy(coord.X, coord.Y);
	printf(str);
}

void print_on_raw_coord(int x, int y, char str[]){
	gotoxy(x, y);
	printf(str);
}

void string_to_uppercase(char cadena[])
{
	int i;
	int str_length = strlen(cadena);
	for (i = 0; i < str_length; i++)
	{
		cadena[i] = toupper(cadena[i]);
	}
}

void clean_screen()
{
	system("cls");
}

void main()
{
	login_screen(); /* Login loop until password is correct */

	main_menu(); /* Run main menu id login loop finished */
}

void draw_login_form()
{
	COORD coord;

	/** esquinas de recuadro de usuario*/
	print_on_raw_coord(29, 8, "\xC9");
	print_on_raw_coord(50, 8, "\xBB");
	print_on_raw_coord(29, 11, "\xC8");
	print_on_raw_coord(50, 11, "\xBC");

	/** draw user input box*/
	coord.Y = 8;
	do
	{ /**left side of user box*/
		coord.Y++;
		print_on_raw_coord(29, coord.Y, "\xBA");
	} while (coord.Y != 10);

	coord.Y = 8;
	do
	{ /**right side of user box*/
		coord.Y++;
		print_on_raw_coord(50, coord.Y, "\xBA");
	} while (coord.Y != 10);

	coord.X = 29;
	do
	{ /**the bottom of the user box*/
		coord.X++;
		print_on_raw_coord(coord.X, 11, "\xCD");
	} while (coord.X != 49);

	coord.X = 29;
	do
	{ /**the top of user box*/
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

int authentication() /** comparar contraseña de usuario para acceder al menu */
{
	char input_password[5];			  /**ENTRADA DE USUARIO*/
	char static_password[5] = "FMAT"; /**USUARIO DEL PROGRAMA*/

	set_color_and_background(7, 0);
	fgets(input_password, 5, stdin);

	return strcmp(input_password, static_password); /**Comparar String si son iguales devuelve 0*/
}

void login_screen()
{
	const int IS_LOGGED = 0;
	int auth_response;

	do
	{
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

void draw_screen_border()
{
	COORD coord;

	/** Dibujar esquinas */
	print_on_raw_coord(1, 1, "\xC9");
	print_on_raw_coord(1, 24, "\xC8");
	print_on_raw_coord(77, 1, "\xBB");
	print_on_raw_coord(77, 24, "\xBC");

	/** Dibujo del Marco o Dorde*/

	coord.X = 1;
	do
	{ /**lado superior*/
		coord.X++;
		print_on_raw_coord(coord.X, 1, "\xCD");
	} while (coord.X != 76);

	coord.X = 1;
	do
	{ /**lado inferior*/
		coord.X++;
		print_on_raw_coord(coord.X, 24, "\xCD");
	} while (coord.X != 76);

	coord.Y = 1;
	do
	{ /** lado derecho*/
		coord.Y++;
		print_on_raw_coord(77, coord.Y, "\xBA");
	} while (coord.Y != 23);

	coord.Y = 1;
	do
	{ /** lado izquierdo*/
		coord.Y++;
		print_on_raw_coord(1, coord.Y, "\xBA");
	} while (coord.Y != 23);
}

void main_menu()
{
	/**Coordenadas iniciales X y Y del plano */
	COORD coord;
	coord.X = 5;
	coord.Y = 8;

	int encryption_type;
	bool exit = false;
	bool go_back = false;
	int menu_index = 0;
	char pressed_key; /** valores capturados por teclas de navegacion */

	do
	{
		clean_screen();

		/*********************************************************/
		/** Se imprime Un dibujo representando la opcion marcada */
		if (coord.Y == 8)
		{
			padlock_close_icon();
		}
		if (coord.Y == 11)
		{
			padlock_open_icon();
		}
		if (coord.Y == 14)
		{
			set_color_and_background(9, 0); /**Color Azul*/
			about_icon();
		}
		if (coord.Y == 17)
		{
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
		if (pressed_key == -32)
		{
			pressed_key = getch();
		}
		if (pressed_key == KEY_DOWN)
		{
			if (coord.Y < 17)
			{
				coord.Y += 3;
				coord.X += 7;
				menu_index++;
			}
			else
			{
				coord.Y = 8;
				coord.X = 5;
				menu_index = 0;
			}
		}
		if (pressed_key == KEY_UP)
		{
			if (coord.Y > 8)
			{
				coord.Y -= 3;
				coord.X -= 7;
				menu_index--;
			}
			else
			{
				coord.Y = 17;
				coord.X = 26;
				menu_index = 3;
			}
		}
		if (pressed_key == KEY_ENTER)
		{
			set_color_and_background(50, 0); /** establecer color Verde de nuevo porque acabo de limpiar la pantalla*/
			if (menu_index == ENCRYPTION)	 /** Cifrar */
			{
				clean_screen();
				encryption_type = encryption_type_option_screen(); /** tipo seria del 1 al 4  */
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
					go_back = vigerene_encryption();
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
			if (menu_index == DECRYPTION) /** Descifrar */
			{
				clean_screen();
				gotoxy(13, 13);
				encryption_type = decryption_type_option_screen(); /** tipo seria del 1 al 4          */
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
			if (menu_index == ABOUT) /** Acerca de  */
			{
				clean_screen();
				about_screen(); /** Animacion e Informacion de los desarrolladores */
				getch();
			}
			if (menu_index == EXIT) /** Salir  */
			{
				clean_screen();
				bye_animation();
				exit = true;
			}
		}

	} while (exit == false);
}

void draw_message_input_form()
{
	COORD coord;

	draw_screen_border();

	for (coord.X = 2; coord.X < 77; coord.X++)
	{ /**Sombreado Superior*/
		for (coord.Y = 2; coord.Y < 8; coord.Y++)
		{
			print_on_coord(coord, "\xB1");
		}
	}

	for (coord.Y = 8; coord.Y < 24; coord.Y++)
	{
		coord.X = 2;
		print_on_coord(coord, "\xB1");
	}

	for (coord.Y = 8; coord.Y < 24; coord.Y++)
	{
		coord.X = 76;
		print_on_coord(coord, "\xB1");
	}

	for (coord.X = 2; coord.X < 76; coord.X++)
	{
		coord.Y = 23;
		print_on_coord(coord, "\xB1");
	}

	print_on_raw_coord(3, 5, "         ");
	print_on_raw_coord(3, 6, " MENSAJE ");
	print_on_raw_coord(3, 7, "         ");
}

char *input_text() /**Funcion Para leer texto dentro del recuadro de MENSAJE*/
{
	char *text_field = malloc(sizeof(char) * 910);
	char pressed_key, back_to_menu = 0;
	int string_length;
	int i = 0;
	COORD coord = {.X = 3, .Y = 9};

	while (pressed_key != KEY_ENTER) /** Termina si el usuario presiona enter*/
	{
		if ((pressed_key == 8) && (coord.Y >= 9))
		{						   /** 8 es la tecla DEL */
			i = i - 2;			   /** al retroceder i se resta 2 para retroceder 1 lugar ya que al final se aumento i una vez mas*/
			text_field[i] = '\0';  /** al retroceder ingresa un valor null en el numero de matriz[i]*/
			coord.X = coord.X - 2; /** la coordenada igual retrocede para poder escribir en una coordenada anterior*/
			if (coord.X < 3)
			{
				coord.Y--;	  /**si la COORD x es menor a 3, y subira a la ultima linea*/
				coord.X = 72; /**al subir Y, x tiene que ubicarse al final de la linea*/
			}
		}
		coord.X++; /** se aumenta COORD x cada ciclo para simular que se escribe una cadena*/
		if (coord.X == 74)
		{
			printf("\n"); /** si COORD x llega a 74, este brinca una linea para continuar escribiendo y no borre el marco dibujado*/
			coord.Y++;	  /** COORD y aumenta 1 por lo tanto brinca a la linea de abajo */
			coord.X = 4;  /** al estar en la linea de abajo x regresa a su valor inicial para esribir de izq a derecha*/
		}
		if (i == 910)
		{							 /** determina si ya llego al limite de caracteres para la matriz*/
			printf("\a");			 /** se genera un sonido en caso de llegar al limite de caracteres*/
			pressed_key = KEY_ENTER; /** se genera un ENTER automatico para continuar con el programa*/
		}
		else
		{
			gotoxy(coord.X, coord.Y); /** Funcion para ubicar en el plano la impresion de cada caracter*/
			pressed_key = getch();	  /** entrada de caracteres*/
			if (pressed_key == KEY_ESC)
			{
				return ""; /** Return empty value to indicate that the operation has been aborted and handle go back to the menu */
			}
			printf("%c", pressed_key);	 /** mostrar el caracter que acaba de ser tecleado*/
			text_field[i] = pressed_key; /** agrega caracter a cadena de texto  */
			i++;
		}
	}

	text_field[i] = '\0'; /** inserta un valor NULL al final*/
	string_length = strlen(text_field);

	clean_screen();

	return text_field;
}

bool save_text_to_file(char str[])
{
	doc = fopen("mensaje.txt", "w");
	int success = fprintf(doc, "%s", str); /** PRUEBA IMPRIME TODO LOS CARACTERES ALMACENADOS */
	fflush(doc);
	fclose(doc);

	if (success >= 0)
	{
		return true;
	}
	return false;
}

int encryption_type_option_screen()
{
	COORD coord;
	coord.X = 20;
	coord.Y = 8;

	char pressed_key;
	int option;
	bool exit = false;

	do
	{
		clean_screen();
		draw_screen_border();

		print_on_raw_coord(26, 4,  "* SELECCIONA TIPO DE CIFRADO *");
		print_on_raw_coord(24, 8,  "1.-SIMPLE");
		print_on_raw_coord(24, 12, "2.-XOR");
		print_on_raw_coord(45, 8,  "3.-VIGERENE");
		print_on_raw_coord(45, 12, "4.-RUN LENGTH");
		print_on_raw_coord(45, 13, "  (COMPRESOR)");

		print_on_coord(coord, "-->");

		pressed_key = getch();
		if (pressed_key == KEY_DOWN)
		{
			if (coord.Y < 12)
			{
				coord.Y += 4;
			}
			else
			{
				coord.Y = 8;
			}
		}

		if (pressed_key == KEY_UP)
		{
			if (coord.Y > 8)
			{
				coord.Y -= 4;
			}
			else
			{
				coord.Y = 12;
			}
		}

		if ((pressed_key == KEY_RIGHT) || (pressed_key == KEY_LEFT))
		{
			if (coord.X < 41)
			{
				coord.X += 21;
			}
			else
			{
				coord.X = 20;
			}
		}

		if (pressed_key == KEY_ESC) /** si presiona la tecla ESC pasa valor 5 y regresa a menu */
		{
			option = 5;
			exit = true; /** como queremos regresar a menu aux = 1 es la condicion para salir del while */
		}

		if (pressed_key == KEY_ENTER)
		{ /** Lo que pasaria en cada caso  */
			exit = true;

			if ((coord.X == 20) && (coord.Y == 8))
			{ /** si se presiona la tecla enter*/
				option = SIMPLE;
			}

			if ((coord.X == 20) && (coord.Y == 12))
			{
				option = XOR;
			}

			if ((coord.X == 41) && (coord.Y == 8))
			{
				option = VIGERENE;
			}

			if ((coord.X == 41) && (coord.Y == 12))
			{
				option = RUN_LENGTH;
			}
		}
	} while (exit != true);

	return option;
}

void loading_animation()
{
	int loading;
	COORD coord;

	print_on_raw_coord(30, 8,  "Cifrando mensaje...");
	print_on_raw_coord(40, 23, "Generando archivo mensaje.txt");

	draw_screen_border();
	/** esquinas de recuadro de usuario*/
	print_on_raw_coord(29, 9, "\xC9");
	print_on_raw_coord(50, 9, "\xBB");
	print_on_raw_coord(29, 12, "\xC8");
	print_on_raw_coord(50, 12, "\xBC");

	/**box*/

	coord.Y = 9;
	do
	{ /**left side of box*/
		coord.Y++;
		print_on_raw_coord(29, coord.Y, "\xBA");
	} while (coord.Y != 11);

	coord.Y = 9;
	do
	{ /**right side of box*/
		coord.Y++;
		print_on_raw_coord(50, coord.Y, "\xBA");
	} while (coord.Y != 11);

	coord.X = 29;
	do
	{ /**the bottom of the box*/
		coord.X++;
		print_on_raw_coord(coord.X, 12, "\xCD");
	} while (coord.X != 49);

	coord.X = 29;
	do
	{ /**the top of box*/
		coord.X++;
		print_on_raw_coord(coord.X, 9, "\xCD");
	} while (coord.X != 49);

	/** Cargano Animacion*/

	for (loading = 30; loading < 50; loading++)
	{
		print_on_raw_coord(loading, 10, "\xDB");
		print_on_raw_coord(loading, 11, "\xDB");
		Sleep(100);
	}

	print_on_raw_coord(40, 23, "                                    "); /** borrar printf de "generando txt" */
	print_on_raw_coord(30, 8, "  Cifrado Exitoso! ");
	print_on_raw_coord(20, 17, "Presione una tecla para volver al menu.");
	getch();
}

void about_screen()
{
	int transition;

	for (transition = 16; transition > 0; transition--)
	{
		print_on_raw_coord(24, 8,  "  ___       _                    \n");
		print_on_raw_coord(24, 9,  " | __>._ _ <_> ___.._ _ _  ____ \n");
		print_on_raw_coord(24, 10, " | _> |   || |/ . || Y Y |<_>  |\n");
		print_on_raw_coord(24, 11, " |___>|_|_||_|\\_. ||_|_|_|<____|\xA9\n");
		print_on_raw_coord(24, 12, "              <___:              \n");

		char* message = 
			"EnigmaProject fue realizado por:\n\n"
			" -Arias Morales Marvin\n\n"
			" -Canul Flota Ricardo.\n\n"
			" -Cordova Villamil Jorge\n\n"
			" -Pool Alvarado Marco";
		print_on_raw_coord(0, transition, message);
		Sleep(300);
		if (transition > 1)
		{
			clean_screen();
		}
	}
	print_on_raw_coord(19, 18, "Pulse una tecla para volver al menu");
}

void padlock_close_icon()
{
	COORD coord;

	int keydraw[][9] = {/** Cada numero representa un valor en ASCII*/
						{32, 220, 223, 223, 223, 220, 32, 32},
						{32, 219, 32, 32, 32, 219, 32, 32},
						{219, 219, 219, 219, 219, 219, 219, 32},
						{219, 219, 32, 32, 32, 219, 219, 32},
						{219, 219, 219, 220, 219, 219, 219, 32}};

	for (coord.Y = 0; coord.Y < 5; coord.Y++)
	{ /**saltos del linea o coordenas Y*/
		gotoxy(60, 10 + coord.Y);
		for (coord.X = 0; coord.X < 9; coord.X++)
		{ /**Coordendas X*/
			if (coord.Y < 2)
			{
				set_color_and_background(6, 0);
			}
			else
			{
				set_color_and_background(3, 0);
			}
			printf("%c", keydraw[coord.Y][coord.X]);
			if (coord.X == 8)
			{ /** si llega al ultimo lugar brinca para seguir dibujando en Y++ */
				printf("\n");
			}
		}
	}
}

void padlock_open_icon()
{
	COORD coord;

	int keydraw[][9] = {/** Cada numero representa un valor en ASCII*/
						{32, 32, 32, 32, 32, 220, 223, 223, 220},
						{32, 32, 32, 32, 32, 219, 32, 32, 223},
						{219, 219, 219, 219, 219, 219, 219, 32, 32},
						{219, 219, 32, 32, 32, 219, 219, 32, 32},
						{219, 219, 219, 220, 219, 219, 219, 32, 32}

	};

	for (coord.Y = 0; coord.Y < 5; coord.Y++)
	{ /**saltos del linea o coordenas Y*/
		gotoxy(60, 10 + coord.Y);
		for (coord.X = 0; coord.X < 9; coord.X++)
		{ /**Coordendas X*/
			if (coord.Y < 2)
			{
				set_color_and_background(6, 0);
			}
			else
			{
				set_color_and_background(2, 0);
			}
			printf("%c", keydraw[coord.Y][coord.X]);
			if (coord.X == 8)
			{ /** si llega al ultimo lugar brinca para seguir dibujando en Y++ */
				printf("\n");
			}
		}
	}
}

void about_icon()
{
	COORD coord;

	int keydraw[][9] = {
		/** Cada numero representa un valor en ASCII*/
		{32, 32, 32, 32, 157, 32, 32, 32, 32},
		{32, 32, 201, 205, 205, 205, 187, 32, 32},
		{32, 32, 200, 187, 32, 201, 188, 32, 32},
		{32, 32, 32, 186, 32, 186, 32, 32, 32},
		{32, 32, 32, 186, 32, 186, 32, 32, 32},
		{32, 32, 201, 188, 32, 200, 187, 32, 32},
		{32, 32, 200, 205, 205, 205, 188, 32, 32},

	};

	for (coord.Y = 0; coord.Y < 7; coord.Y++)
	{ /**saltos del linea o coordenas Y*/
		gotoxy(60, 9 + coord.Y);
		for (coord.X = 0; coord.X < 9; coord.X++)
		{ /**Coordendas X*/
			printf("%c", keydraw[coord.Y][coord.X]);
			if (coord.X == 8)
			{ /** si llega al ultimo lugar brinca para seguir dibujando en Y++ */
				printf("\n");
			}
		}
	}
}

void exit_icon()
{
	COORD coord;

	int keydraw[][9] = {
		/** Cada numero representa un valor en ASCII*/
		{32, 201, 205, 205, 205, 205, 187, 32},
		{32, 186, 178, 178, 178, 178, 186, 32},
		{32, 186, 178, 178, 178, 178, 186, 32},
		{32, 186, 208, 178, 178, 178, 186, 32},
		{32, 186, 178, 178, 178, 178, 186, 32},
		{32, 186, 178, 178, 178, 178, 186, 32},
		{32, 200, 205, 205, 205, 205, 188, 32},
	};

	gotoxy(62, 9);
	printf("EXIT");
	for (coord.Y = 0; coord.Y < 7; coord.Y++)
	{ /**saltos del linea o coordenas Y*/
		gotoxy(60, 10 + coord.Y);
		for (coord.X = 0; coord.X < 9; coord.X++)
		{ /**Coordendas X*/
			printf("%c", keydraw[coord.Y][coord.X]);
			if (coord.X == 8)
			{ /** si llega al ultimo lugar brinca para seguir dibujando en Y++ */
				printf("\n");
			}
		}
	}
}

int decryption_type_option_screen()
{ /** Menu de seleccion de descifrado */
	COORD coord;
	coord.X = 20;
	coord.Y = 8;

	char pressed_key;
	int option;
	bool exit = false;

	do
	{
		clean_screen();
		draw_screen_border();

		print_on_raw_coord(26, 4, "* SELECCIONA TIPO DE DESCIFRADO *");
		print_on_raw_coord(24, 8,  "1.-SIMPLE");
		print_on_raw_coord(24, 12, "2.-XOR");
		print_on_raw_coord(45, 8,  "3.-VIGERENE");
		print_on_raw_coord(45, 12, "4.-RUN LENGTH");
		print_on_raw_coord(45, 13, "  (COMPRESOR)");

		print_on_coord(coord, "-->");

		pressed_key = getch();
		if (pressed_key == KEY_DOWN)
		{
			if (coord.Y < 12)
			{
				coord.Y += 4;
			}
			else
			{
				coord.Y = 8;
			}
		}
		if (pressed_key == KEY_UP)
		{
			if (coord.Y > 8)
			{
				coord.Y -= 4;
			}
			else
			{
				coord.Y = 12;
			}
		}
		if ((pressed_key == KEY_RIGHT) || (pressed_key == KEY_LEFT))
		{
			if (coord.X < 41)
			{
				coord.X += 21;
			}
			else
			{
				coord.X = 20;
			}
		}
		if (pressed_key == KEY_ESC) /** si presiona la tecla ESC pasa valor 5 y regresa a menu */
		{
			option = 5;
			exit = true;
		}

		if (pressed_key == KEY_ENTER) /** Lo que pasaria en cada caso  */
		{
			exit = true;
			if ((coord.X == 20) && (coord.Y == 8))
			{
				option = SIMPLE;
			}
			if ((coord.X == 20) && (coord.Y == 12))
			{
				option = XOR;
			}
			if ((coord.X == 41) && (coord.Y == 8))
			{
				option = VIGERENE;
			}
			if ((coord.X == 41) && (coord.Y == 12))
			{
				option = RUN_LENGTH;
			}
		}
	} while (exit != true);

	return option;
}

void decryption_animation()
{
	int loading;
	COORD coord;

	print_on_raw_coord(30, 8, "Descifrando mensaje...");
	print_on_raw_coord(48, 22, "Leyendo mensaje.txt...");

	draw_screen_border();
	/** esquinas de recuadro de usuario*/

	print_on_raw_coord(29, 9, "\xC9");
	print_on_raw_coord(50, 9, "\xBB");
	print_on_raw_coord(29, 12, "\xC8");
	print_on_raw_coord(50, 12, "\xBC");

	/**box*/

	coord.Y = 9;
	do
	{ /**left side of box*/
		coord.Y++;
		print_on_raw_coord(29, coord.Y, "\xBA");
	} while (coord.Y != 11);

	coord.Y = 9;
	do
	{ /**right side of box*/
		coord.Y++;
		print_on_raw_coord(50, coord.Y, "\xBA");
	} while (coord.Y != 11);

	coord.X = 29;
	do
	{ /**the bottom of the box*/
		coord.X++;
		print_on_raw_coord(coord.X, 12, "\xCD");
	} while (coord.X != 49);

	coord.X = 29;
	do
	{ /**the top of box*/
		coord.X++;
		print_on_raw_coord(coord.X, 9, "\xCD");
	} while (coord.X != 49);

	/** Cargando Animacion*/

	for (loading = 30; loading < 50; loading++)
	{
		print_on_raw_coord(loading, 10, "\xDB");
		print_on_raw_coord(loading, 11, "\xDB");
		Sleep(100);
	}

	print_on_raw_coord(30, 8, "  Archivo Descifrado ");
	gotoxy(30, 8);
}

int simple_encryption()
{
	char input_length;
	char cipher_str[910];

	/** Read text*/
	char *input_str = input_text();
	if (input_str && !input_str[0])
	{
		return 1; /** Return key to cancel and go back to menu */
	}
	input_length = strlen(input_str) - 2;

	/***************************************************************************************************/
	/***** Algoritmo de Cifrado Simple */

	int i = 0;
	while (i <= input_length)
	{									  /**Genera el codigo cifrado*/
		cipher_str[i] = input_str[i] + 3; /**Modifica el numero*/
		i++;
	}
	cipher_str[i] = '\0'; /** se agrega final para que no imprima signos raros*/

	loading_animation();
	clean_screen();
	printf(" Mensaje Cifrado:\n");
	for (i = 0; i < input_length + 1; i++)
	{
		printf("%c", cipher_str[i]);
	}

	if (!save_text_to_file(cipher_str))
	{
		printf("Error saving message.txt file");
	}

	return 0;
}

int run_length_encryption()
{
	char input_length;
	int char_repeat_counter;
	char cipher_str[910], character;

	/** Read text*/
	char *input_str = input_text();
	if (input_str && !input_str[0])
	{
		return 1; /** Return key to cancel and go back to menu */
	}
	input_length = strlen(input_str) - 1;

	/***************************************************************************************************/
	/***** Algoritmo de Cifrado Run Length *************************************************************/
	/***************************************************************************************************/
	char_repeat_counter = 1;
	int i = 0, j = 0;
	for (i = 0; i < input_length; i++)
	{
		character = input_str[i]; /** se guardan caracteres de la cadena */
		if (input_str[i] == input_str[i + 1])
		{						   /** si es igual que su anterior entra */
			char_repeat_counter++; /** numero de veces que se repite     */
		}
		else
		{
			if (input_str[i] == input_str[i - 1])
			{ /** si no es igual entra              */
				cipher_str[j] = '#';
				j++;
				cipher_str[j] = character;
				j++;
				cipher_str[j] = char_repeat_counter + '0';
				j++;
				char_repeat_counter = 1;
			}
			else
			{
				cipher_str[j] = character;
				j++;
			}
		}
	}

	cipher_str[j] = '\0';

	/***************************************************************************************************/
	/*** Guardar Resultado en un TXT *******************************************************************/
	/***************************************************************************************************/
	loading_animation();
	clean_screen();
	printf(" Mensaje Cifrado:\n");
	for (i = 0; i < input_length; i++)
	{
		printf("%c", cipher_str[i]);
	}

	if (!save_text_to_file(cipher_str))
	{
		printf("Error saving message.txt");
	}
	return 0;
}

int simple_decryption()
{
	char input_str[910], decrypted_str[910];
	int input_length, i;

	/******************ABRE ARCHIVO TXT ************************************************/
	doc = fopen("mensaje.txt", "r");

	if (doc == NULL)
	{
		printf("\n\t\t\tARCHIVO NO ENCONTRADO!\n\n Asegurese de poner el archivo 'mensaje.txt' en la carpeta del programa");
		return 1; /** Regresa a menu */
	}

	fgets(input_str, 910, doc);
	fclose(doc);
	/*************************************************************************************/

	input_length = strlen(input_str);
	i = 0;

	while (i <= input_length - 1)
	{
		decrypted_str[i] = input_str[i] - 3;
		printf("%c", decrypted_str[i]);
		i++;
	}

	return 0;
}

int run_length_decryption()
{
	char input_str[910], decrypted_str[910];
	int input_length, decrypt_counter = 0, char_counter;
	char temp_char;

	/******************ABRE ARCHIVO TXT ************************************************/
	doc = fopen("mensaje.txt", "r");

	if (doc == NULL)
	{
		printf("\n\t\t\tARCHIVO NO ENCONTRADO!\n\n Asegurese de poner el arvhivo 'mensaje.txt' en la carpeta del programa");
		return 1; /** Regresa a menu */
	}

	fgets(input_str, 910, doc);
	fclose(doc);

	input_length = strlen(input_str);
	int i, j;

	for (i = 0; i <= input_length; i++)
	{
		if (input_str[i] == '#')
		{
			i++;							  /**Aumenta un espacio en el vector para leer la letra despues del signo # */
			temp_char = input_str[i];		  /** lee la letra comprimida */
			i++;							  /**Aumenta un espacio para leer el numero de veces que se repetira */
			char_counter = input_str[i] - 48; /** se guarda numero de veces en un entero */
			/** menos 48 porque en ASCII es donde comienzan los numeros del 0 al 9 */

			for (j = 0; j < char_counter; j++)
			{
				decrypted_str[decrypt_counter] = temp_char;
				printf("%c", temp_char);
				decrypt_counter++;
			}
		}
		else
		{
			decrypted_str[decrypt_counter] = input_str[i];
			printf("%c", decrypted_str[decrypt_counter]);
			decrypt_counter++;
		}
	}

	return 0;
}

int xor_encryption()
{
	char go_back_to_menu = 0, cipher_str[910];
	int i = 0;

	/**variables de algoritmo XOR*/
	int input_length, cadena_convert_decimal[910], j;
	int binary_8bit_ascii[7], inverted_binary[7], remainder, bin_counter, store_counter;
	int binary_store[910][8];
	int clave[8], claveaux, cipher_binary[910][8];
	int decimal_storage, temp_binary, decimal;
	/************************************/

	/** Read text*/
	char *cadena = input_text();
	if (cadena && !cadena[0])
	{
		return 1; /** Return key to cancel and go back to menu */
	}
	input_length = strlen(cadena) - 1;

	/***************************************************************************************************/
	/***** Algoritmo de Cifrado XOR ********************************************************************/
	/***************************************************************************************************/

	store_counter = 0;
	for (i = 0; i < input_length; i++)
	{
		cadena_convert_decimal[i] = cadena[i];

		for (j = 0; j <= 7; j++)
		{ /******* convierte a binario aunque invertido */
			remainder = (cadena_convert_decimal[i]) % 2;
			cadena_convert_decimal[i] = (cadena_convert_decimal[i]) / 2;
			inverted_binary[j] = remainder;
		}

		j = 0;
		for (bin_counter = 7; bin_counter >= 0; bin_counter--)
		{
			binary_8bit_ascii[j] = inverted_binary[bin_counter]; /** se cambia el invertido por el correcto */

			/**Matriz bidimencional para almacenar cada serie binaria de 8 digitos por cada lugar *****************/
			/** de los lugares recervados para cada caracter contado con ichar de cadena[];  **********************/
			binary_store[store_counter][j] = binary_8bit_ascii[j]; /**********************/
			/******************************************************************************************************/
			j++;
		}
		store_counter++; /** se aumenta 1 para pasar a otra dimension y almacenar otros 8 digitos *******/
	}

	/**********************************FIN DE CONVERSION A BINARIO ***************************************/
	printf("\nIngresa clave de cifrado binario de 8 bits\n"); /** esto debe ir despues de pedir el texto */
	for (i = 0; i < 8; i++)
	{
		claveaux = getch();
		clave[i] = claveaux - '0';
		if ((clave[i] != 0) && (clave[i] != 1))
		{
			printf("\tError!\nEjemplo de clave: '10110110'\n");
			i = -1;
		}
		else
		{
			printf("%d", clave[i]);
		}
	}
	printf("\n\nGuarda tu clave para poder descifrar el mensaje\nMuy bien! ahora presiona cualquier tecla para continuar");
	getch();
	clean_screen();
	loading_animation();
	clean_screen();

	/** Ciclo para Cifrar el Binario de cada letra ***************************************/
	printf("\n");
	for (i = 0; i < input_length; i++)
	{ /** validar binario de letras con Clave para cifrar */
		for (j = 0; j < 8; j++)
		{
			if (clave[j] == binary_store[i][j])
			{ /** si son iguales se cambia valor por 0*/
				cipher_binary[i][j] = 0;
			}
			else
			{ /** si son diferentes se cambia valor por 1 */
				cipher_binary[i][j] = 1;
			}
		}
	}

	/** Ciclo que convierte los Binarios Cifrados a Decimales....************************/

	for (i = 0; i < input_length; i++)
	{
		decimal_storage = 0;
		for (j = 0; j < 8; j++)
		{
			temp_binary = cipher_binary[i][j];
			decimal = temp_binary * pow(2, j);
			decimal_storage = decimal + decimal_storage;
		}
		cipher_str[i] = decimal_storage; /** se guarda en Cifrado cada numero decimal para leerlo posteriormente como caracter */
	}

	/************ IMPRIMIR MENSAJE CIFRADO **************************************/
	printf("Mensaje Cifrado:\n");
	for (i = 0; i < input_length; i++)
	{
		printf("%c", cipher_str[i]);
	}

	/***************************************************************************************************/
	/*** Guardar Resultado en un TXT *******************************************************************/
	/***************************************************************************************************/

	if (!save_text_to_file(cipher_str))
	{
		printf("Error saving message.txt");
	}

	return go_back_to_menu;
}

int xor_decryption()
{
	char input_str[910], decrypted_str[910];
	int char_counter, i;

	/*** Variables de Descifrado XOR *************/
	char confirmation = 'n';
	int clave[8], inverted_binary[8], binary_store[910][8], cipher_binary[910][8];
	int claveaux, remainder, j, binary_counter, decimal_storage, temp_binary, decimal;

	/*********************************************/

	/******************ABRE ARCHIVO TXT ************************************************/
	doc = fopen("mensaje.txt", "r");

	if (doc == NULL)
	{
		printf("\n\t\t\tARCHIVO NO ENCONTRADO!\n\n Asegurese de poner el arvhivo 'mensaje.txt' en la carpeta del programa");
		return 1; /** Regresa a menu */
	}

	fgets(input_str, 910, doc);
	printf("%s", input_str);
	fclose(doc);

	char_counter = strlen(input_str);

	/***********************************************************************************/

	while (confirmation != 'y')
	{
		clean_screen();
		printf("\n\tIngrese Clave binaria de decifrado: ");
		for (i = 7; i >= 0; i--)
		{
			claveaux = getch();
			if (claveaux == KEY_ESC)
			{
				return 1; /** si presiona ESC se regresa al menu */
			}
			clave[i] = claveaux - '0';
			if ((clave[i] != 0) && (clave[i] != 1))
			{
				printf("\tError!\nEjemplo de clave: '10110110'\n");
				i = 8;
			}
			else
			{
				printf("%d", clave[i]);
			}
		}
		printf("\n\tEstas seguro? y/n");
		confirmation = getch();
	}
	clean_screen();
	decryption_animation();
	clean_screen();

	for (i = 0; i < char_counter; i++)
	{
		decimal = input_str[i];
		/** hay simbolos que lee como decimales negativos      */
		if (decimal < 0)
		{
			decimal = input_str[i] + 256; /** la condicion es para convertirlos a positivos      */
		}								  /** sumandole 256 que es el total de simbolos en ASCII */

		/** convierte a binario aunque invertido */
		for (j = 0; j < 8; j++)
		{
			remainder = decimal % 2;
			decimal = decimal / 2;
			inverted_binary[j] = remainder;
		}

		j = 0;
		for (binary_counter = 7; binary_counter >= 0; binary_counter--)
		{
			binary_store[i][j] = inverted_binary[binary_counter]; /** se cambia el invertido por el correcto */
			j++;
		}
	}

	/** Ciclo para Descifrar el Binario de cada letra ***************************************/

	printf("\n");
	for (i = 0; i < char_counter; i++)
	{ /** validar binario de letras con Clave para cifrar */
		for (j = 0; j < 8; j++)
		{
			if (clave[j] == binary_store[i][j])
			{ /** si son iguales se cambia valor por 0*/
				cipher_binary[i][j] = 0;
			}
			else
			{ /** si son diferentes se cambia valor por 1 */
				cipher_binary[i][j] = 1;
			}
		}
	}

	/********** Convierte Binario a Decimal **************************************************/

	for (i = 0; i < char_counter; i++)
	{
		decimal_storage = 0;
		for (j = 0; j < 8; j++)
		{
			temp_binary = cipher_binary[i][j];
			decimal = temp_binary * (pow(2, j));
			decimal_storage = decimal + decimal_storage;
		}
		decrypted_str[i] = decimal_storage;
	}

	printf("Mensaje Descifrado:\n");
	for (i = 0; i < char_counter; i++)
	{
		printf("%c", decrypted_str[i]);
	}

	return 0;
}

int vigerene_encryption()
{
	char go_back_to_menu = 0, cipher_str[910];
	int i = 0, input_length;

	/**variables de algoritmo Vigerene*/

	char clave[4];
	int c = 0, iclave;

	/************************************/

	/** Read text*/
	char *input_str = input_text();
	if (input_str && !input_str[0])
	{
		return 1; /** Return key to cancel and go back to menu */
	}
	input_length = strlen(input_str) - 1;

	/***************************************************************************************************/
	/***** Algoritmo de Cifrado Vigerene ***************************************************************/
	/***************************************************************************************************/

	printf("\n Clave de Cifrado(MAX: 4 letras): ");
	scanf("%s", clave);
	iclave = strlen(clave);

	string_to_uppercase(input_str);
	string_to_uppercase(clave);
	for (i = 0; i < input_length; i++)
	{
		if (input_str[i] >= 'A' && input_str[i] <= 'Z')
		{
			if (c == iclave)
				c = 0;
			cipher_str[i] = (((input_str[i] - 65) + (clave[c] - 65)) % 26) + 65;
			c++;
		}
		else
		{
			cipher_str[i] = input_str[i];
		}
	}
	loading_animation();
	clean_screen();
	printf("Mensaje Cifrado:\n");
	for (i = 0; i < input_length; i++)
	{
		printf("%c", cipher_str[i]);
	}

	/***************************************************************************************************/
	/*** Guardar Resultado en un TXT *******************************************************************/
	/***************************************************************************************************/

	if (!save_text_to_file(cipher_str))
	{
		printf("Error saving message.txt");
	}

	return go_back_to_menu;
}

int vigerene_decryption()
{
	char input_str[910], cipher_str[910];
	int input_length, i;

	/*** Variables de Descifrado Vigerene *************/

	char clave[4];
	int c, iclave;

	/******************ABRE ARCHIVO TXT ************************************************/
	doc = fopen("mensaje.txt", "r");

	if (doc == NULL)
	{
		printf("\n\t\t\tARCHIVO NO ENCONTRADO!\n\n Asegurese de poner el archivo 'mensaje.txt' en la carpeta del programa");
		printf("\n\nPresione una tecla para salir");
		getch();
		return 1; /** Regresa a menu */
	}

	fgets(input_str, 909, doc);
	fclose(doc);

	printf("\tMensaje leido:\n\n %s", input_str);
	print_on_raw_coord(0, 2, " ");

	input_length = strlen(input_str);

	/***********************************************************************************/

	printf("\n\n\tCLAVE: ");
	i = 0;
	do
	{
		clave[i] = getch();
		if (clave[i] == KEY_ESC)
		{
			return 1;
		}
		printf("%c", clave[i]);
		i++;
	} while (i != 4);
	printf("\n\nListo! presiona Enter para continuar");
	getch();

	clean_screen();
	decryption_animation();
	clean_screen();

	iclave = strlen(clave);

	string_to_uppercase(input_str);
	string_to_uppercase(clave);
	c = 0;
	printf("\n\n   Mensaje Descifrado:\n\n");
	printf(" ");
	for (i = 0; i < input_length; i++)
	{
		if (input_str[i] >= 'A' && input_str[i] <= 'Z')
		{
			if (c == iclave - 1)
			{
				c = 0;
			}
			cipher_str[i] = (((input_str[i] - 65) - (clave[c] - 65)) + 26) % 26 + 'A';
			c++;
		}
		else
			cipher_str[i] = input_str[i];
	}

	for (i = 0; i < input_length; i++)
	{
		printf("%c", cipher_str[i]);
	}

	return 0;
}

void bye_animation()
{
	COORD coord;

	int bye[][18] = {
		{32, 95, 95, 95, 95, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32},
		{124, 32, 32, 95, 32, 92, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32},
		{124, 32, 124, 95, 41, 32, 124, 95, 32, 32, 32, 95, 32, 32, 95, 95, 95, 32},
		{124, 32, 32, 32, 32, 60, 124, 32, 124, 32, 124, 32, 124, 47, 32, 95, 32, 92},
		{124, 32, 124, 95, 41, 32, 124, 32, 124, 32, 124, 32, 124, 32, 32, 95, 95, 47},
		{124, 95, 95, 95, 95, 47, 32, 92, 95, 95, 44, 32, 124, 92, 95, 95, 95, 124},
		{32, 32, 32, 32, 32, 32, 32, 32, 95, 95, 47, 32, 124, 32, 32, 32, 32, 32},
		{32, 32, 32, 32, 32, 32, 32, 124, 95, 95, 95, 47, 32, 32, 32, 32, 32, 32}};

	int admiracion[][3] = {
		{32, 95, 32},
		{124, 32, 124},
		{124, 32, 124},
		{124, 32, 124},
		{124, 95, 124},
		{40, 95, 41}};

	/** Bye 1 */
	for (coord.Y = 0; coord.Y < 8; coord.Y++)
	{
		gotoxy(18, 7 + coord.Y);
		for (coord.X = 0; coord.X < 18; coord.X++)
		{
			printf("%c", bye[coord.Y][coord.X]);
		}
	}
	/** Bye 2 */
	for (coord.Y = 0; coord.Y < 8; coord.Y++)
	{
		gotoxy(37, 7 + coord.Y);
		for (coord.X = 0; coord.X < 18; coord.X++)
		{
			printf("%c", bye[coord.Y][coord.X]);
		}
	}
	/** Signo de Admiracion */
	for (coord.Y = 0; coord.Y < 6; coord.Y++)
	{
		gotoxy(55, 7 + coord.Y);
		for (coord.X = 0; coord.X < 3; coord.X++)
		{
			printf("%c", admiracion[coord.Y][coord.X]);
		}
	}

	coord.Y = 0;
	for (coord.X = 0; coord.X < 41; coord.X++)
	{ /**Impresion de asteriscos horizontales*/
		print_on_raw_coord(17 + coord.X, 15, "*");
		print_on_raw_coord(58 - coord.X, 7, "*");

		if ((coord.X % 5 == 0))
		{ /** impresion de asteriscos verticales */
			coord.Y++;
			print_on_raw_coord(17, 6 + coord.Y, "*");
			print_on_raw_coord(58, 16 - coord.Y, "*");
		}

		Sleep(50);
	}
	Sleep(500);
}
