void
DrawTargetTiled::Stroke(const Path* aPath, const Pattern& aPattern, const StrokeOptions& aStrokeOptions, const DrawOptions& aDrawOptions)
{
  // Approximate the stroke extents, since Path::GetStrokeExtents can be slow
  Rect deviceRect = aPath->GetBounds(mTransform);
  deviceRect.Inflate(MaxStrokeExtents(aStrokeOptions, mTransform));
  for (size_t i = 0; i < mTiles.size(); i++) {
    if (!mTiles[i].mClippedOut &&
        deviceRect.Intersects(Rect(mTiles[i].mTileOrigin.x,
                                   mTiles[i].mTileOrigin.y,
                                   mTiles[i].mDrawTarget->GetSize().width,
                                   mTiles[i].mDrawTarget->GetSize().height))) {
      mTiles[i].mDrawTarget->Stroke(aPath, aPattern, aStrokeOptions, aDrawOptions);
    }
  }
}