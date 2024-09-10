static void itemview_rebuildAttr( UThread* ut, GItemView* ep,
                                  const UBuffer* items, int page )
{
#define MAX_ITEM_TRIS   400
#define MAX_DEC_TRIS    100
#define TRI_ATTR_BYTES  (3 * AttrCount * sizeof(GLfloat))
    DrawContext dc;
    UBlockIter bi;
    UBlockIter layout;
    UBuffer* fcBuf;
    const UCell* loStart;
    UCell* cell;
    float* attr;
    int bsize;
    int height = ep->itemHeight;
    int caOffset = items->used + DECORATION_GROUPS;


    // Reserve triangles for each item.
    ur_binReserve( &glEnv.tmpBin,
           (MAX_DEC_TRIS + (items->used * MAX_ITEM_TRIS)) * TRI_ATTR_BYTES );
    attr = glEnv.tmpBin.ptr.f;

    // Reserve first & count arrays.  fcBuf->used tracks the number of items
    // and view decorations, which is half the number of integers used for
    // both arrays.
    fcBuf = &ep->fc[ page ];
    ur_arrReserve( fcBuf, caOffset * 2 );
    fcBuf->used = 0;

    dc.attr = attr;
    dc.drawFirst = 0;
    dc.penX = 0.0;

#if 1
    // Build selected background tris.
    dc.drawCount = 0;

    if( ep->selRow > -1 )
    {
        dc.color[0] = 1.0;
        dc.color[1] = dc.color[2] = 0.0;
        dc.penY = ep->wid.area.h;

        cell = glEnv.guiStyle + CI_STYLE_AREA;
        //ur_setId(cell, UT_COORD)
        cell->coord.len = 4;
        cell->coord.n[0] = 0;
        cell->coord.n[1] = (ep->selRow + 1) * -height;
        cell->coord.n[2] = ep->itemWidth;
        cell->coord.n[3] = height;

        layout.buf = ur_buffer( ep->selectBgBlkN );
        layout.it  = layout.buf->ptr.cell;
        layout.end = layout.it + layout.buf->used;

        if( ! itemview_parse( &dc, ut, &layout, (GWidget*) ep ) )
        {
            boron_reset(ut);
            printf( "KR itemview_parse failed\n" );
        }
    }

    fcBuf->ptr.i[ fcBuf->used ] = dc.drawFirst;
    fcBuf->ptr.i[ fcBuf->used + caOffset ] = dc.drawCount;
    ++fcBuf->used;

    dc.attr = attr + MAX_DEC_TRIS * 3 * AttrCount;
    dc.drawFirst = MAX_DEC_TRIS * 3;
#endif

    dc.penY = ep->wid.area.h;


    // Setup the data item and layout iterators.
    bi.it  = items->ptr.cell;
    bi.end = bi.it + items->used;

    layout.buf = ur_buffer( ep->layoutBlkN );
    loStart    = layout.buf->ptr.cell;
    layout.end = loStart + layout.buf->used;

    ur_foreach( bi )
    {
        // Set item word to current data value.
        cell = ur_ctxCell( ur_buffer( ep->bindCtxN ), 0 );
        *cell = *bi.it;

        dc.drawCount = 0;
        dc.color[0] = 1.0;
        dc.color[1] = dc.color[2] = 0.0;
        dc.penY -= height;

        layout.it = loStart;
        if( ! itemview_parse( &dc, ut, &layout, (GWidget*) ep ) )
        {
            boron_reset(ut);
            printf( "KR itemview_parse failed\n" );
        }

        //printf( "KR fc %d,%d\n", dc.drawFirst, dc.drawCount );

        fcBuf->ptr.i[ fcBuf->used ] = dc.drawFirst;
        fcBuf->ptr.i[ fcBuf->used + caOffset ] = dc.drawCount;
        ++fcBuf->used;

        dc.drawFirst += dc.drawCount;
        //dc.drawFirst += MAX_ITEM_TRIS;
    }

    assert( fcBuf->used == caOffset );


    // Transfer vertex data to GPU.
    bsize = dc.drawFirst * TRI_ATTR_BYTES;
    if( ep->vboSize[ page ] < bsize )
    {
        ep->vboSize[ page ] = bsize;
        glBufferData( GL_ARRAY_BUFFER, bsize, attr, GL_STATIC_DRAW );
    }
    else
    {
        float* abuf = (float*) glMapBuffer( GL_ARRAY_BUFFER, GL_WRITE_ONLY );
        if( abuf )
        {
            memCpy( abuf, attr, bsize );
            glUnmapBuffer( GL_ARRAY_BUFFER );
        }
    }
}