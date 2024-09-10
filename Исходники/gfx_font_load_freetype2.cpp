static void write_default(void)
{
    FILE* pf = 0;

    if ((pf = OPENFILE(CONFIG_FILE, F("a+")))) {

        fprintf(pf, "[%s]\n", "sung");
        fprintf(pf, "path=%s\n", "sung.ttf");
        fprintf(pf, "[%s]\n", "arial");
        fprintf(pf, "path=%s\n", "arial.ttf");

        fclose(pf);
    }
}