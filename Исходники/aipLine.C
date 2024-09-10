/* STATIC */
void Line::drawProfile(float *y, int npts, double len, string ylabel) {
    const int buflen = 100;
    static int index = 0;

    if (y && len <= 0) {
        y = NULL;
    }

    // Open file
    char fname[128];
    sprintf(fname, "%s%d.%d", baseFilename.c_str(), getpid(), index);
    index++;
    index %= 2;
    FILE *fd = fopen(fname, "w");
    if (!fd) {
        fprintf(stderr,"Cannot open file for line profile: %s\n", fname);
        return;
    }

    char buf[buflen];
    if (y == NULL) {
        // Write out header
        fprintf(fd, "XLabel Distance (cm)\n");
        fprintf(fd, "YLabel %s\n", ylabel.c_str());
        //fprintf(fd,"YMin 0\n");
        //fprintf(fd,"YMax getReal("aipProfileMaxY", 0)\n");
        fprintf(fd, "NPoints 0\n");
        fprintf(fd, "Data\n");
        sprintf(buf, "Max:");
    } else {
        double ymax;
        // Set scale
        ymax = y[0];
        for (int i=0; i<npts; ++i) {
            if (ymax < y[i]) {
                ymax = y[i];
            }
        }
        double graphYmax = ymax;
        if (::isActive("aipProfileMaxY")) {
            graphYmax = max(ymax, getReal("aipProfileMaxY", 0));
        }
        setReal("aipProfileMaxY", ymax, false); // No notification

        // Write out header
        //fprintf(fd,"YMin 0\n");
        //fprintf(fd,"YMax %g\n", graphYmax);
        string showZero;
        showZero = getString("aipProfileShowZero", "y");
        if (showZero[0] == 'y' || showZero[0] == 'Y') {
            fprintf(fd,"ShowZeroY\n");
        }
        fprintf(fd,"XLabel Distance (cm)\n");
        fprintf(fd,"YLabel %s\n", ylabel.c_str());
        fprintf(fd,"NPoints %d\n", npts);
        fprintf(fd,"Data\n");
        sprintf(buf, "Max: %.4g", ymax);

        // Write out the data
        double x = 0;
        double dx = len / (npts - 1);
        for (int i=0; i<npts; ++i, x += dx) {
            fprintf(fd,"%g %g\n", x, y[i]);
        }
    }
    fprintf(fd,"EndData\n");
    fclose(fd);

    // Set parameters
    setString("aipProfileFile", fname, true);// Send notification of change
    static char maxStr[buflen] = "---";
    if (strcmp(buf, maxStr)) {
        strcpy(maxStr, buf);
        setString("aipProfileMaxMsg", buf, true);
    }
}