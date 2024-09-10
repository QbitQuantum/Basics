//! Build the mesh object
Teuchos::RCP<STK_Interface> SculptMeshFactory::buildMesh(stk_classic::ParallelMachine parallelMach) const
{
   PANZER_FUNC_TIME_MONITOR("panzer::SculptMeshFactory::buildMesh()");

   RCP<STK_Interface> mesh = buildUncommitedMesh(parallelMach);

   // commit meta data
   mesh->initialize(parallelMach);

   // build bulk data
   completeMeshConstruction(*mesh,parallelMach);

   // wrtie exodus file
   //mesh->writeToExodus("STKSculptMesh.exo");
 
   return mesh;
}