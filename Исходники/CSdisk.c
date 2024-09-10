/*this writes the actual data*/
static void writestructs(SDF *sdfp1, SDF *sdfp2, FILE *fp, fpos_t pos_npart)
{
    int i, j, nvecs1, nvecs2, nmembers1, nmembers2, nmembers;
    char **vecs1, **vecs2, **members1, **members2;
    SDF_type_t *types;
    SDF_type_t type2;
    size_t stride = 0, outstride = 0;
    void *btab;
    void **addrs;
    int *inoffsets, *strides, *starts, *lines;
    int flag=0, incr=1;
    int npart1, npart2, newnpart, countnpart, max;
    int ident, idindex, ident_last, ident_max, identnew;
    fpos_t pos1_npart;
    double x, y, z;
    float radius, R0, maxR0, disk_h;
    /*make INCR and nlines user input */

    nvecs1 = SDFnvecs(sdfp1);
    vecs1 = SDFvecnames(sdfp1);
    max = nvecs1;

    nvecs2 = SDFnvecs(sdfp2);
    vecs2 = SDFvecnames(sdfp2);

    /* Count structure members */
    /* don't use SDFnrecs, since that reads in the entire file which I'm trying to
       avoid. But I know that the structure (so far) always has "x" as the first
       member, so I can start counting from there -CE */
    for (i = 0, nmembers1 = 0; i < nvecs1; ++i) {
        if (strncmp(vecs1[i], "x", strlen(vecs1[i])) == 0) {
            /* x is the first member of the structure */
            flag=1;
        }
	if (flag) ++nmembers1;
    }

    flag=0;
    for (i = 0, nmembers2 = 0; i < nvecs2; ++i) {
        if (strncmp(vecs2[i], "x", strlen(vecs2[i])) == 0) {
            /* x is the first member of the structure */
            flag=1;
        }
	if (flag) ++nmembers2;
    }

    if( nmembers1 != nmembers2) {
        fprintf(stderr, "non-matching headers: %d and %d\n",nvecs1,nvecs2);
//        exit(1);
    }

    printf("Enter disk radius: ");
    scanf("%f", &R0);
    printf(" %f\n", R0);

    printf("Enter disk height: ");
    scanf("%f", &disk_h);
    printf(" %f\n", disk_h);

    printf("Enter max r: ");
    scanf("%f",&maxR0);
    printf("%f\n",maxR0); 

    SDFgetint(sdfp1, "npart", &npart1);
    SDFgetint(sdfp2, "npart", &npart2);
    printf("%d and %d particles\n", npart1, npart2);

/*malloc memory space for the respective features of the struct-CE*/
    members1 = (char **)malloc(nmembers1 * sizeof(char *));
    members2 = (char **)malloc(nmembers2 * sizeof(char *));
    addrs = (void **)malloc(nmembers1 * sizeof(void *));
    types = (SDF_type_t *)malloc(nmembers1 * sizeof(SDF_type_t));
    inoffsets = (int *)malloc(nmembers1 * sizeof(int));
    strides = (int *)malloc(nmembers1 * sizeof(int));
    starts = (int *)malloc(nmembers1 * sizeof(int));
    lines = (int *)malloc(nmembers1 * sizeof(int));

    printf("done malloc'ing\n");
    flag=0;
/*one by one, go through the fields in the column, i.e. members of the struct?-CE*/
    for (i = 0, stride = 0, nmembers = 0; i < nvecs1; ++i) {
        if (strncmp(vecs1[i], "x", strlen(vecs1[i])) == 0) flag=1;
        if (strncmp(vecs1[i], "ident", strlen(vecs1[i])) == 0) idindex=nmembers;
        if(flag) {
	    members1[nmembers] = vecs1[i];
//	    members2[nmembers] = vecs2[i];
	    types[nmembers] = SDFtype(members1[nmembers], sdfp1);
	    inoffsets[nmembers] = stride;/* offsets (from beginning of 'line'?) of each column
                                            of data (struct member) */
	    stride += SDFtype_sizes[types[nmembers]];
            lines[nmembers] = incr;
            nmembers++;
	}
    }

    /* unnecesary, just use 'stride' ? CE */
    outstride = 0;
    for(i=0; i< nmembers1; i++) outstride += SDFtype_sizes[ types[i] ];

    printf("outstride = %d\n", outstride);

    btab = (void *)malloc( outstride*incr );

    printf("printing header\n");
    /*print the struct declaration part from the header-CE*/
    fprintf(fp, "struct {\n");
    for (i = 0; i < nmembers1; ++i) {
        strides[i] = stride;
	switch (types[i]) {
	case SDF_INT:
	    fprintf(fp, "\tint %s;\n", members1[i]);
	    break;
	case SDF_FLOAT:
            fprintf(fp, "\tfloat %s;\n", members1[i]);
	    break;
	case SDF_DOUBLE:
	    fprintf(fp, "\tdouble %s;\n", members1[i]);
	    break;
	default:
	    fprintf(stderr, "%s: type not supported\n", members1[i]);
	    exit(-1);
	}
    }
    fgetpos(fp, &pos1_npart);
    fprintf(fp, "}[%d];\n", npart1); /*figure out how to save the location of the file position
                                       indicator, so we can come back and update npart -CE */
    fprintf(fp, "#\n");
    fprintf(fp, "# SDF-EOH\n");

    /*calculate the byte offset in memory to the address of the next member-CE*/
    addrs[0] = (char *)btab;
    for (i=1; i< nmembers1; i++) addrs[i] = addrs[i-1] + SDFtype_sizes[ types[i-1] ];

    /* writing ISM material with cut out disk; assume whole ISM file is kept */
    /* cut out a disk for r<R0 and z<disk_h */

    printf("getting file 1 .... ");
    for( i=0, countnpart = 0; i < npart1-1; i++) {
        /* need to increment starts-array */
        for( j = 0; j < nmembers1; j++)
            starts[j] = i;

        /* read data into btab (via addrs) */
        SDFseekrdvecsarr(sdfp1, nmembers1, members1, starts, lines, addrs, strides);

        x = *((double *)(btab + inoffsets[0]));
        y = *((double *)(btab + inoffsets[1]));
        z = *((double *)(btab + inoffsets[2]));
        radius = sqrt(x*x + y*y);

	/*dump the btab data into the file now-CE*/
        if( radius > R0 || fabs(z) > disk_h ) {
            ident_last=ident;
            ident = *((int *)(btab + inoffsets[idindex]));
            if(ident_last==ident)printf("same ident\n");
            identnew = countnpart; /* renumber the idents */
            memcpy( btab + inoffsets[idindex], &identnew, sizeof(ident) );
	    fwrite(btab, outstride, 1, fp);
            countnpart++;
        }

    }
    newnpart = countnpart-1;
    ident_max=identnew;

    /* add the disk */
    printf("got %d lines, last ident=%d\n",countnpart,ident_max);
    printf("getting file 2 .... ");
    for( i=0, countnpart = 0; i < npart2-1; i++) {
        /* need to increment starts-array */
        for( j = 0; j < nmembers1; j++)
            starts[j] = i;

        /* read data into btab (via addrs) */
        SDFseekrdvecsarr(sdfp2, nmembers1, members1, starts, lines, addrs, strides);

        x = *((double *)(btab + inoffsets[0]));
        y = *((double *)(btab + inoffsets[1]));
        z = *((double *)(btab + inoffsets[2]));
        radius = sqrt(x*x + y*y);

	/*dump the btab data into the file now-CE*/
        if( radius < R0 && fabs(z) < disk_h) { /* radius is always greater than -99., no extra case needed*/
            /* update the particle id, so it does not start at 1 again */
            ident_last=ident;
            ident = *((int *)(btab + inoffsets[idindex]));
            if(ident_last==ident)printf(" same ident ");
            ++countnpart;
            identnew = countnpart + ident_max; /* so there aren't duplicate particle ids */
            memcpy( btab + inoffsets[idindex], &identnew, sizeof(ident) );

	    fwrite(btab, outstride, 1, fp);
        } 

    }
    newnpart += countnpart-1;
    printf("got %d lines\n",countnpart);

    /* update npart to the new value */
    fsetpos(fp, &pos1_npart);
    fprintf(fp, "}[%d];", newnpart);

    fsetpos(fp, &pos_npart);
    fprintf(fp, "int %s = %d;", "npart", newnpart);

/*and we're done! clean up now -CE: if it ever works*/
/*    free(members);
    free(btab);
    free(addrs);
    free(types);
    free(inoffsets);
*/
    /*free(outbtab);*/
}