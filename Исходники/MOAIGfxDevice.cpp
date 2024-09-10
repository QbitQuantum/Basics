//----------------------------------------------------------------//
void MOAIGfxDevice::UpdateViewVolume () {

	USMatrix4x4 invViewProj;
	invViewProj.Inverse ( this->GetViewProjMtx ());
	this->mViewVolume.Init ( invViewProj );
}