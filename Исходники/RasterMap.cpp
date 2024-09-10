void
RasterMap::ScanLine(const GeoPoint &start, const GeoPoint &end,
                    short *buffer, unsigned size, bool interpolate) const
{
  assert(buffer != NULL);
  assert(size > 0);

  const short invalid = RasterBuffer::TERRAIN_INVALID;

  const fixed total_distance = start.Distance(end);
  if (!positive(total_distance)) {
    std::fill(buffer, buffer + size, invalid);
    return;
  }

  /* clip the line to the map bounds */

  GeoPoint clipped_start = start, clipped_end = end;
  const GeoClip clip(GetBounds());
  if (!clip.ClipLine(clipped_start, clipped_end)) {
    std::fill(buffer, buffer + size, invalid);
    return;
  }

  fixed clipped_start_distance =
    std::max(clipped_start.Distance(start), fixed(0));
  fixed clipped_end_distance =
    std::max(clipped_end.Distance(start), fixed(0));

  /* calculate the offsets of the clipped range within the buffer */

  unsigned clipped_start_offset =
    (unsigned)(size * clipped_start_distance / total_distance);
  unsigned clipped_end_offset =
    uround(size * clipped_end_distance / total_distance);
  if (clipped_end_offset > size)
    clipped_end_offset = size;
  if (clipped_start_offset + 2 > clipped_end_offset) {
    std::fill(buffer, buffer + size, invalid);
    return;
  }

  assert(clipped_start_offset < size);
  assert(clipped_end_offset <= size);

  /* fill the two regions which are outside the map  */

  std::fill(buffer, buffer + clipped_start_offset, invalid);
  std::fill(buffer + clipped_end_offset, buffer + size, invalid);

  /* now scan the middle part which is within the map */

  const unsigned max_x = raster_tile_cache.GetFineWidth();
  const unsigned max_y = raster_tile_cache.GetFineHeight();

  RasterLocation raster_start = projection.ProjectFine(clipped_start);
  if (raster_start.x >= max_x)
    raster_start.x = max_x - 1;
  if (raster_start.y >= max_y)
    raster_start.y = max_y - 1;

  RasterLocation raster_end = projection.ProjectFine(clipped_end);
  if (raster_end.x >= max_x)
    raster_end.x = max_x - 1;
  if (raster_end.y >= max_y)
    raster_end.y = max_y - 1;

  raster_tile_cache.ScanLine(raster_start, raster_end,
                             buffer + clipped_start_offset,
                             clipped_end_offset - clipped_start_offset,
                             interpolate);
}