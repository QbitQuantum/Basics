bool
SvgWindow::glDraw (const GLMatrix     &transform,
		   const GLWindowPaintAttrib &attrib,
		   const CompRegion   &region,
		   unsigned int       mask)
{
    bool status = gWindow->glDraw (transform, attrib, region, mask);

    if (!status)
	return status;

    const CompRegion &reg = (mask & PAINT_WINDOW_TRANSFORMED_MASK) ?
			    infiniteRegion : region;

    if (context && reg.numRects ())
    {
	GLTexture::MatrixList matrix (1);
	int		      x1, y1, x2, y2;
	CompRect              rect = context->box.boundingRect ();

	x1 = MIN (rect.x1 (), sScreen->zoom.x1 ());
	y1 = MIN (rect.y1 (), sScreen->zoom.y1 ());
	x2 = MAX (rect.x2 (), sScreen->zoom.x2 ());
	y2 = MAX (rect.y2 (), sScreen->zoom.y2 ());

	rect.setGeometry (x1, y1, x2 - x1, y2 - y1);

	for (unsigned int i = 0; i < context->texture[0].textures.size (); i++)
	{
	    matrix[0] = context->texture[0].matrices[i];

	    gWindow->vertexBuffer ()->begin ();
	    gWindow->glAddGeometry (matrix, context->box, reg);
	    gWindow->vertexBuffer ()->end ();

	    if (mask & PAINT_WINDOW_TRANSLUCENT_MASK)
		mask |= PAINT_WINDOW_BLEND_MASK;

	    gWindow->glDrawTexture (context->texture[0].textures[i], transform,
	                            attrib, mask);

	    if (rect.width () > 0 && rect.height () > 0)
	    {
		float    xScale, yScale;
		float    dx, dy;
		int      width, height;

		rect.setGeometry (rect.x1 () - 1,
				  rect.y1 () - 1,
				  rect.width () + 1,
				  rect.height () + 1);

		xScale = screen->width  () /
		         (float) (sScreen->zoom.width ());
		yScale = screen->height () /
		         (float) (sScreen->zoom.height ());

		dx = rect.width ();
		dy = rect.height ();

		width  = dx * xScale + 0.5f;
		height = dy * yScale + 0.5f;

		if (rect   != context->rect          ||
		    width  != context->size.width () ||
		    height != context->size.height ())
		{
		    float x1, y1, x2, y2;

		    context->rect = rect;
		    context->size.setWidth (width);
		    context->size.setHeight (height);

		    dx = context->box.boundingRect ().width ();
		    dy = context->box.boundingRect ().height ();

		    x1 = (rect.x1 () - context->box.boundingRect ().x ()) / dx;
		    y1 = (rect.y1 () - context->box.boundingRect ().y ()) / dy;
		    x2 = (rect.x2 () - context->box.boundingRect ().x ()) / dx;
		    y2 = (rect.y2 () - context->box.boundingRect ().y ()) / dy;

		    finiTexture (context->texture[1]);

		    if (initTexture (context->source, context->texture[1],
				     context->size))
		    {
			renderSvg (context->source, context->texture[1],
				   context->size, x1, y1, x2, y2);

			updateSvgMatrix ();
		    }
		}

		for (unsigned int j = 0; j < context->texture[1].textures.size (); j++)
		{
		    GLTexture::Filter saveFilter;
		    CompRegion        r (rect);

		    matrix[0] = context->texture[1].matrices[j];

		    saveFilter = gScreen->filter (SCREEN_TRANS_FILTER);
		    gScreen->setFilter (SCREEN_TRANS_FILTER, GLTexture::Good);

		    gWindow->vertexBuffer ()->begin ();
		    gWindow->glAddGeometry (matrix, r, reg);
		    gWindow->vertexBuffer ()->end ();

		    gWindow->glDrawTexture (context->texture[1].textures[j],
					    transform, attrib, mask);

		    gScreen->setFilter (SCREEN_TRANS_FILTER, saveFilter);
		}
	    }
	    else if (context->texture[1].size.width ())
	    {
		finiTexture (context->texture[1]);
		initTexture (source, context->texture[1], CompSize ());

		memset (&context->rect, 0, sizeof (BoxRec));
		context->size.setWidth (0);
		context->size.setHeight (0);
	    }
	}
    }

    return status;
}