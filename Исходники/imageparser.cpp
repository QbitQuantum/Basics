  void defineShapes(Shapes *S) {
    // simplify contours
    vector<vector<Point> > contours_poly( contours.size() ); 
    for( int i = 0; i< contours.size(); i++ ) {
      approxPolyDP( Mat(contours[i]), contours_poly[i], 1.1, true ); 
    }

    RNG rng(12345);
    for( int i = 0; i< contours.size(); i++ ) {
      PolyLine *PL = new PolyLine();
      PL->setPenColor(0,0,0);
      if (use_random_colors) { PL->setPenColor(rng.uniform(100,200),rng.uniform(100,200),rng.uniform(100,200)); }

      if (contours_poly[i].size()>min_contour_length) {
	// printf("Contour:%i [%lu points]\n",i,contours_poly[i].size());
	for (int j=0; j<contours_poly[i].size();j++) {
	  //printf("(%i,%i)",contours[i][j].x,contours[i][j].y);
	  //if (j!=contours_poly[i].size()-1) { printf(","); }
	  PL->addPoint(contours_poly[i][j].x,contours_poly[i][j].y);
	}
	S->addShape(PL);
	//printf("\n");
      }
    }
  }