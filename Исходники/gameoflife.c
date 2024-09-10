void pfprint(field_t pf) {
	coord_t x,y;
	for(y=YSIZE; y--;) {
		for(x=XSIZE; x--;) {
			setpixel((pixel){x,y},getcell(pf,x,y)*3);
		}
	}
}