void ComputeBoundingBoxVisitor::apply(osg::Transform& node)
{
    if(node.asMatrixTransform() || node.asPositionAttitudeTransform())
    {
        osg::Matrix prevMatrix = m_curMatrix;

        //m_curMatrix.preMult(node.asMatrixTransform()->getMatrix());
	node.computeLocalToWorldMatrix(m_curMatrix,this);

        traverse(node);

        m_curMatrix = prevMatrix;
    }
}