void fx::InitAll(ID3D10Device* device)
{
	SkyFX     = CreateFX(device, L"sky.fx");
	CubeMapFX = CreateFX(device, L"cubemap.fx");
}