 //--------------------------------------------------------------------------
 Distribution LossDistHomogeneous::operator()(const vector<Real>& nominals,
                                 const vector<Real>& probabilities) const {
 //--------------------------------------------------------------------------
     return operator()(nominals[0], probabilities);
 }