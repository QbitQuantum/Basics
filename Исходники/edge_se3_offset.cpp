  void EdgeSE3Offset::initialEstimate(const OptimizableGraph::VertexSet& from_, OptimizableGraph::Vertex* /*to_*/) {
    VertexSE3 *from = static_cast<VertexSE3*>(_vertices[0]);
    VertexSE3 *to   = static_cast<VertexSE3*>(_vertices[1]);

    Eigen::Isometry3d virtualMeasurement = _cacheFrom->offsetParam()->offset() * measurement() * _cacheTo->offsetParam()->offset().inverse();
    
    if (from_.count(from) > 0) {
      to->setEstimate(from->estimate() * virtualMeasurement);
    } else
      from->setEstimate(to->estimate() * virtualMeasurement.inverse());
  }