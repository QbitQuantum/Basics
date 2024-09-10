  // -----------------------------------------------------------------------------
  bool Compute( vector< double > &                  positions,
                gp_Pnt                              pIn,
                gp_Pnt                              pOut,
                SMESH_Mesh&                         aMesh,
                const StdMeshers_LayerDistribution* hyp)
  {
    double len = pIn.Distance( pOut );
    if ( len <= DBL_MIN ) return error("Too close points of inner and outer shells");

    if ( !hyp || !hyp->GetLayerDistribution() )
      return error( "Invalid LayerDistribution hypothesis");
    myUsedHyps.clear();
    myUsedHyps.push_back( hyp->GetLayerDistribution() );

    TopoDS_Edge edge = BRepBuilderAPI_MakeEdge( pIn, pOut );
    SMESH_Hypothesis::Hypothesis_Status aStatus;
    if ( !StdMeshers_Regular_1D::CheckHypothesis( aMesh, edge, aStatus ))
      return error( "StdMeshers_Regular_1D::CheckHypothesis() failed "
                    "with LayerDistribution hypothesis");

    BRepAdaptor_Curve C3D(edge);
    double f = C3D.FirstParameter(), l = C3D.LastParameter();
    list< double > params;
    if ( !StdMeshers_Regular_1D::computeInternalParameters( aMesh, C3D, len, f, l, params, false ))
      return error("StdMeshers_Regular_1D failed to compute layers distribution");

    positions.clear();
    positions.reserve( params.size() );
    for (list<double>::iterator itU = params.begin(); itU != params.end(); itU++)
      positions.push_back( *itU / len );
    return true;
  }