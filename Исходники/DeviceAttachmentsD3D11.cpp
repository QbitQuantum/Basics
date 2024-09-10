/* static */ RefPtr<DeviceAttachmentsD3D11>
DeviceAttachmentsD3D11::Create(ID3D11Device* aDevice)
{
  // We don't return null even if the attachments object even if it fails to
  // initialize, so the compositor can grab the failure ID.
  RefPtr<DeviceAttachmentsD3D11> attachments = new DeviceAttachmentsD3D11(aDevice);
  attachments->Initialize();
  return attachments.forget();
}