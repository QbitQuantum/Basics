/* restores terminal title from title_state.title */
static void
restore_term_title()
{
#ifdef _WIN32
	if(title_state.title[0] != L'\0')
		SetConsoleTitleW(title_state.title);
#else
	if(title_state.title[0] != '\0')
	{
		char *const title = format_str("\033]2;%s\007", title_state.title);
		putp(title);
		fflush(stdout);
		free(title);
	}

#if defined(HAVE_X11) && defined(DYN_X11)
	unload_xlib();
#endif
#endif
}