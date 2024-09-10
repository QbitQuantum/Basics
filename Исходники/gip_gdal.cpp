    //! Warp a single image into output image with cutline
    GeoImage& WarpToImage(const GeoImage& imgin, GeoImage& imgout, GDALWarpOptions *psWarpOptions, OGRGeometry* site) {
        if (Options::Verbose() > 2) cout << imgin.Basename() << " warping into " << imgout.Basename() << " " << std::flush;

        // Create cutline transform to pixel coordinates
        char **papszOptionsCutline = NULL;
        papszOptionsCutline = CSLSetNameValue( papszOptionsCutline, "DST_SRS", imgout.Projection().c_str() );
        papszOptionsCutline = CSLSetNameValue( papszOptionsCutline, "INSERT_CENTER_LONG", "FALSE" );
        CutlineTransformer oTransformer;

        oTransformer.hSrcImageTransformer = GDALCreateGenImgProjTransformer2( imgin.GetGDALDataset(), NULL, papszOptionsCutline );
        OGRGeometry* site_t = site->clone();
        site_t->transform(&oTransformer);

        //psWarpOptions->hCutline = site_t;
        char* wkt;
        site_t->exportToWkt(&wkt);
        psWarpOptions->papszWarpOptions = CSLSetNameValue(psWarpOptions->papszWarpOptions,"CUTLINE", wkt);

        // set options
        //psWarpOptions->papszWarpOptions = CSLDuplicate(papszOptions);
        psWarpOptions->hSrcDS = imgin.GetGDALDataset();
        psWarpOptions->pTransformerArg =
            GDALCreateGenImgProjTransformer( imgin.GetGDALDataset(), imgin.GetGDALDataset()->GetProjectionRef(),
                                            imgout.GetGDALDataset(), imgout.GetGDALDataset()->GetProjectionRef(), TRUE, 0.0, 0 );
        psWarpOptions->pfnTransformer = GDALGenImgProjTransform;

        // Perform transformation
        GDALWarpOperation oOperation;
        oOperation.Initialize( psWarpOptions );
        //if (Options::Verbose() > 3) cout << "Error: " << CPLGetLastErrorMsg() << endl;
        oOperation.ChunkAndWarpMulti( 0, 0, imgout.XSize(), imgout.YSize() );

        // destroy things
        GDALDestroyGenImgProjTransformer( psWarpOptions->pTransformerArg );
        GDALDestroyGenImgProjTransformer( oTransformer.hSrcImageTransformer );
        CSLDestroy( papszOptionsCutline );
        OGRGeometryFactory::destroyGeometry(site_t);
        return imgout;
    }