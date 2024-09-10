/* Breakpoint command */
int		cmd_bp()
{
  char		*str;
  int		ret;
  eresi_Addr	addr;
  char		logbuf[BUFSIZ];
  int		idx;
  int		index;
  elfsh_SAddr	off = 0;
  char		*name;
  elfshbp_t	*cur;
  char		**keys;
  int		keynbr;

  PROFILER_IN(__FILE__, __FUNCTION__, __LINE__);

  /* build argc */
  for (idx = 0; world.curjob->curcmd->param[idx] != NULL; idx++);
  str = revm_lookup_string(world.curjob->curcmd->param[0]);

  /* Select subcommand */
  switch (idx)
    {
      
      /* List breakpoints */
      case 0:
	e2dbg_output(" .:: Breakpoints ::.\n\n");	      
	keys = hash_get_keys(&e2dbgworld.bp, &keynbr);
	for (index = 0; index < keynbr; index++)
	  {
	    cur = hash_get(&e2dbgworld.bp, keys[index]);
	    name = revm_resolve(world.curjob->curfile, 
				(eresi_Addr) cur->addr, &off);
	    if (off)
	      snprintf(logbuf, BUFSIZ, " %c [%02u] " XFMT " <%s + " UFMT ">\n", 
		       (e2dbg_is_watchpoint(cur) ? 'W' : 'B'),
		       cur->id, cur->addr, name, off);
	    else
	      snprintf(logbuf, BUFSIZ, " %c [%02u] " XFMT " <%s>\n", 
		       (e2dbg_is_watchpoint(cur) ? 'W' : 'B'),
		       cur->id, cur->addr, name);
	    e2dbg_output(logbuf);
	  }
	hash_free_keys(keys);
	if (!index)
	  e2dbg_output(" [*] No breakpoints\n");
	e2dbg_output("\n");
	break;
      
	/* Supply a new breakpoint */
      case 1:
	if (!elfsh_is_runtime_mode())
	  PROFILER_ERR(__FILE__, __FUNCTION__, __LINE__,
		       "Not in dynamic or debugger mode", -1);
	if (!str || !(*str))
	  PROFILER_ERR(__FILE__, __FUNCTION__, __LINE__, 
		       "Invalid argument", -1);
      
	/* Break on a supplied virtual address */
	if (IS_VADDR(str))
	  {
	    if (sscanf(str + 2, AFMT, &addr) != 1)
	      PROFILER_ERR(__FILE__, __FUNCTION__, __LINE__, 
			   "Invalid virtual address requested", (-1));
	  }
      
	/* Resolve first a function name */
	else
	  {
	    addr = e2dbg_breakpoint_find_addr(str);
	    if (addr == 0)
	      PROFILER_ERR(__FILE__, __FUNCTION__, __LINE__, 
			   "Requested symbol address unknown", -1);
	  }
      
	/* Add the breakpoint */
	ret = e2dbg_breakpoint_add(addr);
	if (ret < 0)
	  PROFILER_ERR(__FILE__, __FUNCTION__, __LINE__, 
		       "Breakpoint insertion failed\n", (-1));
	if (ret >= 0)
	  {
	    name = revm_resolve(world.curjob->curfile, addr, &off);
	    if (!off)
	      snprintf(logbuf, BUFSIZ - 1, 
		       " [*] Breakpoint added at <%s> (" XFMT ")\n\n", name, addr);
	    else
	      snprintf(logbuf, BUFSIZ - 1, 
		       " [*] Breakpoint added at <%s + " UFMT "> (" XFMT ")\n\n", 
		       name, off, addr);
	    e2dbg_output(logbuf);
	  }
	break;

	/* Wrong command syntax */
      default:
	PROFILER_ERR(__FILE__, __FUNCTION__, __LINE__, 
		     "Wrong arg number", (-1));
    }

  PROFILER_ROUT(__FILE__, __FUNCTION__, __LINE__, (ret));
}