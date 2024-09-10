 Rectf get_tile_bbox(int x, int y) const
 { return Rectf(get_tile_position(x, y), get_tile_position(x+1, y+1)); }