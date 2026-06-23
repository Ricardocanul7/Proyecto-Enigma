/**
 * EnigmaProject - Simple Encryption/Decryption Algorithm
 *
 * Implements substitution cipher (shift of 3 characters)
 * and file read/write operations.
 */

#include "../../include/enigma.h"

FILE *doc;

int simple_encryption(void)
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

	/***** Simple Encryption Algorithm */

	int i = 0;
	while (i <= input_length)
	{
		cipher_str[i] = input_str[i] + 3;
		i++;
	}
	cipher_str[i] = '\0';

	loading_animation();
	clean_screen();
	printf(" Encrypted Message:\n");
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

int simple_decryption(void)
{
	char input_str[910], decrypted_str[910];
	int input_length, i;

	/******************OPEN TXT FILE ************************************************/
	doc = fopen("mensaje.txt", "r");

	if (doc == NULL)
	{
		printf("\n\t\t\tFILE NOT FOUND!\n\n Make sure 'mensaje.txt' is in the program folder");
		return 1;
	}

	fgets(input_str, 910, doc);
	fclose(doc);

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

char *input_text(void)
{
	char *text_field = malloc(sizeof(char) * 910);
	char pressed_key, back_to_menu = 0;
	int string_length;
	int i = 0;
	COORD coord = {.X = 3, .Y = 9};

	while (pressed_key != KEY_ENTER)
	{
		if ((pressed_key == 8) && (coord.Y >= 9))
		{
			i = i - 2;
			text_field[i] = '\0';
			coord.X = coord.X - 2;
			if (coord.X < 3)
			{
				coord.Y--;
				coord.X = 72;
			}
		}
		coord.X++;
		if (coord.X == 74)
		{
			printf("\n");
			coord.Y++;
			coord.X = 4;
		}
		if (i == 910)
		{
			printf("\a");
			pressed_key = KEY_ENTER;
		}
		else
		{
			gotoxy(coord.X, coord.Y);
			pressed_key = getch();
			if (pressed_key == KEY_ESC)
			{
				return "";
			}
			printf("%c", pressed_key);
			text_field[i] = pressed_key;
			i++;
		}
	}

	text_field[i] = '\0';
	string_length = strlen(text_field);

	clean_screen();

	return text_field;
}

bool save_text_to_file(char str[])
{
	doc = fopen("mensaje.txt", "w");
	int success = fprintf(doc, "%s", str);
	fflush(doc);
	fclose(doc);

	if (success >= 0)
	{
		return true;
	}
	return false;
}
