void PltWin::drawIt(QPainter *p)
{
  QString txt;
  double x, y, x0, y0, x1, y1, x2, y2, xprev, yprev, shift, ubmin, ubmax, ub, alpha;
  int n, layer, lay, prev_layer, circDia, i, j, at, ichain, a, istart, iend, icurr, xs, ys;
  int idx, nmax;
  bool dum;

  QPen *pen = new QPen();
  QBrush *brush = new QBrush();
  QBrush *brush_unrld = new QBrush();

  // antialiasing of primitives if ANTIALIASE is set to true
  if (!paintEPS) p->setRenderHint(QPainter::Antialiasing, ANTIALIASE);

  // plot the grain boundary line
  if (isGBfile && showGB) {
    x0 = ZFact*xyzMin(1) - xPan - (ZFact-1)*xyzCen(1);
    x1 = ZFact*xyzMax(1) - xPan - (ZFact-1)*xyzCen(1);
    y  = ZFact*gbYcoor - yPan - (ZFact-1)*xyzCen(2);
    DrawLine(p, x0, y, x1, y);
  }

  if (AtomPos==COMPOSITE) {
    if (!paintEPS) {
      brush_unrld->setColor( Qt::lightGray );
      brush_unrld->setStyle( Qt::SolidPattern );
    }
  }

  // plotting of atomic arrangement in the initial configuration
  prev_layer = -1;
  x0 = y0 = x1 = y1 = 0;

  // need to construct the neighbor list in the relaxed configuration
  if (plotType == PLOT_ATOM_NEIGHBORS) {    
    if (AtomPos == UNRELAXED && NeighListInit.data == NULL)
      InitNeighborList(this, NeighListInit, numNeighInit);
    
    if ((AtomPos == RELAXED || AtomPos == COMPOSITE) && NeighListRel.data == NULL)
      RelNeighborList(this, rcut, NeighListRel, numNeighRel);

    if (AtomPos == UNRELAXED) {
      nmax = -1;
      for (at=1; at<=NInit; at++) {
	n = numNeighInit(at);
	if (n > nmax) nmax = n;
      }
      colormap(nmax+1, cmap);
    }

    if (AtomPos == RELAXED) {
      nmax = -1;
      for (at=1; at<=NRel; at++) {
	n = numNeighRel(at);
	if (n > nmax) nmax = n;
      }
      colormap(nmax+1, cmap);
    }
  }

  if (plotType == PLOT_ATOM_TYPES) {
    nmax = -1;
    for (at=1; at<=NInit; at++) {
      n = atomType(at);
      if (n > nmax) nmax = n;
    }
    colormap(nmax, cmap);
  }
  
  //
  //  Plot the atomic configuration such that the atoms in the front (in the top layer) are plotted
  //  at the end.
  //

  for (i=1; i<=NInit; i++) {
    at = aorder(i);
    if (!zLayerSel(zLayer(at)))
      continue;    

    layer = zLayer(at);
    circDia = zDiamLayer(layer);
    
    switch(plotType) {
      case PLOT_ATOM_LAYERS:
	layer = zLayer(at);

	if (!paintEPS && layer != prev_layer) {
	  pen->setColor(zColorLayer(layer, 1));
	  pen->setWidth(zLineThickLayer(layer));
	  p->setPen(*pen);
	  
	  brush->setColor(zColorLayer(layer, 2));
	  brush->setStyle(Qt::SolidPattern);
	  p->setBrush(*brush);
	}
	break;
	
      case PLOT_ATOM_TYPES:
	lay = layer;
	layer = atomType(at);
	
	if (!paintEPS && layer != prev_layer) {
	  pen->setColor(Qt::black);
	  pen->setWidth(zLineThickLayer(lay));
	  p->setPen(*pen);
	  
	  if (layer == 0) {
	    brush->setColor(Qt::lightGray);
	  } else {
	    brush->setColor(cmap[layer-1]);
	  }
	  brush->setStyle(Qt::SolidPattern);
	  p->setBrush(*brush);
	}
	break;

      case PLOT_ATOM_NEIGHBORS:
	lay = layer;
	if (AtomPos == UNRELAXED)
	  layer = numNeighInit(at);
	else if (AtomPos == RELAXED || AtomPos == COMPOSITE)	  
	  layer = numNeighRel(at);

	if (!paintEPS && layer != prev_layer) {
	  pen->setColor(Qt::black);
	  pen->setWidth(zLineThickLayer(lay));
	  p->setPen(*pen);
	  
	  if (layer == 0)
	    brush->setColor(Qt::lightGray);
	  else {
	    brush->setColor(QColor(cmap[layer]));
	  }
	  brush->setStyle(Qt::SolidPattern);
	  p->setBrush(*brush);
	}
	break;
    }
    
    if (layer != prev_layer) prev_layer = layer;

    switch(AtomPos) {
      case UNRELAXED:
        x = ZFact*xyzInit(at,1) - xPan - (ZFact-1)*xyzCen(1);
	y = ZFact*xyzInit(at,2) - yPan - (ZFact-1)*xyzCen(2);
	DrawAtom(p, at, x, y, circDia);	
        break;

      case RELAXED:
	x = ZFact*(xyzInit(at,1) + AtomDispScale*aDisp(at,1)) - xPan - (ZFact-1)*xyzCen(1);
        y = ZFact*(xyzInit(at,2) + AtomDispScale*aDisp(at,2)) - yPan - (ZFact-1)*xyzCen(2);
        DrawAtom(p, at, x, y, circDia);
	break;

      case COMPOSITE:
	if (!paintEPS) { p->setBrush( *brush_unrld ); }
	x = ZFact*xyzInit(at,1) - xPan - (ZFact-1)*xyzCen(1);
	y = ZFact*xyzInit(at,2) - yPan - (ZFact-1)*xyzCen(2);
        DrawAtom(p, -1, x, y, circDia);
        if (!paintEPS) { p->setBrush( *brush ); }
	x = ZFact*(xyzInit(at,1) + AtomDispScale*aDisp(at,1)) - xPan - (ZFact-1)*xyzCen(1);
	y = ZFact*(xyzInit(at,2) + AtomDispScale*aDisp(at,2)) - yPan - (ZFact-1)*xyzCen(2); 
        DrawAtom(p, at, x, y, circDia);
	break;
    }

    if (x < x0) x0 = x;
    if (x > x1) x1 = x;
    if (y < y0) y0 = y;
    if (y > y1) y1 = y;

    // atom numbers
    if (AtomNumbers) {
      txt.sprintf("%d", at);
      shift = circDia/(2.0*factor);
      DrawText(p, x+shift, y+shift, txt);
    }
  }

  // plot the inert atoms
  if (InertAtoms) {
    if (!paintEPS) {
      pen->setColor(Qt::black);
      pen->setWidth(zLineThickLayer(layer));
      p->setPen(*pen);
      
      brush->setColor(Qt::black);
      brush->setStyle(Qt::NoBrush);
      p->setBrush( *brush );
    }
            
    for (at=1; at<=NInert; at++) {
      // plot only those atoms which belong to the selected (active) layers
      //      if (!zLayerSel(zLayer(n)))
      //	continue;
      x = ZFact*xyzInert(at,1) - xPan - (ZFact-1)*xyzCen(1);
      y = ZFact*xyzInert(at,2) - yPan - (ZFact-1)*xyzCen(2);
      DrawAtom(p, 0, x, y, circDia);
    }    
  }

  // highlight the atoms picked
  if (!paintEPS && napicked > 0) {
    pen->setColor(Qt::green);
    pen->setWidth(2);
    p->setPen(*pen);    
    brush->setStyle(Qt::NoBrush);
    p->setBrush(*brush);
    
    dum = ATOM_3DSPHERE;
    ATOM_3DSPHERE = false;
    for (n=1; n<=napicked; n++) {
      at = apicked(n);
      x = ZFact*xyzInit(at,1) - xPan - (ZFact-1)*xyzCen(1);
      y = ZFact*xyzInit(at,2) - yPan - (ZFact-1)*xyzCen(2);
      DrawAtom(p, at, x, y, circDia+4);
      if (n > 1) DrawLine(p, xprev, yprev, x, y);
      xprev = x;
      yprev = y;
    }
    ATOM_3DSPHERE = dum;
  }

  // highlight the atoms in selected chains
  if (!paintEPS && nchain > 0) {
    pen->setColor(Qt::green);
    pen->setWidth(2);
    p->setPen(*pen);

    for (ichain=1; ichain<=nchain; ichain++) {
      for (i=1; i<=nachain(ichain); i++) {
	a = achain(ichain,i);
	x = ZFact*xyzInit(a,1) - xPan - (ZFact-1)*xyzCen(1);
	y = ZFact*xyzInit(a,2) - yPan - (ZFact-1)*xyzCen(2);	
	if (i>1) DrawLine(p, x0, y0, x, y);       
	x0 = x;
	y0 = y;

      }
    }

    if (!paintEPS && nchain >= 2) {
      QPen *pen2 = new QPen();
      pen2->setColor(Qt::green);
      pen2->setStyle(Qt::DashLine);
      p->setPen(*pen2);

      for (i=1; i<nchain; i+=2) {
	x1 = ZFact*dposchain(i,1) - xPan - (ZFact-1)*xyzCen(1);
	y1 = ZFact*dposchain(i,2) - yPan - (ZFact-1)*xyzCen(2);
	x2 = ZFact*dposchain(i+1,1) - xPan - (ZFact-1)*xyzCen(1);
	y2 = ZFact*dposchain(i+1,2) - yPan - (ZFact-1)*xyzCen(2);
	DrawLine(p, x1, y1, x2, y2);
      }
    }
  }

  // plotting the coordinate system centered at the initial position of
  // the dislocation line
  if (PlaneTraces) DrawPlaneTraces(p, x0, y0, x1, y1);

  // plotting of arrows
  if (arrNeighNum > 0) {
    if (!paintEPS) {
      pen->setColor(Qt::black);
      pen->setWidth(thicknessArrow);
      p->setPen(*pen); 
      p->setBrush(Qt::black);
    }
    
    switch(DispComponent) {
      case EDGE:
	plotEdgeComponent(p);
	break;
	
      case SCREW:
	plotScrewComponent(p);
	break;
      
      case PROJ:
	plotScrewComponent(p);   // plotted the same way as screw components
	break;
      
      case DIFF_EDGE:
      case DIFF_SCREW:
	plotDifference(p);
	break;
    }
  }
  
  // position of dislocation center
  if (DisloCenter) {
    DrawLine(p, xCore, y0, xCore, y1);    
    DrawLine(p, x0, yCore, x1, yCore);    
  }

  // small inset to show the active Z-layers
  if (!paintEPS && showZLayers)
    ShowActiveZLayers(p);

  // show color map
  if (!paintEPS && (plotType == PLOT_ATOM_TYPES || plotType == PLOT_ATOM_NEIGHBORS))
    ShowColorMap(p);

  // lines showing the division of the block into cells (for the linked neighbor list)
  if (showNeighCells) {
    if (!paintEPS) {
      pen->setColor(Qt::black);
      p->setPen(*pen);
    }

    for (i=0; i<=ncell(1); i++) {
      x = ZFact*(xyzMin(1)+i*cellsize(1)) - xPan - (ZFact-1)*xyzCen(1);
      y0 = ZFact*xyzMin(2) - yPan - (ZFact-1)*xyzCen(2);
      y1 = ZFact*xyzMax(2) - yPan - (ZFact-1)*xyzCen(2);
      DrawLine(p, x, y0, x, y1);    
      
      for (j=0; j<=ncell(2); j++) {
	y = ZFact*(xyzMin(2)+j*cellsize(2)) - yPan - (ZFact-1)*xyzCen(2);
	x0 = ZFact*xyzMin(1) - xPan - (ZFact-1)*xyzCen(1);
	x1 = ZFact*xyzMax(1) - xPan - (ZFact-1)*xyzCen(1);
	DrawLine(p, x0, y, x1, y);
      }
    }
  }

  // coordinate system of the block
  if (!paintEPS && showCSys)
    ShowCSys(p);

  // show the polygon that encompasses the dislocation center
  if (!paintEPS && ndpoly > 0) {
    pen->setColor(Qt::green);
    p->setPen(*pen);

    for (n=1; n<=ndpoly; n++) {
      x1 = ZFact*dpoly(n,1) - xPan - (ZFact-1)*xyzCen(1);
      y1 = ZFact*dpoly(n,2) - yPan - (ZFact-1)*xyzCen(2);
      if (n<ndpoly) {
	x2 = ZFact*dpoly(n+1,1) - xPan - (ZFact-1)*xyzCen(1);
	y2 = ZFact*dpoly(n+1,2) - yPan - (ZFact-1)*xyzCen(2);
      } else {
	x2 = ZFact*dpoly(1,1) - xPan - (ZFact-1)*xyzCen(1);
	y2 = ZFact*dpoly(1,2) - yPan - (ZFact-1)*xyzCen(2);
      }
      DrawLine(p, x1, y1, x2, y2);
    }
  }

  if (!paintEPS && ndpath > 0) {
    pen->setColor(Qt::green);
    p->setPen(*pen);
    brush->setColor(Qt::green);
    brush->setStyle(Qt::NoBrush);
    p->setBrush(*brush);

    for (n=1; n<ndpath; n++) {
      x1 = ZFact*dpath(n,1) - xPan - (ZFact-1)*xyzCen(1);
      y1 = ZFact*dpath(n,2) - yPan - (ZFact-1)*xyzCen(2);
      x2 = ZFact*dpath(n+1,1) - xPan - (ZFact-1)*xyzCen(1);
      y2 = ZFact*dpath(n+1,2) - yPan - (ZFact-1)*xyzCen(2);
      DrawLine(p, x1, y1, x2, y2);
      if (n==1) {
	xyWorldToScreen(x1, y1, xs, ys);
	xs -= 2;
	ys -= 2;
	p->drawEllipse(xs, ys, 4, 4);
      }
      xyWorldToScreen(x2, y2, xs, ys);
      xs -= 2;
      ys -= 2;
      p->drawEllipse(xs, ys, 4, 4);
    }
  }
}