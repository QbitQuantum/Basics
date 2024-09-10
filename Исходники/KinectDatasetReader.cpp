void KinectDatasetReader::MoveGroundTruthsToOrigin()
{
    Eigen::Isometry3f origin = mGroundTruth[0].LocalTransform;
    origin = origin.inverse();
    
    for(size_t i = 0; i < mGroundTruth.size(); i++)
        mGroundTruth[i].LocalTransform = origin * mGroundTruth[i].LocalTransform;
}