//--------------------------------------------------------------------
// setWorldPosition()
//--------------------------------------------------------------------
void LLJoint::setWorldPosition( const LLVector3& pos )
{
	if (mParent == NULL)
	{
		this->setPosition( pos );
		return;
	}

	LLMatrix4 temp_matrix = getWorldMatrix();
	temp_matrix.mMatrix[VW][VX] = pos.mV[VX];
	temp_matrix.mMatrix[VW][VY] = pos.mV[VY];
	temp_matrix.mMatrix[VW][VZ] = pos.mV[VZ];

	LLMatrix4 parentWorldMatrix = mParent->getWorldMatrix();
	LLMatrix4 invParentWorldMatrix = parentWorldMatrix.invert();

	temp_matrix *= invParentWorldMatrix;

	LLVector3 localPos(	temp_matrix.mMatrix[VW][VX],
						temp_matrix.mMatrix[VW][VY],
						temp_matrix.mMatrix[VW][VZ] );

	setPosition( localPos );
}