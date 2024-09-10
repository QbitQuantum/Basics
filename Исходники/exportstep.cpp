void StepFileWriter::ExportSurface(SSurface *ss, SBezierList *sbl) {
    int i, j, srfid = id;

    // First, we create the untrimmed surface. We always specify a rational
    // B-spline surface (in fact, just a Bezier surface).
    fprintf(f, "#%d=(\n", srfid);
    fprintf(f, "BOUNDED_SURFACE()\n");
    fprintf(f, "B_SPLINE_SURFACE(%d,%d,(", ss->degm, ss->degn);
    for(i = 0; i <= ss->degm; i++) {
        fprintf(f, "(");
        for(j = 0; j <= ss->degn; j++) {
            fprintf(f, "#%d", srfid + 1 + j + i*(ss->degn + 1));
            if(j != ss->degn) fprintf(f, ",");
        }
        fprintf(f, ")");
        if(i != ss->degm) fprintf(f, ",");
    }
    fprintf(f, "),.UNSPECIFIED.,.F.,.F.,.F.)\n");
    fprintf(f, "B_SPLINE_SURFACE_WITH_KNOTS((%d,%d),(%d,%d),",
        (ss->degm + 1), (ss->degm + 1),
        (ss->degn + 1), (ss->degn + 1));
    fprintf(f, "(0.000,1.000),(0.000,1.000),.UNSPECIFIED.)\n");
    fprintf(f, "GEOMETRIC_REPRESENTATION_ITEM()\n");
    fprintf(f, "RATIONAL_B_SPLINE_SURFACE((");
    for(i = 0; i <= ss->degm; i++) {
        fprintf(f, "(");
        for(j = 0; j <= ss->degn; j++) {
            fprintf(f, "%.10f", ss->weight[i][j]);
            if(j != ss->degn) fprintf(f, ",");
        }
        fprintf(f, ")");
        if(i != ss->degm) fprintf(f, ",");
    }
    fprintf(f, "))\n");
    fprintf(f, "REPRESENTATION_ITEM('')\n");
    fprintf(f, "SURFACE()\n");
    fprintf(f, ");\n");

    // The control points for the untrimmed surface.
    for(i = 0; i <= ss->degm; i++) {
        for(j = 0; j <= ss->degn; j++) {
            fprintf(f, "#%d=CARTESIAN_POINT('',(%.10f,%.10f,%.10f));\n",
                srfid + 1 + j + i*(ss->degn + 1),
                CO(ss->ctrl[i][j]));
        }
    }
    fprintf(f, "\n");

    id = srfid + 1 + (ss->degm + 1)*(ss->degn + 1);

    // Now we do the trim curves. We must group each outer loop separately
    // along with its inner faces, so do that now.
    SBezierLoopSetSet sblss;
    ZERO(&sblss);
    SPolygon spxyz;
    ZERO(&spxyz);
    bool allClosed;
    SEdge notClosedAt;
    // We specify a surface, so it doesn't check for coplanarity; and we
    // don't want it to give us any open contours. The polygon and chord
    // tolerance are required, because they are used to calculate the
    // contour directions and determine inner vs. outer contours.
    sblss.FindOuterFacesFrom(sbl, &spxyz, ss,
                             SS.ChordTolMm() / SS.exportScale,
                             &allClosed, &notClosedAt,
                             NULL, NULL,
                             NULL);

    // So in our list of SBezierLoopSet, each set contains at least one loop
    // (the outer boundary), plus any inner loops associated with that outer
    // loop.
    SBezierLoopSet *sbls;
    for(sbls = sblss.l.First(); sbls; sbls = sblss.l.NextAfter(sbls)) {
        SBezierLoop *loop = sbls->l.First();

        List<int> listOfLoops;
        ZERO(&listOfLoops);
        // Create the face outer boundary from the outer loop.
        int fob = ExportCurveLoop(loop, false);
        listOfLoops.Add(&fob);

        // And create the face inner boundaries from any inner loops that
        // lie within this contour.
        loop = sbls->l.NextAfter(loop);
        for(; loop; loop = sbls->l.NextAfter(loop)) {
            int fib = ExportCurveLoop(loop, true);
            listOfLoops.Add(&fib);
        }

        // And now create the face that corresponds to this outer loop
        // and all of its holes.
        int advFaceId = id;
        fprintf(f, "#%d=ADVANCED_FACE('',(", advFaceId);
        int *fb;
        for(fb = listOfLoops.First(); fb; fb = listOfLoops.NextAfter(fb)) {
            fprintf(f, "#%d", *fb);
            if(listOfLoops.NextAfter(fb) != NULL) fprintf(f, ",");
        }

        fprintf(f, "),#%d,.T.);\n", srfid);
        fprintf(f, "\n");
        advancedFaces.Add(&advFaceId);

        id++;
        listOfLoops.Clear();
    }
    sblss.Clear();
    spxyz.Clear();
}