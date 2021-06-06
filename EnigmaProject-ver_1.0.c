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

/** Teclas de direccion o navegacion "DEPRACATED - REMOVE WHEN NO REFERENCES LEFT ON MAIN CODE"
 * Replaced by enum KeyboardKeys below.
*/
#define arriba 72
#define abajo 80
#define izquierda 75
#define derecha 77
#define enter 13
#define Espacio 32
#define ESC 27

FILE *doc; /** doc es la variable usada para el archivo txt que se guardara en el proceso de cifrado*/

/* Screens */
void main_menu();		   /**Diseño del Menu interactivo de inicio del programa*/
void draw_screen_border(); /**Diseño del Marco del programa*/
void draw_login_form();	   /** recuadro de usuario y logotipo de ENIGMA*/
void login_screen();
int encryption_type_option_screen();
int decryption_type_option_screen();
void draw_message_input_form();
int insert_text();	 /**Estructura para ingresar datos de cadena para cada tipo de encriptado... no sera funcion*/
void about_screen(); /** Info+Animacion de la seccion Acerca de */

/* Animations */
void loading_animation();	 /** Animacion de Cargando(CIFRANDO) */
void decryption_animation(); /** Animacion Descifrado */
void bye_animation();

/* Actions */
int authentication(); /**Compara el usuario que se ingresa del teclado con el de la constante*/
int open_file();	  /** abrir texto para descifrar */

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

/** ICONOS *********************************/
void padlock_close_icon(); /***/
void padlock_open_icon();  /***/
void about_icon();		   /***/
void exit_icon();		   /***/
/*******************************************/

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

void uppercase_to_lowercase(char cadena[])
{
	int cambiar = 32, i; /** lA DISTANCIA DE LAS MINUSCULAS A MAYUSCULAS ES 32*/
	for (i = 0; i < 910; i++)
	{
		if (cadena[i] > 96 && cadena[i] < 123)
		{
			cadena[i] = cadena[i] - cambiar;
		}
	}
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
	gotoxy(29, 8);
	printf("\xC9");
	gotoxy(50, 8);
	printf("\xBB");
	gotoxy(29, 11);
	printf("\xC8");
	gotoxy(50, 11);
	printf("\xBC");

	/** draw user input box*/
	coord.Y = 8;
	do
	{ /**left side of user box*/
		coord.Y++;
		gotoxy(29, coord.Y);
		printf("\xBA");
	} while (coord.Y != 10);

	coord.Y = 8;
	do
	{ /**right side of user box*/
		coord.Y++;
		gotoxy(50, coord.Y);
		printf("\xBA");
	} while (coord.Y != 10);

	coord.X = 29;
	do
	{ /**the bottom of the user box*/
		coord.X++;
		gotoxy(coord.X, 11);
		printf("\xCD");
	} while (coord.X != 49);

	coord.X = 29;
	do
	{ /**the top of user box*/
		coord.X++;
		gotoxy(coord.X, 8);
		printf("\xCD");
	} while (coord.X != 49);

	gotoxy(24, 2); /**Title Enigma at the top*/
	printf("  ___       _                    \n");
	gotoxy(24, 3);
	printf(" | __>._ _ <_> ___. _ _ _  ____ \n");
	gotoxy(24, 4);
	printf(" | _> | � || |/ . || � � |<_>  |\n");
	gotoxy(24, 5);
	printf(" |___>|_|_||_|\\_. ||_|_|_|<____|\xA9\n");
	gotoxy(24, 6);
	printf("              <___:              \n");

	gotoxy(36, 13); /**coordenadas debajo del user box*/
	printf("         ");
	gotoxy(36, 14);
	printf(" USUARIO ");
	gotoxy(36, 15);
	printf("         ");

	gotoxy(32, 10); /** coordenadas para ingresar texto*/
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
			gotoxy(32, 10);
			set_color_and_background(4, 0);
			printf("¡Incorrecto!");
			Sleep(300); /**tiempo que aparecera "¡Incorrecto!" en pantalla*/
		}

		system("cls"); /** limpia pantalla cada bucle para poder ingresar usuario nuevo*/
	} while (auth_response != IS_LOGGED);
	printf("\a");
}

void draw_screen_border()
{
	COORD coord;

	/** Dibujar esquinas */

	gotoxy(1, 1);
	printf("\xC9");
	gotoxy(1, 24);
	printf("\xC8");
	gotoxy(77, 1);
	printf("\xBB");
	gotoxy(77, 24);
	printf("\xBC");

	/** Dibujo del Marco o Dorde*/

	coord.X = 1;
	do
	{ /**lado superior*/
		coord.X++;
		gotoxy(coord.X, 1);
		printf("\xCD");
	} while (coord.X != 76);

	coord.X = 1;
	do
	{ /**lado inferior*/
		coord.X++;
		gotoxy(coord.X, 24);
		printf("\xCD");
	} while (coord.X != 76);

	coord.Y = 1;
	do
	{ /** lado derecho*/
		coord.Y++;
		gotoxy(77, coord.Y);
		printf("\xBA");
	} while (coord.Y != 23);

	coord.Y = 1;
	do
	{ /** lado izquierdo*/
		coord.Y++;
		gotoxy(1, coord.Y);
		printf("\xBA");
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
		system("cls");

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
		gotoxy(10, 8);
		printf("Encriptar");
		gotoxy(17, 11);
		printf("Desencriptar");
		gotoxy(24, 14);
		printf("Acerca de");
		gotoxy(31, 17);
		printf("Salir");
		gotoxy(coord.X, coord.Y);
		printf("-->");

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
				system("cls");
				gotoxy(13, 13);
				encryption_type = encryption_type_option_screen(); /** tipo seria del 1 al 4  */
				system("cls");
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
				system("cls");
				gotoxy(13, 13);
				encryption_type = decryption_type_option_screen(); /** tipo seria del 1 al 4          */
				system("cls");
				switch (encryption_type)
				{
				case SIMPLE:
					decryption_animation();
					system("cls");
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
					system("cls");
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
				system("cls");
				about_screen(); /** Animacion e Informacion de los desarrolladores */
				getch();
			}
			if (menu_index == EXIT) /** Salir  */
			{
				system("cls");
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
			gotoxy(coord.X, coord.Y);
			printf("\xB1");
		}
	}

	for (coord.Y = 8; coord.Y < 24; coord.Y++)
	{
		gotoxy(2, coord.Y);
		printf("\xB1");
	}

	for (coord.Y = 8; coord.Y < 24; coord.Y++)
	{
		gotoxy(76, coord.Y);
		printf("\xB1");
	}

	for (coord.X = 2; coord.X < 76; coord.X++)
	{
		gotoxy(coord.X, 23);
		printf("\xB1"); /**Base de dise�o*/
	}
	gotoxy(3, 5);
	printf("         ");
	gotoxy(3, 6);
	printf(" MENSAJE ");
	gotoxy(3, 7);
	printf("         ");
}

