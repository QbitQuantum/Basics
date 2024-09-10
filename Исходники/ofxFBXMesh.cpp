//Compute the transform matrix that the cluster will transform the vertex.
void ofxFBXMesh::computeClusterDeformation(FbxAMatrix& pGlobalPosition,
                                           FbxMesh* pMesh,
                                           FbxCluster* pCluster,
                                           FbxAMatrix& pVertexTransformMatrix,
                                           FbxTime pTime,
                                           FbxPose* pPose) {
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
    
    ofxFBXBone* bone        = NULL;
    ofxFBXCluster* cluster  = NULL; 
    
    if(pCluster->GetLink()) {
        FbxNode* boneNode = pCluster->GetLink();
        if(boneNode->GetUserDataPtr()) {
            bone = static_cast<ofxFBXBone *>(boneNode->GetUserDataPtr());
        }
    }
    
    if(bone != NULL) {
        if(pCluster->GetUserDataPtr()) {
            cluster = static_cast<ofxFBXCluster *>(pCluster->GetUserDataPtr());
//            cluster->update( pTime, pPose );
        }
    }
    
    if( bone != NULL && cluster != NULL ) {
//        cout << "We have cached cluster and bone! " << bone->getName() << endl;
        pVertexTransformMatrix = cluster->preTrans * bone->fbxTransform * cluster->postTrans;
    } else {
        // nothing is setup for the control of the bones, so we are just doing animation
        // right now, can't do animation and control the bones at the same time.
        if (lClusterMode == FbxCluster::eAdditive && pCluster->GetAssociateModel()) {
            pCluster->GetTransformAssociateModelMatrix(lAssociateGlobalInitPosition);
            // Geometric transform of the model
            lAssociateGeometry = GetGeometry(pCluster->GetAssociateModel());
            lAssociateGlobalInitPosition *= lAssociateGeometry;
            lAssociateGlobalCurrentPosition = GetGlobalPosition(pCluster->GetAssociateModel(), pTime, pPose);
            
            pCluster->GetTransformMatrix(lReferenceGlobalInitPosition);
            // Multiply lReferenceGlobalInitPosition by Geometric Transformation
            lReferenceGeometry = GetGeometry(pMesh->GetNode());
            lReferenceGlobalInitPosition *= lReferenceGeometry;
            lReferenceGlobalCurrentPosition = pGlobalPosition;
            
            // Get the link initial global position and the link current global position.
            pCluster->GetTransformLinkMatrix(lClusterGlobalInitPosition);
            // Multiply lClusterGlobalInitPosition by Geometric Transformation
            lClusterGeometry = GetGeometry(pCluster->GetLink());
            lClusterGlobalInitPosition *= lClusterGeometry;
            lClusterGlobalCurrentPosition = GetGlobalPosition(pCluster->GetLink(), pTime, pPose);
            
            // Compute the shift of the link relative to the reference.
            //ModelM-1 * AssoM * AssoGX-1 * LinkGX * LinkM-1*ModelM
            pVertexTransformMatrix = lReferenceGlobalInitPosition.Inverse() * lAssociateGlobalInitPosition * lAssociateGlobalCurrentPosition.Inverse() *
            lClusterGlobalCurrentPosition * lClusterGlobalInitPosition.Inverse() * lReferenceGlobalInitPosition;
        } else {
            pCluster->GetTransformMatrix(lReferenceGlobalInitPosition);
            lReferenceGlobalCurrentPosition = pGlobalPosition;
            // Multiply lReferenceGlobalInitPosition by Geometric Transformation
            lReferenceGeometry = GetGeometry(pMesh->GetNode());
            lReferenceGlobalInitPosition *= lReferenceGeometry;
            
            // Get the link initial global position and the link current global position.
            pCluster->GetTransformLinkMatrix(lClusterGlobalInitPosition);
            lClusterGlobalCurrentPosition = GetGlobalPosition(pCluster->GetLink(), pTime, pPose);
            
            // Compute the initial position of the link relative to the reference.
            lClusterRelativeInitPosition = lClusterGlobalInitPosition.Inverse() * lReferenceGlobalInitPosition;
            
            // Compute the current position of the link relative to the reference.
            lClusterRelativeCurrentPositionInverse = lReferenceGlobalCurrentPosition.Inverse() * lClusterGlobalCurrentPosition;
            
            // Compute the shift of the link relative to the reference.
            pVertexTransformMatrix = lClusterRelativeCurrentPositionInverse * lClusterRelativeInitPosition;
        }
    }
}