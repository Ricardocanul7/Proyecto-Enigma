#include "test.h"
#include "../include/enigma.h"

void test_vigenere(void)
{
	char output[BUFFER_SIZE];

	TEST_SECTION("Vigenere Encrypt");

	vigenere_encrypt_str("HELLO", "KEY", output, 5);
	ASSERT_EQ_STR("RIJVS", output);

	vigenere_encrypt_str("A", "A", output, 1);
	ASSERT_EQ_STR("A", output);

	vigenere_encrypt_str("ABC", "A", output, 3);
	ASSERT_EQ_STR("ABC", output);

	vigenere_encrypt_str("ATTACK", "KEY", output, 6);
	ASSERT_EQ_STR("KXRKGI", output);

	TEST_SECTION("Vigenere Decrypt");

	vigenere_decrypt_str("RIJVS", "KEY", output, 5);
	ASSERT_EQ_STR("HELLO", output);

	vigenere_decrypt_str("KXRKGI", "KEY", output, 6);
	ASSERT_EQ_STR("ATTACK", output);

	TEST_SECTION("Vigenere Roundtrip");

	vigenere_encrypt_str("HELLOWORLD", "SECRET", output, 10);
	vigenere_decrypt_str(output, "SECRET", output, 10);
	ASSERT_EQ_STR("HELLOWORLD", output);

	vigenere_encrypt_str("A", "B", output, 1);
	vigenere_decrypt_str(output, "B", output, 1);
	ASSERT_EQ_STR("A", output);
}
