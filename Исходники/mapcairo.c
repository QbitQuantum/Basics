int msPopulateRendererVTableCairoRaster( rendererVTableObj *renderer ) {
#ifdef USE_CAIRO
    renderer->supports_pixel_buffer=1;
    renderer->supports_transparent_layers = 0;
    renderer->default_transform_mode = MS_TRANSFORM_SIMPLIFY;
    initializeCache(&MS_RENDERER_CACHE(renderer));
    renderer->startLayer = startLayerRasterCairo;
    renderer->endLayer = closeLayerRasterCairo;
    renderer->renderLineTiled = NULL;
    renderer->renderLine=&renderLineCairo;
    renderer->createImage=&createImageCairo;
    renderer->saveImage=&saveImageCairo;
    renderer->getRasterBufferHandle=&getRasterBufferHandleCairo;
    renderer->getRasterBufferCopy=&getRasterBufferCopyCairo;
    renderer->renderPolygon=&renderPolygonCairo;
    renderer->renderGlyphs=&renderGlyphsCairo;
    renderer->freeImage=&freeImageCairo;
    renderer->renderEllipseSymbol = &renderEllipseSymbolCairo;
    renderer->renderVectorSymbol = &renderVectorSymbolCairo;
    renderer->renderTruetypeSymbol = &renderTruetypeSymbolCairo;
    renderer->renderPixmapSymbol = &renderPixmapSymbolCairo;
    renderer->mergeRasterBuffer = &mergeRasterBufferCairo;
    renderer->getTruetypeTextBBox = &getTruetypeTextBBoxCairo;
    renderer->renderTile = &renderTileCairo;
    renderer->loadImageFromFile = &msLoadMSRasterBufferFromFile;
    renderer->renderPolygonTiled = &renderPolygonTiledCairo;
    renderer->freeSymbol = &freeSymbolCairo;
    renderer->cleanup = &cleanupCairo;
    return MS_SUCCESS;
#else
    msSetError(MS_MISCERR, "Cairo Driver requested but is not built in", 
            "msPopulateRendererVTableCairoRaster()");
    return MS_FAILURE;
#endif
}