void BackgroundImageGeometry::setRepeatY(const FillLayer& fillLayer,
                                         LayoutUnit unsnappedTileHeight,
                                         LayoutUnit snappedAvailableHeight,
                                         LayoutUnit unsnappedAvailableHeight,
                                         LayoutUnit extraOffset) {
  // We would like to identify the phase as a fraction of the image size in the
  // absence of snapping, then re-apply it to the snapped values. This is to
  // handle large positions.
  if (unsnappedTileHeight) {
    LayoutUnit computedYPosition = roundedMinimumValueForLength(
        fillLayer.yPosition(), unsnappedAvailableHeight);
    if (fillLayer.backgroundYOrigin() == BottomEdge) {
      float numberOfTilesInPosition =
          (snappedAvailableHeight - computedYPosition + extraOffset).toFloat() /
          unsnappedTileHeight.toFloat();
      float fractionalPositionWithinTile =
          numberOfTilesInPosition - truncf(numberOfTilesInPosition);
      setPhaseY(LayoutUnit(
          roundf(fractionalPositionWithinTile * tileSize().height())));
    } else {
      float numberOfTilesInPosition =
          (computedYPosition + extraOffset).toFloat() /
          unsnappedTileHeight.toFloat();
      float fractionalPositionWithinTile =
          1.0f - (numberOfTilesInPosition - truncf(numberOfTilesInPosition));
      setPhaseY(LayoutUnit(
          roundf(fractionalPositionWithinTile * tileSize().height())));
    }
  } else {
    setPhaseY(LayoutUnit());
  }
  setSpaceSize(LayoutSize(spaceSize().width(), LayoutUnit()));
}