int insert_text()
{ /**Funcion Para leer texto dentro del recuadro de MENSAJE(Esta funcion no se usa, solo es un prototipo para recibir texto en cada funcion de cifrado)*/
	char cadena[910], ch, numcaracters, Regresar_Menu = 0;
	int i = 0, y = 9, x = 3;

	while (ch != 13) /** Termina si el usuario presiona enter*/
	{
		if ((ch == 8) && (y >= 9))
		{					  /** 8 es la tecla DEL */
			i = i - 2;		  /** al retroceder i se resta 2 para retroceder 1 lugar ya que al final se aumento i una vez mas*/
			cadena[i] = '\0'; /** al retroceder ingresa un valor null en el numero de matriz[i]*/
			x = x - 2;		  /** la coordenada igual retrocede para poder escribir en una coordenada anterior*/
			if (x < 3)
			{
				y--;	/**si la COORD x es menor a 3, y subira a la ultima linea*/
				x = 72; /**al subir Y, x tiene que ubicarse al final de la linea*/
			}
		}
		x++; /** se aumenta COORD x cada ciclo para simular que se escribe una cadena*/
		if (x == 74)
		{
			printf("\n"); /** si COORD x llega a 74, este brinca una linea para continuar escribiendo y no borre el marco dibujado*/
			y++;		  /** COORD y aumenta 1 por lo tanto brinca a la linea de abajo */
			x = 4;		  /** al estar en la linea de abajo x regresa a su valor inicial para esribir de izq a derecha*/
		}
		if (i == 910)
		{				  /** determina si ya llego al limite de caracteres para la matriz*/
			printf("\a"); /** se genera un sonido en caso de llegar al limite de caracteres*/
			ch = 13;	  /** se genera un ENTER automatico para continuar con el programa*/
		}
		else
		{
			gotoxy(x, y); /** Funcion para ubicar en el plano la impresion de cada caracter*/
			ch = getch(); /** entrada de caracteres*/
			if (ch == ESC)
			{
				return 1;
			}
			printf("%c", ch); /** mostrar el caracter que acaba de ser tecleado*/
			cadena[i] = ch;
			i++; /** contador para asignar caracter a cada matriz*/
		}
	}

	cadena[i] = '\0'; /** inserta un valor NULL al final*/
	numcaracters = strlen(cadena);

	system("cls");								/**limpia la pantalla para imprimir desde el principio de la terminal*/
	printf("\n %d Caracteres\n", numcaracters); /** PRUEBA DE NUMERO DE CARACTERES*/

	doc = fopen("mensaje.txt", "w");
	fprintf(doc, "%s", cadena); /** PRUEBA IMPRIME TODO LOS CARACTERES ALMACENADOS */
	fflush(doc);
	fclose(doc);

	return Regresar_Menu;
}

