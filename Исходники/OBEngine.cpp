void OBEngine::drawNormal(FGGraphics &g)
{
	// draw
	g.setColor(0);
	g.fillRect(0, 0, m_screenW, m_screenH);

	m_sun.drawSelf(g);
	if ( m_bShowVenus )
	{
		m_venusPath.drawSelf(g, NULL);
	}

	m_earthPath.drawSelf(g, NULL);
	m_marsPath.drawSelf(g, NULL);

	// ship
	m_ship.drawSelf(g, m_hoverAccelPoint);

	// output
	bool bShowPlanets = false;
	if ( m_hoverPathPointIdx != -1 )
	{
		g.setColor(0xff0000);
		m_ship.drawThrustLine(g, m_hoverPathPointIdx);

		// also note the day
		int daynum = (m_hoverPathPointIdx*86400)/(int)POINTS_TIME + 1;
		FGString out;
		out.set("Day ");
		out.add(daynum);

		// report distances
		int emDist = (int)FGDoubleGeometry::getDistance(m_earthPath.m_points[m_hoverPathPointIdx], m_marsPath.m_points[m_hoverPathPointIdx]);
		int ehDist = (int)FGDoubleGeometry::getDistance(m_earthPath.m_points[m_hoverPathPointIdx], m_ship.m_points[m_hoverPathPointIdx]);
		int mhDist = (int)FGDoubleGeometry::getDistance(m_marsPath.m_points[m_hoverPathPointIdx], m_ship.m_points[m_hoverPathPointIdx]);
		out.add("\nE-M Dist: ");
		addDistInfo(out, emDist);
		out.add("\nE-H Dist: ");
		addDistInfo(out, ehDist);
		out.add("\nH-M Dist: ");
		addDistInfo(out, mhDist);
		m_font.drawText(g, out.getNativeString(), 0, 0, m_screenW);

		bShowPlanets = true;
	}

	if ( m_uiMode == UI_ADJUSTINGMARS ) bShowPlanets = true;
	if ( isKeyDown(17) ) bShowPlanets = true;

	if ( bShowPlanets )
	{
		int idx = m_hoverPathPointIdx;
		if ( idx == -1 )
		{
			// just show the start point
			idx = 0;
		}

		// draw planets
		if ( m_bShowVenus )
		{
			g.setColor(m_venus.m_color);
			drawPathObject(g, &m_venusPath, m_hoverPathPointIdx);
		}

		g.setColor(m_earth.m_color);
		drawPathObject(g, &m_earthPath, m_hoverPathPointIdx);

		g.setColor(m_mars.m_color);
		drawPathObject(g, &m_marsPath, m_hoverPathPointIdx);
	}

	// message
	if ( m_msg.length() > 0 )
	{
		m_font.setJustify(FGFont::JUSTIFY_CENTER);
		m_font.drawText(g, m_msg.getNativeString(), 0, 0, m_screenW);
		m_font.setJustify(FGFont::JUSTIFY_LEFT);
	}
}