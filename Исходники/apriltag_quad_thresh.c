zarray_t *apriltag_quad_thresh(apriltag_detector_t *td, image_u8_t *im)
{
    ////////////////////////////////////////////////////////
    // step 1. threshold the image, creating the edge image.

    int w = im->width, h = im->height, s = im->stride;

    image_u8_t *threshim = threshold(td, im);
    assert(threshim->stride == s);

    image_u8_t *edgeim = image_u8_create(w, h);

    if (1) {
        image_u8_t *sumim = image_u8_create(w, h);

        // apply a horizontal sum kernel of width 3
        for (int y = 0; y < h; y++) {
            for (int x = 1; x+1 < w; x++) {

                sumim->buf[y*s + x] =
                    threshim->buf[y*s + x - 1] +
                    threshim->buf[y*s + x + 0] +
                    threshim->buf[y*s + x + 1];
            }
        }
        timeprofile_stamp(td->tp, "sumim");

        // deglitch
        if (td->qtp.deglitch) {
            for (int y = 1; y+1 < h; y++) {
                for (int x = 1; x+1 < w; x++) {
                    // edge: black pixel next to white pixel
                    if (threshim->buf[y*s + x] == 0 &&
                        sumim->buf[y*s + x - s] + sumim->buf[y*s + x] + sumim->buf[y*s + x + s] == 8) {
                        threshim->buf[y*s + x] = 1;
                        sumim->buf[y*s + x - 1]++;
                        sumim->buf[y*s + x + 0]++;
                        sumim->buf[y*s + x + 1]++;
                    }

                    if (threshim->buf[y*s + x] == 1 &&
                        sumim->buf[y*s + x - s] + sumim->buf[y*s + x] + sumim->buf[y*s + x + s] == 1) {
                        threshim->buf[y*s + x] = 0;
                        sumim->buf[y*s + x - 1]--;
                        sumim->buf[y*s + x + 0]--;
                        sumim->buf[y*s + x + 1]--;
                   }
                }
            }

            timeprofile_stamp(td->tp, "deglitch");
        }

        // apply a vertical sum kernel of width 3; check if any
        // over-threshold pixels are adjacent to an under-threshold
        // pixel.
        //
        // There are two types of edges: white pixels neighboring a
        // black pixel, and black pixels neighboring a white pixel. We
        // label these separately.  (Values 0xc0 and 0x3f are picked
        // such that they add to 255 (see below) and so that they can be
        // viewed as pixel intensities for visualization purposes.)
        //
        // symmetry of detection. We don't want to use JUST "black
        // near white" (or JUST "white near black"), because that
        // biases the detection towards one side of the edge. This
        // measurably reduces detection performance.
        //
        // On large tags, we could treat "neighbor" pixels the same
        // way. But on very small tags, there may be other edges very
        // near the tag edge. Since each of these edges is effectively
        // two pixels thick (the white pixel near the black pixel, and
        // the black pixel near the white pixel), it becomes likely
        // that these two nearby edges will actually touch.
        //
        // A partial solution to this problem is to define edges to be
        // adjacent white-near-black and black-near-white pixels.
        //

        for (int y = 1; y+1 < h; y++) {
            for (int x = 1; x+1 < w; x++) {
                if (threshim->buf[y*s + x] == 0) {
                    // edge: black pixel next to white pixel
                    if (sumim->buf[y*s + x - s] + sumim->buf[y*s + x] + sumim->buf[y*s + x + s] > 0)
                        edgeim->buf[y*s + x] = 0xc0;
                } else {
                    // edge: white pixel next to black pixel when both
                    // edge types are on, we get less bias towards one
                    // side of the edge.
                    if (sumim->buf[y*s + x - s] + sumim->buf[y*s + x] + sumim->buf[y*s + x + s] < 9)
                        edgeim->buf[y*s + x] = 0x3f;
                }
            }
        }

        if (td->debug) {
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    threshim->buf[y*s + x] *= 255;
                }
            }

            image_u8_write_pnm(threshim, "debug_threshold.pnm");
            image_u8_write_pnm(edgeim, "debug_edge.pnm");
//            image_u8_destroy(edgeim2);
        }

        image_u8_destroy(threshim);
        image_u8_destroy(sumim);
    }

    timeprofile_stamp(td->tp, "edges");

    ////////////////////////////////////////////////////////
    // step 2. find connected components.

    unionfind_t *uf = unionfind_create(w * h);

    for (int y = 1; y < h - 1; y++) {
        for (int x = 1; x < w -1; x++) {
            uint8_t v = edgeim->buf[y*s + x];
            if (v==0)
                continue;

            // (dx,dy) pairs for 8 connectivity:
            //          (REFERENCE) (1, 0)
            // (-1, 1)    (0, 1)    (1, 1)
            //
            // i.e., the minimum value of dx should be:
            //   y=0:   1
            //   y=1:  -1
            for (int dy = 0; dy <= 1; dy++) {
                for (int dx = 1-2*dy; dx <= 1; dx++) {
                    if (edgeim->buf[(y+dy)*s + (x+dx)] == v) {
                        unionfind_connect(uf, y*w + x, (y+dy)*w + x + dx);
                    }
                }
            }
        }
    }

    timeprofile_stamp(td->tp, "unionfind");

    zhash_t *clustermap = zhash_create(sizeof(uint64_t), sizeof(zarray_t*),
                                       zhash_uint64_hash, zhash_uint64_equals);

    for (int y = 1; y < h-1; y++) {
        for (int x = 1; x < w-1; x++) {

            uint8_t v0 = edgeim->buf[y*s + x];
            if (v0 == 0)
                continue;

            uint64_t rep0 = unionfind_get_representative(uf, y*w + x);

            // 8 connectivity. (4 neighbors to check).
//            for (int dy = 0; dy <= 1; dy++) {
//                for (int dx = 1-2*dy; dx <= 1; dx++) {

            // 4 connectivity. (2 neighbors to check)
            for (int n = 1; n <= 2; n++) {
                int dy = n & 1;
                int dx = (n & 2) >> 1;

                uint8_t v1 = edgeim->buf[(y+dy)*s + x + dx];
                if (v0 + v1 != 255)
                    continue;
                uint64_t rep1 = unionfind_get_representative(uf, (y+dy)*w + x+dx);

                uint64_t clusterid;
                if (rep0 < rep1)
                    clusterid = (rep1 << 32) + rep0;
                else
                    clusterid = (rep0 << 32) + rep1;

                zarray_t *cluster = NULL;
                if (!zhash_get(clustermap, &clusterid, &cluster)) {
                    cluster = zarray_create(sizeof(struct pt));
                    zhash_put(clustermap, &clusterid, &cluster, NULL, NULL);
                }

                // NB: We will add some points multiple times to a
                // given cluster.  I don't know an efficient way to
                // avoid that here; we remove them later on when we
                // sort points by pt_compare_theta.
                if (1) {
                    struct pt p = { .x = x, .y = y};
                    zarray_add(cluster, &p);
                }
                if (1) {
                    struct pt p = { .x = x+dx, .y = y+dy};
                    zarray_add(cluster, &p);
                }
            }
        }
    }

    // make segmentation image.
    if (td->debug) {
        image_u8_t *d = image_u8_create(w, h);
        assert(d->stride == s);

        uint8_t *colors = (uint8_t*) calloc(w*h, 1);

        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++) {
                uint32_t v = unionfind_get_representative(uf, y*w+x);
                uint32_t sz = unionfind_get_set_size(uf, y*w+x);
                if (sz < td->qtp.min_cluster_pixels)
                    continue;

                uint8_t color = colors[v];

                if (color == 0) {
                    const int bias = 20;
                    color = bias + (random() % (255-bias));
                    colors[v] = color;
                }

                float mix = 0.7;
                mix = 1.0;
                d->buf[y*d->stride + x] = mix*color + (1-mix)*im->buf[y*im->stride + x];
            }
        }

        free(colors);

        image_u8_write_pnm(d, "debug_segmentation.pnm");
        image_u8_destroy(d);
    }

    timeprofile_stamp(td->tp, "make clusters");


    ////////////////////////////////////////////////////////
    // step 3. process each connected component.

    zarray_t *clusters = zhash_values(clustermap);
    zhash_destroy(clustermap);

    zarray_t *quads = zarray_create(sizeof(struct quad));

    int sz = zarray_size(clusters);
    int chunksize = 1 + sz / (APRILTAG_TASKS_PER_THREAD_TARGET * td->nthreads);
    struct quad_task tasks[sz / chunksize + 1];

    int ntasks = 0;
    for (int i = 0; i < sz; i += chunksize) {
        tasks[ntasks].td = td;
        tasks[ntasks].cidx0 = i;
        tasks[ntasks].cidx1 = imin(sz, i + chunksize);
        tasks[ntasks].h = h;
        tasks[ntasks].w = w;
        tasks[ntasks].quads = quads;
        tasks[ntasks].clusters = clusters;
        tasks[ntasks].im = im;

        workerpool_add_task(td->wp, do_quad_task, &tasks[ntasks]);
        ntasks++;
    }

    workerpool_run(td->wp);

    timeprofile_stamp(td->tp, "fit quads to clusters");

    if (td->debug) {
        FILE *f = fopen("debug_lines.ps", "w");
        fprintf(f, "%%!PS\n\n");

        image_u8_t *im2 = image_u8_copy(im);
        image_u8_darken(im2);
        image_u8_darken(im2);

        // assume letter, which is 612x792 points.
        double scale = fmin(612.0/im->width, 792.0/im2->height);
        fprintf(f, "%.15f %.15f scale\n", scale, scale);
        fprintf(f, "0 %d translate\n", im2->height);
        fprintf(f, "1 -1 scale\n");

        postscript_image(f, im);

        for (int i = 0; i < zarray_size(quads); i++) {
            struct quad *q;
            zarray_get_volatile(quads, i, &q);

            float rgb[3];
            int bias = 100;

            for (int i = 0; i < 3; i++)
                rgb[i] = bias + (random() % (255-bias));

            fprintf(f, "%f %f %f setrgbcolor\n", rgb[0]/255.0f, rgb[1]/255.0f, rgb[2]/255.0f);
            fprintf(f, "%.15f %.15f moveto %.15f %.15f lineto %.15f %.15f lineto %.15f %.15f lineto %.15f %.15f lineto stroke\n",
                    q->p[0][0], q->p[0][1],
                    q->p[1][0], q->p[1][1],
                    q->p[2][0], q->p[2][1],
                    q->p[3][0], q->p[3][1],
                    q->p[0][0], q->p[0][1]);
        }

        fclose(f);
    }

//        printf("  %d %d %d %d\n", indices[0], indices[1], indices[2], indices[3]);

/*
        if (td->debug) {
            for (int i = 0; i < 4; i++) {
            int i0 = indices[i];
                int i1 = indices[(i+1)&3];

                if (i1 < i0)
                    i1 += zarray_size(cluster);

                for (int j = i0; j <= i1; j++) {
                    struct pt *p;
                    zarray_get_volatile(cluster, j % zarray_size(cluster), &p);

                    edgeim->buf[p->y*edgeim->stride + p->x] = 30+64*i;
                }
            }
            } */

    unionfind_destroy(uf);

    for (int i = 0; i < zarray_size(clusters); i++) {
        zarray_t *cluster;
        zarray_get(clusters, i, &cluster);
        zarray_destroy(cluster);
    }

    zarray_destroy(clusters);

    image_u8_destroy(edgeim);

    return quads;
}