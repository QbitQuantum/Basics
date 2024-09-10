static HRESULT shape_run( ME_Context *c, ME_Run *run )
{
    HRESULT hr;
    HFONT old_font;
    int i;

    if (!run->glyphs)
    {
        run->max_glyphs = 1.5 * run->len + 16; /* This is suggested in the uniscribe documentation */
        run->max_glyphs = (run->max_glyphs + 7) & ~7; /* Keep alignment simple */
        get_run_glyph_buffers( run );
    }

    if (run->max_clusters < run->len)
    {
        heap_free( run->clusters );
        run->max_clusters = run->len * 2;
        run->clusters = heap_alloc( run->max_clusters * sizeof(WORD) );
    }

    old_font = ME_SelectStyleFont( c, run->style );
    while (1)
    {
        hr = ScriptShape( c->hDC, &run->style->script_cache, get_text( run, 0 ), run->len, run->max_glyphs,
                          &run->script_analysis, run->glyphs, run->clusters, run->vis_attrs, &run->num_glyphs );
        if (hr != E_OUTOFMEMORY) break;
        if (run->max_glyphs > 10 * run->len) break; /* something has clearly gone wrong */
        run->max_glyphs *= 2;
        get_run_glyph_buffers( run );
    }

    if (SUCCEEDED(hr))
        hr = ScriptPlace( c->hDC, &run->style->script_cache, run->glyphs, run->num_glyphs, run->vis_attrs,
                          &run->script_analysis, run->advances, run->offsets, NULL );

    if (SUCCEEDED(hr))
    {
        for (i = 0, run->nWidth = 0; i < run->num_glyphs; i++)
            run->nWidth += run->advances[i];
    }

    ME_UnselectStyleFont( c, run->style, old_font );

    return hr;
}