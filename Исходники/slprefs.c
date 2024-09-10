//-------------------------------------------------------------------------
void SavePreferences(void)
{
    int i;
    char name[256];
    WINDOWPLACEMENT wp;
    FILE *out;
    GetUserDataPath(name);
    strcat(name, PREFFILE);
    out = fopen(name, "w");
    if (!out)
        return;
    fprintf(out, "<UIPREFS>\n");
    fprintf(out, "\t<VERSION ID=\"%d\"/>\n", PREFVERS);
    wp.length = sizeof(wp);
    GetWindowPlacement(hwndFrame, &wp);
    fprintf(out, "\t<PLACEMENT VALUE=\"%d %d %d %d %d %d %d %d %d %d\"/>\n",
        wp.flags, wp.showCmd, wp.ptMinPosition.x, wp.ptMinPosition.y,
        wp.ptMaxPosition.x, wp.ptMaxPosition.y, wp.rcNormalPosition.left,
        wp.rcNormalPosition.top, wp.rcNormalPosition.right,
        wp.rcNormalPosition.bottom);
    fprintf(out, "\t<CUSTOMCOLORS>\n\t\t");
    for (i = 0; i < 16; i++)
    {
        fprintf(out, "%d ", custColors[i]);
        if (i == 7)
            fprintf(out, "\n\t\t");
    }
    fprintf(out, "\n\t</CUSTOMCOLORS>\n");
    fprintf(out, "\t<MEMWND WORDSIZE=\"%d\"/>\n", memoryWordSize);
    fprintf(out, "\t<FIND FMODE=\"%d\" RMODE=\"%d\" FIFFINDMODE=\"%d\" FIFREPLACEMODE=\"%d\">\n", findmode, replacemode, fiffindmode, fifreplacemode);
    for (i=0; i < F_M_MAX; i++)
    {
        fprintf(out, "\t\t<MODE INDEX=\"%d\" FIND=\"%d\" REPLACE=\"%d\"/>\n", i, findflags[i], replaceflags[i]);
    }			
    fprintf(out, "\t</FIND>\n");
    fprintf(out, "\t<PROPERTIES>\n");
    SaveProps(out, generalProject.profiles->debugSettings, 2);
    fprintf(out, "\t</PROPERTIES>\n");
    fprintf(out, "\t<RULES>\n");
    SaveBuildRules(out);
    fprintf(out, "\t</RULES>\n");
    fprintf(out, "</UIPREFS>\n");
    fclose(out);
}