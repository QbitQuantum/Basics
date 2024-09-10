void init_eolith_speedup(running_machine &machine)
{
	int n_game = 0;
	eolith_speedup_address = 0;
	eolith_speedup_resume_scanline = 0;

	while( eolith_speedup_table[ n_game ].s_name != NULL )
	{
		if( strcmp( machine.system().name, eolith_speedup_table[ n_game ].s_name ) == 0 )
		{
			eolith_speedup_address = eolith_speedup_table[ n_game ].speedup_address;
			eolith_speedup_address2 = eolith_speedup_table[ n_game ].speedup_address2;
			eolith_speedup_resume_scanline = eolith_speedup_table[ n_game ].speedup_resume_scanline;
		}
		n_game++;
	}
}