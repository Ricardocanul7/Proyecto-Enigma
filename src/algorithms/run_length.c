/**
 * EnigmaProject - Algoritmo de Run-Length Encoding (Compresor)
 *
 * Comprime secuencias repetidas en el mensaje usando el formato #caracternum
 */

#include "../../include/enigma.h"

int run_length_encryption(void)
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

	/***** Algoritmo de Cifrado Run Length */
	char_repeat_counter = 1;
	int i = 0, j = 0;
	for (i = 0; i < input_length; i++)
	{
		character = input_str[i];
		if (input_str[i] == input_str[i + 1])
		{
			char_repeat_counter++;
		}
		else
		{
			if (input_str[i] == input_str[i - 1])
			{
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

int run_length_decryption(void)
{
	char input_str[910], decrypted_str[910];
	int input_length, decrypt_counter = 0, char_counter;
	char temp_char;

	/******************ABRE ARCHIVO TXT ************************************************/
	doc = fopen("mensaje.txt", "r");

	if (doc == NULL)
	{
		printf("\n\t\t\tARCHIVO NO ENCONTRADO!\n\n Asegurese de poner el arvhivo 'mensaje.txt' en la carpeta del programa");
		return 1;
	}

	fgets(input_str, 910, doc);
	fclose(doc);

	input_length = strlen(input_str);
	int i, j;

	for (i = 0; i <= input_length; i++)
	{
		if (input_str[i] == '#')
		{
			i++;
			temp_char = input_str[i];
			i++;
			char_counter = input_str[i] - 48;

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
