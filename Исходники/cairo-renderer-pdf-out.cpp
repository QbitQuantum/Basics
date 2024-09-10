static bool
pdf_render_document_to_file(SPDocument *doc, gchar const *filename, unsigned int level,
                            bool texttopath, bool omittext, bool filtertobitmap, int resolution,
                            const gchar * const exportId, bool exportDrawing, bool exportCanvas, float bleedmargin_px)
{
    doc->ensureUpToDate();

/* Start */

    SPItem *base = NULL;

    bool pageBoundingBox = TRUE;
    if (exportId && strcmp(exportId, "")) {
        // we want to export the given item only
        base = SP_ITEM(doc->getObjectById(exportId));
        pageBoundingBox = exportCanvas;
    }
    else {
        // we want to export the entire document from root
        base = doc->getRoot();
        pageBoundingBox = !exportDrawing;
    }

    if (!base) {
        return false;
    }
    
    /* Create new arena */
    Inkscape::Drawing drawing;
    drawing.setExact(true);
    unsigned dkey = SPItem::display_key_new(1);
    base->invoke_show(drawing, dkey, SP_ITEM_SHOW_DISPLAY);

    /* Create renderer and context */
    CairoRenderer *renderer = new CairoRenderer();
    CairoRenderContext *ctx = renderer->createContext();
    ctx->setPDFLevel(level);
    ctx->setTextToPath(texttopath);
    ctx->setOmitText(omittext);
    ctx->setFilterToBitmap(filtertobitmap);
    ctx->setBitmapResolution(resolution);

    bool ret = ctx->setPdfTarget (filename);
    if(ret) {
        /* Render document */
        ret = renderer->setupDocument(ctx, doc, pageBoundingBox, bleedmargin_px, base);
        if (ret) {
            renderer->renderItem(ctx, base);
            ret = ctx->finish();
        }
    }

    base->invoke_hide(dkey);

    renderer->destroyContext(ctx);
    delete renderer;

    return ret;
}