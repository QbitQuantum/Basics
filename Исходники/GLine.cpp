//--------------------------------------------------------------------------
//　선택 지점의 좌표 포인트 반환
//--------------------------------------------------------------------------
int GLine::FindSelectPoint(CPoint pt) {
	
	int tempThick = (GObject::m_nsThickness > 4 ? GObject::m_nsThickness : 5); // 기본 크기는 5 
	
	CRgn rgn;
	CPoint tempPt = GObject::m_sStartPoint;
	rgn.CreateEllipticRgn(tempPt.x - tempThick, tempPt.y - tempThick, tempPt.x + tempThick, tempPt.y + tempThick); // 리전 생성

	// 시작점이 Rgn 안에 있으며 시작점이 선택
	if(rgn.PtInRegion(pt) == TRUE) {
		return 0;
	}

	tempPt = GObject::m_sEndPoint;
	rgn.DeleteObject();
	rgn.CreateEllipticRgn(tempPt.x - tempThick, tempPt.y - tempThick, tempPt.x + tempThick, tempPt.y + tempThick); // 리전 생성

	// 끝점이 선택된 경우
	if(rgn.PtInRegion(pt) == TRUE) {
		return 4;
	}
	return -1;
}