/**
 * EnigmaProject - Animation Functions
 *
 * All functions related to console animations
 */

#include "../../include/enigma.h"

void loading_animation(void)
{
	int loading;
	COORD coord;

	print_on_raw_coord(30, 8,"Encrypting message...");
	print_on_raw_coord(40, 23,"Generating message.txt file");

	draw_screen_border();
	/** user box corners */
	print_on_raw_coord(29, 9,"\xC9");
	print_on_raw_coord(50, 9,"\xBB");
	print_on_raw_coord(29, 12,"\xC8");
	print_on_raw_coord(50, 12,"\xBC");

	/**box*/

	coord.Y = 9;
	do { /**left side of box*/
		coord.Y++;
		print_on_raw_coord(29, coord.Y,"\xBA");
	} while (coord.Y != 11);

	coord.Y = 9;
	do { /**right side of box*/
		coord.Y++;
		print_on_raw_coord(50, coord.Y,"\xBA");
	} while (coord.Y != 11);

	coord.X = 29;
	do { /**the bottom of the box*/
		coord.X++;
		print_on_raw_coord(coord.X, 12,"\xCD");
	} while (coord.X != 49);

	coord.X = 29;
	do { /**the top of box*/
		coord.X++;
		print_on_raw_coord(coord.X, 9,"\xCD");
	} while (coord.X != 49);

	/** Loading Animation */

	for (loading = 30; loading < 50; loading++) {
		print_on_raw_coord(loading, 10,"\xDB");
		print_on_raw_coord(loading, 11,"\xDB");
		Sleep(100);
	}

	print_on_raw_coord(40, 23,"                                    "); /** clear "generating txt" printf */
	print_on_raw_coord(30, 8,"  Encryption Successful! ");
	print_on_raw_coord(20, 17,"Press any key to return to menu.");
	getch();
}

void decryption_animation(void)
{
	int loading;
	COORD coord;

	print_on_raw_coord(30, 8,"Decrypting message...");
	print_on_raw_coord(48, 22,"Reading message.txt...");

	draw_screen_border();
	/** user box corners */

	print_on_raw_coord(29, 9,"\xC9");
	print_on_raw_coord(50, 9,"\xBB");
	print_on_raw_coord(29, 12,"\xC8");
	print_on_raw_coord(50, 12,"\xBC");

	/**box*/

	coord.Y = 9;
	do { /**left side of box*/
		coord.Y++;
		print_on_raw_coord(29, coord.Y,"\xBA");
	} while (coord.Y != 11);

	coord.Y = 9;
	do { /**right side of box*/
		coord.Y++;
		print_on_raw_coord(50, coord.Y,"\xBA");
	} while (coord.Y != 11);

	coord.X = 29;
	do { /**the bottom of the box*/
		coord.X++;
		print_on_raw_coord(coord.X, 12,"\xCD");
	} while (coord.X != 49);

	coord.X = 29;
	do { /**the top of box*/
		coord.X++;
		print_on_raw_coord(coord.X, 9,"\xCD");
	} while (coord.X != 49);

	/** Loading Animation */

	for (loading = 30; loading < 50; loading++) {
		print_on_raw_coord(loading, 10,"\xDB");
		print_on_raw_coord(loading, 11,"\xDB");
		Sleep(100);
	}

	print_on_raw_coord(30, 8,"  Decrypted File ");
	gotoxy(30, 8);
}

void about_screen(void)
{
	int transition;

	for (transition = 16; transition > 0; transition--) {
		print_on_raw_coord(24, 8,"  ___       _                    \n");
		print_on_raw_coord(24, 9," | __>._ _ <_> ___.._ _ _  ____ \n");
		print_on_raw_coord(24, 10," | _> |   || |/ . || Y Y |<_>  |\n");
		print_on_raw_coord(24, 11," |___>|_|_||_|\\_. ||_|_|_|<____|\xA9\n");
		print_on_raw_coord(24, 12,"              <___:              \n");

		char* message =
			"EnigmaProject was made by:\n\n"
			" -Arias Morales Marvin\n\n"
			" -Canul Flota Ricardo.\n\n"
			" -Cordova Villamil Jorge\n\n"
			" -Pool Alvarado Marco";
		print_on_raw_coord(0, transition, message);
		Sleep(300);
		if (transition > 1) {
			clean_screen();
		}
	}
	print_on_raw_coord(19, 18,"Press any key to return to menu");
}

void bye_animation(void)
{
	COORD coord;

	int bye[][18] = {
		{32, 95, 95, 95, 95, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32},
		{124, 32, 32, 95, 32, 92, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32},
		{124, 32, 124, 95, 41, 32, 124, 95, 32, 32, 32, 95, 32, 32, 95, 95, 95},
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
	for (coord.Y = 0; coord.Y < 8; coord.Y++) {
		gotoxy(18, 7 + coord.Y);
		for (coord.X = 0; coord.X < 18; coord.X++) {
			printf("%c", bye[coord.Y][coord.X]);
		}
	}
	/** Bye 2 */
	for (coord.Y = 0; coord.Y < 8; coord.Y++) {
		gotoxy(37, 7 + coord.Y);
		for (coord.X = 0; coord.X < 18; coord.X++) {
			printf("%c", bye[coord.Y][coord.X]);
		}
	}
	/** Exclamation Sign */
	for (coord.Y = 0; coord.Y < 6; coord.Y++) {
		gotoxy(55, 7 + coord.Y);
		for (coord.X = 0; coord.X < 3; coord.X++) {
			printf("%c", admiracion[coord.Y][coord.X]);
		}
	}

	coord.Y = 0;
	for (coord.X = 0; coord.X < 41; coord.X++) { /**Horizontal asterisk animation*/
		print_on_raw_coord(17 + coord.X, 15,"*");
		print_on_raw_coord(58 - coord.X, 7,"*");

		if ((coord.X % 5 == 0)) { /** vertical asterisk animation */
			coord.Y++;
			print_on_raw_coord(17, 6 + coord.Y,"*");
			print_on_raw_coord(58, 16 - coord.Y,"*");
		}

		Sleep(50);
	}
	Sleep(500);
}
