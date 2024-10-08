//--------------------------------------------------------------------------
//-------- execute ---------------------------------------------------------
//--------------------------------------------------------------------------
void
AssembleContinuityElemSolverAlgorithm::execute()
{

  stk::mesh::MetaData & meta_data = realm_.meta_data();

  const int nDim = meta_data.spatial_dimension();

  // time step
  const double dt = realm_.get_time_step();
  const double gamma1 = realm_.get_gamma1();
  const double projTimeScale = dt/gamma1;

  // deal with interpolation procedure
  const double interpTogether = realm_.get_mdot_interp();
  const double om_interpTogether = 1.0-interpTogether;

  // space for LHS/RHS; nodesPerElem*nodesPerElem and nodesPerElem
  std::vector<double> lhs;
  std::vector<double> rhs;
  std::vector<stk::mesh::Entity> connected_nodes;

  // supplemental algorithm setup
  const size_t supplementalAlgSize = supplementalAlg_.size();
  for ( size_t i = 0; i < supplementalAlgSize; ++i )
    supplementalAlg_[i]->setup();

  // nodal fields to gather
  std::vector<double> ws_vrtm;
  std::vector<double> ws_Gpdx;
  std::vector<double> ws_coordinates;
  std::vector<double> ws_pressure;
  std::vector<double> ws_density;

  // geometry related to populate
  std::vector<double> ws_scs_areav;
  std::vector<double> ws_dndx;
  std::vector<double> ws_dndx_lhs;
  std::vector<double> ws_deriv;
  std::vector<double> ws_det_j;
  std::vector<double> ws_shape_function;

  // integration point data that depends on size
  std::vector<double> uIp(nDim);
  std::vector<double> rho_uIp(nDim);
  std::vector<double> GpdxIp(nDim);
  std::vector<double> dpdxIp(nDim);

  // pointers to everyone...
  double *p_uIp = &uIp[0];
  double *p_rho_uIp = &rho_uIp[0];
  double *p_GpdxIp = &GpdxIp[0];
  double *p_dpdxIp = &dpdxIp[0];

  // deal with state
  ScalarFieldType &densityNp1 = density_->field_of_state(stk::mesh::StateNP1);

  // define some common selectors
  stk::mesh::Selector s_locally_owned_union = meta_data.locally_owned_part()
    & stk::mesh::selectUnion(partVec_) 
    & !(realm_.get_inactive_selector());

  stk::mesh::BucketVector const& elem_buckets =
    realm_.get_buckets( stk::topology::ELEMENT_RANK, s_locally_owned_union );
  for ( stk::mesh::BucketVector::const_iterator ib = elem_buckets.begin();
        ib != elem_buckets.end() ; ++ib ) {
    stk::mesh::Bucket & b = **ib ;
    const stk::mesh::Bucket::size_type length   = b.size();

    // extract master element
    MasterElement *meSCS = realm_.get_surface_master_element(b.topology());
    MasterElement *meSCV = realm_.get_volume_master_element(b.topology());

    // extract master element specifics
    const int nodesPerElement = meSCS->nodesPerElement_;
    const int numScsIp = meSCS->numIntPoints_;
    const int *lrscv = meSCS->adjacentNodes();

    // resize some things; matrix related
    const int lhsSize = nodesPerElement*nodesPerElement;
    const int rhsSize = nodesPerElement;
    lhs.resize(lhsSize);
    rhs.resize(rhsSize);
    connected_nodes.resize(nodesPerElement);

    // algorithm related
    ws_vrtm.resize(nodesPerElement*nDim);
    ws_Gpdx.resize(nodesPerElement*nDim);
    ws_coordinates.resize(nodesPerElement*nDim);
    ws_pressure.resize(nodesPerElement);
    ws_density.resize(nodesPerElement);
    ws_scs_areav.resize(numScsIp*nDim);
    ws_dndx.resize(nDim*numScsIp*nodesPerElement);
    ws_dndx_lhs.resize(nDim*numScsIp*nodesPerElement);
    ws_deriv.resize(nDim*numScsIp*nodesPerElement);
    ws_det_j.resize(numScsIp);
    ws_shape_function.resize(numScsIp*nodesPerElement);

    // pointers
    double *p_lhs = &lhs[0];
    double *p_rhs = &rhs[0];
    double *p_vrtm = &ws_vrtm[0];
    double *p_Gpdx = &ws_Gpdx[0];
    double *p_coordinates = &ws_coordinates[0];
    double *p_pressure = &ws_pressure[0];
    double *p_density = &ws_density[0];
    double *p_scs_areav = &ws_scs_areav[0];
    double *p_dndx = &ws_dndx[0];
    double *p_dndx_lhs = reducedSensitivities_ ? &ws_dndx_lhs[0] : &ws_dndx[0];
    double *p_shape_function = &ws_shape_function[0];

    if ( shiftMdot_)
      meSCS->shifted_shape_fcn(&p_shape_function[0]);
    else
      meSCS->shape_fcn(&p_shape_function[0]);

    // resize possible supplemental element alg
    for ( size_t i = 0; i < supplementalAlgSize; ++i )
      supplementalAlg_[i]->elem_resize(meSCS, meSCV);

    for ( stk::mesh::Bucket::size_type k = 0 ; k < length ; ++k ) {

      // get elem
      stk::mesh::Entity elem = b[k];

      // zero lhs/rhs
      for ( int p = 0; p < lhsSize; ++p )
        p_lhs[p] = 0.0;
      for ( int p = 0; p < rhsSize; ++p )
        p_rhs[p] = 0.0;

      //===============================================
      // gather nodal data; this is how we do it now..
      //===============================================
      stk::mesh::Entity const *  node_rels = b.begin_nodes(k);
      int num_nodes = b.num_nodes(k);

      // sanity check on num nodes
      ThrowAssert( num_nodes == nodesPerElement );

      for ( int ni = 0; ni < num_nodes; ++ni ) {
        stk::mesh::Entity node = node_rels[ni];

        // set connected nodes
        connected_nodes[ni] = node;

        // pointers to real data
        const double * Gjp    = stk::mesh::field_data(*Gpdx_, node );
        const double * coords = stk::mesh::field_data(*coordinates_, node );
        const double * vrtm   = stk::mesh::field_data(*velocityRTM_, node );

        // gather scalars
        p_pressure[ni] = *stk::mesh::field_data(*pressure_, node );
        p_density[ni]  = *stk::mesh::field_data(densityNp1, node );

        // gather vectors
        const int niNdim = ni*nDim;
        for ( int j=0; j < nDim; ++j ) {
          p_vrtm[niNdim+j] = vrtm[j];
          p_Gpdx[niNdim+j] = Gjp[j];
          p_coordinates[niNdim+j] = coords[j];
        }
      }

      // compute geometry
      double scs_error = 0.0;
      meSCS->determinant(1, &p_coordinates[0], &p_scs_areav[0], &scs_error);

      // compute dndx for residual
      if ( shiftPoisson_ )
        meSCS->shifted_grad_op(1, &p_coordinates[0], &ws_dndx[0], &ws_deriv[0], &ws_det_j[0], &scs_error);
      else
        meSCS->grad_op(1, &p_coordinates[0], &ws_dndx[0], &ws_deriv[0], &ws_det_j[0], &scs_error);
      
      // compute dndx for LHS
      if ( reducedSensitivities_ )
        meSCS->shifted_grad_op(1, &p_coordinates[0], &ws_dndx_lhs[0], &ws_deriv[0], &ws_det_j[0], &scs_error);

      for ( int ip = 0; ip < numScsIp; ++ip ) {

        // left and right nodes for this ip
        const int il = lrscv[2*ip];
        const int ir = lrscv[2*ip+1];

        // corresponding matrix rows
        int rowL = il*nodesPerElement;
        int rowR = ir*nodesPerElement;

        // setup for ip values; sneak in geometry for possible reduced sens
        for ( int j = 0; j < nDim; ++j ) {
          p_uIp[j] = 0.0;
          p_rho_uIp[j] = 0.0;
          p_GpdxIp[j] = 0.0;
          p_dpdxIp[j] = 0.0;
        }
        double rhoIp = 0.0;

        const int offSet = ip*nodesPerElement;
        for ( int ic = 0; ic < nodesPerElement; ++ic ) {

          const double r = p_shape_function[offSet+ic];
          const double nodalPressure = p_pressure[ic];
          const double nodalRho = p_density[ic];

          rhoIp += r*nodalRho;

          double lhsfac = 0.0;
          const int offSetDnDx = nDim*nodesPerElement*ip + ic*nDim;
          for ( int j = 0; j < nDim; ++j ) {
            p_GpdxIp[j] += r*p_Gpdx[nDim*ic+j];
            p_uIp[j] += r*p_vrtm[nDim*ic+j];
            p_rho_uIp[j] += r*nodalRho*p_vrtm[nDim*ic+j];
            p_dpdxIp[j] += p_dndx[offSetDnDx+j]*nodalPressure;
            lhsfac += -p_dndx_lhs[offSetDnDx+j]*p_scs_areav[ip*nDim+j];
          }

          // assemble to lhs; left
          p_lhs[rowL+ic] += lhsfac;

          // assemble to lhs; right
          p_lhs[rowR+ic] -= lhsfac;

        }

        // assemble mdot
        double mdot = 0.0;
        for ( int j = 0; j < nDim; ++j ) {
          mdot += (interpTogether*p_rho_uIp[j] + om_interpTogether*rhoIp*p_uIp[j] 
                   - projTimeScale*(p_dpdxIp[j] - p_GpdxIp[j]))*p_scs_areav[ip*nDim+j];
        }

        // residual; left and right
        p_rhs[il] -= mdot/projTimeScale;
        p_rhs[ir] += mdot/projTimeScale;
      }

      // call supplemental
      for ( size_t i = 0; i < supplementalAlgSize; ++i )
        supplementalAlg_[i]->elem_execute( &lhs[0], &rhs[0], elem, meSCS, meSCV);

      apply_coeff(connected_nodes, rhs, lhs, __FILE__);

    }
  }
}