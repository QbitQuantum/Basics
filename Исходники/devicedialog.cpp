QModelIndex DeviceDialog::getDevice(DeviceModel *model)
{
    DeviceDialog deviceDialog(model);

    // Check the return value since the user may have made
    // a valid selection but clicked the cancel button
    if(deviceDialog.exec() == QDialog::Accepted) {
        return deviceDialog.selectedDeviceIndex();
    } else {
        return QModelIndex();
    }
}