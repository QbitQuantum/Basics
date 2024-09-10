void SE_BoneAnimation::onUpdate(SE_TimeMS realDelta, SE_TimeMS simulateDelta, float percent, int frameIndex)
{
	if(getCurrentFrame() == frameIndex)
		return;
    if(!mSkinJointController)
        return;
    if(!mMesh)
        return;
    int surfaceNum = mMesh->getSurfaceNum();
    for(int i = 0 ; i < surfaceNum ; i++)
    {
        SE_Surface* surface = mMesh->getSurface(i);
        _Vector3f* vertex = NULL;
        int vertexNum = 0;
        int* vertexIndex = NULL;
        int vertexIndexNum = 0;
        surface->getVertex(vertex, vertexNum);
		if(!mVertex)
		{
			mVertexNum = vertexNum;
			mVertex = new _Vector3f[vertexNum];
			memcpy(mVertex, vertex, sizeof(_Vector3f) * vertexNum);
		}
        surface->getVertexIndexInGeometryData(vertexIndex, vertexIndexNum);
        if(vertex)
        {
			mSkinJointController->createBoneToWorldMatrix(frameIndex);
            for(int j = 0 ; j < vertexNum ; j++)
            {
                SE_Vector3f v(mVertex[j].d[0], mVertex[j].d[1], mVertex[j].d[2]);
				SE_Spatial* spatial = mSimObject->getSpatial();
				SE_Matrix4f worldTM = spatial->getWorldTransform();
				SE_Vector4f v4(v.x, v.y, v.z, 1.0);
				v4 = worldTM.map(v4);
				v = v4.xyz();
                v = mSkinJointController->convert(vertexIndex[j], frameIndex, v4.xyz());
                vertex[j].d[0] = v.x;
                vertex[j].d[1] = v.y;
                vertex[j].d[2] = v.z;
            }
        }
    }
}