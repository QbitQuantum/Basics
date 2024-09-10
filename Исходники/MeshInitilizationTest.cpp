void test( const std::string & meshFile, const uint_t numProcesses, const uint_t numTotalBlocks )
{
   auto mesh = make_shared<MeshType>();
   mesh::readAndBroadcast( meshFile, *mesh);

   auto aabb = computeAABB( *mesh );

   auto domainAABB = aabb.getScaled( typename MeshType::Scalar(3) );

   auto triDist = make_shared< mesh::TriangleDistance<MeshType> >( mesh );
   auto distanceOctree = make_shared< DistanceOctree< MeshType > >( triDist );

   const real_t meshVolume  = real_c( computeVolume( *mesh ) );
   const real_t blockVolume = meshVolume / real_c( numTotalBlocks );
   static const real_t cellsPersBlock = real_t(1000);
   const real_t cellVolume = blockVolume / cellsPersBlock;
   const Vector3<real_t> cellSize( std::pow( cellVolume, real_t(1) / real_t(3) ) );

   ComplexGeometryStructuredBlockforestCreator bfc( domainAABB, cellSize, makeExcludeMeshInterior( distanceOctree, cellSize.min() ) );
   auto wl = mesh::makeMeshWorkloadMemory( distanceOctree, cellSize );
   wl.setInsideCellWorkload(0);
   wl.setOutsideCellWorkload(1);
   wl.setForceZeroMemoryOnZeroWorkload(true);
   bfc.setWorkloadMemorySUIDAssignmentFunction( wl );
   bfc.setRefinementSelectionFunction( makeRefinementSelection( distanceOctree, 5, cellSize[0], cellSize[0] * real_t(5) ) );

   WALBERLA_LOG_INFO_ON_ROOT( "Creating SBF with StaticLevelwiseCurveBalanceWeighted Partitioner" );
   bfc.setTargetProcessAssignmentFunction( blockforest::StaticLevelwiseCurveBalanceWeighted() );
   auto sbf_default = bfc.createSetupBlockForest( Vector3<uint_t>(64,64,64), numProcesses );
   //sbf_default->writeVTKOutput("sbf_default");
   WALBERLA_LOG_INFO_ON_ROOT( sbf_default->toString() );

   return;
#ifdef WALBERLA_BUILD_WITH_PARMETIS

   WALBERLA_LOG_INFO_ON_ROOT( "Creating SBF with ParMetis (PART_KWAY, no commweights)" );
   bfc.setTargetProcessAssignmentFunction( blockforest::StaticLevelwiseParMetis( blockforest::StaticLevelwiseParMetis::PARMETIS_PART_KWAY ) );
   auto sbf = bfc.createSetupBlockForest( numTotalBlocks, numProcesses );
   //sbf->writeVTKOutput("sbf");
   WALBERLA_LOG_INFO_ON_ROOT( sbf->toString() );


   WALBERLA_LOG_INFO_ON_ROOT( "Creating SBF with ParMetis (PART_KWAY, commweights)" );
   bfc.setTargetProcessAssignmentFunction( blockforest::StaticLevelwiseParMetis( commInXDirection, blockforest::StaticLevelwiseParMetis::PARMETIS_PART_KWAY ) );
   auto sbf_edge = bfc.createSetupBlockForest( numTotalBlocks, numProcesses );
   //sbf_edge->writeVTKOutput("sbf_edge");
   WALBERLA_LOG_INFO_ON_ROOT( sbf_edge->toString() );

   WALBERLA_LOG_INFO_ON_ROOT( "Creating SBF with ParMetis (PART_GEOM_KWAY, no commweights)" );
   bfc.setTargetProcessAssignmentFunction( blockforest::StaticLevelwiseParMetis( blockforest::StaticLevelwiseParMetis::PARMETIS_PART_GEOM_KWAY ) );
   auto sbf_geom = bfc.createSetupBlockForest( numTotalBlocks, numProcesses );
   //sbf_geom->writeVTKOutput("sbf_geom");
   WALBERLA_LOG_INFO_ON_ROOT( sbf_geom->toString() );


   WALBERLA_LOG_INFO_ON_ROOT( "Creating SBF with ParMetis (PART_GEOM_KWAY, commweights)" );
   bfc.setTargetProcessAssignmentFunction( blockforest::StaticLevelwiseParMetis( commInXDirection, blockforest::StaticLevelwiseParMetis::PARMETIS_PART_GEOM_KWAY ) );
   auto sbf_geom_edge = bfc.createSetupBlockForest( numTotalBlocks, numProcesses );
   //sbf_geom_edge->writeVTKOutput("sbf_geom_edge");
   WALBERLA_LOG_INFO_ON_ROOT( sbf_geom_edge->toString() );

#endif
}