void a600xl_mmu(running_machine &machine, UINT8 new_mmu)
{
	/* check if self-test ROM changed */
	if ( new_mmu & 0x80 )
	{
		logerror("%s MMU SELFTEST RAM\n", machine.system().name);
		machine.device("maincpu")->memory().space(AS_PROGRAM).nop_readwrite(0x5000, 0x57ff);
	}
	else
	{
		logerror("%s MMU SELFTEST ROM\n", machine.system().name);
		machine.device("maincpu")->memory().space(AS_PROGRAM).install_read_bank(0x5000, 0x57ff, "bank2");
		machine.device("maincpu")->memory().space(AS_PROGRAM).unmap_write(0x5000, 0x57ff);
		machine.root_device().membank("bank2")->set_base(machine.root_device().memregion("maincpu")->base() + 0x5000);
	}
}