int encryption_type_option_screen()
{
	COORD coord;
	coord.X = 20;
	coord.Y = 8;

	char pressed_key;
	int aux = 0, option;

	do
	{
		system("cls");
		draw_screen_border();
		gotoxy(26, 4);
		printf("* SELECCIONA TIPO DE CIFRADO *");
		gotoxy(24, 8);
		printf("1.-SIMPLE");
		gotoxy(24, 12);
		printf("2.-XOR");
		gotoxy(45, 8);
		printf("3.-VIGERENE");
		gotoxy(45, 12);
		printf("4.-RUN LENGTH");
		gotoxy(45, 13);
		printf("  (COMPRESOR)");

		gotoxy(coord.X, coord.Y);
		printf("-->");

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

		if (pressed_key == KEY_ESC)
		{ /** si presiona la tecla ESC pasa valor 5 y regresa a menu */
			option = 5;
			aux = 1; /** como queremos regresar a menu aux = 1 es la condicion para salir del while */
		}

		if (pressed_key == KEY_ENTER)
		{ /** Lo que pasaria en cada caso  */
			aux = 1;

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
	} while (aux != 1);

	return option;
}

void loading_animation()
{
	int loading;
	COORD coord;

	gotoxy(30, 8);
	printf("Cifrando mensaje...");
	gotoxy(40, 23);
	printf("Generando archivo mensaje.txt");

	draw_screen_border();
	/** esquinas de recuadro de usuario*/
	gotoxy(29, 9);
	printf("\xC9");
	gotoxy(50, 9);
	printf("\xBB");
	gotoxy(29, 12);
	printf("\xC8");
	gotoxy(50, 12);
	printf("\xBC");

	/**box*/

	coord.Y = 9;
	do
	{ /**left side of box*/
		coord.Y++;
		gotoxy(29, coord.Y);
		printf("\xBA");
	} while (coord.Y != 11);

	coord.Y = 9;
	do
	{ /**right side of box*/
		coord.Y++;
		gotoxy(50, coord.Y);
		printf("\xBA");
	} while (coord.Y != 11);

	coord.X = 29;
	do
	{ /**the bottom of the box*/
		coord.X++;
		gotoxy(coord.X, 12);
		printf("\xCD");
	} while (coord.X != 49);

	coord.X = 29;
	do
	{ /**the top of box*/
		coord.X++;
		gotoxy(coord.X, 9);
		printf("\xCD");
	} while (coord.X != 49);

	/** Cargano Animacion*/

	for (loading = 30; loading < 50; loading++)
	{

		gotoxy(loading, 10);
		printf("\xDB");
		gotoxy(loading, 11);
		printf("\xDB");
		Sleep(100);
	}
	gotoxy(40, 23);
	printf("                                    "); /** borrar printf de "generando txt" */
	gotoxy(30, 8);
	printf("  Cifrado Exitoso! ");
	gotoxy(20, 17);
	printf("Presione una tecla para volver al menu.");
	getch();
}

void about_screen()
{
	int transicion;

	for (transicion = 16; transicion > 0; transicion--)
	{

		gotoxy(24, 8); /**Titulo de Enigma en el centro de la pantalla*/
		printf("  ___       _                    \n");
		gotoxy(24, 9);
		printf(" | __>._ _ <_> ___. _ _ _  ____ \n");
		gotoxy(24, 10);
		printf(" | _> | � || |/ . || � � |<_>  |\n");
		gotoxy(24, 11);
		printf(" |___>|_|_||_|\\_. ||_|_|_|<____|\xA9\n");
		gotoxy(24, 12);
		printf("              <___:              \n");

		gotoxy(0, transicion);
		printf("EnigmaProject fue realizado por:\n\n -Arias Morales Marvin\n\n -Canul Flota Ricardo.\n\n -Cordova Villamil Jorge\n\n -Pool Alvarado Marco");
		Sleep(300);
		if (transicion > 1)
		{
			system("cls");
		}
	}
	gotoxy(19, 18);
	printf("Pulse una tecla para volver al menu");
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
	int aux = 0, option;

	do
	{
		system("cls");
		draw_screen_border();
		gotoxy(26, 4);
		printf("* SELECCIONA TIPO DE DESCIFRADO *");
		gotoxy(24, 8);
		printf("1.-SIMPLE");
		gotoxy(24, 12);
		printf("2.-XOR");
		gotoxy(45, 8);
		printf("3.-VIGERENE");
		gotoxy(45, 12);
		printf("4.-RUN LENGTH");
		gotoxy(45, 13);
		printf("  (DESCOMPRESOR)");

		gotoxy(coord.X, coord.Y);
		printf("-->");

		pressed_key = getch();
		if (pressed_key == KEY_DOWN)
		{ /** TECLAS   */
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
		{ /** DE       */
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
		{ /** DIRECCION */
			if (coord.X < 41)
			{
				coord.X += 21;
			}
			else
			{
				coord.X = 20;
			}
		}
		if (pressed_key == KEY_ESC)
		{ /** si presiona la tecla ESC pasa valor 5 y regresa a menu */
			option = 5;
			aux = 1; /** como queremos regresar a menu aux = 1 es la condicion para salir del while */
		}

		if (pressed_key == KEY_ENTER)
		{ /** Lo que pasaria en cada caso  */
			aux = 1;
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
	} while (aux != 1);

	return option;
}

void decryption_animation()
{
	int cargando;
	int x, y;

	gotoxy(30, 8);
	printf("Descifrando mensaje...");
	gotoxy(48, 22);
	printf("Leyendo mensaje.txt...");

	draw_screen_border();
	/** esquinas de recuadro de usuario*/
	gotoxy(29, 9);
	printf("\xC9");
	gotoxy(50, 9);
	printf("\xBB");
	gotoxy(29, 12);
	printf("\xC8");
	gotoxy(50, 12);
	printf("\xBC");

	/**box*/

	y = 9;
	do
	{ /**left side of box*/
		y++;
		gotoxy(29, y);
		printf("\xBA");
	} while (y != 11);

	y = 9;
	do
	{ /**right side of box*/
		y++;
		gotoxy(50, y);
		printf("\xBA");
	} while (y != 11);

	x = 29;
	do
	{ /**the bottom of the box*/
		x++;
		gotoxy(x, 12);
		printf("\xCD");
	} while (x != 49);

	x = 29;
	do
	{ /**the top of box*/
		x++;
		gotoxy(x, 9);
		printf("\xCD");
	} while (x != 49);

	/** Cargando Animacion*/

	for (cargando = 30; cargando < 50; cargando++)
	{
		gotoxy(cargando, 10);
		printf("\xDB");
		gotoxy(cargando, 11);
		printf("\xDB");
		Sleep(100);
	}
	gotoxy(30, 8);
	printf("  Archivo Descifrado ");
}

int simple_encryption()
{ /** Algoritmo de Cifrado Simple*/
	char cadena[910], ch, ichar;
	int i = 0, y = 9, x = 3;
	int cifrar[910];
	char cifrar_char[910];

	while (ch != 13) /** Termina si el usuario presiona enter*/
	{
		if ((ch == 8) && (y >= 9))
		{					  /** 8 es la tecla DEL */
			i = i - 2;		  /** al retroceder i se resta 2 para retroceder 1 lugar ya que al final se aumento i una vez mas*/
			cadena[i] = '\0'; /** al retroceder ingresa un valor null en el numero de matriz[i]*/
			x = x - 2;		  /** la coordenada igual retrocede para poder escribir en una coordenada anterior*/
			if (x < 3)
			{
				y--;	/**si la COORD x es menor a 3, y subira a la ultima linea*/
				x = 72; /**al subir Y, x tiene que ubicarse al final de la linea*/
			}
		}
		x++; /** se aumenta COORD x cada ciclo para simular que se escribe una cadena*/
		if (x == 74)
		{
			printf("\n"); /** si COORD x llega a 74, este brinca una linea para continuar escribiendo y no borre el marco dibujado*/
			y++;		  /** COORD y aumenta 1 por lo tanto brinca a la linea de abajo */
			x = 4;		  /** al estar en la linea de abajo x regresa a su valor inicial para esribir de izq a derecha*/
		}
		if (i == 910)
		{				  /** determina si ya llego al limite de caracteres para la matriz*/
			printf("\a"); /** se genera un sonido en caso de llegar al limite de caracteres*/
			ch = 13;	  /** se genera un ENTER automatico para continuar con el programa*/
		}
		else
		{
			gotoxy(x, y); /** Funcion para ubicar en el plano la impresion de cada caracter*/
			ch = getch(); /** entrada de caracteres*/
			if (ch == ESC)
			{
				return 1;
				/**ch = 13;*/
			}
			printf("%c", ch); /** mostrar el caracter que acaba de ser tecleado*/
			cadena[i] = ch;
			i++; /** contador para asignar caracter a cada matriz*/
		}
	}
	/**if(i == 1){
		** como solo dio una vuelta el while quiere decir que se presiono ESC no hace nada y sale */
	/** entonces regresa al menu principal*
		Regresar_Menu = 1;
	}
	else{*/
	cadena[i] = '\0'; /** inserta un valor NULL al final*/
	ichar = strlen(cadena) - 2;

	system("cls"); /**limpia la pantalla para imprimir desde el principio de la terminal*/
	/**printf("\n %d Caracteres\n",ichar);     ** PRUEBA DE NUMERO DE CARACTERES*/

	/***************************************************************************************************/
	/***** Algoritmo de Cifrado Simple */

	i = 0;

	while (i <= ichar)
	{									/**Genera el codigo cifrado*/
		cifrar[i] = cadena[i];			/**Convierte el caracter a codigo ASCII*/
		cifrar_char[i] = cifrar[i] + 3; /**Modifica el numero*/
		/** ESto lo puse como comentario porque interfiere con la animacion de Cifrando... */
		/**printf("%c",cifrar_char[i]);        **Regresa el numero modificado a caracter****/
		/***********************************************************************************/
		i++;
	}
	cifrar_char[i] = '\0'; /** se agrega final para que no imprima signos raros*/

	loading_animation();
	system("cls");
	printf(" Mensaje Cifrado:\n");
	for (i = 0; i < ichar + 1; i++)
	{
		printf("%c", cifrar_char[i]);
	}

	doc = fopen("mensaje.txt", "w");
	fprintf(doc, "%s", cifrar_char); /** PRUEBA IMPRIME TODO LOS CARACTERES ALMACENADOS y los manda al ARCHIVO TXT */
	fflush(doc);
	fclose(doc);
	/**}*/
	return 0;
}

int run_length_encryption()
{
	char cadena[910], ch, ichar;
	int i = 0, y = 9, x = 3;

	/**variables de algoritmo run length*/
	int Repeticiones, j;		 /***/
	char Cifrado[910], caracter; /***/
	/************************************/

	while (ch != enter) /** Termina si el usuario presiona enter*/
	{
		if ((ch == 8) && (y >= 9))
		{					  /** 8 es la tecla DEL */
			i = i - 2;		  /** al retroceder i se resta 2 para retroceder 1 lugar ya que al final se aumento i una vez mas*/
			cadena[i] = '\0'; /** al retroceder ingresa un valor null en el numero de matriz[i]*/
			x = x - 2;		  /** la coordenada igual retrocede para poder escribir en una coordenada anterior*/
			if (x < 3)
			{
				y--;	/**si la COORD x es menor a 3, y subira a la ultima linea*/
				x = 72; /**al subir Y, x tiene que ubicarse al final de la linea*/
			}
		}
		x++; /** se aumenta COORD x cada ciclo para simular que se escribe una cadena*/
		if (x == 74)
		{
			printf("\n"); /** si COORD x llega a 74, este brinca una linea para continuar escribiendo y no borre el marco dibujado*/
			y++;		  /** COORD y aumenta 1 por lo tanto brinca a la linea de abajo */
			x = 4;		  /** al estar en la linea de abajo x regresa a su valor inicial para esribir de izq a derecha*/
		}
		if (i == 910)
		{				  /** determina si ya llego al limite de caracteres para la matriz*/
			printf("\a"); /** se genera un sonido en caso de llegar al limite de caracteres*/
			ch = 13;	  /** se genera un ENTER automatico para continuar con el programa*/
		}
		else
		{
			gotoxy(x, y); /** Funcion para ubicar en el plano la impresion de cada caracter*/
			ch = getch(); /** entrada de caracteres*/
			if (ch == ESC)
			{
				return 1;
				/**ch = 13;*/
			}
			printf("%c", ch); /** mostrar el caracter que acaba de ser tecleado*/
			cadena[i] = ch;
			i++; /** contador para asignar caracter a cada matriz*/
		}
	}
	/**if(i == 1){
		** como solo dio una vuelta el while quiere decir que se presiono ESC no hace nada y sale */
	/** entonces regresa al menu principal*
		Regresar_Menu = 1;
	}
	else{*/
	cadena[i] = '\0'; /** inserta un valor NULL al final*/
	ichar = strlen(cadena) - 1;

	system("cls"); /**limpia la pantalla para imprimir desde el principio de la terminal*/
	/**printf("\n %d Caracteres\n",ichar);     ** PRUEBA DE NUMERO DE CARACTERES*/

	/***************************************************************************************************/
	/***** Algoritmo de Cifrado Run Length *************************************************************/
	/***************************************************************************************************/
	Repeticiones = 1;
	j = 0;

	for (i = 0; i < ichar; i++)
	{
		caracter = cadena[i]; /** se guardan caracteres de la cadena */
		if (cadena[i] == cadena[i + 1])
		{					/** si es igual que su anterior entra */
			Repeticiones++; /** numero de veces que se repite     */
		}
		else
		{
			if (cadena[i] == cadena[i - 1])
			{ /** si no es igual entra              */
				Cifrado[j] = '#';
				j++;
				Cifrado[j] = caracter;
				j++;
				Cifrado[j] = Repeticiones + '0';
				j++;
				Repeticiones = 1;
			}
			else
			{
				Cifrado[j] = caracter;
				j++;
			}
		}
	}

	Cifrado[j] = '\0';
	/**printf("%s",Cifrado);*/

	/***************************************************************************************************/
	/*** Guardar Resultado en un TXT *******************************************************************/
	/***************************************************************************************************/
	loading_animation();
	system("cls");
	printf(" Mensaje Cifrado:\n");
	for (i = 0; i < ichar; i++)
	{
		printf("%c", Cifrado[i]);
	}

	doc = fopen("mensaje.txt", "w");
	fprintf(doc, "%s", Cifrado); /** PRUEBA IMPRIME TODO LOS CARACTERES ALMACENADOS y los manda al ARCHIVO TXT */
	fflush(doc);
	fclose(doc);
	/**}*/
	return 0;
}

int simple_decryption()
{
	char lectura[910], descifrar[910];
	int decimalC[910];
	int ichar, i;

	/******************ABRE ARCHIVO TXT ************************************************/
	doc = fopen("mensaje.txt", "r");

	if (doc == NULL)
	{
		printf("\n\t\t\tARCHIVO NO ENCONTRADO!\n\n Asegurese de poner el arvhivo 'mensaje.txt' en la carpeta del programa");
		return 1; /** Regresa a menu */
	}

	fgets(lectura, 910, doc);
	/**fscanf(doc,"%s\0",lectura);*/
	/**printf("%s\n",lectura);                     ** PRUEBA */
	fclose(doc);
	/*********** Termina lectura de archivo ahora podemos usar Lectura[]; para descifrar */
	/*************************************************************************************/

	ichar = strlen(lectura);
	/**printf("Numero de Caracteres %d\n",ichar);  ** PRUEBA */

	i = 0;

	while (i <= ichar - 1)
	{
		decimalC[i] = lectura[i];
		descifrar[i] = decimalC[i] - 3;
		printf("%c", descifrar[i]);
		i++;
	}

	return 0;
}

int run_length_decryption()
{
	char lectura[910], descifrar[910];
	int ichar, i, iDescifrar = 0, icaracteres, j;
	char caracterTemp;

	/******************ABRE ARCHIVO TXT ************************************************/
	doc = fopen("mensaje.txt", "r");

	if (doc == NULL)
	{
		printf("\n\t\t\tARCHIVO NO ENCONTRADO!\n\n Asegurese de poner el arvhivo 'mensaje.txt' en la carpeta del programa");
		return 1; /** Regresa a menu */
	}

	fgets(lectura, 910, doc);
	/**fscanf(doc,"%s\0",&lectura);*/
	/**printf("%s\n",lectura);                     ** PRUEBA */
	fclose(doc);
	/*********** Termina lectura de archivo ahora podemos usar Lectura[]; para descifrar */

	ichar = strlen(lectura);
	/**printf("Numero de Caracteres %d\n",ichar);  ** PRUEBA */

	for (i = 0; i <= ichar; i++)
	{
		if (lectura[i] == '#')
		{
			i++;						   /**Aumenta un espacio en el vector para leer la letra despues del signo # */
			caracterTemp = lectura[i];	   /** lee la letra comprimida */
			i++;						   /**Aumenta un espacio para leer el numero de veces que se repetira */
			icaracteres = lectura[i] - 48; /** se guarda numero de veces en un entero */
			/** menos 48 porque en ASCII es donde comienzan los numeros del 0 al 9 */

			/**printf("\n( %d )",icaracteres);  ** Prueba para saber si funciona */

			for (j = 0; j < icaracteres; j++)
			{
				descifrar[iDescifrar] = caracterTemp;
				printf("%c", caracterTemp);
				iDescifrar++;
			}
		}
		else
		{
			descifrar[iDescifrar] = lectura[i];
			printf("%c", descifrar[iDescifrar]);
			iDescifrar++;
		}
	}

	return 0;
}

int xor_encryption()
{
	char cadena[910], ch, Regresar_Menu = 0, Cifrado[910];
	int i = 0, y = 9, x = 3;

	/**variables de algoritmo XOR*/
	int ichar, cadena_convert_decimal[910], j;
	int Binario_8bit_ASCII[7], Binario_Invertido[7], resto, contadorbin, contador_Almacen;
	/**int contador_Salto_linea;*/
	int Almacen_Binario[910][8];
	int clave[8], claveaux, CifradoBin[910][8];
	int suma, binTemp, decimal;
	/************************************/

	while (ch != 13) /** Termina si el usuario presiona enter*/
	{
		if ((ch == 8) && (y >= 9))
		{					  /** 8 es la tecla DEL */
			i = i - 2;		  /** al retroceder i se resta 2 para retroceder 1 lugar ya que al final se aumento i una vez mas*/
			cadena[i] = '\0'; /** al retroceder ingresa un valor null en el numero de matriz[i]*/
			x = x - 2;		  /** la coordenada igual retrocede para poder escribir en una coordenada anterior*/
			if (x < 3)
			{
				y--;	/**si la COORD x es menor a 3, y subira a la ultima linea*/
				x = 72; /**al subir Y, x tiene que ubicarse al final de la linea*/
			}
		}
		x++; /** se aumenta COORD x cada ciclo para simular que se escribe una cadena*/
		if (x == 74)
		{
			printf("\n"); /** si COORD x llega a 74, este brinca una linea para continuar escribiendo y no borre el marco dibujado*/
			y++;		  /** COORD y aumenta 1 por lo tanto brinca a la linea de abajo */
			x = 4;		  /** al estar en la linea de abajo x regresa a su valor inicial para esribir de izq a derecha*/
		}
		if (i == 910)
		{				  /** determina si ya llego al limite de caracteres para la matriz*/
			printf("\a"); /** se genera un sonido en caso de llegar al limite de caracteres*/
			ch = 13;	  /** se genera un ENTER automatico para continuar con el programa*/
		}
		else
		{
			gotoxy(x, y); /** Funcion para ubicar en el plano la impresion de cada caracter*/
			ch = getch(); /** entrada de caracteres*/
			if (ch == ESC)
			{
				return 1;
				/**ch = 13;*/
			}
			printf("%c", ch); /** mostrar el caracter que acaba de ser tecleado*/
			cadena[i] = ch;
			i++; /** contador para asignar caracter a cada matriz*/
		}
	}
	/**if(i == 1){
		** como solo dio una vuelta el while quiere decir que se presiono ESC no hace nada y sale */
	/** entonces regresa al menu principal*
		Regresar_Menu = 1;
	}
	else{*/
	cadena[i] = '\0'; /** inserta un valor NULL al final*/
	ichar = strlen(cadena) - 1;

	system("cls"); /**limpia la pantalla para imprimir desde el principio de la terminal*/
	/**printf("\n %d Caracteres\n",ichar);     ** PRUEBA DE NUMERO DE CARACTERES*/

	/***************************************************************************************************/
	/***** Algoritmo de Cifrado XOR ********************************************************************/
	/***************************************************************************************************/

	/**printf("\nnumero de caracteres: %d\n",ichar); ** prueba para saber si funciona */
	/**printf("Binario en 8 bits\n\n");*/
	contador_Almacen = 0;
	for (i = 0; i < ichar; i++)
	{
		cadena_convert_decimal[i] = cadena[i];
		/**printf("Prueba de que paso a decimal %d\n",cadena_convert_decimal[i]);*/

		for (j = 0; j <= 7; j++)
		{ /******* convierte a binario aunque invertido */
			resto = (cadena_convert_decimal[i]) % 2;
			cadena_convert_decimal[i] = (cadena_convert_decimal[i]) / 2;
			Binario_Invertido[j] = resto;
			/**printf("%d",resto);                  ** prueba para saber si pasa a binario */
		}

		j = 0;
		for (contadorbin = 7; contadorbin >= 0; contadorbin--)
		{
			Binario_8bit_ASCII[j] = Binario_Invertido[contadorbin]; /** se cambia el invertido por el correcto */
			/**printf("%d",Binario_8bit_ASCII[j]);             ** imprimo del 0++; para verificar que este en orden */

			/**Matriz bidimencional para almacenar cada serie binaria de 8 digitos por cada lugar *****************/
			/** de los lugares recervados para cada caracter contado con ichar de cadena[];  **********************/
			Almacen_Binario[contador_Almacen][j] = Binario_8bit_ASCII[j]; /**********************/
			/******************************************************************************************************/
			j++;
		}
		contador_Almacen++; /** se aumenta 1 para pasar a otra dimension y almacenar otros 8 digitos *******/
	}

	/** impresion de numeros binarios para verificar que se hayan guardado en la matriz   *
		contador_Salto_linea = 0;
		for(i = 0; i < ichar ; i++){             
		for(j = 0; j <= 7; j++){
		printf("%d",Almacen_Binario[i][j]);       **imprimira los binarios almacenado en cada dimension *
		}                                             ** para verificar que han sido salvados correctamente *
		** y posteriormente darles un uso  *
		printf(" ");      ** espacio entre cada serie de 8 digitos*
		contador_Salto_linea++;
		if(contador_Salto_linea == 8){   ** si llega a 8 series de 8 digitos hace salto de linea  *
		printf("\n\n");
		contador_Salto_linea = 0;   ** y el contador regresa a cero para poder contar de 0 a 8*
		}
		}
		********************************FIN DE CONVERSION A BINARIO ***************************************/
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
	system("cls");
	loading_animation();
	system("cls");

	/** Ciclo para Cifrar el Binario de cada letra ***************************************/

	printf("\n");
	for (i = 0; i < ichar; i++)
	{ /** validar binario de letras con Clave para cifrar */
		for (j = 0; j < 8; j++)
		{
			if (clave[j] == Almacen_Binario[i][j])
			{ /** si son iguales se cambia valor por 0*/
				CifradoBin[i][j] = 0;
			}
			else
			{ /** si son diferentes se cambia valor por 1 */
				CifradoBin[i][j] = 1;
			}
		}
	}

	/**********************************************************************************/
	/****Imprime el Binario Cifredo como Prueba...************************************/
	/**
		contador_Salto_linea = 0;
		for(i = 0; i < ichar ; i++){             
		for(j = 0; j <= 7; j++){
		printf("%d",CifradoBin[i][j]);       **imprimira los binarios almacenado en cada dimension *
		}                                             ** para verificar que han sido salvados correctamente *
		** y posteriormente darles un uso  *
		printf(" ");      ** espacio entre cada serie de 8 digitos*
		contador_Salto_linea++;
		if(contador_Salto_linea == 8){   ** si llega a 8 series de 8 digitos hace salto de linea  *
		printf("\n\n");
		contador_Salto_linea = 0;   ** y el contador regresa a cero para poder contar de 0 a 8*
		}
		}  **********************************Eliminar cuando deje de servir *********************/
	/********************************************************************************************/

	/** Ciclo que convierte los Binarios Cifrados a Decimales....************************/

	for (i = 0; i < ichar; i++)
	{
		/**printf("\n");*/
		suma = 0;
		for (j = 0; j < 8; j++)
		{
			binTemp = CifradoBin[i][j];
			decimal = binTemp * pow(2, j);
			suma = decimal + suma;
		}
		/**printf("=%d,",suma);   ** prueba para saber si el decimal esta bien  */
		Cifrado[i] = suma; /** se guarda en Cifrado cada numero decimal para leerlo posteriormente como caracter */
	}

	/************ PRUEBA DE IMPRIMIR MENSAJE CIFRADO **************************************/
	printf("Mensaje Cifrado:\n");
	for (i = 0; i < ichar; i++)
	{
		printf("%c", Cifrado[i]);
	}

	/***************************************************************************************************/
	/*** Guardar Resultado en un TXT *******************************************************************/
	/***************************************************************************************************/

	doc = fopen("mensaje.txt", "w");
	fprintf(doc, "%s", Cifrado); /** PRUEBA IMPRIME TODO LOS CARACTERES ALMACENADOS y los manda al ARCHIVO TXT */
	fflush(doc);
	fclose(doc);
	/**}*/
	return Regresar_Menu;
}

int xor_decryption()
{
	char lectura[910], descifrar[910];
	int ichar, i;

	/*** Variables de Descifrado XOR *************/
	char seguro = 'n';
	int clave[8], Binario_Invertido[8], Almacen_Binario[910][8], CifradoBin[910][8];
	int claveaux, resto, j, contadorbin, suma, binTemp, decimal;

	/*********************************************/

	/******************ABRE ARCHIVO TXT ************************************************/
	doc = fopen("mensaje.txt", "r");

	if (doc == NULL)
	{
		printf("\n\t\t\tARCHIVO NO ENCONTRADO!\n\n Asegurese de poner el arvhivo 'mensaje.txt' en la carpeta del programa");
		return 1; /** Regresa a menu */
	}

	fgets(lectura, 910, doc);
	/**fscanf(doc,"%s\0",lectura);*/
	printf("%s", lectura); /** PRUEBA */
	/**getch();*/
	fclose(doc);
	/*********** Termina lectura de archivo ahora podemos usar Lectura[]; para descifrar */

	ichar = strlen(lectura);
	/**printf("Numero de Caracteres %d\n",ichar);  ** PRUEBA */

	/***********************************************************************************/

	while (seguro != 'y')
	{
		system("cls");
		printf("\n\tIngrese Clave binaria de decifrado: ");
		for (i = 7; i >= 0; i--)
		{
			claveaux = getch();
			if (claveaux == ESC)
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
		seguro = getch();
	}
	system("cls");
	decryption_animation();
	system("cls");

	for (i = 0; i < ichar; i++)
	{
		/*************************************************************************************/
		decimal = lectura[i]; /***/
		if (decimal < 0)
		{								/** hay simbolos que lee como decimales negativos      */
			decimal = lectura[i] + 256; /** la condicion es para convertirlos a positivos      */
		}								/** sumandole 256 que es el total de simbolos en ASCII */
		/*************************************************************************************/

		for (j = 0; j < 8; j++)
		{ /******* convierte a binario aunque invertido */
			resto = decimal % 2;
			decimal = decimal / 2;
			Binario_Invertido[j] = resto;
		}

		j = 0;
		for (contadorbin = 7; contadorbin >= 0; contadorbin--)
		{
			Almacen_Binario[i][j] = Binario_Invertido[contadorbin]; /** se cambia el invertido por el correcto */
			j++;
		}
	}

	/** Ciclo para Descifrar el Binario de cada letra ***************************************/

	printf("\n");
	for (i = 0; i < ichar; i++)
	{ /** validar binario de letras con Clave para cifrar */
		for (j = 0; j < 8; j++)
		{
			if (clave[j] == Almacen_Binario[i][j])
			{ /** si son iguales se cambia valor por 0*/
				CifradoBin[i][j] = 0;
			}
			else
			{ /** si son diferentes se cambia valor por 1 */
				CifradoBin[i][j] = 1;
			}
		}
	}

	/********** Convierte Binario a Decimal **************************************************/

	for (i = 0; i < ichar; i++)
	{
		suma = 0;
		for (j = 0; j < 8; j++)
		{
			binTemp = CifradoBin[i][j];
			decimal = binTemp * (pow(2, j));
			suma = decimal + suma;
		}
		/**printf("%d,",suma);   ** prueba para saber si el decimal esta bien */
		descifrar[i] = suma;
	}

	printf("Mensaje Descifrado:\n");
	for (i = 0; i < ichar; i++)
	{
		printf("%c", descifrar[i]);
	}

	return 0;
}

int vigerene_encryption()
{
	char cadena[910], ch, Regresar_Menu = 0, Cifrado[910];
	int i = 0, y = 9, x = 3, ichar;

	/**variables de algoritmo Vigerene*/

	char clave[4];
	int c = 0, iclave;

	/************************************/

	while (ch != 13) /** Termina si el usuario presiona enter*/
	{
		if ((ch == 8) && (y >= 9))
		{					  /** 8 es la tecla DEL */
			i = i - 2;		  /** al retroceder i se resta 2 para retroceder 1 lugar ya que al final se aumento i una vez mas*/
			cadena[i] = '\0'; /** al retroceder ingresa un valor null en el numero de matriz[i]*/
			x = x - 2;		  /** la coordenada igual retrocede para poder escribir en una coordenada anterior*/
			if (x < 3)
			{
				y--;	/**si la COORD x es menor a 3, y subira a la ultima linea*/
				x = 72; /**al subir Y, x tiene que ubicarse al final de la linea*/
			}
		}
		x++; /** se aumenta COORD x cada ciclo para simular que se escribe una cadena*/
		if (x == 74)
		{
			printf("\n"); /** si COORD x llega a 74, este brinca una linea para continuar escribiendo y no borre el marco dibujado*/
			y++;		  /** COORD y aumenta 1 por lo tanto brinca a la linea de abajo */
			x = 4;		  /** al estar en la linea de abajo x regresa a su valor inicial para esribir de izq a derecha*/
		}
		if (i == 910)
		{				  /** determina si ya llego al limite de caracteres para la matriz*/
			printf("\a"); /** se genera un sonido en caso de llegar al limite de caracteres*/
			ch = 13;	  /** se genera un ENTER automatico para continuar con el programa*/
		}
		else
		{
			gotoxy(x, y); /** Funcion para ubicar en el plano la impresion de cada caracter*/
			ch = getch(); /** entrada de caracteres*/
			if (ch == ESC)
			{
				return 1;
				/**ch = 13;*/
			}
			printf("%c", ch); /** mostrar el caracter que acaba de ser tecleado*/
			cadena[i] = ch;
			i++; /** contador para asignar caracter a cada matriz*/
		}
	}
	/**if(i == 1){
		** como solo dio una vuelta el while quiere decir que se presiono ESC no hace nada y sale *
		** entonces regresa al menu principal*
		Regresar_Menu = 1;
	}
	else{*/
	printf("\a");
	/**cadena[i]= '\0';                     ** inserta un valor NULL al final*/
	ichar = strlen(cadena) - 1;

	system("cls"); /**limpia la pantalla para imprimir desde el principio de la terminal*/
	/**printf("\n %d Caracteres\n",ichar);     ** PRUEBA DE NUMERO DE CARACTERES*/

	/***************************************************************************************************/
	/***** Algoritmo de Cifrado Vigerene ***************************************************************/
	/***************************************************************************************************/

	printf("\n Clave de Cifrado(MAX: 4 letras): ");
	scanf("%s", clave);
	/**fgets(clave, 10, stdin);*/
	iclave = strlen(clave);

	uppercase_to_lowercase(cadena);
	for (i = 0; i < ichar; i++)
	{
		if (cadena[i] >= 64 && cadena[i] < 91)
		{
			if (c == iclave)
				c = 0;
			Cifrado[i] = ((cadena[i] - 65 + clave[c] - 65) % 26) + 65;
			c++;
		}
		else
		{
			Cifrado[i] = cadena[i];
		}
	}
	loading_animation();
	system("cls");
	printf("Mensaje Cifrado:\n");
	for (i = 0; i < ichar; i++)
	{
		printf("%c", Cifrado[i]);
	}

	/***************************************************************************************************/
	/*** Guardar Resultado en un TXT *******************************************************************/
	/***************************************************************************************************/

	doc = fopen("mensaje.txt", "w");
	fprintf(doc, "%s", Cifrado); /** PRUEBA IMPRIME TODO LOS CARACTERES ALMACENADOS y los manda al ARCHIVO TXT */
	fflush(doc);
	fclose(doc);
	/**}*/
	return Regresar_Menu;
}

int vigerene_decryption()
{
	char lectura[910], descifrar[910];
	int ichar, i;

	/*** Variables de Descifrado Vigerene *************/

	char clave[4];
	int c, iclave;

	/*********************************************/

	/******************ABRE ARCHIVO TXT ************************************************/
	doc = fopen("mensaje.txt", "r");

	if (doc == NULL)
	{
		printf("\n\t\t\tARCHIVO NO ENCONTRADO!\n\n Asegurese de poner el archivo 'mensaje.txt' en la carpeta del programa");
		printf("\n\nPresione una tecla para salir");
		getch();
		return 1; /** Regresa a menu */
	}

	fgets(lectura, 909, doc);
	/**fscanf(doc,"%s^[\0]",lectura);*/ /** no funciona!!! solo lee una palabra */
	fclose(doc);

	printf("\tMensaje leido:\n\n %s", lectura); /** PRUEBA */
	gotoxy(0, 2);
	printf(" ");

	/*********** Termina lectura de archivo ahora podemos usar Lectura[]; para descifrar */

	ichar = strlen(lectura);

	/**printf("\nNumero de Caracteres %d\n",ichar);  ** PRUEBA */

	/***********************************************************************************/

	printf("\n\n\tCLAVE: ");
	i = 0;
	do
	{
		clave[i] = getch();
		if (clave[i] == ESC)
		{
			return 1;
		}
		printf("%c", clave[i]);
		i++;
	} while (i != 4);
	printf("\n\nListo! presiona Enter para continuar");
	getch();

	/**scanf("%s",clave);
	**fgets(clave, 10, stdin);*/
	system("cls");
	decryption_animation();
	system("cls");

	iclave = strlen(clave);

	uppercase_to_lowercase(lectura);
	c = 0;
	printf("\n\n   Mensaje Descifrado:\n\n");
	printf(" ");
	for (i = 0; i < ichar; i++)
	{
		if (lectura[i] >= 64 && lectura[i] < 91)
		{
			if (c == iclave)
				c = 0;
			descifrar[i] = (((((lectura[i] - 65) % 26) - ((clave[c] - 65) % 26) + 26) % 26)) + 65;
			c++;
		}
		else
			descifrar[i] = lectura[i];
	}

	for (i = 0; i < ichar; i++)
	{
		printf("%c", descifrar[i]);
	}
	/**gotoxy(0,10);   ** para eliminar una letra que se imprime en esta coordenada y es erronea *
	printf(" ");*/

	return 0;
}

void bye_animation()
{
	int x, y;

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
	for (y = 0; y < 8; y++)
	{
		gotoxy(18, 7 + y);
		for (x = 0; x < 18; x++)
		{
			printf("%c", bye[y][x]);
		}
	}
	/** Bye 2 */
	for (y = 0; y < 8; y++)
	{
		gotoxy(37, 7 + y);
		for (x = 0; x < 18; x++)
		{
			printf("%c", bye[y][x]);
		}
	}
	/** Signo de Admiracion */
	for (y = 0; y < 6; y++)
	{
		gotoxy(55, 7 + y);
		for (x = 0; x < 3; x++)
		{
			printf("%c", admiracion[y][x]);
		}
	}

	y = 0;
	for (x = 0; x < 41; x++)
	{ /**Impresion de asteriscos horizontales*/
		gotoxy(17 + x, 15);
		printf("*");
		gotoxy(58 - x, 7);
		printf("*");

		if ((x % 5 == 0))
		{ /** impresion de asteriscos verticales */
			y++;
			gotoxy(17, 6 + y);
			printf("*");
			gotoxy(58, 16 - y);
			printf("*");
		}

		Sleep(50);
	}
	Sleep(500);
}
