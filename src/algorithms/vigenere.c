/**
 * EnigmaProject - Vigenere Encryption/Decryption Algorithm
 *
 * It is a polyalphabetic substitution cipher.
 * The key must consist of letters without spaces or special characters.
 */

#include "../../include/enigma.h"

int vigenere_encryption(void)
{
	char go_back_to_menu = 0, cipher_str[910];
	int i = 0, input_length;

	/**Vigenere algorithm variables*/
	char clave[4];
	int c = 0, iclave;

	/** Read text*/
	char *input_str = input_text();
	if (input_str && !input_str[0])
	{
		return 1;
	}
	input_length = strlen(input_str) - 1;

	/***** Vigenere Encryption Algorithm */

	printf("\n Encryption Key (MAX: 4 letters): ");
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
	printf("Encrypted Message:\n");
	for (i = 0; i < input_length; i++)
	{
		printf("%c", cipher_str[i]);
	}

	if (!save_text_to_file(cipher_str))
	{
		printf("Error saving message.txt");
	}

	return go_back_to_menu;
}

int vigerene_decryption(void)
{
	char input_str[910], cipher_str[910];
	int input_length, i;

	/*** Vigenere Decryption Variables */
	char clave[4];
	int c, iclave;

	/******************OPEN TXT FILE ************************************************/
	doc = fopen("mensaje.txt", "r");

	if (doc == NULL)
	{
		printf("\n\t\t\tFILE NOT FOUND!\n\n Make sure 'mensaje.txt' is in the program folder");
		printf("\n\nPress any key to exit");
		getch();
		return 1;
	}

	fgets(input_str, 909, doc);
	fclose(doc);

	printf("\tRead message:\n\n %s", input_str);
	print_on_raw_coord(0, 2, " ");

	input_length = strlen(input_str);

	printf("\n\n\tKEY: ");
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
	printf("\n\nReady! Press Enter to continue");
	getch();

	clean_screen();
	decryption_animation();
	clean_screen();

	iclave = strlen(clave);

	string_to_uppercase(input_str);
	string_to_uppercase(clave);
	c = 0;
	printf("\n\n   Decrypted Message:\n\n");
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
