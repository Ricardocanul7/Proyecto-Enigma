#include "test.h"

int _tests_run = 0;
int _tests_passed = 0;
int _tests_failed = 0;

extern void test_simple(void);
extern void test_xor(void);
extern void test_vigenere(void);
extern void test_run_length(void);

int main(void)
{
	printf("=== Proyecto Enigma - Unit Tests ===\n");

	test_simple();
	test_xor();
	test_vigenere();
	test_run_length();

	TEST_SUMMARY();
	return TEST_EXIT_CODE();
}
