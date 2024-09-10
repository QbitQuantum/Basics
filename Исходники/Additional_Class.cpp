void Additional_Class::Get_ArcMiddle( AcDbObjectId PolyLineId, AcGePoint3dArray &Middle_List,AcGePoint3dArray &CenterListInput, LINEINFO &ArcInfoRList, LINEINFO &ArcInfoAList )
{
	double PI=3.1415926535897932384626433832795;
	AcDbEntity *pEnt_Temp = NULL;
	Acad::ErrorStatus es = acdbOpenAcDbEntity(pEnt_Temp, PolyLineId, AcDb::kForRead);
	if (es != Acad::eOk)
	{
		acutPrintf(_T("\nOPEN ENTITY ERROR"));
		return;
	}
	if (!pEnt_Temp->isKindOf(AcDbPolyline::desc()))
	{
		acutPrintf(_T("\nENTITY NOT POLYLINE"));
		return;
	}
	AcDbPolyline *pPolyLine = AcDbPolyline::cast(pEnt_Temp);
	int num = pPolyLine->numVerts();
	AcGePoint3d Start_temp_PT,End_temp_PT;
	AcGePoint3dArray Center_List;
	for (int index=0; index<num; index++)
	{
		if (pPolyLine->segType(index) == AcDbPolyline::kArc)
		{
			AcGeCircArc2d tempArc;
			pPolyLine->getArcSegAt(index,tempArc);
			AcGePoint2d CenterPoint;
			CenterPoint = tempArc.center();
			AcGePoint3d CenterPoint3d;
			CenterPoint3d.set(CenterPoint.x, CenterPoint.y, 0);
			Center_List.append(CenterPoint3d);
			AcGePoint3d Start_temp_PT, End_temp_PT;
			Start_temp_PT.set(tempArc.startPoint().x,tempArc.startPoint().y,0);
			End_temp_PT.set(tempArc.endPoint().x,tempArc.endPoint().y,0);
			AcGeVector3d tempVec;
			tempVec = End_temp_PT - Start_temp_PT;
			double tempVec_Len = tempVec.length();
			tempVec.normalize();
			tempVec = tempVec*(tempVec_Len/2);
			AcGeVector3d CenterVec;
			CenterVec = Start_temp_PT - CenterPoint3d;
			CenterVec = CenterVec + tempVec;
			AcGeLine2d CenterLine2d;
			AcGePoint3d Middle_Pt_OnLine;
			Middle_Pt_OnLine = CenterPoint3d+CenterVec;
			AcGePoint2d middle2d;
			middle2d.set(Middle_Pt_OnLine.x, Middle_Pt_OnLine.y);
			CenterLine2d.set(CenterPoint, middle2d);

			int s;
			AcGePoint2d MiddlePT, pt2;
			tempArc.intersectWith(CenterLine2d, s,  MiddlePT, pt2);
			AcGePoint3d MiddlePoint;
			MiddlePoint.set(MiddlePT.x,MiddlePT.y,0);
			Middle_List.append(MiddlePoint);

			double StartAngle = tempArc.startAng();
			double EndAngle = tempArc.endAng();
			double Angle = EndAngle-StartAngle;
			Angle = (180/PI)*Angle;
			double Radius = tempArc.radius();
			CString tempStr_Angle,tempStr_Radius,sita,du,banjing;
			sita = "θ=";
			du = "°";
			banjing = "R=";
			tempStr_Angle.Format(_T("%.1f"),Angle);
			tempStr_Angle = sita+tempStr_Angle+du;
			tempStr_Radius.Format(_T("%.1f"),Radius);
			tempStr_Radius = banjing + tempStr_Radius;
			ArcInfoRList.push_back(tempStr_Radius);
			ArcInfoAList.push_back(tempStr_Angle);
		}
	}
	CenterListInput = Center_List;
}