bool AffineMapMetric::evaluate( PatchData& pd, size_t handle, double& value, MsqError& err )
{
  Sample s = ElemSampleQM::sample( handle );
  size_t e = ElemSampleQM::  elem( handle );
  MsqMeshEntity& elem = pd.element_by_index( e );
  EntityTopology type = elem.get_element_type();
  unsigned edim = TopologyInfo::dimension( type );
  const size_t* conn = elem.get_vertex_index_array();
  
    // This metric only supports sampling at corners, except for simplices.
    // If element is a simpex, then the Jacobian is constant over a linear 
    // element.  In this case, always evaluate at any vertex.
  //unsigned corner = s.number;
  if (s.dimension != 0) {
    if (type == TRIANGLE || type == TETRAHEDRON)
      /*corner = 0*/;
    else {
      MSQ_SETERR(err)("Invalid sample point for AffineMapMetric", MsqError::UNSUPPORTED_ELEMENT );
      return false;
    }
  }
  
  bool rval;
  if (edim == 3) { // 3x3 or 3x2 targets ?
    Vector3D c[3] = { Vector3D(0,0,0), Vector3D(0,0,0), Vector3D(0,0,0) };
    unsigned n;
    const unsigned* adj = TopologyInfo::adjacent_vertices( type, s.number, n );
    c[0] = pd.vertex_by_index( conn[adj[0]] ) - pd.vertex_by_index( conn[s.number] );
    c[1] = pd.vertex_by_index( conn[adj[1]] ) - pd.vertex_by_index( conn[s.number] );
    c[2] = pd.vertex_by_index( conn[adj[2]] ) - pd.vertex_by_index( conn[s.number] );
    MsqMatrix<3,3> A;
    A.set_column( 0, MsqMatrix<3,1>(c[0].to_array()) );
    A.set_column( 1, MsqMatrix<3,1>(c[1].to_array()) );
    A.set_column( 2, MsqMatrix<3,1>(c[2].to_array()) );
    if (type == TETRAHEDRON)
      A = A * TET_XFORM;

    MsqMatrix<3,3> W;
    targetCalc->get_3D_target( pd, e, s, W, err ); MSQ_ERRZERO(err);
    rval = targetMetric->evaluate( A * inverse(W), value, err ); MSQ_ERRZERO(err);
  }
  else {
    Vector3D c[2] = { Vector3D(0,0,0), Vector3D(0,0,0) };
    unsigned n;
    const unsigned* adj = TopologyInfo::adjacent_vertices( type, s.number, n );
    c[0] = pd.vertex_by_index( conn[adj[0]] ) - pd.vertex_by_index( conn[s.number] );
    c[1] = pd.vertex_by_index( conn[adj[1]] ) - pd.vertex_by_index( conn[s.number] );
    MsqMatrix<3,2> App;
    App.set_column( 0, MsqMatrix<3,1>(c[0].to_array()) );
    App.set_column( 1, MsqMatrix<3,1>(c[1].to_array()) );
    
    MsqMatrix<3,2> Wp;
    targetCalc->get_surface_target( pd, e, s, Wp, err ); MSQ_ERRZERO(err);

    MsqMatrix<2,2> A, W;
    MsqMatrix<3,2> RZ;
    surface_to_2d( App, Wp, W, RZ );
    A = transpose(RZ) * App;
    if (type == TRIANGLE)
      A = A * TRI_XFORM;
    
    rval = targetMetric->evaluate( A*inverse(W), value, err ); MSQ_ERRZERO(err);
  }
  
    // apply target weight to value
  if (weightCalc) {
    double ck = weightCalc->get_weight( pd, e, s, err ); MSQ_ERRZERO(err);
    value *= ck;
  }
  return rval;
}