RenderDeviceD3D::~RenderDeviceD3D()
{
	m_Swapchain->SetFullscreenState(FALSE, NULL);

	uninitialize();
	destroyDevice();
}