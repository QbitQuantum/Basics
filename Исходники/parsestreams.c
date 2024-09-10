/*ARGSUSED*/
int
xxxinit(
	unsigned int fc,
	struct vddrv *vdp,
	addr_t vdin,
	struct vdstat *vds
	)
{
	extern struct fmodsw fmodsw[];
	extern int fmodcnt;

	struct fmodsw *fm    = fmodsw;
	struct fmodsw *fmend = &fmodsw[fmodcnt];
	struct fmodsw *ifm   = (struct fmodsw *)0;
	char *mname          = parseinfo.st_rdinit->qi_minfo->mi_idname;

	switch (fc)
	{
	    case VDLOAD:
		vdp->vdd_vdtab = (struct vdlinkage *)&parsesync_vd;
		/*
		 * now, jog along fmodsw scanning for an empty slot
		 * and deposit our name there
		 */
		while (fm <= fmend)
		{
			if (!Strncmp(fm->f_name, mname, FMNAMESZ))
			{
				printf("vddrinit[%s]: STREAMS module already loaded.\n", mname);
				return(EBUSY);
			}
			else
			    if ((ifm == (struct fmodsw *)0) &&
				(fm->f_name[0] == '\0') &&
				(fm->f_str == (struct streamtab *)0))
			    {
				    /*
				     * got one - so move in
				     */
				    ifm = fm;
				    break;
			    }
			fm++;
		}

		if (ifm == (struct fmodsw *)0)
		{
			printf("vddrinit[%s]: no slot free for STREAMS module\n", mname);
			return (ENOSPC);
		}
		else
		{
			static char revision[] = "4.7";
			char *s, *S, *t;

			s = rcsid;		/* NOOP - keep compilers happy */

			Strncpy(ifm->f_name, mname, FMNAMESZ);
			ifm->f_name[FMNAMESZ] = '\0';
			ifm->f_str = &parseinfo;
			/*
			 * copy RCS revision into Drv_name
			 *
			 * are we forcing RCS here to do things it was not built for ?
			 */
			s = revision;
			if (*s == '$')
			{
				/*
				 * skip "$Revision: "
				 * if present. - not necessary on a -kv co (cvs export)
				 */
				while (*s && (*s != ' '))
				{
					s++;
				}
				if (*s == ' ') s++;
			}

			t = parsesync_vd.Drv_name;
			while (*t && (*t != ' '))
			{
				t++;
			}
			if (*t == ' ') t++;

			S = s;
			while (*S && (((*S >= '0') && (*S <= '9')) || (*S == '.')))
			{
				S++;
			}

			if (*s && *t && (S > s))
			{
				if (Strlen(t) >= (S - s))
				{
					(void) Strncpy(t, s, S - s);
				}
			}
			return (0);
		}
		break;

	    case VDUNLOAD:
		if (parsebusy > 0)
		{
			printf("vddrinit[%s]: STREAMS module has still %d instances active.\n", mname, parsebusy);
			return (EBUSY);
		}
		else
		{
			while (fm <= fmend)
			{
				if (!Strncmp(fm->f_name, mname, FMNAMESZ))
				{
					/*
					 * got it - kill entry
					 */
					fm->f_name[0] = '\0';
					fm->f_str = (struct streamtab *)0;
					fm++;

					break;
				}
				fm++;
			}
			if (fm > fmend)
			{
				printf("vddrinit[%s]: cannot find entry for STREAMS module\n", mname);
				return (ENXIO);
			}
			else
			    return (0);
		}


	    case VDSTAT:
		return (0);

	    default:
		return (EIO);

	}
	return EIO;
}