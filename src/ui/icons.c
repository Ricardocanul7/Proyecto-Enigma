/**
 * EnigmaProject - Funciones de Iconos Gráficos
 * 
 * Todas las funciones relacionadas con iconos ASCII art
 */

#include "../../include/enigma.h"

void padlock_close_icon(void)
{
	COORD coord;

	int keydraw[][9] = { /** Cada numero representa un valor en ASCII*/
		{32, 220, 223, 223, 223, 220, 32, 32},
		{32, 219, 32, 32, 32, 219, 32, 32},
		{219, 219, 219, 219, 219, 219, 219, 32},
		{219, 219, 32, 32, 32, 219, 219, 32},
		{219, 219, 219, 220, 219, 219, 219, 32}};

	for (coord.Y = 0; coord.Y < 5; coord.Y++) { /**saltos del linea o coordenas Y*/
		gotoxy(60, 10 + coord.Y);
		for (coord.X = 0; coord.X < 9; coord.X++) { /**Coordendas X*/
			if (coord.Y < 2) {
				set_color_and_background(6, 0);
			} else {
				set_color_and_background(3, 0);
			}
			printf("%c", keydraw[coord.Y][coord.X]);
			if (coord.X == 8) { /** si llega al ultimo lugar brinca para seguir dibujando en Y++ */
				printf("\n");
			}
		}
	}
}

void padlock_open_icon(void)
{
	COORD coord;

	int keydraw[][9] = { /** Cada numero representa un valor en ASCII*/
		{32, 32, 32, 32, 32, 220, 223, 223, 220},
		{32, 32, 32, 32, 32, 219, 32, 32, 223},
		{219, 219, 219, 219, 219, 219, 219, 32, 32},
		{219, 219, 32, 32, 32, 219, 219, 32, 32},
		{219, 219, 219, 220, 219, 219, 219, 32, 32}

	};

	for (coord.Y = 0; coord.Y < 5; coord.Y++) { /**saltos del linea o coordenas Y*/
		gotoxy(60, 10 + coord.Y);
		for (coord.X = 0; coord.X < 9; coord.X++) { /**Coordendas X*/
			if (coord.Y < 2) {
				set_color_and_background(6, 0);
			} else {
				set_color_and_background(2, 0);
			}
			printf("%c", keydraw[coord.Y][coord.X]);
			if (coord.X == 8) { /** si llega al ultimo lugar brinca para seguir dibujando en Y++ */
				printf("\n");
			}
		}
	}
}

void about_icon(void)
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

	for (coord.Y = 0; coord.Y < 7; coord.Y++) { /**saltos del linea o coordenas Y*/
		gotoxy(60, 9 + coord.Y);
		for (coord.X = 0; coord.X < 9; coord.X++) { /**Coordendas X*/
			printf("%c", keydraw[coord.Y][coord.X]);
			if (coord.X == 8) { /** si llega al ultimo lugar brinca para seguir dibujando en Y++ */
				printf("\n");
			}
		}
	}
}

void exit_icon(void)
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
	for (coord.Y = 0; coord.Y < 7; coord.Y++) { /**saltos del linea o coordenas Y*/
		gotoxy(60, 10 + coord.Y);
		for (coord.X = 0; coord.X < 9; coord.X++) { /**Coordendas X*/
			printf("%c", keydraw[coord.Y][coord.X]);
			if (coord.X == 8) { /** si llega al ultimo lugar brinca para seguir dibujando en Y++ */
				printf("\n");
			}
		}
	}
}