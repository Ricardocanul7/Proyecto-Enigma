/**
 * EnigmaProject - Simple Encryption/Decryption Algorithm
 *
 * Implements substitution cipher (shift of 3 characters)
 * and file read/write operations.
 */

#include "../../include/enigma.h"

int simple_encryption(void)
{
	int input_length;
	char cipher_str[BUFFER_SIZE];

	char *input_str = input_text();
	if (!input_str)
		return 1;

	input_length = strlen(input_str);

	int i = 0;
	while (i < input_length)
	{
		cipher_str[i] = input_str[i] + 3;
		i++;
	}
	cipher_str[i] = '\0';

	loading_animation();
	clean_screen();
	printf(" Encrypted Message:\n");
	for (i = 0; i < input_length; i++)
	{
		printf("%c", cipher_str[i]);
	}

	if (!save_text_to_file(cipher_str))
	{
		printf("Error saving message.txt file");
	}

	free_text_input(input_str);
	return 0;
}

int simple_decryption(void)
{
	char input_str[BUFFER_SIZE];
	int input_length, i;

	FILE *doc = fopen("mensaje.txt", "r");
	if (doc == NULL)
	{
		printf("\n\t\t\tFILE NOT FOUND!\n\n Make sure 'mensaje.txt' is in the program folder");
		return 1;
	}

	fgets(input_str, BUFFER_SIZE, doc);
	fclose(doc);

	input_length = strlen(input_str);
	for (i = 0; i < input_length; i++)
	{
		printf("%c", input_str[i] - 3);
	}

	return 0;
}
