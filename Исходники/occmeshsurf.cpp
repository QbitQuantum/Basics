  void OCCSurface :: GetNormalVector (const Point<3> & p, 
				      const PointGeomInfo & geominfo,
				      Vec<3> & n) const
  {
    gp_Pnt pnt;
    gp_Vec du, dv;

    /*
      double gu = geominfo.u;
      double gv = geominfo.v;

      if (fabs (gu) < 1e-3) gu = 0;
      if (fabs (gv) < 1e-3) gv = 0;

      occface->D1(gu,gv,pnt,du,dv);
    */

    /*
      occface->D1(geominfo.u,geominfo.v,pnt,du,dv);

      n = Cross (Vec<3>(du.X(), du.Y(), du.Z()),
      Vec<3>(dv.X(), dv.Y(), dv.Z()));
      n.Normalize();
    */



    GeomLProp_SLProps lprop(occface,geominfo.u,geominfo.v,1,1e-5);
    double setu=geominfo.u,setv=geominfo.v;

    if(lprop.D1U().Magnitude() < 1e-5 || lprop.D1V().Magnitude() < 1e-5)
      {
	double ustep = 0.01*(umax-umin);
	double vstep = 0.01*(vmax-vmin);

	n=0;

	while(setu < umax && (lprop.D1U().Magnitude() < 1e-5 || lprop.D1V().Magnitude() < 1e-5))
	  setu += ustep;
	if(setu < umax)
	  {
	    lprop.SetParameters(setu,setv);
	    n(0)+=lprop.Normal().X();
	    n(1)+=lprop.Normal().Y();
	    n(2)+=lprop.Normal().Z();
	  }
	setu = geominfo.u;
	while(setu > umin && (lprop.D1U().Magnitude() < 1e-5 || lprop.D1V().Magnitude() < 1e-5))
	  setu -= ustep;
	if(setu > umin)
	  {
	    lprop.SetParameters(setu,setv);
	    n(0)+=lprop.Normal().X();
	    n(1)+=lprop.Normal().Y();
	    n(2)+=lprop.Normal().Z();
	  }
	setu = geominfo.u;

	while(setv < vmax && (lprop.D1U().Magnitude() < 1e-5 || lprop.D1V().Magnitude() < 1e-5))
	  setv += ustep;
	if(setv < vmax)
	  {
	    lprop.SetParameters(setu,setv);
	    n(0)+=lprop.Normal().X();
	    n(1)+=lprop.Normal().Y();
	    n(2)+=lprop.Normal().Z();
	  }
	setv = geominfo.v;
	while(setv > vmin && (lprop.D1U().Magnitude() < 1e-5 || lprop.D1V().Magnitude() < 1e-5))
	  setv -= ustep;
	if(setv > vmin)
	  {
	    lprop.SetParameters(setu,setv);
	    n(0)+=lprop.Normal().X();
	    n(1)+=lprop.Normal().Y();
	    n(2)+=lprop.Normal().Z();
	  }
	setv = geominfo.v;

	n.Normalize();
      }
    else
      {
	n(0)=lprop.Normal().X();
	n(1)=lprop.Normal().Y();
	n(2)=lprop.Normal().Z();
      }

    if(glob_testout)
      {
	(*testout) << "u " << geominfo.u << " v " << geominfo.v 
		   << " du " << lprop.D1U().X() << " "<< lprop.D1U().Y() << " "<< lprop.D1U().Z()
		   << " dv " << lprop.D1V().X() << " "<< lprop.D1V().Y() << " "<< lprop.D1V().Z() << endl;
      }



    if (orient == TopAbs_REVERSED) n = -1*n;
    //  (*testout) << "GetNormalVector" << endl;
  }