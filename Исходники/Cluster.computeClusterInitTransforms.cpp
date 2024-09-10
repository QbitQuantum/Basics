/*
The result of this function is a matrix which transforms the verts from their position (where they were when the skeleton was bound to them) to the space of the bone when the verts were bound.
We can then append the bone's current transform in the animation to get the verts into worls space at the current point in the animation.
*/
void Cluster::computeClusterInitTransforms(FbxMesh* mesh, FbxCluster* cluster)
{
	FbxCluster::ELinkMode lClusterMode = cluster->GetLinkMode();

	FbxAMatrix lReferenceGlobalInitPosition;
	FbxAMatrix lAssociateGlobalInitPosition;
	FbxAMatrix lClusterGlobalInitPosition;

	FbxAMatrix lClusterGeometry;
	FbxAMatrix lReferenceGeometry;

	if (lClusterMode == FbxCluster::eAdditive && cluster->GetAssociateModel())
	{
		throw "Addative skinning mode not supported";
	}
	else
	{
		// Transform from the verts' local position at bind time (which is their position when loaded from file) to world space.
		cluster->GetTransformMatrix(lReferenceGlobalInitPosition);
		

		lReferenceGeometry = getGeometry(mesh->GetNode());
		lReferenceGlobalInitPosition *= lReferenceGeometry;
		// Get the link initial global position and the link current global position.
		cluster->GetTransformLinkMatrix(lClusterGlobalInitPosition);
		// Transform from world space to bones space at binding time
		FbxAMatrix globalInitPosInv = lClusterGlobalInitPosition.Inverse();
		FbxAMatrix initTransform = globalInitPosInv * lReferenceGlobalInitPosition;
		meshToBoneTransform = Matrix44<float>(
			initTransform[0][0], initTransform[0][1], initTransform[0][2], initTransform[0][3],
			initTransform[1][0], initTransform[1][1], initTransform[1][2], initTransform[1][3],
			initTransform[2][0], initTransform[2][1], initTransform[2][2], initTransform[2][3],
			initTransform[3][0], initTransform[3][1], initTransform[3][2], initTransform[3][3]);
	}
}