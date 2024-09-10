/* ************************************************************************* */
double LinearizedHessianFactor::error(const Values& c) const {

  // Construct an error vector in key-order from the Values
  Vector dx = Vector::Zero(dim());
  size_t index = 0;
  for(unsigned int i = 0; i < this->size(); ++i){
    Key key = this->keys()[i];
    const Value& newPt = c.at(key);
    const Value& linPt = lin_points_.at(key);
    dx.segment(index, linPt.dim()) = linPt.localCoordinates_(newPt);
    index += linPt.dim();
  }

  // error 0.5*(f - 2*x'*g + x'*G*x)
  double f = constantTerm();
  double xtg = dx.dot(linearTerm());
  double xGx = dx.transpose() * squaredTerm() * dx;

  return 0.5 * (f - 2.0 * xtg +  xGx);
}