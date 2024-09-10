void
MapWindow::DrawGlideThroughTerrain(Canvas &canvas) const
{
  if (SettingsComputer().FinalGlideTerrain) {
    canvas.select(MapGfx.hpTerrainLineBg);
    canvas.polyline(Groundline, TERRAIN_ALT_INFO::NUMTERRAINSWEEPS + 1);

    canvas.select(MapGfx.hpTerrainLine);
    canvas.polyline(Groundline, TERRAIN_ALT_INFO::NUMTERRAINSWEEPS + 1);
  }

  if (!Basic().flight.Flying)
    return;

  if (!Calculated().TerrainWarningLocation.is_null()) {
    POINT sc;
    if (projection.LonLat2ScreenIfVisible(Calculated().TerrainWarningLocation,
                                          &sc))
      MapGfx.hTerrainWarning.draw(canvas, bitmap_canvas, sc.x, sc.y);
  }
}