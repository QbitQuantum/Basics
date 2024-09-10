FbxAMatrix	LoaderFbxMesh::parseTransformMatrixAssociateModel(FbxCluster* cluster, FbxMesh* mesh, FbxPose* fbxPose, FbxAMatrix globalPosition)
{
	FbxAMatrix associateGeometry;
	FbxAMatrix associateGlobalInitPosition;
	FbxAMatrix associateGlobalCurrentPosition;

	FbxAMatrix referenceGeometry;
	FbxAMatrix referenceGlobalInitPosition;
	FbxAMatrix referenceGlobalCurrentPosition;

	FbxAMatrix clusterGeometry;
	FbxAMatrix clusterGlobalInitPosition;
	FbxAMatrix clusterGlobalCurrentPosition;

	FbxTime time(0);

	cluster->GetTransformAssociateModelMatrix(associateGlobalInitPosition);
	associateGeometry = getGeometry(cluster->GetAssociateModel());
	associateGlobalInitPosition *= associateGeometry;
	associateGlobalCurrentPosition = getGlobalPosition(cluster->GetAssociateModel(), time, fbxPose, nullptr);

	cluster->GetTransformMatrix(referenceGlobalInitPosition);
	referenceGeometry = getGeometry(mesh->GetNode());
	referenceGlobalInitPosition *= referenceGeometry;
	referenceGlobalCurrentPosition = globalPosition;

	cluster->GetTransformLinkMatrix(clusterGlobalInitPosition);
	clusterGeometry = getGeometry(cluster->GetLink());
	clusterGlobalInitPosition *= clusterGeometry;
	clusterGlobalCurrentPosition = getGlobalPosition(cluster->GetLink(), time, fbxPose, nullptr);

	FbxAMatrix offsetMatrix;
	offsetMatrix = referenceGlobalInitPosition.Inverse() * associateGlobalInitPosition * associateGlobalCurrentPosition.Inverse() *
			clusterGlobalCurrentPosition * clusterGlobalInitPosition.Inverse() * referenceGlobalInitPosition;

	return offsetMatrix;
}