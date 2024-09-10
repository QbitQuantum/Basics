bool Recording::computeActiveSegments(const util::Params& params, const Scan& scene,
                                      float maxDistToSegment, float maxDistGaze,
                                      bool forceRecompute /* = false */) {
  if (hasActiveSegments && !forceRecompute) {
    return true;
  }

  cout << "[Recording] Computing actSegs: " << id << "...";
  const int kNearestSegsPerJoint = params.get<int>("Interaction.kNearestSegsPerJoint");
  const bool ignoreInferredJoints = params.get<bool>("Interaction.ignoreInferredJoints");
  const float maxSegmentSizeRatio = params.get<float>("Interaction.maxSegmentSizeRatio");

  for (Interaction* in : interactions) {
    const int numSkels = static_cast<int>(in->skelRange.size());
    in->jointSegments.resize(numSkels);
    in->activeSegments.clear();

#pragma omp parallel for
    for (int iSkel = 0; iSkel < numSkels; iSkel++) {
      const Skeleton& skel = in->skelRange[iSkel];
      scene.getActiveSegments(skel, ignoreInferredJoints, kNearestSegsPerJoint,
                              maxDistToSegment, maxDistGaze, maxSegmentSizeRatio,
                              &in->jointSegments[iSkel]);
    }

    // Also accumulate all segs in activeSegments
    for (int iSkel = 0; iSkel < numSkels; iSkel++) {
      const auto& segs = in->jointSegments[iSkel];
      for (const auto& jointSegs : segs) {
        in->activeSegments.insert(jointSegs.begin(), jointSegs.end());
      }
    }
  }

  cout << "done." << endl;
  hasActiveSegments = true;
  return true;
}