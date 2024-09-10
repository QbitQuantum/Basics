void
__fex_mklog(ucontext_t *uap, char *addr, int f, enum fex_exception e,
    int m, void *p)
{
	struct	frame	*fp;
	char		*stk, *name, buf[30];
	int		fd;

	/* if logging is disabled, just return */
	mutex_lock(&log_lock);
	if (log_fp == NULL) {
		mutex_unlock(&log_lock);
		return;
	}

	/* get stack info */
#if defined(__sparc)
	stk = (char*)uap->uc_mcontext.gregs[REG_PC];
	fp = FRAMEP(uap->uc_mcontext.gregs[REG_SP]);
#elif defined(__amd64)
	stk = (char*)uap->uc_mcontext.gregs[REG_PC];
	fp = FRAMEP(uap->uc_mcontext.gregs[REG_RBP]);
#elif defined(__i386)	/* !defined(__amd64) */
	stk = (char*)uap->uc_mcontext.gregs[PC];
	fp = FRAMEP(uap->uc_mcontext.gregs[EBP]);
#else
#error Unknown architecture
#endif

	/* if the handling mode is the default and this exception's
	   flag is already raised, don't make an entry */
	if (m == FEX_NONSTOP) {
		switch (e) {
		case fex_inexact:
			if (f & FE_INEXACT) {
				mutex_unlock(&log_lock);
				return;
			}
			break;
		case fex_underflow:
			if (f & FE_UNDERFLOW) {
				mutex_unlock(&log_lock);
				return;
			}
			break;
		case fex_overflow:
			if (f & FE_OVERFLOW) {
				mutex_unlock(&log_lock);
				return;
			}
			break;
		case fex_division:
			if (f & FE_DIVBYZERO) {
				mutex_unlock(&log_lock);
				return;
			}
			break;
		default:
			if (f & FE_INVALID) {
				mutex_unlock(&log_lock);
				return;
			}
			break;
		}
	}

	/* if we've already logged this exception at this address,
	   don't make an entry */
	if (check_exc_list(addr, (unsigned long)e, stk, fp)) {
		mutex_unlock(&log_lock);
		return;
	}

	/* make an entry */
	fd = fileno(log_fp);
	write(fd, "Floating point ", 15);
	write(fd, exception[e], strlen(exception[e]));
	write(fd, buf, sprintf(buf, " at 0x%0" PDIG "lx", (long)addr));
	__fex_sym_init();
	if (__fex_sym(addr, &name) != NULL) {
		write(fd, " ", 1);
		write(fd, name, strlen(name));
	}
	switch (m) {
	case FEX_NONSTOP:
		write(fd, ", nonstop mode\n", 15);
		break;

	case FEX_ABORT:
		write(fd, ", abort\n", 8);
		break;

	case FEX_NOHANDLER:
		if (p == (void *)SIG_DFL) {
			write(fd, ", handler: SIG_DFL\n", 19);
			break;
		}
		else if (p == (void *)SIG_IGN) {
			write(fd, ", handler: SIG_IGN\n", 19);
			break;
		}
		/* fall through*/
	default:
		write(fd, ", handler: ", 11);
		if (__fex_sym((char *)p, &name) != NULL) {
			write(fd, name, strlen(name));
			write(fd, "\n", 1);
		} else {
			write(fd, buf, sprintf(buf, "0x%0" PDIG "lx\n",
			    (long)p));
		}
		break;
	}
	print_stack(fd, stk, fp);
	mutex_unlock(&log_lock);
}