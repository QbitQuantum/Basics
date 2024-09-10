bool Zone::ParsePolygonString(const char *poly_string, Polygon &polygon) {
  Debug(3, "Parsing polygon string '%s'", poly_string);

  char *str_ptr = new char[strlen(poly_string)+1];
  char *str = str_ptr;
  strcpy(str, poly_string);

  char *ws;
  int n_coords = 0;
  int max_n_coords = strlen(str)/4;
  Coord *coords = new Coord[max_n_coords];
  while( true ) {
    if ( *str == '\0' ) {
      break;
    }
    ws = strchr(str, ' ');
    if ( ws ) {
      *ws = '\0';
    }
    char *cp = strchr(str, ',');
    if ( !cp ) {
      Error("Bogus coordinate %s found in polygon string", str);
      delete[] coords;
      delete[] str_ptr;
      return false;
    } else {
      *cp = '\0';
      char *xp = str;
      char *yp = cp+1;

      int x = atoi(xp);
      int y = atoi(yp);

      Debug(3, "Got coordinate %d,%d from polygon string", x, y);
#if 0
			if ( x < 0 )
				x = 0;
			else if ( x >= width )
				x = width-1;
			if ( y < 0 )
				y = 0;
			else if ( y >= height )
				y = height-1;
#endif
			coords[n_coords++] = Coord( x, y );
		}
		if ( ws )
			str = ws+1;
		else
			break;
	}
	polygon = Polygon(n_coords, coords);

	Debug(3, "Successfully parsed polygon string");
	//printf( "Area: %d\n", pg.Area() );
	//printf( "Centre: %d,%d\n", pg.Centre().X(), pg.Centre().Y() );

	delete[] coords;
	delete[] str_ptr;

	return true;
}