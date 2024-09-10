main()
{
	int ret, si, ni, fi;
	int status = 0;

	for (si = 0; si < nitems(scale); si++) {
		for (ni = 0; ni < nitems(num); ni++) {
			for (fi = 0; fi < nitems(funcs); fi++) {
				char cmd[100];
				FILE *fp;
				long double v, d1, d2, diff, prec;

				v = num[ni];
				if (v == 0.0 && funcs[fi].f == logl)
					continue;
				snprintf(cmd, sizeof(cmd),
				    "bc -l -e scale=%d -e '%s(%.19Lf)' -equit",
				    scale[si], funcs[fi].name, v);
				fp = popen(cmd, "r");
				ret = fscanf(fp, "%Lf", &d1);
				pclose(fp);
				d2 = funcs[fi].f(v);
				diff = fabsl(d1 - d2);
				prec = powl(10.0L, (long double)-scale[si]);
				if (prec < LDBL_EPSILON)
					prec = LDBL_EPSILON;
				prec *= 2;
				/* XXX cheating ? */
				if (funcs[fi].f == logl)
					prec *= 4;
				else if (funcs[fi].f == expl)
					prec *= 8;
				if (diff > prec) {
					printf("%s %d %Le %Le %Le %Le %Le\n",
					    funcs[fi].name, scale[si],
					    v, d1, d2, diff, prec);
					status = 1;
				}

			}
		}
	}
	return status;
}