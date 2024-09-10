static void
writeHeader(FILE * const headerFileP,
            const char * const prefix,
            unsigned int const width,
            unsigned int const height,
            unsigned int const nfiles,
            const char ** const names,
            const Coord * const coords,
            const struct pam * imgs) {

    unsigned int i;

    fprintf(headerFileP, "#define %sOVERALLX %u\n", prefix, width);

    fprintf(headerFileP, "#define %sOVERALLY %u\n", prefix, height);

    fprintf(headerFileP, "\n");

    for (i = 0; i < nfiles; ++i) {
        char * const buffer = strdup(names[i]);
        Coord const coord = coords[i];
        struct pam const img = imgs[i];

        unsigned int j;
        
        *strchr(buffer, '.') = 0;
        for (j = 0; buffer[j]; ++j) {
            if (ISLOWER(buffer[j]))
                buffer[j] = TOUPPER(buffer[j]);
        }
        fprintf(headerFileP, "#define %s%sX %u\n", 
                prefix, buffer, coord.x);

        fprintf(headerFileP, "#define %s%sY %u\n",
                prefix, buffer, coord.y);

        fprintf(headerFileP, "#define %s%sSZX %u\n",
                prefix, buffer, img.width);

        fprintf(headerFileP, "#define %s%sSZY %u\n",
                prefix, buffer, img.height);

        fprintf(headerFileP, "\n");
    }
}