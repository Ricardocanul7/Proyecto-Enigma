#include "test.h"
#include "../include/enigma.h"

void test_run_length(void)
{
	char output[BUFFER_SIZE];
	int len;

	TEST_SECTION("Run-Length Encode");

	len = run_length_encode_str("A", output);
	ASSERT_EQ_STR("A", output);
	ASSERT_EQ_INT(1, len);

	len = run_length_encode_str("AAABBBCC", output);
	ASSERT_EQ_STR("#A3#B3#C2", output);
	ASSERT_EQ_INT(9, len);

	len = run_length_encode_str("ABC", output);
	ASSERT_EQ_STR("ABC", output);
	ASSERT_EQ_INT(3, len);

	len = run_length_encode_str("AAAA", output);
	ASSERT_EQ_STR("#A4", output);
	ASSERT_EQ_INT(3, len);

	TEST_SECTION("Run-Length Decode");

	run_length_decode_str("A", output);
	ASSERT_EQ_STR("A", output);

	run_length_decode_str("#A3#B3#C2", output);
	ASSERT_EQ_STR("AAABBBCC", output);

	run_length_decode_str("ABC", output);
	ASSERT_EQ_STR("ABC", output);

	run_length_decode_str("#A4", output);
	ASSERT_EQ_STR("AAAA", output);

	TEST_SECTION("Run-Length Roundtrip");

	char encoded[BUFFER_SIZE];
	run_length_encode_str("AAABBBCC", encoded);
	run_length_decode_str(encoded, output);
	ASSERT_EQ_STR("AAABBBCC", output);

	run_length_encode_str("Hello", encoded);
	run_length_decode_str(encoded, output);
	ASSERT_EQ_STR("Hello", output);

	run_length_encode_str("AAAAAABBBBB", encoded);
	run_length_decode_str(encoded, output);
	ASSERT_EQ_STR("AAAAAABBBBB", output);
}
