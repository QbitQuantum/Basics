CTile* CMainMap::getTileFromScreen(long xScreen, long yScreen) {
	
	CTile* retTile = NULL;
	long tx, ty;

	if (xScreen >= 0 && yScreen >= 0) {
		
		ldiv_t ldivresult;

		ldivresult = ldiv(xScreen+1, m_tileWidth);
		tx = ldivresult.quot;

		ldivresult = ldiv(yScreen+1, m_tileHeight);
		ty = ldivresult.quot;

		ostringstream ostr;
		ostr << "\ntx: " << tx << ", ty: " << ty << "\n";
		fprintf(stderr, ostr.str().c_str());

		retTile = getTileFromMap(tx, ty);
	}
	else {
		fprintf(stderr, "DataErr: CTile::getTile - x or y value <0!!\n");
	}

	return retTile;
}