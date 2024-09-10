void TSShapeLoader::generateGroundAnimation(TSShape::Sequence& seq, const AppSequence* appSeq)
{
   seq.firstGroundFrame = shape->groundTranslations.size();
   seq.numGroundFrames = 0;

   if (!boundsNode)
      return;

   // Check if the bounds node is animated by this sequence
   seq.numGroundFrames = (S32)((seq.duration + 0.25f/AppGroundFrameRate) * AppGroundFrameRate);

   seq.flags |= TSShape::MakePath;

   // Get ground transform at the start of the sequence
   MatrixF invStartMat = boundsNode->getNodeTransform(appSeq->getStart());
   zapScale(invStartMat);
   invStartMat.inverse();

   for (int iFrame = 0; iFrame < seq.numGroundFrames; iFrame++)
   {
      F32 time = appSeq->getStart() + seq.duration * iFrame / getMax(1, seq.numGroundFrames - 1);

      // Determine delta bounds node transform at 't'
      MatrixF mat = boundsNode->getNodeTransform(time);
      zapScale(mat);
      mat = invStartMat * mat;

      // Add ground transform
      Quat16 rotation;
      rotation.set(QuatF(mat));
      shape->groundTranslations.push_back(mat.getPosition());
      shape->groundRotations.push_back(rotation);
   }
}