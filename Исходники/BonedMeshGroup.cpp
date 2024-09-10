boneConstantBuffer* BonedMeshGroup::getBoneConstantBuffer(int* ids,int num){
	boneConstantBuffer* result=new boneConstantBuffer;
	XMMATRIX* m=(XMMATRIX*)malloc(40*64);;
	result->boneTrans=m;
	XMMATRIX rmatrix=XMMatrixIdentity();
	rmatrix=XMMatrixTranspose(rmatrix);
	for(int i=0;i<40;i++){
		memcpy(&m[i],&rmatrix,64);

	}
	for(int i=0;i<num;i++)
	{
		boneSample sample=m_bgroup->getBoneSample(ids[i],(int)m_CurFrame);
		boneTM first=m_bgroup->getBone(ids[i])->getFirstTM();
		XMMATRIX rmatrix=XMMatrixTranslation(-first.translate.x,-first.translate.y,-first.translate.z);		
		rmatrix*=XMMatrixRotationQuaternion(XMVectorSet(first.rotate.x,first.rotate.y,first.rotate.z,first.rotate.w));
		rmatrix*=XMMatrixRotationQuaternion(XMVectorSet(sample.tm.rotate.x,sample.tm.rotate.y,sample.tm.rotate.z,-sample.tm.rotate.w));
		rmatrix=rmatrix*XMMatrixTranslation(sample.tm.translate.x,sample.tm.translate.y,sample.tm.translate.z);
		rmatrix=XMMatrixTranspose(rmatrix);
		memcpy(&m[i],&rmatrix,64);
	}	
	
	return result;
}