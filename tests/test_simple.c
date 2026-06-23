#include "test.h"
#include "../include/enigma.h"

void test_simple(void)
{
	char output[BUFFER_SIZE];

	TEST_SECTION("Simple Cipher");

	simple_encrypt_str("ABC", output, 3);
	ASSERT_EQ_STR("DEF", output);

	simple_encrypt_str("HELLO", output, 5);
	ASSERT_EQ_STR("KHOOR", output);

	simple_encrypt_str("xyz", output, 3);
	ASSERT_EQ_STR("{|}", output);

	simple_decrypt_str("DEF", output, 3);
	ASSERT_EQ_STR("ABC", output);

	simple_decrypt_str("KHOOR", output, 5);
	ASSERT_EQ_STR("HELLO", output);

	simple_encrypt_str("A", output, 1);
	simple_decrypt_str(output, output, 1);
	ASSERT_EQ_STR("A", output);

	simple_encrypt_str("TEST123", output, 7);
	simple_decrypt_str(output, output, 7);
	ASSERT_EQ_STR("TEST123", output);
}
