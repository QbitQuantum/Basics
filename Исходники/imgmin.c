/*
 * special handling for PNGs
 * there exist many high-quality PNG optimization tools; if they exist then leverage them
 */
static void do_png(MagickWand *mw, const char *src, const char *dst,
                    const struct imgmin_options *opt)
{
    char out[MAX_PATH+1];
    struct filesize files[8];
    int filecnt = 0;
    int srcnamelen = max(0, (int)(strlen(src) - 4)); /* {foo}.png */
    const char *srcext = src + srcnamelen; /* foo{.png} */

    /* our fallback is the unchanged file itself */
    strcpy(files[0].tool, "none");
    strcpy(files[0].path, src);
    files[0].bytes = getfilesize(src);
    filecnt = 1;

    fputc('\n', stderr);

    /* if we find other well-known png optimizers, try them and record their results in files[] */

    if (!system("which pngnq 2>/dev/null >/dev/null"))
    {
        char * const argv[] = { "pngnq", "-f", src, (char*)0};
        if (!strcmp(srcext, ".png"))
            snprintf(out, sizeof out, "%.*s-nq8%s", srcnamelen, src, srcext);
        else /* does not recognize non-".png" extension... */
            snprintf(out, sizeof out, "%s-nq8.png", src);
        filecnt += do_png_cmd2("pngnq", argv, out, files + filecnt);
    }

    if (!system("which pngcrush 2>/dev/null >/dev/null"))
    {
        char * const argv[] = { "pngcrush", "-force", src, out, (char*)0 };
        snprintf(out, sizeof out, "%.*s-pngcrush%s", srcnamelen, src, srcext);
        filecnt += do_png_cmd2("pngcrush", argv, out, files + filecnt);
    }

    if (!system("which pngquant 2>/dev/null >/dev/null"))
    {
        char * const argv[] = { "pngquant", "-force", "256", src, (char*)0 };
        if (!strcmp(srcext, ".png"))
            snprintf(out, sizeof out, "%.*s-fs8%s", srcnamelen, src, srcext);
        else /* does not recognize non-".png" extension... */
            snprintf(out, sizeof out, "%s-fs8.png", src);
        filecnt += do_png_cmd2("pngquant", argv, out, files + filecnt);
    }

    /* find the smallest of all output files[] */
    {
        int i, smalli = 0;
        for (i = 1; i < filecnt; i++)
        {
            fprintf(stderr, " %.1fk@%s", files[i].bytes / 1024.0, files[i].tool);
            if (files[i].bytes < files[smalli].bytes)
                smalli = i;
        }
        files[0] = files[smalli];
    }

    /* cp the smallest resulting file to dst */
    fprintf(stderr, "\nUsing %s %4.1fk...\n", files[0].tool, files[0].bytes / 1024.0);
    {
        char * const argv[] = { "cp", files[0].path, dst, NULL };
        (void) do_png_cmd2("cp", argv, dst, files);
    }

    /* clean up intermediate files (but don't nuke src or dst!) */
    {
        char rmpath[MAX_PATH+1];
        char * const argv[] = { "rm", rmpath, NULL};
        int i;
        for (i = 1; i < filecnt; i++)
        {
            if (strcmp(files[i].path, dst) != 0)
            {
                strcpy(rmpath, files[i].path);
                (void) do_png_cmd2("rm", argv, dst, files);
            }
        }
    }

}