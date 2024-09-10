//================================================================
void CVertexRingElement::init(
	const int vid, const Vector3d& pos, 
	const int nRod, const int pRingNodeID[], 
	const CMeMaterialPropertyPtr pMaterial[], 
	const Vector3d pRingNodePos[], const double edgevol[],
	CMemoryMgr &mgr)
{
	m_nVertexID = vid;
	m_nv = nRod;
	//allocate ring buffer
	m_pVertexRingNode = (CVertexRingNode*)mgr.Malloc(sizeof(CVertexRingNode)*nRod);
	//compute weight
	double weight[VERTEX_BUFFER_LENGTH];
	double totalE = 0;
	for (int i=0; i<nRod; i++) totalE += pMaterial[i]->getYoung();
	for (int i=0; i<nRod; i++) weight[i] = pMaterial[i]->getYoung()/totalE;
	
	if (m_nv >= 3){
		for (int i=0; i<nRod; i++){
			CVertexRingNode& e = m_pVertexRingNode[i];
			const Vector3d lpos = pRingNodePos[i] - pos;
			e = CVertexRingNode(pRingNodeID[i], pMaterial[i], lpos, edgevol[i], weight[i]);
		}
	}
	else{
		//BUG: here it is incompatible with the new method which computes edge forces only once 
		//need to modify this 
		assert(nRod == 2);
		Vector3d v[2];
		double3x3 rot;
		v[0]=pRingNodePos[0]-pos; v[1]=pRingNodePos[1]-pos;
		computePlanarRotationMatrix((const double*)v, sizeof(Vector3d), weight, sizeof(double), rot);
		v[0]=rot*v[0]; v[1]=rot*v[1];
		for (int i=0; i<nRod; i++){
			CVertexRingNode& e = m_pVertexRingNode[i];
			const Vector3d lpos = pRingNodePos[i] - pos;
			e = CVertexRingNode(pRingNodeID[i], pMaterial[i], v[i], edgevol[i], weight[i]);
		}
	}
	m_R.setIdentityMatrix();
	m_R0.setIdentityMatrix();
	m_quat = IdentityQuat;
	m_quat0 = IdentityQuat;
}