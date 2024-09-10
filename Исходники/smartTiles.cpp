GLTile *smartTile(TGLmap *map, int x, int y, float wleft, float wup, float wright, float wdown, List<GLTile> *tiles)
{
	GLTile *best = 0;
	float best_score = 0;
	List<GLTile> l;
	GLTile *tile = 0;
	GLTile *tile_left = 0;
	GLTile *tile_up = 0;
	GLTile *tile_right = 0;
	GLTile *tile_down = 0;
	Uint32 pixel;
	Uint8 r,g,b,a;
	Uint32 pixel2;;
	Uint8 r2,g2,b2,a2;
	int windowSize = 4;
	
	if (x>0) tile_left = map->getFGTile((x-1)+y*map->get_fg_dx()); else wleft = 0;
	if (y>0) tile_up = map->getFGTile((x)+(y-1)*map->get_fg_dx()); else wup = 0;
	if (x<map->get_fg_dx()-1) tile_right = map->getFGTile((x+1)+y*map->get_fg_dx()); else wright = 0;
	if (y<map->get_fg_dy()-1) tile_down = map->getFGTile((x)+(y+1)*map->get_fg_dx()); else wdown = 0;
	
	l.Instance(*tiles);
	
	/*
	 #ifdef __DEBUG_MESSAGES
	 output_debug_message("smartTile %i,%i with (%i,%i,%i,%i)\n",x,y,l.PositionRef(tile_left), l.PositionRef(tile_up), l.PositionRef(tile_right), l.PositionRef(tile_down));
	 #endif	
	 */
	
	// score of the empty tile:
	{
		float score_left = 0;
		float score_up = 0;
		float score_right = 0;
		float score_down = 0;
		float score = 0;
		if (wleft>0) score_left = smartTileScore(0,tile_left,0,windowSize);
		if (wup>0) score_up = smartTileScore(0,tile_up,1,windowSize);
		if (wright>0) score_right = smartTileScore(0,tile_right,2,windowSize);
		if (wdown>0) score_down = smartTileScore(0,tile_down,3,windowSize);
		best = 0;
		best_score += wleft*score_left + wup*score_up + wright*score_right + wdown*score_down;
	}
	
	l.Rewind();
	while(l.Iterate(tile)) {		
		float score_left = 0;
		float score_up = 0;
		float score_right = 0;
		float score_down = 0;
		float score = 0;
		if (wleft>0) score_left = smartTileScore(tile,tile_left,0,windowSize);
		if (wup>0) score_up = smartTileScore(tile,tile_up,1,windowSize);
		if (wright>0) score_right = smartTileScore(tile,tile_right,2,windowSize);
		if (wdown>0) score_down = smartTileScore(tile,tile_down,3,windowSize);

		score += wleft*score_left + wup*score_up + wright*score_right + wdown*score_down;
		
		if (score<best_score) {
			best = tile;
			best_score = score;
		} else if (score==best_score) {
			// select the tile with least number of non-zero pixels:
			if (smartTileNumberOfNonZeroPizels(best)>smartTileNumberOfNonZeroPizels(tile)) {
				best = tile;
			}
		}
	}
	
	return best;
}