bool Swan::invalidMove(location next, Floor floor){
	location floorSize = floor.getSize();
	char nextTile = floor.getTile(next.r, next.c);
	if(nextTile == '#'){
		return true;
	}
	if(nextTile == 'D'){
		return true;
	}
	if(nextTile == 'E'){
		return true;
	}
	if(next.r<0 || next.c<0 || next.r>floorSize.r || next.c>floorSize.c){
		return true;
	}
	return false;
}