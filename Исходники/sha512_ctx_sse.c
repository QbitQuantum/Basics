static inline uint32_t hash_pad(uint8_t padblock[SHA512_BLOCK_SIZE * 2], uint64_t total_len)
{
	uint32_t i = (uint32_t) (total_len & (SHA512_BLOCK_SIZE - 1));

	memclr_fixedlen(&padblock[i], SHA512_BLOCK_SIZE);
	padblock[i] = 0x80;

	// Move i to the end of either 1st or 2nd extra block depending on length
	i += ((SHA512_BLOCK_SIZE - 1) & (0 - (total_len + SHA512_PADLENGTHFIELD_SIZE + 1))) +
	    1 + SHA512_PADLENGTHFIELD_SIZE;

#if SHA512_PADLENGTHFIELD_SIZE == 16
	*((uint64_t *) & padblock[i - 16]) = 0;
#endif

	*((uint64_t *) & padblock[i - 8]) = _byteswap_uint64((uint64_t) total_len << 3);

	return i >> SHA512_LOG2_BLOCK_SIZE;	// Number of extra blocks to hash
}