static void open_browser(const char *uri)
{
#ifdef _WIN32
    ShellExecuteA(NULL, "open", uri, 0, 0, SW_SHOWNORMAL);
#else
    const char *browser = getenv("BROWSER");
    if (!browser)
    {
#ifdef __APPLE__
        browser = "open";
#else
        browser = "xdg-open";
#endif
    }
    if (fork() == 0)
    {
        execlp(browser, browser, uri, (char*)0);
        fprintf(stderr, "cannot exec '%s'\n", browser);
        exit(0);
    }
#endif
}