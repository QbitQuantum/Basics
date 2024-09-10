void run_pult () {

	register ret, o_errno;
	struct wordb word;

	_dos_setvect (0x1C, old_timer);
	VIClear ();
	ret = spawnlp (P_WAIT, pult_file, pult_file, NULL);
	o_errno = errno; /* VRedraw () портит errno */
	VRedraw ();
	_dos_setvect (0x1C, timer_int);
	if (ret == -1)
		error ("%s : %s", pult_file, sys_errlist[o_errno]);
	else {
		ptinitialize();
		old_addr = -1;
		_disable ();
		int_tab [0].ticks = TICK_CHK;
		_enable ();
	}
}