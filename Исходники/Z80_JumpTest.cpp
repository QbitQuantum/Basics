void TestJumpToAddressInRegHL(uint8_t opcode, uint16_t address, std::list<Flags> &&set_flags)
{
	std::list<Flags> all_flags{ Flags::Zero, Flags::Subtract, Flags::HalfCarry, Flags::Carry };
	all_flags.sort();
	set_flags.sort();
	std::list<Flags> unexpected_flags;
	auto it = std::set_difference(all_flags.begin(), all_flags.end(), set_flags.begin(), set_flags.end(), std::back_inserter(unexpected_flags));

	TesterMMU mmu;
	Z80 z80(mmu);

	for (const auto& flag : set_flags)
	{
		z80.GetRegisters().SetFlag(flag, true);
	}
	z80.GetRegisters().Write(Register16bit::HL, address);
	z80.Execute(opcode);

	ASSERT_EQ(address, z80.GetRegisters().Read(Register16bit::PC)) << "PC read unexpected value: "
		<< static_cast<size_t>(z80.GetRegisters().Read(Register16bit::PC)) << " (input value: 0x" << std::hex << static_cast<size_t>(address) << ")";
	// Cycles information extracted from GameBoyProgrammingManual.pdf
	ASSERT_EQ(Clock(1, 4), z80.GetClock()) << "Unexpected operation duration: "
		<< static_cast<size_t>(z80.GetClock().GetTicks()) << " (input value: 0x" << std::hex << static_cast<size_t>(address) << ")";
	for (const auto& flag : set_flags)
	{
		ASSERT_TRUE(z80.GetRegisters().IsFlagSet(flag)) << "Expected flag is not set: " << flag << " (input value: 0x" << std::hex << static_cast<size_t>(address) << ")";
	}
	for (const auto& flag : unexpected_flags)
	{
		ASSERT_FALSE(z80.GetRegisters().IsFlagSet(flag)) << "Unexpected flag is set: " << flag << " (input value: 0x" << std::hex << static_cast<size_t>(address) << ")";
	}
}