int SolidifyPW::Display(
		TimeValue t, INode* inode, ViewExp *vpt, int flags, 
		ModContext *mc) 
	{	

	return 0;

	GraphicsWindow *gw = vpt->getGW();
	// Transform the gizmo with the node.
	Matrix3 ntm = inode->GetObjectTM(t);
	gw->setTransform(ntm);	

	Point3 selGizmoColor = GetUIColor(COLOR_SEL_GIZMOS);
	Point3 gizmoColor = GetUIColor(COLOR_GIZMOS);

	Point3 green(0.0f,1.0f,0.0f);
	Point3 blue(0.0f,0.0f,1.0f);
	Point3 red(1.0f,0.0f,0.0f);

	gw->setColor(LINE_COLOR, gizmoColor);

	for (int i = 0; i < meshInfo.bevelData.Count(); i++)
	{
		if (meshInfo.bevelData[i].ct == 2)

		{
			Point3 l[3];

			gw->setColor(LINE_COLOR, gizmoColor);

			l[0] = meshInfo.bevelData[i].p;
			
			l[1] = meshInfo.bevelData[i].p + meshInfo.bevelData[i].vec[0]*1.f;
			gw->polyline(2, l, NULL, NULL, 0);

			l[1] = meshInfo.bevelData[i].p + meshInfo.bevelData[i].vec[1]*1.f;
			gw->polyline(2, l, NULL, NULL, 0);

			gw->setColor(LINE_COLOR, selGizmoColor);

			
			l[1] = meshInfo.bevelData[i].p + meshInfo.bevelData[i].vnorm*10.f;
			gw->polyline(2, l, NULL, NULL, 0);

			gw->setColor(LINE_COLOR, red);
			
			l[1] = meshInfo.bevelData[i].p + meshInfo.bevelData[i].norm*1.f*meshInfo.bevelData[i].realLength;
			gw->polyline(2, l, NULL, NULL, 0);

/*
			gw->setColor(LINE_COLOR, green);

			l[1] = bevelData[i].p + bevelData[i].cross[0]*5.f;
			gw->polyline(2, l, NULL, NULL, 0);

			gw->setColor(LINE_COLOR, blue );

			l[1] = bevelData[i].p + bevelData[i].cross[1]*5.f;
			gw->polyline(2, l, NULL, NULL, 0);
*/

		}

	}

		return 0;


/*
	for (int i = 0; i < vPlanes.Count(); i++)
		{
		if (vPlanes[i].display)
			{
		
			gw->setColor(LINE_COLOR, gizmoColor);
			gw->marker(&vPlanes[i].debugP1,PLUS_SIGN_MRKR);
			gw->marker(&vPlanes[i].debugP2,PLUS_SIGN_MRKR);


			Point3 l[3];
			l[0] = vPlanes[i].debugP1;
			l[1] = vPlanes[i].debugP2;
			gw->polyline(2, l, NULL, NULL, 0);

			gw->setColor(LINE_COLOR, selGizmoColor);
			gw->marker(&vPlanes[i].debugBase,PLUS_SIGN_MRKR);

			l[0] = vPlanes[i].debugBase;
			l[1] = vPlanes[i].debugBase+(vPlanes[i].debugNorm);
			gw->polyline(2, l, NULL, NULL, 0);

			gw->setColor(LINE_COLOR, red);
			l[0] = vPlanes[i].debugBase;
			l[1] = vPlanes[i].debugBase+(vPlanes[i].vnorm);
			gw->polyline(2, l, NULL, NULL, 0);


			}

		}

*/
	

	for (int i = 0; i < meshInfo.op.Count(); i++)
		{

		gw->setColor(LINE_COLOR, selGizmoColor);
		
		gw->marker(&meshInfo.cdata[i].p,PLUS_SIGN_MRKR);


		Point3 l[3];
		l[0] = meshInfo.op[i];
		l[1] = meshInfo.op[i] + meshInfo.vnorms[i];

		gw->polyline(2, l, NULL, NULL, 0);

		gw->setColor(LINE_COLOR, gizmoColor);

//		l[0] = cdata[i].p;
//		l[1] = cdata[i].p + cdata[i].hyp;
//
//		gw->polyline(2, l, NULL, NULL, 0);

//		l[0] = cdata[i].p + cdata[i].norm;;
//		l[1] = cdata[i].p + cdata[i].hyp;

//		gw->setColor(LINE_COLOR, red);
//		gw->polyline(2, l, NULL, NULL, 0);

		}

	return 0;	
	}