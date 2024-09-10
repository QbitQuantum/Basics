void
EditorInputCenter::update_tile_selection() {
  Rectf select = tile_drag_rect();
  auto tiles = Editor::current()->tileselect.tiles.get();
  auto tilemap = dynamic_cast<TileMap*>(Editor::current()->layerselect.selected_tilemap);
  if ( !tilemap ) {
    return;
  }

  tiles->tiles.clear();
  tiles->width = select.get_width() + 1;
  tiles->height = select.get_height() + 1;

  int w = tilemap->get_width();
  int h = tilemap->get_height();
  for (int y = select.p1.y; y <= select.p2.y; y++) {
    for (int x = select.p1.x; x <= select.p2.x; x++) {
      if ( x < 0 || y < 0 || x >= w || y >= h) {
        tiles->tiles.push_back(0);
      } else {
        tiles->tiles.push_back(tilemap->get_tile_id(x, y));
      }
    }
  }
}