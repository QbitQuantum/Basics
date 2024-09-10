float BKE_brush_sample_masktex(
    const Scene *scene, Brush *br, const float point[2], const int thread, struct ImagePool *pool)
{
  UnifiedPaintSettings *ups = &scene->toolsettings->unified_paint_settings;
  MTex *mtex = &br->mask_mtex;
  float rgba[4], intensity;

  if (!mtex->tex) {
    return 1.0f;
  }
  if (mtex->brush_map_mode == MTEX_MAP_MODE_STENCIL) {
    float rotation = -mtex->rot;
    float point_2d[2] = {point[0], point[1]};
    float x, y;
    float co[3];

    x = point_2d[0] - br->mask_stencil_pos[0];
    y = point_2d[1] - br->mask_stencil_pos[1];

    if (rotation > 0.001f || rotation < -0.001f) {
      const float angle = atan2f(y, x) + rotation;
      const float flen = sqrtf(x * x + y * y);

      x = flen * cosf(angle);
      y = flen * sinf(angle);
    }

    if (fabsf(x) > br->mask_stencil_dimension[0] || fabsf(y) > br->mask_stencil_dimension[1]) {
      zero_v4(rgba);
      return 0.0f;
    }
    x /= (br->mask_stencil_dimension[0]);
    y /= (br->mask_stencil_dimension[1]);

    co[0] = x;
    co[1] = y;
    co[2] = 0.0f;

    externtex(
        mtex, co, &intensity, rgba, rgba + 1, rgba + 2, rgba + 3, thread, pool, false, false);
  }
  else {
    float rotation = -mtex->rot;
    float point_2d[2] = {point[0], point[1]};
    float x = 0.0f, y = 0.0f; /* Quite warnings */
    float invradius = 1.0f;   /* Quite warnings */
    float co[3];

    if (mtex->brush_map_mode == MTEX_MAP_MODE_VIEW) {
      /* keep coordinates relative to mouse */

      rotation += ups->brush_rotation_sec;

      x = point_2d[0] - ups->mask_tex_mouse[0];
      y = point_2d[1] - ups->mask_tex_mouse[1];

      /* use pressure adjusted size for fixed mode */
      invradius = 1.0f / ups->pixel_radius;
    }
    else if (mtex->brush_map_mode == MTEX_MAP_MODE_TILED) {
      /* leave the coordinates relative to the screen */

      /* use unadjusted size for tiled mode */
      invradius = 1.0f / BKE_brush_size_get(scene, br);

      x = point_2d[0];
      y = point_2d[1];
    }
    else if (mtex->brush_map_mode == MTEX_MAP_MODE_RANDOM) {
      rotation += ups->brush_rotation_sec;
      /* these contain a random coordinate */
      x = point_2d[0] - ups->mask_tex_mouse[0];
      y = point_2d[1] - ups->mask_tex_mouse[1];

      invradius = 1.0f / ups->pixel_radius;
    }

    x *= invradius;
    y *= invradius;

    /* it is probably worth optimizing for those cases where
     * the texture is not rotated by skipping the calls to
     * atan2, sqrtf, sin, and cos. */
    if (rotation > 0.001f || rotation < -0.001f) {
      const float angle = atan2f(y, x) + rotation;
      const float flen = sqrtf(x * x + y * y);

      x = flen * cosf(angle);
      y = flen * sinf(angle);
    }

    co[0] = x;
    co[1] = y;
    co[2] = 0.0f;

    externtex(
        mtex, co, &intensity, rgba, rgba + 1, rgba + 2, rgba + 3, thread, pool, false, false);
  }

  CLAMP(intensity, 0.0f, 1.0f);

  switch (br->mask_pressure) {
    case BRUSH_MASK_PRESSURE_CUTOFF:
      intensity = ((1.0f - intensity) < ups->size_pressure_value) ? 1.0f : 0.0f;
      break;
    case BRUSH_MASK_PRESSURE_RAMP:
      intensity = ups->size_pressure_value + intensity * (1.0f - ups->size_pressure_value);
      break;
    default:
      break;
  }

  return intensity;
}