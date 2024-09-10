/* 1が立っているビットを算出 */
int CountBit(BitBoard bit)
{
	int l_moves = bit & 0x00000000FFFFFFFF;
	int h_moves = (bit & 0xFFFFFFFF00000000) >> 32;

	int count = _mm_popcnt_u32(l_moves);
	count += _mm_popcnt_u32(h_moves);

	/*l_moves -= (l_moves >> 1) & 0x55555555;
	l_moves = (l_moves & 0x33333333) + ((l_moves >> 2) & 0x33333333);
	l_moves = (l_moves + (l_moves >> 4)) & 0x0F0F0F0F;
	l_moves += l_moves >> 8;
	l_moves += l_moves >> 16;
	l_moves &= 0x0000003f;

	h_moves -= (h_moves >> 1) & 0x55555555;
	h_moves = (h_moves & 0x33333333) + ((h_moves >> 2) & 0x33333333);
	h_moves = (h_moves + (h_moves >> 4)) & 0x0F0F0F0F;
	h_moves += h_moves >> 8;
	h_moves += h_moves >> 16;
	h_moves &= 0x0000003f;

	return l_moves + h_moves;*/

	return count;
}