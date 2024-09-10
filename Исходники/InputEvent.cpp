ECode InputEvent::GetDevice(
    /* [out] */ IInputDevice** device)
{
    assert(device);
    Int32 deviceId;
    GetDeviceId(&deviceId);
    return CInputDevice::GetDevice(deviceId, device);
}