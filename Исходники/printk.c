/*
 * This is printk.  It can be called from any context.  We want it to work.
 * 
 * We try to grab the console_sem.  If we succeed, it's easy - we log the output and
 * call the console drivers.  If we fail to get the semaphore we place the output
 * into the log buffer and return.  The current holder of the console_sem will
 * notice the new output in release_console_sem() and will send it to the
 * consoles before releasing the semaphore.
 *
 * One effect of this deferred printing is that code which calls printk() and
 * then changes console_loglevel may break. This is because console_loglevel
 * is inspected when the actual printing occurs.
 */
asmlinkage int printk(const char *fmt, ...)
{
	va_list args;
	unsigned long flags;
	int printed_len;
	char *p;
	static char printk_buf[1024];
	static int log_level_unknown = 1;

	if (oops_in_progress) {
		/* If a crash is occurring, make sure we can't deadlock */
		spin_lock_init(&logbuf_lock);
		/* And make sure that we print immediately */
		init_MUTEX(&console_sem);
	}

	/* This stops the holder of console_sem just where we want him */
	spin_lock_irqsave(&logbuf_lock, flags);

	/* Emit the output into the temporary buffer */
	va_start(args, fmt);
	printed_len = vsnprintf(printk_buf, sizeof(printk_buf), fmt, args);
	va_end(args);

	/*
	 * Copy the output into log_buf.  If the caller didn't provide
	 * appropriate log level tags, we insert them here
	 */
	for (p = printk_buf; *p; p++) {
		if (log_level_unknown) {
			if (p[0] != '<' || p[1] < '0' || p[1] > '7' || p[2] != '>') {
				emit_log_char('<');
				emit_log_char(default_message_loglevel + '0');
				emit_log_char('>');
			}
			log_level_unknown = 0;
		}
		emit_log_char(*p);
		if (*p == '\n')
			log_level_unknown = 1;
	}

	if (!arch_consoles_callable()) {
		/*
		 * On some architectures, the consoles are not usable
		 * on secondary CPUs early in the boot process.
		 */
		spin_unlock_irqrestore(&logbuf_lock, flags);
		goto out;
	}
	if (!down_trylock(&console_sem)) {
		/*
		 * We own the drivers.  We can drop the spinlock and let
		 * release_console_sem() print the text
		 */
		spin_unlock_irqrestore(&logbuf_lock, flags);
		console_may_schedule = 0;
		release_console_sem();
	} else {
		/*
		 * Someone else owns the drivers.  We drop the spinlock, which
		 * allows the semaphore holder to proceed and to call the
		 * console drivers with the output which we just produced.
		 */
		spin_unlock_irqrestore(&logbuf_lock, flags);
	}
out:
	return printed_len;
}