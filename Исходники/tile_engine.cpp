bool Tile_Engine::does_bottom_collide(position _pos, position _size) {
	int _y      = floor((_size.y+_pos.y)/32.0);
	int x_start = floor(_pos.x/32.0);
	int x_end   = floor(nextafter(_size.x+_pos.x, _size.x-1))/32;
	for (int i = x_start; i <= x_end; i++) {
		if (getTile(i, _y)->getType() == COLLIDES) {
			return COLLIDES;
		}
	}
	return N_COLLIDES;
}