void GraphSLAM::checkCovariance(OptimizableGraph::VertexSet& vset){
  ///////////////////////////////////
  // we need now to compute the marginal covariances of all other vertices w.r.t the newly inserted one

  CovarianceEstimator ce(_graph);

  ce.setVertices(vset);
  ce.setGauge(_lastVertex);
  
  ce.compute();

  assert(!_lastVertex->fixed() && "last Vertex is fixed");
  assert(_firstRobotPose->fixed() && "first Vertex is not fixed");
  
  OptimizableGraph::VertexSet tmpvset = vset;
  for (OptimizableGraph::VertexSet::iterator it = tmpvset.begin(); it != tmpvset.end(); it++){
    VertexSE2 *vertex = (VertexSE2*) *it;
    
    MatrixXd Pv = ce.getCovariance(vertex);
    Matrix2d Pxy; Pxy << Pv(0,0), Pv(0,1), Pv(1,0), Pv(1,1);
    SE2 delta = vertex->estimate().inverse() * _lastVertex->estimate();	
    Vector2d hxy (delta.translation().x(), delta.translation().y());
    double perceptionRange =1;
    if (hxy.x()-perceptionRange>0) 
      hxy.x() -= perceptionRange;
    else if (hxy.x()+perceptionRange<0)
      hxy.x() += perceptionRange;
    else
      hxy.x() = 0;

    if (hxy.y()-perceptionRange>0) 
      hxy.y() -= perceptionRange;
    else if (hxy.y()+perceptionRange<0)
      hxy.y() += perceptionRange;
    else
      hxy.y() = 0;
    
    double d2 = hxy.transpose() * Pxy.inverse() * hxy;
    if (d2 > 5.99)
      vset.erase(*it);
 
  }
  
}