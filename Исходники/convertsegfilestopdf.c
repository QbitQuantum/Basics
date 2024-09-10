main(int    argc,
     char **argv)
{
char        *pagedir, *pagesubstr, *maskdir, *masksubstr;
char        *title, *fileout, *boxaafile, *boxaapath;
l_int32      ret, res, type, thresh;
l_float32    scalefactor;
BOXAA       *baa;
static char  mainName[] = "convertsegfilestopdf";

    if (argc != 12) {
        fprintf(stderr,
	    " Syntax: convertsegfilestopdf dirin substr res type thresh \\ \n"
            "                       boxaafile scalefactor title fileout\n"
            "     where\n"
            "         pagedir:  input directory for image files\n"
            "         pagesubstr:  Use 'allfiles' to convert all files\n"
            "                  in the directory\n"
            "         maskdir:  input directory for mask files;\n"
            "                   use 'skip' to skip \n"
            "         masksubstr:  Use 'allfiles' to convert all files\n"
            "                  in the directory; 'skip' to skip\n"
            "         res:  Input resolution of each image;\n"
            "               assumed to all be the same\n"
            "         type: compression used for non-image regions:\n"
            "               0: default (G4 encoding)\n"
            "               1: JPEG encoding\n"
            "               2: G4 encoding\n"
            "               3: PNG encoding\n"
            "         thresh:  threshold for binarization; use 0 for default\n"
            "         boxaafile: Optional file of 'image' regions within\n"
            "                    each page.  This contains a boxa for each\n"
            "                    page, consisting of a set of regions.\n"
            "                    Use 'skip' to skip.\n"
            "         scalefactor:  Use to scale down the image regions\n"
            "         title:  Use 'none' to omit\n"
            "         fileout:  Output pdf file\n");
        return 1;
    }

    pagedir = argv[1];
    pagesubstr = argv[2];
    maskdir = argv[3];
    masksubstr = argv[4];
    res = atoi(argv[5]);
    type = atoi(argv[6]);
    thresh = atoi(argv[7]);
    boxaafile = argv[8];
    scalefactor = atof(argv[9]);
    title = argv[10];
    fileout = argv[11];

    if (!strcmp(pagesubstr, "allfiles"))
        pagesubstr = NULL;
    if (!strcmp(maskdir, "skip"))
        maskdir = NULL;
    if (!strcmp(masksubstr, "allfiles"))
        masksubstr = NULL;
    if (scalefactor <= 0.0 || scalefactor > 1.0) {
        L_WARNING("invalid scalefactor: setting to 1.0", mainName);
        scalefactor = 1.0;
    }
    if (type != 1 && type != 2 && type != 3)
        type = L_G4_ENCODE;
    if (thresh <= 0)
        thresh = 150;
    if (!strcmp(title, "none"))
        title = NULL;

    if (maskdir)  /* use this; ignore any input boxaafile */
        baa = convertNumberedMasksToBoxaa(maskdir, masksubstr, 0, 0);
    else if (strcmp(boxaafile, "skip")) {  /* use the boxaafile */
        boxaapath = genPathname(boxaafile, NULL);
        baa = boxaaRead(boxaapath);
        FREE(boxaapath);
    } 
    else  /* no maskdir and no input boxaafile */
        baa = NULL;

    ret = convertSegmentedFilesToPdf(pagedir, pagesubstr, res, type, thresh,
                                     baa, 75, scalefactor, title, fileout);
    boxaaDestroy(&baa);
    return ret;
}