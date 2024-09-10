void
xps_parse_tiling_brush(xps_document *doc, const fz_matrix *ctm, const fz_rect *area,
	char *base_uri, xps_resource *dict, fz_xml *root,
	void (*func)(xps_document*, const fz_matrix*, const fz_rect*, char*, xps_resource*, fz_xml*, void*), void *user)
{
	fz_xml *node;
	struct closure c;

	char *opacity_att;
	char *transform_att;
	char *viewbox_att;
	char *viewport_att;
	char *tile_mode_att;

	fz_xml *transform_tag = NULL;

	fz_matrix transform;
	fz_rect viewbox;
	fz_rect viewport;
	float xstep, ystep;
	float xscale, yscale;
	int tile_mode;

	opacity_att = fz_xml_att(root, "Opacity");
	transform_att = fz_xml_att(root, "Transform");
	viewbox_att = fz_xml_att(root, "Viewbox");
	viewport_att = fz_xml_att(root, "Viewport");
	tile_mode_att = fz_xml_att(root, "TileMode");

	c.base_uri = base_uri;
	c.dict = dict;
	c.root = root;
	c.user = user;
	c.func = func;

	for (node = fz_xml_down(root); node; node = fz_xml_next(node))
	{
		if (!strcmp(fz_xml_tag(node), "ImageBrush.Transform"))
			transform_tag = fz_xml_down(node);
		if (!strcmp(fz_xml_tag(node), "VisualBrush.Transform"))
			transform_tag = fz_xml_down(node);
	}

	xps_resolve_resource_reference(doc, dict, &transform_att, &transform_tag, NULL);

	transform = fz_identity;
	if (transform_att)
		xps_parse_render_transform(doc, transform_att, &transform);
	if (transform_tag)
		xps_parse_matrix_transform(doc, transform_tag, &transform);
	fz_concat(&transform, &transform, ctm);

	viewbox = fz_unit_rect;
	if (viewbox_att)
		xps_parse_rectangle(doc, viewbox_att, &viewbox);

	viewport = fz_unit_rect;
	if (viewport_att)
		xps_parse_rectangle(doc, viewport_att, &viewport);

	if (fabsf(viewport.x1 - viewport.x0) < 0.01f || fabsf(viewport.y1 - viewport.y0) < 0.01f)
		fz_warn(doc->ctx, "not drawing tile for viewport size %.4f x %.4f", viewport.x1 - viewport.x0, viewport.y1 - viewport.y0);
	else if (fabsf(viewbox.x1 - viewbox.x0) < 0.01f || fabsf(viewbox.y1 - viewbox.y0) < 0.01f)
		fz_warn(doc->ctx, "not drawing tile for viewbox size %.4f x %.4f", viewbox.x1 - viewbox.x0, viewbox.y1 - viewbox.y0);

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

	xps_begin_opacity(doc, &transform, area, base_uri, dict, opacity_att, NULL);

	fz_pre_translate(&transform, viewport.x0, viewport.y0);
	fz_pre_scale(&transform, xscale, yscale);
	fz_pre_translate(&transform, -viewbox.x0, -viewbox.y0);

	if (tile_mode != TILE_NONE)
	{
		int x0, y0, x1, y1;
		fz_matrix invctm;
		fz_rect local_area = *area;
		fz_transform_rect(&local_area, fz_invert_matrix(&invctm, &transform));
		/* SumatraPDF: make sure that the intended area is covered */
		{
			fz_point tl;
			fz_irect bbox;
			fz_rect bigview = viewbox;
			bigview.x1 = bigview.x0 + xstep;
			bigview.y1 = bigview.y0 + ystep;
			fz_irect_from_rect(&bbox, fz_transform_rect(&bigview, &transform));
			tl.x = bbox.x0;
			tl.y = bbox.y0;
			fz_transform_point(&tl, &invctm);
			local_area.x0 -= fz_max(tl.x, 0); local_area.x1 += xstep - fz_max(tl.x, 0);
			local_area.y0 -= fz_max(tl.y, 0); local_area.y1 += ystep - fz_max(tl.y, 0);
		}
		x0 = floorf(local_area.x0 / xstep);
		y0 = floorf(local_area.y0 / ystep);
		x1 = ceilf(local_area.x1 / xstep);
		y1 = ceilf(local_area.y1 / ystep);

#ifdef TILE
		/* cf. http://code.google.com/p/sumatrapdf/issues/detail?id=2248 */
		if ((local_area.x1 - local_area.x0) / xstep > 1 || (local_area.y1 - local_area.y0) / ystep > 1)
#else
		if (0)
#endif
		{
			fz_rect bigview = viewbox;
			bigview.x1 = bigview.x0 + xstep;
			bigview.y1 = bigview.y0 + ystep;
			fz_begin_tile(doc->dev, &local_area, &bigview, xstep, ystep, &transform);
			xps_paint_tiling_brush(doc, &transform, &viewbox, tile_mode, &c);
			fz_end_tile(doc->dev);
		}
		else
		{
			int x, y;
			for (y = y0; y < y1; y++)
			{
				for (x = x0; x < x1; x++)
				{
					fz_matrix ttm = transform;
					fz_pre_translate(&ttm, xstep * x, ystep * y);
					xps_paint_tiling_brush(doc, &ttm, &viewbox, tile_mode, &c);
				}
			}
		}
	}
	else
	{
		xps_paint_tiling_brush(doc, &transform, &viewbox, tile_mode, &c);
	}

	xps_end_opacity(doc, base_uri, dict, opacity_att, NULL);
}