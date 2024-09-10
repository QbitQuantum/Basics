// BIT n, r
// (Z80 p.241)
Clock Z80::TestBit(uint8_t bit_index, Register8bit reg)
{
	if (bit_index >= 8)
	{
		throw std::logic_error("TestBit called with invalid bit index");
	}

	registers_.SetFlag(Flags::HalfCarry, true);
	registers_.SetFlag(Flags::Subtract, false);
	// C is not affected

	registers_.SetFlag(Flags::Zero, (registers_.Read(reg) & (1 << bit_index)) == 0);

	return Clock(2, 8);
}