/**
 * EnigmaProject - Console/Utility Functions
 *
 * All functions related to console operations
 */

#include "../../include/enigma.h"

void set_color_and_background(int ForgC, int BackC)
{
	WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
}

int *gotoxy(int x, int y)
{
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hcon, dwPos);
	return 0;
}

void print_on_coord(COORD coord, char str[])
{
	gotoxy(coord.X, coord.Y);
	printf(str);
}

void print_on_raw_coord(int x, int y, char str[])
{
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

void clean_screen(void)
{
	system("cls");
}
