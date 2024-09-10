    int
main(int argc, char *argv[])
{
    int		found = 0;
    FILE	*fd;
#ifdef WIN3264
    int		i;
    struct stat st;
    char	icon[BUFSIZE];
    char	path[BUFSIZE];
    char	popup_path[BUFSIZE];

    /* The nsis uninstaller calls us with a "-nsis" argument. */
    if (argc == 2 && stricmp(argv[1], "-nsis") == 0)
	interactive = FALSE;
    else
#endif
	interactive = TRUE;

    /* Initialize this program. */
    do_inits(argv);

    printf("This program will remove the following items:\n");

#ifdef WIN3264
    if (popup_gvim_path(popup_path))
    {
	printf(" - the \"Edit with Vim\" entry in the popup menu\n");
	printf("   which uses \"%s\"\n", popup_path);
	if (interactive)
	    printf("\nRemove it (y/n)? ");
	if (!interactive || confirm())
	{
	    remove_popup();
	    /* Assume the "Open With" entry can be removed as well, don't
	     * bother the user with asking him again. */
	    remove_openwith();
	}
    }
    else if (openwith_gvim_path(popup_path))
    {
	printf(" - the Vim \"Open With...\" entry in the popup menu\n");
	printf("   which uses \"%s\"\n", popup_path);
	printf("\nRemove it (y/n)? ");
	if (confirm())
	    remove_openwith();
    }

    if (get_shell_folder_path(path, "desktop"))
    {
	printf("\n");
	for (i = 0; i < ICON_COUNT; ++i)
	{
	    sprintf(icon, "%s\\%s", path, icon_link_names[i]);
	    if (stat(icon, &st) == 0)
	    {
		printf(" - the \"%s\" icon on the desktop\n", icon_names[i]);
		++found;
	    }
	}
	if (found > 0)
	{
	    if (interactive)
		printf("\nRemove %s (y/n)? ", found > 1 ? "them" : "it");
	    if (!interactive || confirm())
		remove_icons();
	}
    }

    if (get_shell_folder_path(path, VIM_STARTMENU)
	    && stat(path, &st) == 0)
    {
	printf("\n - the \"%s\" entry in the Start Menu\n", VIM_STARTMENU);
	if (interactive)
	    printf("\nRemove it (y/n)? ");
	if (!interactive || confirm())
	    remove_start_menu();
    }
#endif

    printf("\n");
    found = remove_batfiles(0);
    if (found > 0)
    {
	if (interactive)
	    printf("\nRemove %s (y/n)? ", found > 1 ? "them" : "it");
	if (!interactive || confirm())
	    remove_batfiles(1);
    }

    fd = fopen("gvim.exe", "r");
    if (fd != NULL)
    {
	fclose(fd);
	printf("gvim.exe detected.  Attempting to unregister gvim with OLE\n");
	system("gvim.exe -silent -unregister");
    }

    delete_uninstall_key();

    if (interactive)
    {
	printf("\nYou may now want to delete the Vim executables and runtime files.\n");
	printf("(They are still where you unpacked them.)\n");
    }

    if (interactive)
    {
	rewind(stdin);
	printf("\nPress Enter to exit...");
	(void)getchar();
    }
    else
	sleep(3);

    return 0;
}