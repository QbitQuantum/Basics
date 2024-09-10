 /* ************************************************************************* */
 Matrix GaussianFactorGraph::augmentedHessian(
     boost::optional<const Ordering&> optionalOrdering) const {
   // combine all factors and get upper-triangular part of Hessian
   HessianFactor combined(*this, Scatter(*this, optionalOrdering));
   Matrix result = combined.info();
   // Fill in lower-triangular part of Hessian
   result.triangularView<Eigen::StrictlyLower>() = result.transpose();
   return result;
 }