#include "test.h"
#include "../include/enigma.h"

void test_xor(void)
{
	char output[BUFFER_SIZE];
	int key[8] = {1, 0, 1, 1, 0, 1, 1, 0};

	TEST_SECTION("XOR Binary Helpers");

	int binary[8];
	xor_decimal_to_binary(65, binary);
	ASSERT_EQ_INT(0, binary[0]);
	ASSERT_EQ_INT(1, binary[1]);
	ASSERT_EQ_INT(0, binary[2]);
	ASSERT_EQ_INT(0, binary[3]);
	ASSERT_EQ_INT(0, binary[4]);
	ASSERT_EQ_INT(0, binary[5]);
	ASSERT_EQ_INT(0, binary[6]);
	ASSERT_EQ_INT(1, binary[7]);

	int dec = xor_binary_to_decimal(binary);
	ASSERT_EQ_INT(65, dec);

	int result[8];
	int b1[8] = {0, 1, 0, 0, 0, 0, 0, 1};
	int k1[8] = {1, 0, 1, 1, 0, 1, 1, 0};
	xor_apply_key(b1, k1, result);
	ASSERT_EQ_INT(1, result[0]);
	ASSERT_EQ_INT(1, result[1]);
	ASSERT_EQ_INT(1, result[2]);
	ASSERT_EQ_INT(1, result[3]);
	ASSERT_EQ_INT(0, result[4]);
	ASSERT_EQ_INT(1, result[5]);
	ASSERT_EQ_INT(1, result[6]);
	ASSERT_EQ_INT(1, result[7]);

	TEST_SECTION("XOR Encrypt/Decrypt Roundtrip");

	xor_encrypt_str("A", key, output, 1);
	xor_decrypt_str(output, key, output, 1);
	ASSERT_EQ_STR("A", output);

	xor_encrypt_str("HELLO", key, output, 5);
	xor_decrypt_str(output, key, output, 5);
	ASSERT_EQ_STR("HELLO", output);

	xor_encrypt_str("Hello World!", key, output, 12);
	xor_decrypt_str(output, key, output, 12);
	ASSERT_EQ_STR("Hello World!", output);

	int key2[8] = {1, 1, 1, 1, 1, 1, 1, 1};
	xor_encrypt_str("Test123!", key2, output, 8);
	xor_decrypt_str(output, key2, output, 8);
	ASSERT_EQ_STR("Test123!", output);
}
