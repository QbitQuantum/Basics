void GraphicCameraEntity::UpdateOrthogonal(std::shared_ptr<CameraEntity> obj)
{
	XMMATRIX xmPrespective = XMMatrixOrthographicRH((float)this->Width, (float)this->Height,
													this->NearZ, this->FarZ);
	XMStoreFloat4x4(&this->Orthogonal, xmPrespective);
}