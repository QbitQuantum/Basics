/*
 * Read an ascii label in from FILE f,
 * in the same format as that put out by display(),
 * and fill in lp.
 */
int
getasciilabel(FILE *f, struct disklabel *lp)
{
	char **cpp, *cp;
	const char *errstr;
	struct partition *pp;
	char *tp, *s, line[BUFSIZ];
	int lineno = 0, errors = 0;
	u_int32_t v, fsize;
	u_int64_t lv;

	lp->d_version = 1;
	lp->d_bbsize = BBSIZE;				/* XXX */
	lp->d_sbsize = SBSIZE;				/* XXX */
	while (fgets(line, sizeof(line), f)) {
		lineno++;
		if ((cp = strpbrk(line, "#\r\n")))
			*cp = '\0';
		cp = skip(line);
		if (cp == NULL)
			continue;
		tp = strchr(cp, ':');
		if (tp == NULL) {
			warnx("line %d: syntax error", lineno);
			errors++;
			continue;
		}
		*tp++ = '\0', tp = skip(tp);
		if (!strcmp(cp, "type")) {
			if (tp == NULL)
				tp = "unknown";
			else if (strcasecmp(tp, "IDE") == 0)
				tp = "ESDI";
			cpp = dktypenames;
			for (; cpp < &dktypenames[DKMAXTYPES]; cpp++)
				if ((s = *cpp) && !strcasecmp(s, tp)) {
					lp->d_type = cpp - dktypenames;
					goto next;
				}
			v = GETNUM(lp->d_type, tp, 0, &errstr);
			if (errstr || v >= DKMAXTYPES)
				warnx("line %d: warning, unknown disk type: %s",
				    lineno, tp);
			lp->d_type = v;
			continue;
		}
		if (!strcmp(cp, "flags")) {
			for (v = 0; (cp = tp) && *cp != '\0';) {
				tp = word(cp);
				if (!strcmp(cp, "badsect"))
					v |= D_BADSECT;
				else if (!strcmp(cp, "vendor"))
					v |= D_VENDOR;
				else {
					warnx("line %d: bad flag: %s",
					    lineno, cp);
					errors++;
				}
			}
			lp->d_flags = v;
			continue;
		}
		if (!strcmp(cp, "drivedata")) {
			int i;

			for (i = 0; (cp = tp) && *cp != '\0' && i < NDDATA;) {
				v = GETNUM(lp->d_drivedata[i], cp, 0, &errstr);
				if (errstr)
					warnx("line %d: bad drivedata %s",
					   lineno, cp);
				lp->d_drivedata[i++] = v;
				tp = word(cp);
			}
			continue;
		}
		if (sscanf(cp, "%d partitions", &v) == 1) {
			if (v == 0 || v > MAXPARTITIONS) {
				warnx("line %d: bad # of partitions", lineno);
				lp->d_npartitions = MAXPARTITIONS;
				errors++;
			} else
				lp->d_npartitions = v;
			continue;
		}
		if (tp == NULL)
			tp = "";
		if (!strcmp(cp, "disk")) {
			strncpy(lp->d_typename, tp, sizeof (lp->d_typename));
			continue;
		}
		if (!strcmp(cp, "label")) {
			strncpy(lp->d_packname, tp, sizeof (lp->d_packname));
			continue;
		}
		if (!strcmp(cp, "duid")) {
			if (duid_parse(lp, tp) != 0) {
				warnx("line %d: bad %s: %s", lineno, cp, tp);
				errors++;
			}
			continue;
		}
		if (!strcmp(cp, "bytes/sector")) {
			v = GETNUM(lp->d_secsize, tp, 1, &errstr);
			if (errstr || (v % 512) != 0) {
				warnx("line %d: bad %s: %s", lineno, cp, tp);
				errors++;
			} else
				lp->d_secsize = v;
			continue;
		}
		if (!strcmp(cp, "sectors/track")) {
			v = GETNUM(lp->d_nsectors, tp, 1, &errstr);
			if (errstr) {
				warnx("line %d: bad %s: %s", lineno, cp, tp);
				errors++;
			} else
				lp->d_nsectors = v;
			continue;
		}
		if (!strcmp(cp, "sectors/cylinder")) {
			v = GETNUM(lp->d_secpercyl, tp, 1, &errstr);
			if (errstr) {
				warnx("line %d: bad %s: %s", lineno, cp, tp);
				errors++;
			} else
				lp->d_secpercyl = v;
			continue;
		}
		if (!strcmp(cp, "tracks/cylinder")) {
			v = GETNUM(lp->d_ntracks, tp, 1, &errstr);
			if (errstr) {
				warnx("line %d: bad %s: %s", lineno, cp, tp);
				errors++;
			} else
				lp->d_ntracks = v;
			continue;
		}
		if (!strcmp(cp, "cylinders")) {
			v = GETNUM(lp->d_ncylinders, tp, 1, &errstr);
			if (errstr) {
				warnx("line %d: bad %s: %s", lineno, cp, tp);
				errors++;
			} else
				lp->d_ncylinders = v;
			continue;
		}

		/* Ignore fields that are no longer in the disklabel. */
		if (!strcmp(cp, "rpm") ||
		    !strcmp(cp, "interleave") ||
		    !strcmp(cp, "trackskew") ||
		    !strcmp(cp, "cylinderskew") ||
		    !strcmp(cp, "headswitch") ||
		    !strcmp(cp, "track-to-track seek"))
			continue;

		/* Ignore fields that are forcibly set when label is read. */
		if (!strcmp(cp, "total sectors") ||
		    !strcmp(cp, "boundstart") ||
		    !strcmp(cp, "boundend"))
			continue;

		if ('a' <= *cp && *cp <= 'z' && cp[1] == '\0') {
			unsigned int part = *cp - 'a';

			if (part >= lp->d_npartitions) {
				if (part >= MAXPARTITIONS) {
					warnx("line %d: bad partition name: %s",
					    lineno, cp);
					errors++;
					continue;
				} else {
					lp->d_npartitions = part + 1;
				}
			}
			pp = &lp->d_partitions[part];
#define NXTNUM(n, field, errstr) { \
	if (tp == NULL) {					\
		warnx("line %d: too few fields", lineno);	\
		errors++;					\
		break;						\
	} else							\
		cp = tp, tp = word(cp), (n) = GETNUM(field, cp, 0, errstr); \
}
			NXTNUM(lv, lv, &errstr);
			if (errstr) {
				warnx("line %d: bad partition size: %s",
				    lineno, cp);
				errors++;
			} else {
				DL_SETPSIZE(pp, lv);
			}
			NXTNUM(lv, lv, &errstr);
			if (errstr) {
				warnx("line %d: bad partition offset: %s",
				    lineno, cp);
				errors++;
			} else {
				DL_SETPOFFSET(pp, lv);
			}
			if (tp == NULL) {
				pp->p_fstype = FS_UNUSED;
				goto gottype;
			}
			cp = tp, tp = word(cp);
			cpp = fstypenames;
			for (; cpp < &fstypenames[FSMAXTYPES]; cpp++)
				if ((s = *cpp) && !strcasecmp(s, cp)) {
					pp->p_fstype = cpp - fstypenames;
					goto gottype;
				}
			if (isdigit((unsigned char)*cp))
				v = GETNUM(pp->p_fstype, cp, 0, &errstr);
			else
				v = FSMAXTYPES;
			if (errstr || v >= FSMAXTYPES) {
				warnx("line %d: warning, unknown filesystem type: %s",
				    lineno, cp);
				v = FS_UNUSED;
			}
			pp->p_fstype = v;
	gottype:
			switch (pp->p_fstype) {

			case FS_UNUSED:				/* XXX */
				if (tp == NULL)	/* ok to skip fsize/bsize */
					break;
				NXTNUM(fsize, fsize, &errstr);
				if (fsize == 0)
					break;
				NXTNUM(v, v, &errstr);
				pp->p_fragblock =
				    DISKLABELV1_FFS_FRAGBLOCK(fsize, v / fsize);
				break;

			case FS_BSDFFS:
				NXTNUM(fsize, fsize, &errstr);
				if (fsize == 0)
					break;
				NXTNUM(v, v, &errstr);
				pp->p_fragblock =
				    DISKLABELV1_FFS_FRAGBLOCK(fsize, v / fsize);
				NXTNUM(pp->p_cpg, pp->p_cpg, &errstr);
				break;

			default:
				break;
			}
			continue;
		}
		warnx("line %d: unknown field: %s", lineno, cp);
		errors++;
	next:
		;
	}
	errors += checklabel(lp);
	return (errors > 0);
}