int AFRMod::Display(
		TimeValue t, INode* inode, ViewExp *vpt, 
		int flagst, ModContext *mc)
	{
	GraphicsWindow *gw = vpt->getGW();
	Point3 pt[4];
	Matrix3 tm = CompMatrix(t,inode,mc);
	int savedLimits;

	gw->setRndLimits((savedLimits = gw->getRndLimits()) & ~GW_ILLUM);
	gw->setTransform(tm);
	
	// Draw start point
	if (ip && ip->GetSubObjectLevel() == 1) {
		if (sel[0]) 
			 gw->setColor(LINE_COLOR, (float)1.0, (float)0.0, (float)0.0);			 
		else //gw->setColor(LINE_COLOR, (float)1.0, (float)1.0, (float)0.0);
			 gw->setColor(LINE_COLOR,GetUIColor(COLOR_SEL_GIZMOS));
	} else {
		//gw->setColor(LINE_COLOR, (float).85, (float).5, (float)0.0);
		gw->setColor(LINE_COLOR,GetUIColor(COLOR_GIZMOS));
		}	
	p1->GetValue(t,&pt[0],FOREVER,CTRL_ABSOLUTE);
	gw->marker(&pt[0],HOLLOW_BOX_MRKR);

	// Draw end point
	if (ip && ip->GetSubObjectLevel() == 1) {
		if (sel[1]) 
			 gw->setColor(LINE_COLOR, (float)1.0, (float)0.0, (float)0.0);
		else //gw->setColor(LINE_COLOR, (float)1.0, (float)1.0, (float)0.0);
			   gw->setColor(LINE_COLOR,GetUIColor(COLOR_SEL_GIZMOS));
	} else {
		//gw->setColor(LINE_COLOR, (float).85, (float).5, (float)0.0);
		gw->setColor(LINE_COLOR,GetUIColor(COLOR_GIZMOS));
		}	
	p2->GetValue(t,&pt[1],FOREVER,CTRL_ABSOLUTE);
	gw->marker(&pt[1],HOLLOW_BOX_MRKR);

	// Draw a line inbetween
	if (ip && ip->GetSubObjectLevel() == 1) {
		//gw->setColor(LINE_COLOR, (float)1.0, (float)1.0, (float)0.0);
		gw->setColor(LINE_COLOR,GetUIColor(COLOR_SEL_GIZMOS));
	} else {
		//gw->setColor(LINE_COLOR, (float).85, (float).5, (float)0.0);
		gw->setColor(LINE_COLOR,GetUIColor(COLOR_GIZMOS));
		}
	gw->polyline(2, pt, NULL, NULL, 0, NULL);
	
	// Draw arrowhead
	Matrix3 vtm;
	vpt->GetAffineTM(vtm);
	Point3 vz = vtm.GetRow(2) * Inverse(tm);
	Point3 dp = (pt[1]-pt[0]);
	Point3 v = Normalize(vz^dp) * Length(dp) * 0.2f;
	pt[0] = pt[1] - (0.2f*dp) + v;
	pt[2] = pt[1] - (0.2f*dp) - v;
	gw->polyline(3, pt, NULL, NULL, 0, NULL);
	v = Normalize(v^dp) * Length(dp) * 0.2f;
	pt[0] = pt[1] - (0.2f*dp) + v;
	pt[2] = pt[1] - (0.2f*dp) - v;
	gw->polyline(3, pt, NULL, NULL, 0, NULL);

	gw->setRndLimits(savedLimits);
	return 0;
	}