float LocalPCADistance<TImage>::Distance(const TImage* const image, const MatrixType& projectionMatrix,
                                         const VectorType& meanVector,
                                         const itk::ImageRegion<2>& region1,
                                         const itk::ImageRegion<2>& region2)
{
  VectorType vectorizedSource = PatchProjection<MatrixType, VectorType>::
                                  VectorizePatch(image, region1);
  vectorizedSource -= meanVector;

  VectorType vectorizedTarget = PatchProjection<MatrixType, VectorType>::
                                  VectorizePatch(image, region2);
  vectorizedTarget -= meanVector;

  assert(vectorizedSource.size() == projectionMatrix.rows());

  VectorType projectedSource = projectionMatrix.transpose() * vectorizedSource;

  VectorType projectedTarget = projectionMatrix.transpose() * vectorizedTarget;

  // Compute distance between patches in projected space
  float projectedDistance = (projectedSource - projectedTarget).squaredNorm();

  return projectedDistance;
}