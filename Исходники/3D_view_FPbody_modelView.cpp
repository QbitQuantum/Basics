void CMy3D_view_FPbody_modelView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CMy3D_view_FPbody_modelDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	wglMakeCurrent(m_pDC->GetSafeHdc(), NULL); 
	
	OPRT->Set_LBD(FALSE);
	if(pDoc->BP_xy[xyLineIndex][xyPointIndex].Catch==TRUE)
	{
		pDoc->BP_xy[xyLineIndex][xyPointIndex].Catch=FALSE;
	}

	if(pDoc->BP_yz[yzLineIndex][yzPointIndex].Catch==TRUE)
	{
		pDoc->BP_yz[yzLineIndex][yzPointIndex].Catch=FALSE;
	}

	if(pDoc->BP_xz[xzLineIndex][xzPointIndex].Catch==TRUE)
	{
		pDoc->BP_xz[xzLineIndex][xzPointIndex].Catch=FALSE;
	}
/*	int i, index;
	for(index=0;index<pDoc->XYLNum;index++)
	{	
		for(i=0;i<pDoc->XYLINE[index].Get_BP();i++)
		{																	
			if(pDoc->BP_xy[index][i].Catch==TRUE)
			{	
				pDoc->BP_xy[index][i].Catch=FALSE;
				break;
			}
		}
	}
	for(index=0;index<pDoc->YZLNum;index++)
	{	
		for(i=0;i<pDoc->YZLINE[index].Get_BP();i++)
		{																	
			if(pDoc->BP_yz[index][i].Catch==TRUE)
			{	
				pDoc->BP_yz[index][i].Catch=FALSE;
				break;
			}
		}
	}
	for(index=0;index<pDoc->XZLNum;index++)
	{	
		for(i=0;i<pDoc->XZLINE[index].Get_BP();i++)
		{																	
			if(pDoc->BP_xz[index][i].Catch==TRUE)
			{	
				pDoc->BP_xz[index][i].Catch=FALSE;
				break;
			}
		}
	}*/
	InvalidateRect(NULL,FALSE);
	ReleaseCapture();
	CView::OnLButtonUp(nFlags, point);
}