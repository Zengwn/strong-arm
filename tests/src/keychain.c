#include <stdio.h>
#include <string.h>
#include <minunit.h>
#include <strong-arm/keychain.h>


/* Test known results.
*/
START_TEST (test_known)
{
	const FF_NUM base_private_key0 = {{0x914432ca,0x0d08bc13,0x778232d4,0xe6558c2d,0x9b05ad7f,0x6928db34,0xbc050341,0xb6217431}};
	const uint8_t chain_key0[] = {0xa6,0xc0,0xaf,0xed,0xa0,0xcc,0x36,0x53,0x2c,0x23,0xaa,0xc0,0x75,0xd7,0x0f,0xb3,0xfc,0xb9,0xc6,0xb9,0xa6,0x33,0xc6,0x9e,0x33,0x0d,0xb2,0xd6,0x1a,0xde,0x83,0xfd};
	const uint8_t chain_index0[] = {0x7f,0x2c,0x2f,0x2b,0xd1,0x47,0xf7,0x64,0xa4,0xd1,0x5c,0xb6,0x1c,0x95,0x31,0x60};
	const EC_POINT pubkey0 = {{0x88B55835,0xD67CF499,0x680CA143,0xDF092255,0x3B72EE27,0xE7C6F1CE,0x5DB4396B,0x9FD04834},{0xA09B3F62,0x9EB89911,0x5EAD68DD,0x7F114C9E,0x31B9C3C8,0xDCBC6034,0x3A0A37DF,0x8A34AB11}};
	EC_POINT pubkey;

	keychain_calculate (NULL, &pubkey, &base_private_key0, chain_key0, chain_index0);
	mu_assert (memcmp (&pubkey, &pubkey0, sizeof (EC_POINT)) == 0, "key_chain_calculate should calculate the correct derived key for known results.");
}
END_TEST

char *test_keychain (void)
{
	mu_run_test (test_known);
	
	return 0;
}