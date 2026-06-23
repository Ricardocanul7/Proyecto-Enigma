#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <string.h>

extern int _tests_run;
extern int _tests_passed;
extern int _tests_failed;

#define ASSERT_TRUE(expr) do { \
	_tests_run++; \
	if (expr) { \
		_tests_passed++; \
	} else { \
		_tests_failed++; \
		printf("  FAIL: %s:%d: %s\n", __FILE__, __LINE__, #expr); \
	} \
} while (0)

#define ASSERT_FALSE(expr) ASSERT_TRUE(!(expr))

#define ASSERT_EQ_INT(expected, actual) do { \
	_tests_run++; \
	if ((expected) == (actual)) { \
		_tests_passed++; \
	} else { \
		_tests_failed++; \
		printf("  FAIL: %s:%d: expected %d, got %d\n", \
			__FILE__, __LINE__, (expected), (actual)); \
	} \
} while (0)

#define ASSERT_EQ_STR(expected, actual) do { \
	_tests_run++; \
	if (strcmp((expected), (actual)) == 0) { \
		_tests_passed++; \
	} else { \
		_tests_failed++; \
		printf("  FAIL: %s:%d: expected \"%s\", got \"%s\"\n", \
			__FILE__, __LINE__, (expected), (actual)); \
	} \
} while (0)

#define TEST_SECTION(name) printf("\n--- %s ---\n", name)

#define TEST_SUMMARY() do { \
	printf("\n=============================\n"); \
	printf("Tests: %d run, %d passed, %d failed\n", \
		_tests_run, _tests_passed, _tests_failed); \
	printf("=============================\n"); \
} while (0)

#define TEST_EXIT_CODE() (_tests_failed > 0 ? 1 : 0)

#endif /* TEST_H */
