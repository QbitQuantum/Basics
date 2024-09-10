void TestRotateOperation(uint8_t opcode, uint8_t cb_opcode, Register8bit reg, uint8_t value, uint8_t expected_result, std::list<Flags> &&expected_flags, bool set_carry = false)
{
	std::list<Flags> all_flags{ Flags::Zero, Flags::Subtract, Flags::HalfCarry, Flags::Carry };
	all_flags.sort();
	expected_flags.sort();
	std::list<Flags> unexpected_flags;
	auto it = std::set_difference(all_flags.begin(), all_flags.end(), expected_flags.begin(), expected_flags.end(), std::back_inserter(unexpected_flags));

	TesterMMU mmu;
	Z80 z80(mmu);

	if (set_carry)
	{
		z80.GetRegisters().SetFlag(Flags::Carry, true);
	}
	z80.GetRegisters().Write(reg, value);
	mmu.Write8bitToMemory(0, cb_opcode);
	z80.Execute(opcode);

	ASSERT_EQ(expected_result, z80.GetRegisters().Read(reg)) << "Register read unexpected value: "
		<< static_cast<size_t>(z80.GetRegisters().Read(reg)) << " (input value: 0x" << std::hex << static_cast<size_t>(value) << ")";
	ASSERT_EQ(1, z80.GetRegisters().Read(Register16bit::PC)) << "PC read unexpected value: "
		<< static_cast<size_t>(z80.GetRegisters().Read(Register16bit::PC)) << " (input value: 0x" << std::hex << static_cast<size_t>(value) << ")";
	ASSERT_EQ(Clock(2, 8), z80.GetClock()) << "Unexpected operation duration: "
		<< static_cast<size_t>(z80.GetClock().GetTicks()) << " (input value: 0x" << std::hex << static_cast<size_t>(value) << ")";
	for (const auto& flag : expected_flags)
	{
		ASSERT_TRUE(z80.GetRegisters().IsFlagSet(flag)) << "Expected flag is not set: " << flag << " (input value: 0x" << std::hex << static_cast<size_t>(value) << ")";
	}
	for (const auto& flag : unexpected_flags)
	{
		ASSERT_FALSE(z80.GetRegisters().IsFlagSet(flag)) << "Unexpected flag is set: " << flag << " (input value: 0x" << std::hex << static_cast<size_t>(value) << ")";
	}
}