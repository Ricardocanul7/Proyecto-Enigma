/**
 * EnigmaProject - Algoritmo de Cifrado/Descifrado tipo XOR
 *
 * Xor es la operacion bitwise o binaria, con las reglas:
 * 1. Si los bits del numero A y B son iguales el resultado es "0", si no el resultado es "1".
 */

#include "../../include/enigma.h"

int xor_encryption(void)
{
	char go_back_to_menu = 0, cipher_str[910];
	int i = 0;

	/**variables de algoritmo XOR*/
	int input_length, cadena_convert_decimal[910], j;
	int binary_8bit_ascii[8], inverted_binary[8], remainder, bin_counter, store_counter;
	int binary_store[910][8];
	int clave[8], claveaux, cipher_binary[910][8];
	int decimal_storage, temp_binary, decimal;

	/** Read text*/
	char *cadena = input_text();
	if (cadena && !cadena[0])
	{
		return 1;
	}
	input_length = strlen(cadena) - 1;

	/***** Algoritmo de Cifrado XOR */

	store_counter = 0;
	for (i = 0; i < input_length; i++)
	{
		cadena_convert_decimal[i] = cadena[i];

		for (j = 0; j <= 7; j++)
		{
			remainder = (cadena_convert_decimal[i]) % 2;
			cadena_convert_decimal[i] = (cadena_convert_decimal[i]) / 2;
			inverted_binary[j] = remainder;
		}

		j = 0;
		for (bin_counter = 7; bin_counter >= 0; bin_counter--)
		{
			binary_8bit_ascii[j] = inverted_binary[bin_counter];
			binary_store[store_counter][j] = binary_8bit_ascii[j];
			j++;
		}
		store_counter++;
	}

	printf("\nIngresa clave de cifrado binario de 8 bits\n");
	for (i = 0; i < 8; i++)
	{
		claveaux = getch();
		clave[i] = claveaux - '0';
		if ((clave[i] != 0) && (clave[i] != 1))
		{
			printf("\tError!\nEjemplo de clave: '10110110'\n");
			i = -1;
		}
		else
		{
			printf("%d", clave[i]);
		}
	}
	printf("\n\nGuarda tu clave para poder descifrar el mensaje\nMuy bien! ahora presiona cualquier tecla para continuar");
	getch();
	clean_screen();
	loading_animation();
	clean_screen();

	/** Ciclo para Cifrar el Binario de cada letra */
	printf("\n");
	for (i = 0; i < input_length; i++)
	{
		for (j = 0; j < 8; j++)
		{
			if (clave[j] == binary_store[i][j])
			{
				cipher_binary[i][j] = 0;
			}
			else
			{
				cipher_binary[i][j] = 1;
			}
		}
	}

	/** Ciclo que convierte los Binarios Cifrados a Decimales */
	for (i = 0; i < input_length; i++)
	{
		decimal_storage = 0;
		for (j = 0; j < 8; j++)
		{
			temp_binary = cipher_binary[i][j];
			decimal = temp_binary * pow(2, j);
			decimal_storage = decimal + decimal_storage;
		}
		cipher_str[i] = decimal_storage;
	}

	/** IMPRIMIR MENSAJE CIFRADO */
	printf("Mensaje Cifrado:\n");
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

int xor_decryption(void)
{
	char input_str[910], decrypted_str[910];
	int char_counter, i;

	/*** Variables de Descifrado XOR */
	char confirmation = 'n';
	int clave[8], inverted_binary[8], binary_store[910][8], cipher_binary[910][8];
	int claveaux, remainder, j, binary_counter, decimal_storage, temp_binary, decimal;

	/******************ABRE ARCHIVO TXT ************************************************/
	doc = fopen("mensaje.txt", "r");

	if (doc == NULL)
	{
		printf("\n\t\t\tARCHIVO NO ENCONTRADO!\n\n Asegurese de poner el arvhivo 'mensaje.txt' en la carpeta del programa");
		return 1;
	}

	fgets(input_str, 910, doc);
	printf("%s", input_str);
	fclose(doc);

	char_counter = strlen(input_str);

	while (confirmation != 'y')
	{
		clean_screen();
		printf("\n\tIngrese Clave binaria de decifrado: ");
		for (i = 7; i >= 0; i--)
		{
			claveaux = getch();
			if (claveaux == KEY_ESC)
			{
				return 1;
			}
			clave[i] = claveaux - '0';
			if ((clave[i] != 0) && (clave[i] != 1))
			{
				printf("\tError!\nEjemplo de clave: '10110110'\n");
				i = 8;
			}
			else
			{
				printf("%d", clave[i]);
			}
		}
		printf("\n\tEstas seguro? y/n");
		confirmation = getch();
	}
	clean_screen();
	decryption_animation();
	clean_screen();

	for (i = 0; i < char_counter; i++)
	{
		decimal = input_str[i];
		if (decimal < 0)
		{
			decimal = input_str[i] + 256;
		}

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

	/** Ciclo para Descifrar el Binario de cada letra */
	printf("\n");
	for (i = 0; i < char_counter; i++)
	{
		for (j = 0; j < 8; j++)
		{
			if (clave[j] == binary_store[i][j])
			{
				cipher_binary[i][j] = 0;
			}
			else
			{
				cipher_binary[i][j] = 1;
			}
		}
	}

	/** Convierte Binario a Decimal */
	for (i = 0; i < char_counter; i++)
	{
		decimal_storage = 0;
		for (j = 0; j < 8; j++)
		{
			temp_binary = cipher_binary[i][j];
			decimal = temp_binary * (pow(2, j));
			decimal_storage = decimal + decimal_storage;
		}
		decrypted_str[i] = decimal_storage;
	}

	printf("Mensaje Descifrado:\n");
	for (i = 0; i < char_counter; i++)
	{
		printf("%c", decrypted_str[i]);
	}

	return 0;
}
