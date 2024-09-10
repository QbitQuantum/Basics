void MapIcons::paintSpawnIcon(MapParameters& param, 
			      QPainter& p, 
			      const MapIcon& mapIcon,
			      const Spawn* spawn, 
			      const EQPoint& location,
			      const QPoint& point)
{
  // ------------------------
  // Draw Walk Path
  if (mapIcon.showWalkPath() ||
      (m_showNPCWalkPaths && spawn->isNPC()))
  {
    SpawnTrackListIterator trackIt(spawn->trackList());
    
    const SpawnTrackPoint* trackPoint = trackIt.current();
    if (trackPoint)
    {
      if (!mapIcon.useWalkPathPen())
	p.setPen(blue);
      else
	p.setPen(mapIcon.walkPathPen());

      p.moveTo (param.calcXOffsetI(trackPoint->x()), 
		param.calcYOffsetI(trackPoint->y()));
      
      while ((trackPoint = ++trackIt) != NULL)
	p.lineTo (param.calcXOffsetI (trackPoint->x()), 
		  param.calcYOffsetI (trackPoint->y()));
      
      p.lineTo (point.x(), point.y());
    }
  }

  // Draw Line
  if (mapIcon.showLine0())
  {
    p.setPen(mapIcon.line0Pen());
    p.drawLine(param.playerXOffset(), 
	       param.playerYOffset(),
	       point.x(), point.y());
  }

  // calculate distance and draw distance related lines
  uint32_t distance = UINT32_MAX;
  if (mapIcon.line1Distance() || mapIcon.line2Distance() || 
      m_showSpawnNames)
  {
    if (!showeq_params->fast_machine)
      distance = location.calcDist2DInt(param.player());
    else
      distance = (int)location.calcDist(param.player());
    
    if (mapIcon.line1Distance() > distance)
    {
      p.setPen(mapIcon.line1Pen());
      p.drawLine(param.playerXOffset(), 
		 param.playerYOffset(),
		 point.x(), point.y());
    }

    if (mapIcon.line2Distance() > distance)
    {
      p.setPen(mapIcon.line2Pen());
      p.drawLine(param.playerXOffset(), 
		 param.playerYOffset(),
		 point.x(), point.y());
    }
  }

  // Draw Spawn Names
  if (mapIcon.showName() || 
      (m_showSpawnNames && (distance < m_fovDistance)))
  {
    QString spawnNameText;
    
    spawnNameText.sprintf("%2d: %s",
			  spawn->level(),
			  (const char*)spawn->name());
    
    QFontMetrics fm(param.font());
    int width = fm.width(spawnNameText);
    p.setPen(gray);
    p.drawText(point.x() - (width / 2),
	       point.y() + fm.height() + 1, spawnNameText);
  }
  
  // Draw the Icon
  if (mapIcon.image() && 
      (!mapIcon.imageFlash() || m_flash) &&
      (mapIcon.imageStyle() != tIconStyleNone))
  {
    if (mapIcon.imageUseSpawnColorPen())
    {
      QPen pen = mapIcon.imagePen();
      pen.setColor(pickSpawnColor(spawn));
      p.setPen(pen);
    }
    else
      p.setPen(mapIcon.imagePen());

    if (mapIcon.imageUseSpawnColorBrush())
    {
      QBrush brush = mapIcon.imageBrush();
      brush.setColor(pickSpawnColor(spawn));
      p.setBrush(brush);
    }
    else
      p.setBrush(mapIcon.imageBrush());

    mapIcon.paintIconImage(mapIcon.imageStyle(), p, point, 
			   *m_mapIconSizes[mapIcon.imageSize()],
			   *m_mapIconSizesWH[mapIcon.imageSize()]);
  }

  // Draw the highlight
  if (mapIcon.highlight() && 
      (!mapIcon.highlightFlash() || m_flash) &&
      (mapIcon.highlightStyle() != tIconStyleNone))
  {
    if (mapIcon.highlightUseSpawnColorPen())
    {
      QPen pen = mapIcon.highlightPen();
      pen.setColor(pickSpawnColor(spawn));
      p.setPen(pen);
    }
    else
      p.setPen(mapIcon.highlightPen());

    if (mapIcon.highlightUseSpawnColorBrush())
    {
      QBrush brush = mapIcon.highlightBrush();
      brush.setColor(pickSpawnColor(spawn));
      p.setBrush(brush);
    }
    else
      p.setBrush(mapIcon.highlightBrush());

    mapIcon.paintIconImage(mapIcon.highlightStyle(), p, point, 
			   *m_mapIconSizes[mapIcon.highlightSize()],
			   *m_mapIconSizesWH[mapIcon.highlightSize()]);
  }
}