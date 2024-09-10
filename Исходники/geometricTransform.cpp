Matrix3d computeTform(
    const Matrix2Xd& pointsFrom, const Matrix2Xd& pointsTo,
    const VectorXd& indices ) {
  Matrix3d normMatFrom;
  Matrix3d normMatTo;
  Matrix3d T = computeSimilarity(
    normalizePoints( pointsFrom, indices, normMatFrom ),
    normalizePoints( pointsTo, indices, normMatTo ) );
  return normMatFrom.transpose() * ( T * normMatTo.transpose().inverse() );
}