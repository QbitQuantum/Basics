//Compute the transform matrix that the cluster will transform the vertex.
void compute_cluster_deformation(FbxAMatrix& pGlobalPosition,
                                 FbxMesh* pMesh,
                                 FbxCluster* pCluster,
                                 FbxAMatrix& pVertexTransformMatrix,
                                 FbxTime pTime,
                                 FbxPose* pPose)
{
  FbxCluster::ELinkMode lClusterMode = pCluster->GetLinkMode();

  FbxAMatrix lReferenceGlobalInitPosition;
  FbxAMatrix lReferenceGlobalCurrentPosition;
  FbxAMatrix lAssociateGlobalInitPosition;
  FbxAMatrix lAssociateGlobalCurrentPosition;
  FbxAMatrix lClusterGlobalInitPosition;
  FbxAMatrix lClusterGlobalCurrentPosition;

  FbxAMatrix lReferenceGeometry;
  FbxAMatrix lAssociateGeometry;
  FbxAMatrix lClusterGeometry;

  FbxAMatrix lClusterRelativeInitPosition;
  FbxAMatrix lClusterRelativeCurrentPositionInverse;

  if(lClusterMode == FbxCluster::eAdditive && pCluster->GetAssociateModel()) {
    pCluster->GetTransformAssociateModelMatrix(lAssociateGlobalInitPosition);
    // Geometric transform of the model
    lAssociateGeometry = get_geometry(pCluster->GetAssociateModel());
    lAssociateGlobalInitPosition *= lAssociateGeometry;
    lAssociateGlobalCurrentPosition = get_global_position(pCluster->GetAssociateModel(), pTime, pPose);

    pCluster->GetTransformMatrix(lReferenceGlobalInitPosition);
    // Multiply lReferenceGlobalInitPosition by Geometric Transformation
    lReferenceGeometry = get_geometry(pMesh->GetNode());
    lReferenceGlobalInitPosition *= lReferenceGeometry;
    lReferenceGlobalCurrentPosition = pGlobalPosition;

    // Get the link initial global position and the link current global position.
    pCluster->GetTransformLinkMatrix(lClusterGlobalInitPosition);
    // Multiply lClusterGlobalInitPosition by Geometric Transformation
    lClusterGeometry = get_geometry(pCluster->GetLink());
    lClusterGlobalInitPosition *= lClusterGeometry;
    lClusterGlobalCurrentPosition = get_global_position(pCluster->GetLink(), pTime, pPose);

    // Compute the shift of the link relative to the reference.
    //ModelM-1 * AssoM * AssoGX-1 * LinkGX * LinkM-1*ModelM
    pVertexTransformMatrix = lReferenceGlobalInitPosition.Inverse() * lAssociateGlobalInitPosition * lAssociateGlobalCurrentPosition.Inverse() *
                             lClusterGlobalCurrentPosition * lClusterGlobalInitPosition.Inverse() * lReferenceGlobalInitPosition;
  } else {
    pCluster->GetTransformMatrix(lReferenceGlobalInitPosition);
    lReferenceGlobalCurrentPosition = pGlobalPosition;
    // Multiply lReferenceGlobalInitPosition by Geometric Transformation
    lReferenceGeometry = get_geometry(pMesh->GetNode());
    lReferenceGlobalInitPosition *= lReferenceGeometry;

    // Get the link initial global position and the link current global position.
    pCluster->GetTransformLinkMatrix(lClusterGlobalInitPosition);
    lClusterGlobalCurrentPosition = get_global_position(pCluster->GetLink(), pTime, pPose);

    // Compute the initial position of the link relative to the reference.
    lClusterRelativeInitPosition = lClusterGlobalInitPosition.Inverse() * lReferenceGlobalInitPosition;

    // Compute the current position of the link relative to the reference.
    lClusterRelativeCurrentPositionInverse = lReferenceGlobalCurrentPosition.Inverse() * lClusterGlobalCurrentPosition;

    // Compute the shift of the link relative to the reference.
    pVertexTransformMatrix = lClusterRelativeCurrentPositionInverse * lClusterRelativeInitPosition;
  }
}