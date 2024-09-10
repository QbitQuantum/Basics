static bool
png_render_document_to_file(SPDocument *doc, gchar const *filename)
{
    CairoRenderer *renderer;
    CairoRenderContext *ctx;

    sp_document_ensure_up_to_date(doc);

/* Start */
    /* Create new arena */
    SPItem *base = SP_ITEM(sp_document_root(doc));
    NRArena *arena = NRArena::create();
    unsigned dkey = sp_item_display_key_new(1);
    NRArenaItem *root = sp_item_invoke_show(base, arena, dkey, SP_ITEM_SHOW_DISPLAY);
    
    /* Create renderer and context */
    renderer = new CairoRenderer();
    ctx = renderer->createContext();

    /* Render document */
    bool ret = renderer->setupDocument(ctx, doc, TRUE, NULL);
    if (ret) {
        renderer->renderItem(ctx, base);
        ctx->saveAsPng(filename);
        ret = ctx->finish();
    }
    renderer->destroyContext(ctx);

    /* Release arena */
    sp_item_invoke_hide(base, dkey);
    nr_object_unref((NRObject *) arena);
/* end */
    delete renderer;

    return ret;
}