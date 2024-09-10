struct cat* read_cat(const char* fname, int64 nside, double radius_arcsec, int verbose) {

    int barsize=70;

    FILE* fptr=open_file(fname);


    size_t nlines=countlines(fptr);
    if (verbose) wlog("    found %lu lines\n", nlines);
    rewind(fptr);

    struct cat* cat = alloc_or_die(sizeof(struct cat), "catalog struct");

    double radius_radians=0;
    if (radius_arcsec <= 0) {
        cat->radius_in_file=1;
        cat->cos_radius = alloc_or_die(nlines*sizeof(double), "cos_radius array");
    } else {
        cat->radius_in_file=0;
        cat->cos_radius = alloc_or_die(sizeof(double), "cos_radius");

        radius_radians = radius_arcsec/3600.*D2R;
        cat->cos_radius[0] = cos(radius_radians);
    }

    cat->hpix=NULL;
    cat->tree=NULL;

    cat->pts = alloc_or_die(nlines*sizeof(struct point),"points");
    cat->size = nlines;

    if (verbose) wlog("    creating hpix\n");
    cat->hpix = hpix_new(nside);

    if (verbose) {
        wlog("    reading and building tree\n");
        repeat_char('.', barsize); wlog("\n");
    }

    double ra=0, dec=0;
    struct i64stack* listpix = i64stack_new(0);

    // this will produce a more balanced tree across the whole sky
    int64 half_npix=cat->hpix->npix/2;

    size_t count=0;
    struct point* pt = &cat->pts[0];
    for (size_t i=0; i<cat->size; i++) {
        if (2 != fscanf(fptr, "%lf %lf", &ra, &dec)) {
            wlog("expected to read point at line %lu\n", i);
            exit(EXIT_FAILURE);
        }
        if (cat->radius_in_file) {
            if (1 != fscanf(fptr, "%lf", &radius_arcsec)) {
                wlog("expected to read radius at line %lu\n", i);
                exit(EXIT_FAILURE);
            }
            radius_radians = radius_arcsec/3600.*D2R;
            cat->cos_radius[i] = cos(radius_radians);
        }

        hpix_eq2xyz(ra,dec,&pt->x,&pt->y,&pt->z);

        hpix_disc_intersect(cat->hpix, pt->x, pt->y, pt->z, radius_radians, 
                            listpix);

        int64* ptr=listpix->data;
        while (ptr < listpix->data + listpix->size) {
            tree_insert(&cat->tree, (*ptr)-half_npix, count);
            ptr++;
        }

        pt++;
        count++;
        if (verbose) incr_bar(i+1, cat->size, barsize, '=');
    }
    listpix=i64stack_delete(listpix);

    if (verbose) wlog("\n");

    if (count != nlines) {
        wlog("expected %lu lines but read %lu\n", nlines, count);
        exit(EXIT_FAILURE);
    }

    if (verbose)
        wlog("fullest node has %lu members\n", tree_most_members(cat->tree));

    fclose(fptr);
    return cat;
}