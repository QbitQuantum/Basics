int main(int argc, char *argv[])
{
    int i;
    int j;
    char* buffer;
    int use_stdout = FALSE;
    int skip_invalid = FALSE;
    int num_entries = 0;

    int verbose = FALSE;
    char* file_name_in = 0;
    char* file_name_out = 0;
    char separator_sign = ' ';
    char* parse_string = "xyz";

    int64_t global_offset_x = 0;
    int64_t global_offset_y = 0;
    int check = FALSE;
    double scale_x;
    double scale_y;

    LASReaderH reader = NULL;
    LASHeaderH header = NULL;
    LASPointH p = NULL;
    FILE* file_out;
    int len;

    unsigned int index = 0;
    if (argc == 1) {
        usage();
        exit(0);
    }

    for (i = 1; i < argc; i++)
    {
        if (    strcmp(argv[i],"-h") == 0 ||
                strcmp(argv[i],"-help") == 0 ||
                strcmp(argv[i],"--help") == 0
           )
        {
            usage();
            exit(0);
        }
        else if (   strcmp(argv[i],"-v") == 0 ||
                strcmp(argv[i],"--verbose") == 0
                )
        {
            verbose = TRUE;
        }
        else if (   strcmp(argv[i],"-s") == 0 ||
                strcmp(argv[i],"--skip_invalid") == 0
                )
        {
            skip_invalid = TRUE;
        }
        else if (   strcmp(argv[i], "--parse") == 0 ||
                    strcmp(argv[i], "-parse") == 0
                )
        {
            i++;
            parse_string = argv[i];
        }
        else if (   strcmp(argv[i], "--moffset") == 0 ||
                    strcmp(argv[i], "-moffset") == 0
                )
        {
            i++;
            buffer = strtok (argv[i], ",");
            j = 0;
            while (buffer) {
                if (j == 0) {
                    global_offset_x = S64(buffer);
                }
                else if (j == 1) {
                    global_offset_y = S64(buffer);
                }
                j++;
                buffer = strtok (NULL, ",");
                while (buffer && *buffer == '\040')
                    buffer++;
            }
            if (j != 2){
                fprintf(stderr, "Only two int64_t are required in moffset option!\n");
                exit(1);
            }

        }
        else if (   strcmp(argv[i], "--check") == 0 ||
                    strcmp(argv[i], "-check") == 0
                )
        {
            i++;
            check = TRUE;
            buffer = strtok (argv[i], ",");
            j = 0;
            while (buffer) {
                if (j == 0) {
                    sscanf(buffer, "%lf", &scale_x);
                }
                else if (j == 1) {
                    sscanf(buffer, "%lf", &scale_y);
                }
                j++;
                buffer = strtok (NULL, ",");
                while (buffer && *buffer == '\040')
                    buffer++;
            }
            if (j != 2){
                fprintf(stderr, "Only two doubles are required in moffset option!\n");
                exit(1);
            }
        }
        else if (   strcmp(argv[i], "--stdout") == 0
                )
        {
            use_stdout = TRUE;
        }
        else if (   strcmp(argv[i],"--input") == 0  ||
                strcmp(argv[i],"-input") == 0   ||
                strcmp(argv[i],"-i") == 0       ||
                strcmp(argv[i],"-in") == 0
                )
        {
            i++;
            file_name_in = argv[i];
        }
        else if (   strcmp(argv[i],"--output") == 0  ||
                    strcmp(argv[i],"--out") == 0     ||
                    strcmp(argv[i],"-out") == 0     ||
                    strcmp(argv[i],"-o") == 0
                )
        {
            i++;
            file_name_out = argv[i];
        }
        else if (file_name_in == 0 && file_name_out == 0)
        {
            file_name_in = argv[i];
        }
        else if (file_name_in && file_name_out == 0)
        {
            file_name_out = argv[i];
        }
        else
        {
            fprintf(stderr, "ERROR: unknown argument '%s'\n",argv[i]);
            usage();
            exit(1);
        }
    } /* end looping through argc/argv */
    num_entries = strlen(parse_string);

    if (use_stdout == TRUE && file_name_out){
      LASError_Print("If an output file is specified, --stdout must not be used!");
      exit(1);
    }

    reader = LASReader_Create(file_name_in);
    if (!reader) {
        LASError_Print("Unable to read file");
        exit(1);
    }

    header = LASReader_GetHeader(reader);
    if (!header) {
        LASError_Print("Unable to fetch header for file");
        exit(1);
    }

    if (use_stdout)
    {
        file_out = stdout;
    }
    else
    {
        if (file_name_out == NULL)
        {
            if (file_name_in == NULL)
            {
                LASError_Print("No input filename was specified");
                usage();
                exit(1);
            }

            len = (int)strlen(file_name_in);
            file_name_out = LASCopyString(file_name_in);
            if (file_name_out[len-3] == '.' && file_name_out[len-2] == 'g' && file_name_out[len-1] == 'z')
            {
                len = len - 4;
            }
            while (len > 0 && file_name_out[len] != '.')
            {
                len--;
            }
            file_name_out[len] = '\0';
        }
        file_out = fopen(file_name_out, "wb");
    }

    if (file_out == 0)
    {
        LASError_Print("Could not open file for write");
        usage();
        exit(1);
    }

    if (verbose)
    {
        print_header(stderr, header, file_name_in);
    }

    // Compute factors to add to X and Y and check sanity of generated codes
    double file_scale_x = LASHeader_GetScaleX(header);
    double file_scale_y = LASHeader_GetScaleY(header);

    if (check)
    {
        // Check specified scales are like in the LAS file
        if (fabs(scale_x - file_scale_x) > TOLERANCE){
        fprintf(stderr, "ERROR: x scale in input file (%lf) does not match specified x scale (%lf)\n",file_scale_x, scale_x);
            exit(1);
        }
        if (fabs(scale_y - file_scale_y) > TOLERANCE){
            fprintf(stderr, "ERROR: y scale in input file (%lf) does not match specified y scale (%lf)\n",file_scale_y, scale_y);
            exit(1);
        }
        /* Check that the extent of the file (taking into account the global offset)
         * is within 0,2^31 */
        double check_min_x = 1.0 + LASHeader_GetMinX(header) - (((double) global_offset_x) * scale_x);
        if (check_min_x < TOLERANCE) {
            fprintf(stderr, "ERROR: Specied X global offset is too large. (MinX - (GlobalX*ScaleX)) < 0\n");
            exit(1);
        }
        double check_min_y = 1.0 + LASHeader_GetMinY(header) - (((double) global_offset_y) * scale_y);
        if (check_min_y < TOLERANCE) {
            fprintf(stderr, "ERROR: Specied Y global offset is too large. (MinY - (GlobalY*ScaleY)) < 0\n");
            exit(1);
        }
        double check_max_x = LASHeader_GetMaxX(header) - (((double) global_offset_x) * scale_x);
        if (check_max_x > (MAX_INT_31 * scale_x)) {
            fprintf(stderr, "ERROR: Specied X global offset is too small. (MaxX - (GlobalX*ScaleX)) > (2^31)*ScaleX\n");
            exit(1);
        }
        double check_max_y = LASHeader_GetMaxY(header) - (((double) global_offset_y) * scale_y);
        if (check_max_y > (MAX_INT_31 * scale_y)) {
            fprintf(stderr, "ERROR: Specied Y global offset is too small. (MaxY - (GlobalY*ScaleY)) > (2^31)*ScaleY\n");
            exit(1);
        }
    }


    /*Write Postgres header*/
    struct postHeader pgHeader;
    pgHeader.s = "PGCOPY\n\377\r\n\0";
    int i1T = 0, i2T = 0;
    pgHeader.i1 = htonl(i1T);
    pgHeader.i2 = htonl(i2T);
    fwrite(pgHeader.s, 11, 1, file_out);
    fwrite(&pgHeader.i1, sizeof(uint32_t), 1, file_out);
    fwrite(&pgHeader.i2, sizeof(uint32_t), 1, file_out);

    /* declaration for morton*/
    uint32_t rawx = 0;
    uint32_t rawy = 0;
    uint64_t mortonkey = 0;

    /* scaled offsets to add for the morton encoding */
    int64_t factorX =  ((int64_t) (LASHeader_GetOffsetX(header) / file_scale_x)) - global_offset_x;
    int64_t factorY =  ((int64_t) (LASHeader_GetOffsetY(header) / file_scale_y)) - global_offset_y;

    p = LASReader_GetNextPoint(reader);
    while (p)
    {
        if (skip_invalid && !LASPoint_IsValid(p)) {
            if (verbose) {
                LASError_Print("Skipping writing invalid point...");
            }
            p = LASReader_GetNextPoint(reader);
            index -=1;
            continue;
        }
        struct postRow pgRow;
        uint32_t size;
        uint16_t hT = num_entries;
        pgRow.h = htons(hT);
        fwrite(& pgRow.h, 2, 1, file_out);
        size = sizeof(double);
        pgRow.vardSize = htonl(size);
        size = sizeof(uint32_t);
        pgRow.varSize = htonl(size);

        i = 0;
        for (;;)
        {
            LASColorH color = LASPoint_GetColor(p);
            double vard;
            int var;
            unsigned long long int vardL, varL;

            switch (parse_string[i])
               {
                    /* // the morton code on xy */
                case 'k':
                    rawx = (uint32_t) (((int64_t) LASPoint_GetRawX(p)) + factorX);
                    rawy = (uint32_t) (((int64_t) LASPoint_GetRawY(p)) + factorY);
                    mortonkey = EncodeMorton2D(rawx,rawy);
                    varL = htobe64(mortonkey);
                    fwrite(&pgRow.vardSize, sizeof(uint32_t), 1, file_out);
                    fwrite(&varL, sizeof(uint64_t), 1, file_out);
                    break;
                    /* // the x coordinate */
                case 'x':
                    vard = LASPoint_GetX(p);
                    fwrite(&pgRow.vardSize, sizeof(uint32_t), 1, file_out);
                    vardL = bigEndian_double(vard);
                    fwrite(&vardL, sizeof(double), 1, file_out);
                    break;
                    /* // the y coordinate */
                case 'y':
                    vard = LASPoint_GetY(p);
                    fwrite(&pgRow.vardSize, sizeof(uint32_t), 1, file_out);
                    vardL = bigEndian_double(vard);
                    fwrite(&vardL, sizeof(double), 1, file_out);
                    break;
                    /* // the z coordinate */
                case 'z':
                    vard = LASPoint_GetZ(p);
                    fwrite(&pgRow.vardSize, sizeof(uint32_t), 1, file_out);
                    vardL = bigEndian_double(vard);
                    fwrite(&vardL, sizeof(double), 1, file_out);
                    break;
                    /* // the gps-time */
                case 't':
                    vard = LASPoint_GetTime(p);
                    fwrite(&pgRow.vardSize, sizeof(uint32_t), 1, file_out);
                    vardL = bigEndian_double(vard);
                    fwrite(&vardL, sizeof(double), 1, file_out);
                    break;
                    /* // the intensity */
                case 'i':
                    var = LASPoint_GetIntensity(p);
                    fwrite(&pgRow.varSize, sizeof(uint32_t), 1, file_out);
                    varL = htonl(var);
                    fwrite(&varL, sizeof(uint32_t), 1, file_out);
                    break;
                    /* the scan angle */
                case 'a':
                    var = LASPoint_GetScanAngleRank(p);
                    fwrite(&pgRow.varSize, sizeof(uint32_t), 1, file_out);
                    varL = htonl(var);
                    fwrite(&varL, sizeof(uint32_t), 1, file_out);
                    break;
                    /* the number of the return */
                case 'r':
                    var = LASPoint_GetReturnNumber(p);
                    fwrite(&pgRow.varSize, sizeof(uint32_t), 1, file_out);
                    varL = htonl(var);
                    fwrite(&varL, sizeof(uint32_t), 1, file_out);
                    break;
                    /* the classification */
                case 'c':
                    var = LASPoint_GetClassification(p);
                    fwrite(&pgRow.varSize, sizeof(uint32_t), 1, file_out);
                    varL = htonl(var);
                    fwrite(&varL, sizeof(uint32_t), 1, file_out);
                    break;
                    /* the user data */
                case 'u':
                    var = LASPoint_GetUserData(p);
                    fwrite(&pgRow.varSize, sizeof(uint32_t), 1, file_out);
                    varL = htonl(var);
                    fwrite(&varL, sizeof(uint32_t), 1, file_out);
                    break;
                    /* the number of returns of given pulse */
                case 'n':
                    var = LASPoint_GetNumberOfReturns(p);
                    fwrite(&pgRow.varSize, sizeof(uint32_t), 1, file_out);
                    varL = htonl(var);
                    fwrite(&varL, sizeof(uint32_t), 1, file_out);
                    break;
                    /* the red channel color */
                case 'R':
                    var = LASColor_GetRed(color);
                    fwrite(&pgRow.varSize, sizeof(uint32_t), 1, file_out);
                    varL = htonl(var);
                    fwrite(&varL, sizeof(uint32_t), 1, file_out);
                    break;
                    /* the green channel color */
                case 'G':
                    var = LASColor_GetGreen(color);
                    fwrite(&pgRow.varSize, sizeof(uint32_t), 1, file_out);
                    varL = htonl(var);
                    fwrite(&varL, sizeof(uint32_t), 1, file_out);
                    break;
                    /* the blue channel color */
                case 'B':
                    var = LASColor_GetBlue(color);
                    fwrite(&pgRow.varSize, sizeof(uint32_t), 1, file_out);
                    varL = htonl(var);
                    fwrite(&varL, sizeof(uint32_t), 1, file_out);
                    break;
                case 'M':
                    var = index;
                    fwrite(&pgRow.varSize, sizeof(uint32_t), 1, file_out);
                    varL = htonl(var);
                    fwrite(&varL, sizeof(uint32_t), 1, file_out);
                    break;
                case 'p':
                    var = LASPoint_GetPointSourceId(p);
                    fwrite(&pgRow.varSize, sizeof(uint32_t), 1, file_out);
                    varL = htonl(var);
                    fwrite(&varL, sizeof(uint32_t), 1, file_out);
                    break;
                    /* the edge of flight line flag */
                case 'e':
                    var = LASPoint_GetFlightLineEdge(p);
                    fwrite(&pgRow.varSize, sizeof(uint32_t), 1, file_out);
                    varL = htonl(var);
                    fwrite(&varL, sizeof(uint32_t), 1, file_out);
                    break;
                    /* the direction of scan flag */
                case 'd':
                    var = LASPoint_GetScanDirection(p);
                    fwrite(&pgRow.varSize, sizeof(uint32_t), 1, file_out);
                    varL = htonl(var);
                    fwrite(&varL, sizeof(uint32_t), 1, file_out);
                    break;
            }
            i++;
            if (!parse_string[i])
            {
                break;
            }
            LASColor_Destroy(color);
        }
        p = LASReader_GetNextPoint(reader);
        index +=1;
    }
    short endT = -1;
    short end = htons(endT);
    fwrite(&end, sizeof(end), 1, file_out);

    fflush(file_out);
    fclose(file_out);

    LASReader_Destroy(reader);
    LASHeader_Destroy(header);
    return 0;
}