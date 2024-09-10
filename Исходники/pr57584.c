static SCM vm_debug_engine (SCM vm, SCM program, SCM *argv, int nargs) {
    register scm_t_uint8 *ip ;
    register SCM *sp ;
    register SCM *fp ;
    struct scm_vm *vp = ((struct scm_vm *) ((((scm_t_bits) (0? (*(SCM*)0=((((SCM *)((scm_t_cell *) (((scm_t_bits) (0? (*(SCM*)0=((((vm))))): (((vm)))))))) [((1))]))): (((SCM *)((scm_t_cell *) (((scm_t_bits) (0? (*(SCM*)0=((((vm))))): (((vm)))))))) [((1))]))))));
    static const void **jump_table_pointer = ((void *)0);
    const void **jump_table;
    if (__builtin_expect ((!jump_table_pointer), 0))     {
	jump_table_pointer[0] = &&l_nop;
    }
l_nop:
      {
	SCM *old_sp;
	scm_t_int32 n;
	old_sp = sp;
	sp = (fp - 1) + n;
	if (old_sp < sp)     {
	    while (old_sp < sp)         *++old_sp = ((SCM) ((((((9)) << 8) + scm_tc8_flag))));
	}
	  {
	      { if (__builtin_expect ((vp->trace_level > 0), 0)) { { vp->ip = ip; vp->sp = sp; vp->fp = fp; }; vm_dispatch_hook (vm, SCM_VM_NEXT_HOOK); } };
	  };
      }
      {
	SCM k, prompt;
	if ((_setjmp (((struct scm_prompt_registers*)((((scm_t_bits) (0? (*(SCM*)0=((((SCM *)((scm_t_cell *) (((scm_t_bits) (0? (*(SCM*)0=((((prompt))))): (((prompt)))))))) [((2))]))): (((SCM *)((scm_t_cell *) (((scm_t_bits) (0? (*(SCM*)0=((((prompt))))): (((prompt)))))))) [((2))]))))))->regs)))     {
	      { ip = vp->ip; sp = vp->sp; fp = vp->fp; };
	      { { if (__builtin_expect ((vp->trace_level > 0), 0)) { { vp->ip = ip; vp->sp = sp; vp->fp = fp; }; vm_dispatch_hook (vm, SCM_VM_NEXT_HOOK); } }; ; goto *jump_table[(*ip++) & ((1<<8)-1)]; };
	}