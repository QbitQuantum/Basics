void CGLSampleDoc::OnGeometryBSurface()
{
    if(m_bLine)
        m_bLine = false;

	static CBSplineDlg cBsplineDlg( this, BSPLINE_SWEEP );
	cBsplineDlg.Create( IDD_BSPLINE, NULL );
	
	cBsplineDlg.ShowWindow( SW_SHOW );
}