//! Build the mesh object
Teuchos::RCP<STK_Interface> MultiBlockMeshFactory::buildMesh(stk::ParallelMachine parallelMach) const
{
   // build all meta data
   RCP<STK_Interface> mesh = buildUncommitedMesh(parallelMach);

   // commit meta data
   mesh->initialize(parallelMach);

   // build bulk data
   completeMeshConstruction(*mesh,parallelMach);

   return mesh;
}