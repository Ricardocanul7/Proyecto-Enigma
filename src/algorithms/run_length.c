/**
 * EnigmaProject - Run-Length Encoding Algorithm (Compressor)
 *
 * Compresses repeated sequences in the message using the format #characternum
 */

#include "../../include/enigma.h"

int run_length_encryption(void)
{
	int input_length;
	int char_repeat_counter;
	char cipher_str[BUFFER_SIZE], character;

	char *input_str = input_text();
	if (!input_str)
		return 1;

	input_length = strlen(input_str);

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
			if (i > 0 && input_str[i] == input_str[i - 1])
			{
				cipher_str[j++] = '#';
				cipher_str[j++] = character;
				cipher_str[j++] = char_repeat_counter + '0';
				char_repeat_counter = 1;
			}
			else
			{
				cipher_str[j++] = character;
			}
		}
	}

	cipher_str[j] = '\0';

	loading_animation();
	clean_screen();
	printf(" Encrypted Message:\n");
	for (i = 0; i < j; i++)
	{
		printf("%c", cipher_str[i]);
	}

	if (!save_text_to_file(cipher_str))
	{
		printf("Error saving message.txt");
	}

	free_text_input(input_str);
	return 0;
}

int run_length_decryption(void)
{
	char input_str[BUFFER_SIZE], decrypted_str[BUFFER_SIZE];
	int input_length, decrypt_counter = 0, char_counter;
	char temp_char;

	FILE *doc = fopen("mensaje.txt", "r");
	if (doc == NULL)
	{
		printf("\n\t\t\tFILE NOT FOUND!\n\n Make sure 'mensaje.txt' is in the program folder");
		return 1;
	}

	fgets(input_str, BUFFER_SIZE, doc);
	fclose(doc);

	input_length = strlen(input_str);
	int i, j;

	for (i = 0; i < input_length; i++)
	{
		if (input_str[i] == '#')
		{
			i++;
			temp_char = input_str[i];
			i++;
			char_counter = input_str[i] - '0';

			for (j = 0; j < char_counter; j++)
			{
				decrypted_str[decrypt_counter++] = temp_char;
				printf("%c", temp_char);
			}
		}
		else
		{
			decrypted_str[decrypt_counter] = input_str[i];
			printf("%c", decrypted_str[decrypt_counter]);
			decrypt_counter++;
		}
	}
	decrypted_str[decrypt_counter] = '\0';

	return 0;
}
