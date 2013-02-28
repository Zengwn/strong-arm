#include <string.h>
#include <minunit.h>
#include <base58.h>


/* Test known base58 encodings */
START_TEST (test_base58encoding)
{
	uint8_t encoding[37] = {0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55};
	const uint8_t str1[] = {0x00,0xc4,0xc5,0xd7,0x91,0xfc,0xb4,0x65,0x4a,0x1e,0xf5,0xe0,0x3f,0xe0,0xad,0x3d,0x9c,0x59,0x8f,0x98,0x27,0x00,0x00,0x00,0x00};
	const uint8_t encoding1[] = "1JwSSubhmg6iPtRjtyqhUYYH7bZg1RstDD";
	const uint8_t str2[] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
	const uint8_t encoding2[] = "2n1XR4oJkmBdJMxhBGQGb96gQ88xUzxLFyG";
	const uint8_t str3[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
	const uint8_t encoding3[] = "1111111111111111111111111";	// TODO: Determine the correct encoding for 0x00.
	
	memmove (encoding, str1, 26);
	base58_encode (encoding, encoding);
	mu_assert (memcmp (encoding, encoding1, sizeof(encoding1)) == 0, "base58_encode should correctly encode the test strings, even if src and dst point to the same memory.");
	
	base58_encode (encoding, str2);
	mu_assert (memcmp (encoding, encoding2, sizeof(encoding2)) == 0, "base58_encode should correctly encode the test string of all 0xFF.");
	
	base58_encode (encoding, str3);
	mu_assert (memcmp (encoding, encoding3, sizeof(encoding3)) == 0, "base58_encode should correctly encode the test string of all 0x00.");
	
	mu_assert (encoding[36] == 0x55, "base58_encode should not write more than 36 bytes to the destination array.");
}
END_TEST

START_TEST (test_base58checkencoding)
{
	uint8_t encoding[37] = {0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55};
	const uint8_t str1[] = {0xc4,0xc5,0xd7,0x91,0xfc,0xb4,0x65,0x4a,0x1e,0xf5,0xe0,0x3f,0xe0,0xad,0x3d,0x9c,0x59,0x8f,0x98,0x27};
	const uint8_t encoding1[] = "1JwSSubhmg6iPtRjtyqhUYYH7bZg3Lfy1T";

	base58check_encode (encoding, 0, str1);
	mu_assert (memcmp (encoding, encoding1, sizeof(encoding1)) == 0, "base58check_encode should correctly encode the test strings.");

	memcpy (encoding, str1, 20);
	base58check_encode (encoding, 0, encoding);
	mu_assert (memcmp (encoding, encoding1, sizeof(encoding1)) == 0, "base58check_encode should correctly encode the test strings, even if the src and dst point to the same memory.");
}
END_TEST

char *test_base58 (void)
{
	mu_run_test (test_base58encoding);
	mu_run_test (test_base58checkencoding);
	
	return 0;
}