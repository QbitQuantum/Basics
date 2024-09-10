static void dump_kernel_log(struct fiq_debugger_state *state)
{
	char buf[512];
	size_t len;
	struct kmsg_dumper dumper = { .active = true };


	kmsg_dump_rewind_nolock(&dumper);
	while (kmsg_dump_get_line_nolock(&dumper, true, buf,
					 sizeof(buf) - 1, &len)) {
		buf[len] = 0;
		debug_puts(state, buf);
	}
}

static char *mode_name(unsigned cpsr)
{
	switch (cpsr & MODE_MASK) {
	case USR_MODE: return "USR";
	case FIQ_MODE: return "FIQ";
	case IRQ_MODE: return "IRQ";
	case SVC_MODE: return "SVC";
	case ABT_MODE: return "ABT";
	case UND_MODE: return "UND";
	case SYSTEM_MODE: return "SYS";
	default: return "???";
	}
}

static int debug_printf(void *cookie, const char *fmt, ...)
{
	struct fiq_debugger_state *state = cookie;
	char buf[256];
	va_list ap;

	va_start(ap, fmt);
	vsnprintf(buf, sizeof(buf), fmt, ap);
	va_end(ap);

	debug_puts(state, buf);
	return state->debug_abort;
}

/* Safe outside fiq context */
static int debug_printf_nfiq(void *cookie, const char *fmt, ...)
{
	struct fiq_debugger_state *state = cookie;
	char buf[256];
	va_list ap;
	unsigned long irq_flags;

	va_start(ap, fmt);
	vsnprintf(buf, 128, fmt, ap);
	va_end(ap);

	local_irq_save(irq_flags);
	debug_puts(state, buf);
	debug_uart_flush(state);
	local_irq_restore(irq_flags);
	return state->debug_abort;
}

static void dump_regs(struct fiq_debugger_state *state, unsigned *regs)
{
	debug_printf(state, " r0 %08x  r1 %08x  r2 %08x  r3 %08x\n",
			regs[0], regs[1], regs[2], regs[3]);
	debug_printf(state, " r4 %08x  r5 %08x  r6 %08x  r7 %08x\n",
			regs[4], regs[5], regs[6], regs[7]);
	debug_printf(state, " r8 %08x  r9 %08x r10 %08x r11 %08x  mode %s\n",
			regs[8], regs[9], regs[10], regs[11],
			mode_name(regs[16]));
	if ((regs[16] & MODE_MASK) == USR_MODE)
		debug_printf(state, " ip %08x  sp %08x  lr %08x  pc %08x  "
				"cpsr %08x\n", regs[12], regs[13], regs[14],
				regs[15], regs[16]);
	else
		debug_printf(state, " ip %08x  sp %08x  lr %08x  pc %08x  "
				"cpsr %08x  spsr %08x\n", regs[12], regs[13],
				regs[14], regs[15], regs[16], regs[17]);
}