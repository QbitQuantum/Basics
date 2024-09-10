// Rotates/translates the whole map and all keyFrames
void MapMakerServerBase::ApplyGlobalTransformationToMap(TooN::SE3<> se3NewFromOld)
{
  for (MultiKeyFramePtrList::iterator it = mMap.mlpMultiKeyFrames.begin(); it != mMap.mlpMultiKeyFrames.end(); ++it)
  {
    MultiKeyFrame& mkf = *(*it);
    mkf.mse3BaseFromWorld = mkf.mse3BaseFromWorld * se3NewFromOld.inverse();
    for (KeyFramePtrMap::iterator jiter = mkf.mmpKeyFrames.begin(); jiter != mkf.mmpKeyFrames.end(); ++jiter)
    {
      KeyFrame& kf = *(jiter->second);
      kf.mse3CamFromWorld = kf.mse3CamFromBase * mkf.mse3BaseFromWorld; 
    }
  }

  for (MapPointPtrList::iterator it = mMap.mlpPoints.begin(); it != mMap.mlpPoints.end(); ++it)
  {
    MapPoint& point = *(*it);
    point.mv3WorldPos = se3NewFromOld * point.mv3WorldPos;
    point.RefreshPixelVectors();
  }
}