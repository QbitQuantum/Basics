void
prusage(struct rusage *r0, struct rusage *r1, struct timeval *e,
	struct timeval *b)
{
#define	pgtok(p)	((p * pgsize) / 1024)
	static int	pgsize;

	time_t t =
	    (r1->ru_utime.tv_sec - r0->ru_utime.tv_sec) * 100 +
	    (r1->ru_utime.tv_usec - r0->ru_utime.tv_usec) / 10000 +
	    (r1->ru_stime.tv_sec - r0->ru_stime.tv_sec) * 100 +
	    (r1->ru_stime.tv_usec - r0->ru_stime.tv_usec) / 10000;
	tchar *cp;
	int i;
	struct varent *vp = adrof(S_time);
	int ms =
	    (e->tv_sec - b->tv_sec) * 100 + (e->tv_usec - b->tv_usec) / 10000;

#ifdef TRACE
	tprintf("TRACE- prusage()\n");
#endif
	if (pgsize == 0) {
		pgsize = getpagesize();
	}

	cp = S_USAGEFORMAT;	/* "%Uu %Ss %E %P %X+%Dk %I+%Oio %Fpf+%Ww" */
	if (vp && vp->vec[0] && vp->vec[1]) {
		cp = vp->vec[1];
	}
	for (; *cp; cp++) {
		if (*cp != '%') {
			Putchar(*cp);
		} else if (cp[1]) {
			switch (*++cp) {

			case 'U':
				pdeltat(&r1->ru_utime, &r0->ru_utime);
				break;

			case 'S':
				pdeltat(&r1->ru_stime, &r0->ru_stime);
				break;

			case 'E':
				psecs_int(ms / 100);
				break;

			case 'P':
				printf("%d%%", (int)(t * 100 /
				    ((ms ? ms : 1))));
				break;

			case 'W':
				i = r1->ru_nswap - r0->ru_nswap;
				printf("%d", i);
				break;

			case 'X':
				printf("%d", t == 0 ? 0 :
				    pgtok((r1->ru_ixrss - r0->ru_ixrss) / t));
				break;

			case 'D':
				printf("%d", t == 0 ? 0 :
				    pgtok((r1->ru_idrss + r1->ru_isrss-
				    (r0->ru_idrss + r0->ru_isrss)) / t));
				break;

			case 'K':
				printf("%d", t == 0 ? 0 :
				    pgtok(((r1->ru_ixrss + r1->ru_isrss +
				    r1->ru_idrss) - (r0->ru_ixrss +
				    r0->ru_idrss + r0->ru_isrss)) / t));
				break;

			case 'M':
				printf("%d", r1->ru_maxrss / 2);
				break;

			case 'F':
				printf("%d", r1->ru_majflt - r0->ru_majflt);
				break;

			case 'R':
				printf("%d", r1->ru_minflt - r0->ru_minflt);
				break;

			case 'I':
				printf("%d", r1->ru_inblock - r0->ru_inblock);
				break;

			case 'O':
				printf("%d", r1->ru_oublock - r0->ru_oublock);
				break;
			}
		}
	}
	Putchar('\n');
#undef	pgtok
}