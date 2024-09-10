//-----------------------------------------------------------------------------
// Draws the chart
//-----------------------------------------------------------------------------
void	CXYChart::OnDraw( CDC *pDC, CRect destRect, CRect updateRect )
{
	CString			string;
	int				i;
	CAxis			*axis;
	CSize			axisDims;
	CSize			trim(0,0);
	CRect			plotRect, normalPlotRect, normalDestRect;
	double			xRange[] = {1e30, -1e30}, yRange[]={1e30,-1e30};

	updateRect.NormalizeRect();

	normalDestRect = destRect;

	// Check to see that we are even in the update region
	normalDestRect.NormalizeRect();
	normalDestRect.IntersectRect( normalDestRect, updateRect );
	if( normalDestRect.IsRectEmpty() ) return;

	// Make sure our ranges are set
	// Get ranges for plotting
	GetPlotRange( xRange, yRange );

	// Get the size of our plotting rectangle
	plotRect = GetPlotRect( pDC, destRect );

	// Draw the basic structures for the plot
	DrawPlotBasics( pDC, destRect, plotRect );

	// Draw the title
	DrawPlotTitle( pDC, destRect, plotRect );

	normalPlotRect = plotRect;
	normalPlotRect.NormalizeRect();
	updateRect.IntersectRect( updateRect, normalPlotRect );

	if( updateRect.IsRectEmpty() == FALSE )
	{
		// Draw each data set
		DrawDataSet( pDC, plotRect, xRange, yRange );
	}

	// Draw the axes
	for( i = 0; i < m_AxisCount; i++ )
	{
		axis = m_Axes[i];
		axis->OnDraw( pDC, destRect, plotRect );
	}

	CChart::OnDraw( pDC, destRect );
}