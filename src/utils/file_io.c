/**
 * EnigmaProject - File I/O and Text Input Functions
 *
 * Handles user text input and file read/write operations.
 */

#include "../../include/enigma.h"

char *input_text(void)
{
	char *text_field = malloc(sizeof(char) * BUFFER_SIZE);
	if (!text_field)
		return NULL;

	char pressed_key = 0;
	int i = 0;
	COORD coord = {.X = 3, .Y = 9};

	while (pressed_key != KEY_ENTER)
	{
		gotoxy(coord.X, coord.Y);
		pressed_key = getch();

		if (pressed_key == KEY_ESC)
		{
			free(text_field);
			return NULL;
		}

		if (pressed_key == KEY_ENTER)
			break;

		if (pressed_key == 8)
		{
			if (i > 0)
			{
				i--;
				text_field[i] = '\0';
				coord.X--;
				if (coord.X < 3)
				{
					coord.Y--;
					coord.X = 72;
				}
				gotoxy(coord.X, coord.Y);
				printf(" ");
			}
		}
		else if (i < BUFFER_SIZE - 1)
		{
			text_field[i] = pressed_key;
			i++;
			printf("%c", pressed_key);
			coord.X++;
			if (coord.X == 74)
			{
				printf("\n");
				coord.Y++;
				coord.X = 4;
			}
		}
	}

	text_field[i] = '\0';
	clean_screen();
	return text_field;
}

bool save_text_to_file(const char str[])
{
	FILE *doc = fopen("mensaje.txt", "w");
	if (doc == NULL)
		return false;

	int success = fprintf(doc, "%s", str);
	fflush(doc);
	fclose(doc);

	return (success >= 0);
}

void free_text_input(char *text)
{
	if (text)
		free(text);
}
