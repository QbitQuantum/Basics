void
xps_parse_tiling_brush(xps_context *ctx, fz_matrix ctm, fz_rect area,
	char *base_uri, xps_resource *dict, xml_element *root,
	void (*func)(xps_context*, fz_matrix, fz_rect, char*, xps_resource*, xml_element*, void*), void *user)
{
	xml_element *node;
	struct closure c;

	char *opacity_att;
	char *transform_att;
	char *viewbox_att;
	char *viewport_att;
	char *tile_mode_att;
	char *viewbox_units_att;
	char *viewport_units_att;

	xml_element *transform_tag = NULL;

	fz_matrix transform;
	fz_rect viewbox;
	fz_rect viewport;
	float xstep, ystep;
	float xscale, yscale;
	int tile_mode;

	opacity_att = xml_att(root, "Opacity");
	transform_att = xml_att(root, "Transform");
	viewbox_att = xml_att(root, "Viewbox");
	viewport_att = xml_att(root, "Viewport");
	tile_mode_att = xml_att(root, "TileMode");
	viewbox_units_att = xml_att(root, "ViewboxUnits");
	viewport_units_att = xml_att(root, "ViewportUnits");

	c.base_uri = base_uri;
	c.dict = dict;
	c.root = root;
	c.user = user;
	c.func = func;

	for (node = xml_down(root); node; node = xml_next(node))
	{
		if (!strcmp(xml_tag(node), "ImageBrush.Transform"))
			transform_tag = xml_down(node);
		if (!strcmp(xml_tag(node), "VisualBrush.Transform"))
			transform_tag = xml_down(node);
	}

	xps_resolve_resource_reference(ctx, dict, &transform_att, &transform_tag, NULL);

	transform = fz_identity;
	if (transform_att)
		xps_parse_render_transform(ctx, transform_att, &transform);
	if (transform_tag)
		xps_parse_matrix_transform(ctx, transform_tag, &transform);
	ctm = fz_concat(transform, ctm);

	viewbox = fz_unit_rect;
	if (viewbox_att)
		xps_parse_rectangle(ctx, viewbox_att, &viewbox);

	viewport = fz_unit_rect;
	if (viewport_att)
		xps_parse_rectangle(ctx, viewport_att, &viewport);

	/* some sanity checks on the viewport/viewbox size */
	if (fabsf(viewport.x1 - viewport.x0) < 0.01f) return;
	if (fabsf(viewport.y1 - viewport.y0) < 0.01f) return;
	if (fabsf(viewbox.x1 - viewbox.x0) < 0.01f) return;
	if (fabsf(viewbox.y1 - viewbox.y0) < 0.01f) return;

	xstep = viewbox.x1 - viewbox.x0;
	ystep = viewbox.y1 - viewbox.y0;

	xscale = (viewport.x1 - viewport.x0) / xstep;
	yscale = (viewport.y1 - viewport.y0) / ystep;

	tile_mode = TILE_NONE;
	if (tile_mode_att)
	{
		if (!strcmp(tile_mode_att, "None"))
			tile_mode = TILE_NONE;
		if (!strcmp(tile_mode_att, "Tile"))
			tile_mode = TILE_TILE;
		if (!strcmp(tile_mode_att, "FlipX"))
			tile_mode = TILE_FLIP_X;
		if (!strcmp(tile_mode_att, "FlipY"))
			tile_mode = TILE_FLIP_Y;
		if (!strcmp(tile_mode_att, "FlipXY"))
			tile_mode = TILE_FLIP_X_Y;
	}

	if (tile_mode == TILE_FLIP_X || tile_mode == TILE_FLIP_X_Y)
		xstep *= 2;
	if (tile_mode == TILE_FLIP_Y || tile_mode == TILE_FLIP_X_Y)
		ystep *= 2;

	xps_begin_opacity(ctx, ctm, area, base_uri, dict, opacity_att, NULL);

	ctm = fz_concat(fz_translate(viewport.x0, viewport.y0), ctm);
	ctm = fz_concat(fz_scale(xscale, yscale), ctm);
	ctm = fz_concat(fz_translate(-viewbox.x0, -viewbox.y0), ctm);

	if (tile_mode != TILE_NONE)
	{
		int x0, y0, x1, y1;
		fz_matrix invctm = fz_invert_matrix(ctm);
		area = fz_transform_rect(invctm, area);
		x0 = floorf(area.x0 / xstep);
		y0 = floorf(area.y0 / ystep);
		x1 = ceilf(area.x1 / xstep);
		y1 = ceilf(area.y1 / ystep);

#ifdef TILE
		if ((x1 - x0) * (y1 - y0) > 1)
#else
		if (0)
#endif
		{
			fz_rect bigview = viewbox;
			bigview.x1 = bigview.x0 + xstep;
			bigview.y1 = bigview.y0 + ystep;
			fz_begin_tile(ctx->dev, area, bigview, xstep, ystep, ctm);
			xps_paint_tiling_brush(ctx, ctm, viewbox, tile_mode, &c);
			fz_end_tile(ctx->dev);
		}
		else
		{
			int x, y;
			for (y = y0; y < y1; y++)
			{
				for (x = x0; x < x1; x++)
				{
					fz_matrix ttm = fz_concat(fz_translate(xstep * x, ystep * y), ctm);
					xps_paint_tiling_brush(ctx, ttm, viewbox, tile_mode, &c);
				}
			}
		}
	}
	else
	{
		xps_paint_tiling_brush(ctx, ctm, viewbox, tile_mode, &c);
	}

	xps_end_opacity(ctx, base_uri, dict, opacity_att, NULL);
}