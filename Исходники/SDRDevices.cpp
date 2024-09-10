void SDRDevicesDialog::OnPropGridChanged( wxPropertyGridEvent& event ) {
    if (!editId) {
        return;
    }
    SDRDeviceInfo *dev = getSelectedDevice(editId);
    if (editId && event.GetProperty() == devSettings["name"]) {
        DeviceConfig *devConfig = wxGetApp().getConfig()->getDevice(dev->getDeviceId());
        
        wxString devName = event.GetPropertyValue().GetString();
        
        devConfig->setDeviceName(devName.ToStdString());
        if (editId) {
            devTree->SetItemText(editId, devConfig->getDeviceName());
        }
        if (devName == "") {
            event.GetProperty()->SetValueFromString(devConfig->getDeviceName());
        }
    }
    if (dev && event.GetProperty() == devSettings["offset"]) {
        DeviceConfig *devConfig = wxGetApp().getConfig()->getDevice(dev->getDeviceId());
        
        long offset = event.GetPropertyValue().GetInteger();
        
        devConfig->setOffset(offset);
    }
}