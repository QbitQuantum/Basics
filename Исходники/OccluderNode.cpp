void OccluderNode::onMoveComponentUpdate(MoveComponent& movec)
{
	const Transform& trf(movec.getWorldTransform());
	U count = m_vertsL.getSize();
	while(count--)
	{

		m_vertsW[count] = trf.transform(m_vertsL[count]);
	}

	getComponent<OccluderComponent>().setVertices(&m_vertsW[0], m_vertsW.getSize(), sizeof(m_vertsW[0]));
}