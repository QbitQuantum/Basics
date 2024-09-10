MT_Transform KX_Camera::GetWorldToCamera() const
{ 
	MT_Transform camtrans;
	camtrans.invert(MT_Transform(NodeGetWorldPosition(), NodeGetWorldOrientation()));
	
	return camtrans;
}