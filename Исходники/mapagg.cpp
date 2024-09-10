template<class VertexSource> int renderPolygonHatches(imageObj *img,VertexSource &clipper, colorObj *color)
{
  if(img->format->renderer == MS_RENDER_WITH_AGG) {
    AGG2Renderer *r = AGG_RENDERER(img);
    r->m_rasterizer_aa_gamma.reset();
    r->m_rasterizer_aa_gamma.filling_rule(mapserver::fill_non_zero);
    r->m_rasterizer_aa_gamma.add_path(clipper);
    r->m_renderer_scanline.color(aggColor(color));
    mapserver::render_scanlines(r->m_rasterizer_aa_gamma, r->sl_poly, r->m_renderer_scanline);
  } else {
    shapeObj shape;
    msInitShape(&shape);
    int allocated = 20;
    lineObj line;
    shape.line = &line;
    shape.numlines = 1;
    shape.line[0].point = (pointObj*)msSmallCalloc(allocated,sizeof(pointObj));
    shape.line[0].numpoints = 0;
    double x=0,y=0;
    unsigned int cmd;
    clipper.rewind(0);
    while((cmd = clipper.vertex(&x,&y)) != mapserver::path_cmd_stop) {
      switch(cmd) {
        case mapserver::path_cmd_line_to:
          if(shape.line[0].numpoints == allocated) {
            allocated *= 2;
            shape.line[0].point = (pointObj*)msSmallRealloc(shape.line[0].point, allocated*sizeof(pointObj));
          }
          shape.line[0].point[shape.line[0].numpoints].x = x;
          shape.line[0].point[shape.line[0].numpoints].y = y;
          shape.line[0].numpoints++;
          break;
        case mapserver::path_cmd_move_to:
          shape.line[0].point[0].x = x;
          shape.line[0].point[0].y = y;
          shape.line[0].numpoints = 1;
          break;
        case mapserver::path_cmd_end_poly|mapserver::path_flags_close:
          if(shape.line[0].numpoints > 2) {
            if(UNLIKELY(MS_FAILURE == MS_IMAGE_RENDERER(img)->renderPolygon(img,&shape,color))) {
              free(shape.line[0].point);
              return MS_FAILURE;
            }
          }
          break;
        default:
          assert(0); //WTF?
      }
    }
    free(shape.line[0].point);
  }
  return MS_SUCCESS;
}