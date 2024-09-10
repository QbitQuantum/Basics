int fbterm_init(struct fbterm_ctx *ctx)
{
    if (!font) {
        font = font_open(DEFAULT_FONT);

        if (!font)
            return -1;
    }

    memset(ctx, 0, sizeof(struct fbterm_ctx));
    ctx->font = font;

    fb_term_init(ctx);
    fb_cook_wallpaper(ctx, DEFAULT_WALLPAPER);

    VTerm *vt = vterm_new(ctx->rows, ctx->cols);
    ctx->vt = vt;

    VTermScreen *sc = vterm_obtain_screen(vt);
    vterm_screen_set_callbacks(sc, &screen_cbs, ctx);
    vterm_screen_reset(sc, 0);
    ctx->screen = sc;

    VTermRect r = {.start_row = 0, .end_row = ctx->rows, .start_col = 0, .end_col = ctx->cols};
    damage(r, ctx);

    return 0;
}

int kbd_fd = -1;
int pty    = -1;

int fbterm_main()
{
    struct fbterm_ctx *active = &term[0]; 

    struct winsize ws;
    ws.ws_row = active->rows;
    ws.ws_col = active->cols;
    ioctl(pty, TIOCSWINSZ, &ws);

    fbterm_redraw(active);

    size_t len;
    char buf[1024];

    while (1) {
        /* Read input */
        if ((len = read(pty, buf, sizeof(buf))) > 0) {
            vterm_input_write(active->vt, buf, len);
        }

        fbterm_redraw(active);

        /* Write output */
        while (vterm_output_get_buffer_current(active->vt) > 0) {
            size_t s = vterm_output_read(active->vt, buf, 1024);
            write(pty, buf, s);
        }
    }

    return 0;
}

char *pts_fn = NULL;    /* XXX */
void launch_shell()
{
    int shell_pid = 0;
relaunch:
    if (shell_pid = fork()) {   /* Relaunch shell if died */
        int s, pid;
        do {
            pid = waitpid(shell_pid, &s, 0);
        } while (pid != shell_pid);

        /* Uh..Oh shell died */
        goto relaunch;
    } else {
        for (int i = 0; i < 10; ++i)
            close(i);

        int stdin_fd  = open(pts_fn, O_RDONLY);
        int stdout_fd = open(pts_fn, O_WRONLY);
        int stderr_fd = open(pts_fn, O_WRONLY);

        /* run login shell */
        char *argp[] = {DEFAULT_SHELL, "login", NULL};
        char *envp[] = {"PWD=/", "TERM=VT100", NULL};
        execve(DEFAULT_SHELL, argp, envp);
        for (;;);
    }
}