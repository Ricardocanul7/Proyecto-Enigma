/**
 * EnigmaProject - XOR Encryption/Decryption Algorithm
 *
 * XOR is a bitwise or binary operation, with the rules:
 * 1. If bits of number A and B are equal the result is "0", otherwise the result is "1".
 */

#include "../../include/enigma.h"

int xor_encryption(void)
{
	char cipher_str[BUFFER_SIZE];
	int input_length, j;
	int binary_store[BUFFER_SIZE][8];
	int clave[8], claveaux, cipher_binary[BUFFER_SIZE][8];
	int store_counter, bin_counter, remainder;
	int decimal_storage, temp_binary;

	char *cadena = input_text();
	if (!cadena)
		return 1;

	input_length = strlen(cadena);

	store_counter = 0;
	for (int i = 0; i < input_length; i++)
	{
		int decimal = cadena[i];
		int inverted_binary[8];

		for (j = 0; j < 8; j++)
		{
			remainder = decimal % 2;
			decimal = decimal / 2;
			inverted_binary[j] = remainder;
		}

		j = 0;
		for (bin_counter = 7; bin_counter >= 0; bin_counter--)
		{
			binary_store[store_counter][j] = inverted_binary[bin_counter];
			j++;
		}
		store_counter++;
	}

	printf("\nEnter 8-bit binary encryption key:\n");
	for (int i = 0; i < 8; i++)
	{
		claveaux = getch();
		clave[i] = claveaux - '0';
		if ((clave[i] != 0) && (clave[i] != 1))
		{
			printf("\tError!\nKey example: '10110110'\n");
			i = -1;
		}
		else
		{
			printf("%d", clave[i]);
		}
	}
	printf("\n\nSave your key to decrypt the message later\nGood! Now press any key to continue");
	getch();
	clean_screen();
	loading_animation();
	clean_screen();

	printf("\n");
	for (int i = 0; i < input_length; i++)
	{
		for (j = 0; j < 8; j++)
		{
			if (clave[j] == binary_store[i][j])
				cipher_binary[i][j] = 0;
			else
				cipher_binary[i][j] = 1;
		}
	}

	for (int i = 0; i < input_length; i++)
	{
		decimal_storage = 0;
		for (j = 0; j < 8; j++)
		{
			temp_binary = cipher_binary[i][j];
			decimal_storage += temp_binary * (1 << (7 - j));
		}
		cipher_str[i] = decimal_storage;
	}
	cipher_str[input_length] = '\0';

	printf("Encrypted Message:\n");
	for (int i = 0; i < input_length; i++)
	{
		printf("%c", cipher_str[i]);
	}

	if (!save_text_to_file(cipher_str))
	{
		printf("Error saving message.txt");
	}

	free_text_input(cadena);
	return 0;
}

int xor_decryption(void)
{
	char input_str[BUFFER_SIZE], decrypted_str[BUFFER_SIZE];
	int char_counter, i;

	char confirmation = 'n';
	int clave[8], inverted_binary[8], binary_store[BUFFER_SIZE][8], cipher_binary[BUFFER_SIZE][8];
	int claveaux, remainder, j, binary_counter, decimal_storage, temp_binary;

	FILE *doc = fopen("mensaje.txt", "r");
	if (doc == NULL)
	{
		printf("\n\t\t\tFILE NOT FOUND!\n\n Make sure 'mensaje.txt' is in the program folder");
		return 1;
	}

	fgets(input_str, BUFFER_SIZE, doc);
	printf("%s", input_str);
	fclose(doc);

	char_counter = strlen(input_str);

	while (confirmation != 'y')
	{
		clean_screen();
		printf("\n\tEnter binary decryption key: ");
		for (i = 0; i < 8; i++)
		{
			claveaux = getch();
			if (claveaux == KEY_ESC)
				return 1;

			clave[i] = claveaux - '0';
			if ((clave[i] != 0) && (clave[i] != 1))
			{
				printf("\tError!\nKey example: '10110110'\n");
				i = -1;
			}
			else
			{
				printf("%d", clave[i]);
			}
		}
		printf("\n\tAre you sure? y/n");
		confirmation = getch();
	}
	clean_screen();
	decryption_animation();
	clean_screen();

	for (i = 0; i < char_counter; i++)
	{
		int decimal = input_str[i];
		if (decimal < 0)
			decimal = input_str[i] + 256;

		for (j = 0; j < 8; j++)
		{
			remainder = decimal % 2;
			decimal = decimal / 2;
			inverted_binary[j] = remainder;
		}

		j = 0;
		for (binary_counter = 7; binary_counter >= 0; binary_counter--)
		{
			binary_store[i][j] = inverted_binary[binary_counter];
			j++;
		}
	}

	printf("\n");
	for (i = 0; i < char_counter; i++)
	{
		for (j = 0; j < 8; j++)
		{
			if (clave[j] == binary_store[i][j])
				cipher_binary[i][j] = 0;
			else
				cipher_binary[i][j] = 1;
		}
	}

	for (i = 0; i < char_counter; i++)
	{
		decimal_storage = 0;
		for (j = 0; j < 8; j++)
		{
			temp_binary = cipher_binary[i][j];
			decimal_storage += temp_binary * (1 << (7 - j));
		}
		decrypted_str[i] = decimal_storage;
	}
	decrypted_str[char_counter] = '\0';

	printf("Decrypted Message:\n");
	for (i = 0; i < char_counter; i++)
	{
		printf("%c", decrypted_str[i]);
	}

	return 0;
}

void xor_decimal_to_binary(int decimal, int binary[8])
{
	int inverted[8];
	for (int j = 0; j < 8; j++)
	{
		inverted[j] = decimal % 2;
		decimal = decimal / 2;
	}
	for (int j = 0; j < 8; j++)
		binary[j] = inverted[7 - j];
}

int xor_binary_to_decimal(const int binary[8])
{
	int decimal = 0;
	for (int j = 0; j < 8; j++)
		decimal += binary[j] * (1 << (7 - j));
	return decimal;
}

void xor_apply_key(const int binary[8], const int key[8], int result[8])
{
	for (int j = 0; j < 8; j++)
		result[j] = (key[j] == binary[j]) ? 0 : 1;
}

void xor_encrypt_str(const char *input, const int key[8], char *output, int len)
{
	for (int i = 0; i < len; i++)
	{
		int binary[8], xored[8];
		xor_decimal_to_binary((unsigned char)input[i], binary);
		xor_apply_key(binary, key, xored);
		output[i] = (char)xor_binary_to_decimal(xored);
	}
	output[len] = '\0';
}

void xor_decrypt_str(const char *input, const int key[8], char *output, int len)
{
	xor_encrypt_str(input, key, output, len);
}
