library_all_infos_struct* ReadSharedCacheMap(const char *path) {
    uint64_t b_address, e_address;
    char frameworkName[256];
    char *tokens[64];
    char buf[1024];
    char *fnp;
    FILE *fd;
    int    ntokens;
    int    type;
    int    linkedit_found = 0;
    char *substring, *ptr;
    int numFrameworks = 0;

    bzero(buf, sizeof(buf));
    bzero(tokens, sizeof(tokens));

    if ((fd = fopen(path, "r")) == 0)
    {
        return 0;
    }
    while (fgets(buf, 1023, fd)) {
        if (strncmp(buf, "mapping", 7))
            break;
    }
    buf[strlen(buf)-1] = 0;

    frameworkName[0] = 0;

    int start;

    library_all_infos_struct* lib_all_infos =safe_malloc(sizeof(library_all_infos_struct));
    lib_all_infos->count = 0;
    for (;;) {
        //Extract lib name from path name

        ptr = buf;
        substring = ptr;
        start = 0;
        while (*ptr)  {
            if (*ptr == '/' && start == 0) {
                substring = ptr;
                start = 1;
            }
            ptr++;
        }

        strncpy(frameworkName, substring, 256);
        frameworkName[255] = 0;

        fnp = (char *)malloc(strlen(frameworkName) + 1);
        strcpy(fnp, frameworkName);

        while (fgets(buf, 1023, fd) && numFrameworks < (MAXINDEX - 2)) {
            /*
             * Get rid of EOL
             */
            buf[strlen(buf)-1] = 0;

            ntokens = scanline(buf, tokens, 64);

            if (ntokens < 4)
                continue;

            if (strncmp(tokens[0], "__TEXT", 6) == 0)
                type = TEXT_R;
            else if (strncmp(tokens[0], "__DATA", 6) == 0)
                type = DATA_R;
            else if (strncmp(tokens[0], "__OBJC", 6) == 0)
                type = OBJC_R;
            else if (strncmp(tokens[0], "__IMPORT", 8) == 0)
                type = IMPORT_R;
            else if (strncmp(tokens[0], "__UNICODE", 9) == 0)
                type = UNICODE_R;
            else if (strncmp(tokens[0], "__IMAGE", 7) == 0)
                type = IMAGE_R;
            else if (strncmp(tokens[0], "__LINKEDIT", 10) == 0)
                type = LINKEDIT_R;
            else
                type = -1;

            if (type == LINKEDIT_R && linkedit_found)
                break;

            if (type != -1) {
                b_address = strtoull(tokens[1], 0, 16);
                e_address = strtoull(tokens[3], 0, 16);

                library_info_struct* new_lib_info = safe_malloc(sizeof(library_info_struct));

                new_lib_info->b_address    = b_address;
                new_lib_info->e_address    = e_address;
                new_lib_info->r_type    = type;
                new_lib_info->name        = fnp;

                lib_all_infos->lib_info[lib_all_infos->count++] = new_lib_info;

                if (type == LINKEDIT_R) {
                    linkedit_found = 1;
                }
// #if DEBUG
//                 printf("%s(%d): %qx-%qx\n", frameworkInfo[numFrameworks].name, type, b_address, e_address);
// #endif

                numFrameworks++;
            }
            if (type == LINKEDIT_R)
                break;
        }
        if (fgets(buf, 1023, fd) == 0)
            break;

        buf[strlen(buf)-1] = 0;
    }
    fclose(fd);

// #if DEBUG
//     for(int i=0;i<lib_all_infos->count;i++)
//     {
//         library_info_struct* dyldinfo = lib_all_infos->lib_info[i];

//         printf("%p %p %d %s \n", dyldinfo->b_address, dyldinfo->e_address, dyldinfo->r_type, dyldinfo->name);

//     }
// #endif

    return lib_all_infos;
}