int pstatus (char *arg)
{
	struct ioc_vol v;
	struct ioc_read_subchannel ss;
	struct cd_sub_channel_info data;
	int rc, trk, m, s, f;
	int what = 0;
	char *p, vmcn[(4 * 15) + 1];

	while ((p = strtok(arg, " \t"))) {
	    arg = 0;
	    if (!strncasecmp(p, "audio", strlen(p)))
		what |= STATUS_AUDIO;
	    else if (!strncasecmp(p, "media", strlen(p)))
		what |= STATUS_MEDIA;
	    else if (!strncasecmp(p, "volume", strlen(p)))
		what |= STATUS_VOLUME;
	    else {
		warnx("invalid command arguments");
		return 0;
	    }
	}
	if (!what)
	    what = STATUS_AUDIO|STATUS_MEDIA|STATUS_VOLUME;
	if (what & STATUS_AUDIO) {
	    rc = status (&trk, &m, &s, &f);
	    if (rc >= 0)
		if (verbose)
		    printf ("Audio status = %d<%s>, current track = %d, current position = %d:%02d.%02d\n",
			    rc, strstatus (rc), trk, m, s, f);
		else
		    printf ("%d %d %d:%02d.%02d\n", rc, trk, m, s, f);
	    else
		printf ("No current status info available\n");
	}
	if (what & STATUS_MEDIA) {
	    bzero (&ss, sizeof (ss));
	    ss.data = &data;
	    ss.data_len = sizeof (data);
	    ss.address_format = msf ? CD_MSF_FORMAT : CD_LBA_FORMAT;
	    ss.data_format = CD_MEDIA_CATALOG;
	    rc = ioctl (fd, CDIOCREADSUBCHANNEL, (char *) &ss);
	    if (rc >= 0) {
		printf("Media catalog is %sactive",
		    ss.data->what.media_catalog.mc_valid ? "": "in");
		if (ss.data->what.media_catalog.mc_valid &&
		    ss.data->what.media_catalog.mc_number[0])
		{
		    strvisx (vmcn, ss.data->what.media_catalog.mc_number,
			    (sizeof (vmcn) - 1) / 4, VIS_OCTAL | VIS_NL);
		    printf(", number \"%.*s\"", (int)sizeof (vmcn), vmcn);
		}
		putchar('\n');
	    } else
		printf("No media catalog info available\n");
	}
	if (what & STATUS_VOLUME) {
	    rc = ioctl (fd, CDIOCGETVOL, &v);
	    if (rc >= 0)
		if (verbose)
		    printf ("Left volume = %d, right volume = %d\n",
			    v.vol[0], v.vol[1]);
		else
		    printf ("%d %d\n", v.vol[0], v.vol[1]);
	    else
		printf ("No volume level info available\n");
	}
	return(0);
}