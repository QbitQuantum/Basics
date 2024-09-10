void
db_task_trap(
	int		type,
	int		code,
	boolean_t	user_space)
{
	jmp_buf_t db_jmpbuf;
	jmp_buf_t *prev;
	boolean_t	bkpt;
	boolean_t	watchpt;
	task_t		task;
	task_t		task_space;

	task = db_current_task();
	task_space = db_target_space(current_act(), user_space);
	bkpt = IS_BREAKPOINT_TRAP(type, code);
	watchpt = IS_WATCHPOINT_TRAP(type, code);

	/*
	 * Note:  we look up PC values in an address space (task_space),
	 * but print symbols using a (task-specific) symbol table, found
	 * using task.
	 */
	db_init_default_act();
	db_check_breakpoint_valid();
	if (db_stop_at_pc(&bkpt, task, task_space)) {
	    if (db_inst_count) {
		db_printf("After %d instructions (%d loads, %d stores),\n",
			  db_inst_count, db_load_count, db_store_count);
	    }
	    if (bkpt)
		db_printf("Breakpoint at  ");
	    else if (watchpt)
		db_printf("Watchpoint at  ");
	    else
		db_printf("Stopped at  ");
	    db_dot = PC_REGS(DDB_REGS);

	    prev = db_recover;
	    if (_setjmp(db_recover = &db_jmpbuf) == 0) {
#if defined(__alpha)
		db_print_loc(db_dot, task_space);
		db_printf("\n\t");
		db_print_inst(db_dot, task_space);
#else /* !defined(__alpha) */
#if defined(__powerpc__)
		db_print_loc_and_inst(db_dot, task_space);
#else	/* __powerpc__ */
		db_print_loc_and_inst(db_dot, task);
#endif	/* __powerpc__ */
#endif /* defined(__alpha) */
	    } else
		db_printf("Trouble printing location %#X.\n", db_dot);
	    db_recover = prev;

	    db_command_loop();
	}

	db_restart_at_pc(watchpt, task_space);
}