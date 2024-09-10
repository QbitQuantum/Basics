//! Build the mesh object
Teuchos::RCP<STK_Interface> CubeTetMeshFactory::buildMesh(stk_classic::ParallelMachine parallelMach) const
{
  PANZER_FUNC_TIME_MONITOR("panzer::CubeTetMeshFactory::buildMesh()");

   // build all meta data
   RCP<STK_Interface> mesh = buildUncommitedMesh(parallelMach);

   // commit meta data
   mesh->initialize(parallelMach);

   // build bulk data
   completeMeshConstruction(*mesh,parallelMach);

   return mesh;
}