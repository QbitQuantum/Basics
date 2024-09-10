void Topology::Paint(HDC hdc, RECT rc) {

  if (!shapefileopen) return;

  bool nolabels=false;
  if (scaleCategory==10) {
	// for water areas, use scaleDefault
	if ( MapWindow::zoom.Scale()>scaleDefaultThreshold) {
		return;
	}
	// since we just checked category 10, if we are over scale we set nolabels
	if ( MapWindow::zoom.Scale()>scaleThreshold) nolabels=true;
  } else 
  if (MapWindow::zoom.Scale() > scaleThreshold) return;

  // TODO code: only draw inside screen!
  // this will save time with rendering pixmaps especially
  // checkVisible does only check lat lon , not screen pixels..
  // We need to check also screen.

  HPEN  hpOld;
  HBRUSH hbOld;
  HFONT hfOld;

  if (hPen) {
    hpOld = (HPEN)SelectObject(hdc,  hPen);
    hbOld = (HBRUSH)SelectObject(hdc, hbBrush);
  } else {
    hpOld = NULL;
    hbOld = NULL;
  }
  hfOld = (HFONT)SelectObject(hdc, MapLabelFont);

  // get drawing info
    
  int iskip = 1;
  
  // attempt to bugfix 100615 polyline glitch with zoom over 33Km
  // do not skip points, if drawing coast lines which have a scaleThreshold of 100km!
  // != 5 and != 10
  if (scaleCategory>10) { 
  if (MapWindow::zoom.Scale()>0.25*scaleThreshold) {
    iskip = 2;
  } 
  if (MapWindow::zoom.Scale()>0.5*scaleThreshold) {
    iskip = 3;
  }
  if (MapWindow::zoom.Scale()>0.75*scaleThreshold) {
    iskip = 4;
  }
  }

  #if TOPOFASTLABEL
  // use the already existing screenbounds_latlon, calculated by CalculateScreenPositions in MapWindow2
  rectObj screenRect = MapWindow::screenbounds_latlon;
  #else
  rectObj screenRect = MapWindow::CalculateScreenBounds(0.0);
  #endif

  static POINT pt[MAXCLIPPOLYGON];
  bool labelprinted=false;

  for (int ixshp = 0; ixshp < shpfile.numshapes; ixshp++) {
    
    XShape *cshape = shpCache[ixshp];

    if (!cshape || cshape->hide) continue;    

    shapeObj *shape = &(cshape->shape);

    switch(shape->type) {


      case(MS_SHAPE_POINT):{

	#if 101016
	// -------------------------- NOT PRINTING ICONS ---------------------------------------------
	bool dobitmap=false;
	if (scaleCategory<90 || (MapWindow::zoom.Scale()<2)) dobitmap=true;
	// first a latlon overlap check, only approximated because of fastcosine in latlon2screen
	if (checkVisible(*shape, screenRect))
		for (int tt = 0; tt < shape->numlines; tt++) {
			for (int jj=0; jj< shape->line[tt].numpoints; jj++) {
				POINT sc;
				MapWindow::LatLon2Screen(shape->line[tt].point[jj].x, shape->line[tt].point[jj].y, sc);
				if (dobitmap) {
					// bugfix 101212 missing case for scaleCategory 0 (markers)
					if (scaleCategory==0||cshape->renderSpecial(hdc, sc.x, sc.y,labelprinted)) 
						MapWindow::DrawBitmapIn(hdc, sc, hBitmap);
				} else {
					cshape->renderSpecial(hdc, sc.x, sc.y,labelprinted);
				}
			}
		}
	}

	#else
	// -------------------------- PRINTING ICONS ---------------------------------------------
	#if (TOPOFAST)
	// no bitmaps for small town over a certain zoom level and no bitmap if no label at all levels
	bool nobitmap=false, noiconwithnolabel=false;
	if (scaleCategory==90 || scaleCategory==100) {
		noiconwithnolabel=true;
		if (MapWindow::MapScale>4) nobitmap=true;
	}
	#endif

	//#if TOPOFASTLABEL
	if (checkVisible(*shape, screenRect))
		for (int tt = 0; tt < shape->numlines; tt++) {
			for (int jj=0; jj< shape->line[tt].numpoints; jj++) {
				POINT sc;
				MapWindow::LatLon2Screen(shape->line[tt].point[jj].x, shape->line[tt].point[jj].y, sc);
	
				#if (TOPOFAST)
				if (!nobitmap)
				#endif
				#if 101016
				// only paint icon if label is printed too
				if (noiconwithnolabel) {
					if (cshape->renderSpecial(hdc, sc.x, sc.y,labelprinted))
						MapWindow::DrawBitmapIn(hdc, sc, hBitmap);
				} else {
					MapWindow::DrawBitmapIn(hdc, sc, hBitmap);
					cshape->renderSpecial(hdc, sc.x, sc.y,labelprinted);
				}
				#else
				MapWindow::DrawBitmapIn(hdc, sc, hBitmap);
				cshape->renderSpecial(hdc, sc.x, sc.y);
				#endif
			}
		}

	}
	#endif // Use optimized point icons 1.23e
	break;

    case(MS_SHAPE_LINE):

      if (checkVisible(*shape, screenRect))
        for (int tt = 0; tt < shape->numlines; tt ++) {
          
          int minx = rc.right;
          int miny = rc.bottom;
          int msize = min(shape->line[tt].numpoints, MAXCLIPPOLYGON);

	  MapWindow::LatLon2Screen(shape->line[tt].point,
				   pt, msize, 1);
          for (int jj=0; jj< msize; jj++) {
            if (pt[jj].x<=minx) {
              minx = pt[jj].x;
              miny = pt[jj].y;
            }
	  }

          ClipPolygon(hdc, pt, msize, rc, false);
          cshape->renderSpecial(hdc,minx,miny,labelprinted);
        }
      break;
      
    case(MS_SHAPE_POLYGON):

	// if it's a water area (nolabels), print shape up to defaultShape, but print
	// labels only up to custom label levels
	if ( nolabels ) {
		if (checkVisible(*shape, screenRect)) {
			for (int tt = 0; tt < shape->numlines; tt ++) {
				int minx = rc.right;
				int miny = rc.bottom;
				int msize = min(shape->line[tt].numpoints/iskip, MAXCLIPPOLYGON);
				MapWindow::LatLon2Screen(shape->line[tt].point, pt, msize*iskip, iskip);
				for (int jj=0; jj< msize; jj++) {
					if (pt[jj].x<=minx) {
						minx = pt[jj].x;
						miny = pt[jj].y;
					}
				}
				ClipPolygon(hdc,pt, msize, rc, true);
			}
		}
	} else 
	if (checkVisible(*shape, screenRect)) {
		for (int tt = 0; tt < shape->numlines; tt ++) {
			int minx = rc.right;
			int miny = rc.bottom;
			int msize = min(shape->line[tt].numpoints/iskip, MAXCLIPPOLYGON);
			MapWindow::LatLon2Screen(shape->line[tt].point, pt, msize*iskip, iskip);
			for (int jj=0; jj< msize; jj++) {
				if (pt[jj].x<=minx) {
					minx = pt[jj].x;
					miny = pt[jj].y;
				}
			}
			ClipPolygon(hdc,pt, msize, rc, true);
			cshape->renderSpecial(hdc,minx,miny,labelprinted);          
		}
	}
	break;
      
    default:
      break;
    }
  }