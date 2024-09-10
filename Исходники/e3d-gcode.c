  void plot_loops (polygon_t * p, poly_dim_t speed, double flowrate, int dir)
  {
    if (!p)
      return;
    poly_contour_t *c;
    for (c = p->contours; c; c = c->next)
      if (c->vertices && (!dir || dir == c->dir))
	{
	  poly_vertex_t *v = c->vertices;
	  poly_dim_t d = sqrtl ((px - v->x) * (px - v->x) + (py - v->y) * (py - v->y));
	  if (pe && d > layer * 5)
	    {			// hop and pull back extruder while moving
	      move (px, py, z + hop, back);
	      move (v->x, v->y, z + hop, back);
	    }
	  move (v->x, v->y, z, 0);
	  for (v = c->vertices->next; v; v = v->next)
	    extrude (v->x, v->y, z, speed, flowrate);
	  v = c->vertices;
	  extrude (v->x, v->y, z, speed, flowrate);
	}
  }