/**
 * EnigmaProject - Vigenere Encryption/Decryption Algorithm
 *
 * It is a polyalphabetic substitution cipher.
 * The key must consist of letters without spaces or special characters.
 */

#include "../../include/enigma.h"

int vigenere_encryption(void)
{
	char cipher_str[BUFFER_SIZE];
	int i, input_length;

	char password[5];
	int c = 0, password_length;

	char *input_str = input_text();
	if (!input_str)
		return 1;

	input_length = strlen(input_str);

	printf("\n Encryption Key (MAX: 4 letters): ");
	for (i = 0; i < 4; i++)
	{
		password[i] = getch();
		if (password[i] == KEY_ESC)
		{
			free_text_input(input_str);
			return 1;
		}
		if (password[i] == '\r')
			break;
		printf("%c", password[i]);
	}
	password[i] = '\0';
	password_length = strlen(password);

	string_to_uppercase(input_str);
	string_to_uppercase(password);

	c = 0;
	for (i = 0; i < input_length; i++)
	{
		if (input_str[i] >= 'A' && input_str[i] <= 'Z')
		{
			if (c == password_length)
				c = 0;
			cipher_str[i] = (((input_str[i] - 'A') + (password[c] - 'A')) % 26) + 'A';
			c++;
		}
		else
		{
			cipher_str[i] = input_str[i];
		}
	}
	cipher_str[i] = '\0';

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

	free_text_input(input_str);
	return 0;
}

int vigenere_decryption(void)
{
	char input_str[BUFFER_SIZE], cipher_str[BUFFER_SIZE];
	int input_length, i;

	char password[5];
	int c, password_length;

	FILE *doc = fopen("mensaje.txt", "r");
	if (doc == NULL)
	{
		printf("\n\t\t\tFILE NOT FOUND!\n\n Make sure 'mensaje.txt' is in the program folder");
		printf("\n\nPress any key to exit");
		getch();
		return 1;
	}

	fgets(input_str, BUFFER_SIZE, doc);
	fclose(doc);

	printf("\tRead message:\n\n %s", input_str);
	print_on_raw_coord(0, 2, " ");

	input_length = strlen(input_str);

	printf("\n\n\tKEY: ");
	i = 0;
	do
	{
		password[i] = getch();
		if (password[i] == KEY_ESC)
			return 1;
		if (password[i] == '\r')
			break;
		printf("%c", password[i]);
		i++;
	} while (i < 4);
	password[i] = '\0';

	printf("\n\nReady! Press Enter to continue");
	getch();

	clean_screen();
	decryption_animation();
	clean_screen();

	password_length = strlen(password);

	string_to_uppercase(input_str);
	string_to_uppercase(password);
	c = 0;
	printf("\n\n   Decrypted Message:\n\n");
	printf(" ");
	for (i = 0; i < input_length; i++)
	{
		if (input_str[i] >= 'A' && input_str[i] <= 'Z')
		{
			if (c == password_length)
				c = 0;
			cipher_str[i] = (((input_str[i] - 'A') - (password[c] - 'A')) + 26) % 26 + 'A';
			c++;
		}
		else
			cipher_str[i] = input_str[i];
	}
	cipher_str[i] = '\0';

	for (i = 0; i < input_length; i++)
	{
		printf("%c", cipher_str[i]);
	}

	return 0;
}

void vigenere_encrypt_str(const char *input, const char *key, char *output, int len)
{
	int key_len = strlen(key);
	int c = 0;
	for (int i = 0; i < len; i++)
	{
		if (input[i] >= 'A' && input[i] <= 'Z')
		{
			if (c == key_len)
				c = 0;
			output[i] = (((input[i] - 'A') + (key[c] - 'A')) % 26) + 'A';
			c++;
		}
		else
		{
			output[i] = input[i];
		}
	}
	output[len] = '\0';
}

void vigenere_decrypt_str(const char *input, const char *key, char *output, int len)
{
	int key_len = strlen(key);
	int c = 0;
	for (int i = 0; i < len; i++)
	{
		if (input[i] >= 'A' && input[i] <= 'Z')
		{
			if (c == key_len)
				c = 0;
			output[i] = (((input[i] - 'A') - (key[c] - 'A')) + 26) % 26 + 'A';
			c++;
		}
		else
		{
			output[i] = input[i];
		}
	}
	output[len] = '\0';
}
