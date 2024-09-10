void Local_Light_Editor::SetOrientation_Impl( const Quat& newRot )
{
	//mxUNUSED(newRot);
	XMMATRIX rotationMatrix = XMMatrixRotationQuaternion( newRot.quad );
	this->GetLight().m_spotDirection = XMVector3TransformNormal(
		this->GetLight().m_spotDirection,
		rotationMatrix
		);
	this->GetLight().m_spotDirection = XMVector3Normalize( this->GetLight().m_spotDirection );
}