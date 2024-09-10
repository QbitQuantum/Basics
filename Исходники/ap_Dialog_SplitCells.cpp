/*! 
 * This method sets the sensitivity of the radio buttons to above/below/left/right merges
 * Because we can't merge to the left of column zero for example.
 *
 * Call this right after contructing the widget and before dropping into the main loop.
 */
void AP_Dialog_SplitCells::setAllSensitivities(void)
{
	FV_View * pView = 0;

	if (XAP_Frame * pFrame = getApp()->getLastFocussedFrame())
	{
		pView = static_cast<FV_View *>(pFrame->getCurrentView());
	}
	if (!pView)
	{
		setSensitivity(vert_above, false);
		setSensitivity(vert_mid,   false);
		setSensitivity(vert_below, false);
		setSensitivity(hori_left,  false);
		setSensitivity(hori_mid,   false);
		setSensitivity(hori_right, false);
		return;
	}
	if (!pView->isInTable())
	{
		setSensitivity(vert_above, false);
		setSensitivity(vert_mid,   false);
		setSensitivity(vert_below, false);
		setSensitivity(hori_left,  false);
		setSensitivity(hori_mid,   false);
		setSensitivity(hori_right, false);
		return;
	}

	PT_DocPosition iCurPos = pView->getPoint();
	m_iCellSource = iCurPos;
	pView->getCellParams(iCurPos,&m_iLeft,&m_iRight,&m_iTop,&m_iBot);
//
// Now find the number of rows and columns inthis table. This is easiest to
// get from the table container
//
	fl_BlockLayout * pBL =	pView->getLayout()->findBlockAtPosition(iCurPos);
	fp_Run * pRun;
	UT_sint32 xPoint,yPoint,xPoint2,yPoint2,iPointHeight;
	bool bDirection;
	pRun = pBL->findPointCoords(iCurPos, false, xPoint,
							    yPoint, xPoint2, yPoint2,
							    iPointHeight, bDirection);

	UT_return_if_fail(pRun);

	fp_Line * pLine = pRun->getLine();
	UT_return_if_fail(pLine);

	fp_Container * pCon = pLine->getContainer();
	UT_return_if_fail(pCon);

	fp_TableContainer * pTab = static_cast<fp_TableContainer *>(pCon->getContainer());
	UT_return_if_fail(pTab);
	UT_return_if_fail(pTab->getContainerType() == FP_CONTAINER_TABLE);
	m_pTab = pTab;
	m_iNumRows = pTab->getNumRows();
	m_iNumCols = pTab->getNumCols();
	if(m_iBot > m_iTop+2)
	{
		setSensitivity(vert_above,true);
		setSensitivity(vert_below,true);
	}
	else
	{
		setSensitivity(vert_above,false);
		setSensitivity(vert_below,false);
	}
	UT_sint32 diff = m_iBot - m_iTop;
	if((m_iBot - m_iTop == 1) || (2*(diff/2) == diff))
	{
		setSensitivity(vert_mid,true);
	}
	else
	{
		setSensitivity(vert_mid,false);
	}
	if(m_iRight > m_iLeft+2)
	{
		setSensitivity(hori_left,true);
		setSensitivity(hori_right,true);
	}
	else
	{
		setSensitivity(hori_left,false);
		setSensitivity(hori_right,false);
	}
	diff = m_iRight - m_iLeft;
	if((m_iRight - m_iLeft == 1) || (2*(diff/2) == diff))
	{
		setSensitivity(hori_mid,true);
	}
	else
	{
		setSensitivity(hori_mid,false);
	}
}