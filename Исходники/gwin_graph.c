void gwinGraphDrawPoints(GHandle gh, const point *points, unsigned count) {
	#define gg	((GGraphObject *)gh)
	unsigned		i;
	const point		*p;

	if (gh->vmt != &graphVMT || !_gwinDrawStart(gh))
		return;

	// Draw the connecting lines
	for(p = points, i = 0; i < count; p++, i++) {
		if ((gh->flags & GGRAPH_FLG_CONNECTPOINTS)) {
			// Draw the line
			lineto(gg, gg->lastx, gg->lasty, p->x, p->y, &gg->style.line);

			// Redraw the previous point because the line may have overwritten it
			if (i == 0)
				pointto(gg, gg->lastx, gg->lasty, &gg->style.point);

		} else
			gh->flags |= GGRAPH_FLG_CONNECTPOINTS;

		// Save this point for next time.
		gg->lastx = p->x;
		gg->lasty = p->y;
	}


	// Draw the points.
	for(p = points, i = 0; i < count; p++, i++)
		pointto(gg, p->x, p->y, &gg->style.point);

	_gwinDrawEnd(gh);
	#undef gg
}