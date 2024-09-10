void LayerManager::initDevices()
{
	ComResult hr;

	hr = DCompositionCreateDevice2(getCurrentContext().getRenderDevice()->getDevice2(),
		__uuidof(IDCompositionDesktopDevice), &this->pDevice);
	hr = this->pDevice->CreateTargetForHwnd(getCurrentContext().getNativePointer(), true, &this->pTarget);
}