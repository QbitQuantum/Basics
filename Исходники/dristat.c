int main(int argc, char **argv)
{
    int  c;
    int  mask     = 0;
    int  minor    = 0;
    int  interval = 0;
    int  fd;
    char buf[64];
    int  i;

    while ((c = getopt(argc, argv, "avmcsbM:i:")) != EOF)
	switch (c) {
	case 'a': mask = ~0;                          break;
	case 'v': mask |= DRM_VERSION;                break;
	case 'm': mask |= DRM_MEMORY;                 break;
	case 'c': mask |= DRM_CLIENTS;                break;
	case 's': mask |= DRM_STATS;                  break;
	case 'b': mask |= DRM_BUSID;                  break;
	case 'i': interval = strtol(optarg, NULL, 0); break;
	case 'M': minor = strtol(optarg, NULL, 0);    break;
	default:
	    fprintf( stderr, "Usage: dristat [options]\n\n" );
	    fprintf( stderr, "Displays DRM information. Use with no arguments to display available cards.\n\n" );
	    fprintf( stderr, "  -a            Show all available information\n" );
	    fprintf( stderr, "  -b            Show DRM bus ID's\n" );
	    fprintf( stderr, "  -c            Display information about DRM clients\n" );
	    fprintf( stderr, "  -i [interval] Continuously display statistics every [interval] seconds\n" );
	    fprintf( stderr, "  -v            Display DRM module and card version information\n" );
	    fprintf( stderr, "  -m            Display memory use information\n" );
	    fprintf( stderr, "  -s            Display DRM statistics\n" );
	    fprintf( stderr, "  -M [minor]    Select card by minor number\n" );
	    return 1;
	}

    for (i = 0; i < 16; i++) if (!minor || i == minor) {
	sprintf(buf, DRM_DEV_NAME, DRM_DIR_NAME, i);
	fd = drmOpenMinor(i, 1, DRM_NODE_PRIMARY);
	if (fd >= 0) {
	    printf("%s\n", buf);
	    if (mask & DRM_BUSID)   getbusid(fd);
	    if (mask & DRM_VERSION) getversion(fd);
	    if (mask & DRM_MEMORY)  getvm(fd);
	    if (mask & DRM_CLIENTS) getclients(fd);
	    if (mask & DRM_STATS)   getstats(fd, interval);
	    close(fd);
	}
    }

    return 0; 
}