Floor Projectile::checkFloorCollision(int deltax, int deltay) {
	for(int n = 0; n < (int)((mystage -> getFloors()).size()); n++) {
		if(y+deltay <= mystage -> getFloors()[n].y && y+deltay+dy > mystage -> getFloors()[n].y && x+deltax+dx > mystage -> getFloors()[n].x && x+deltax+dx < mystage -> getFloors()[n].x + mystage -> getFloors()[n].length) {
			return mystage -> getFloors()[n];
		}
	}
	return Floor(0, 0, 0, 0, false);
}