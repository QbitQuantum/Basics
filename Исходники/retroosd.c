void mini_osd_interface::init(running_machine &machine)
{
	int gamRot=0;

	osd_interface::init(machine);
	our_target = machine.render().target_alloc();

	initInput(machine);

	write_log("machine screen orientation: %s \n", (
		machine.system().flags & ORIENTATION_SWAP_XY) ? "VERTICAL" : "HORIZONTAL"
	);

        orient  = (machine.system().flags & ORIENTATION_MASK);
	vertical = (machine.system().flags & ORIENTATION_SWAP_XY);
        
        gamRot = (ROT270 == orient) ? 1 : gamRot;
        gamRot = (ROT180 == orient) ? 2 : gamRot;
        gamRot = (ROT90  == orient) ? 3 : gamRot;
        
	prep_retro_rotation(gamRot);

	write_log("osd init done\n");
}