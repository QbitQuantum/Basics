void DeviceProperties::UpdateHardwareInfo() {
    // Hardware information
    QString id = index_.data(DeviceManager::Role_UniqueId).toString();
    if (DeviceLister* lister = manager_->GetLister(index_.row())) {
        QVariantMap info = lister->DeviceHardwareInfo(id);

        // Remove empty items
        for (const QString& key : info.keys()) {
            if (info[key].isNull() || info[key].toString().isEmpty())
                info.remove(key);
        }

        ui_->hardware_info_stack->setCurrentWidget(ui_->hardware_info_page);
        ui_->hardware_info->clear();
        ui_->hardware_info->setRowCount(2 + info.count());

        int row = 0;
        AddHardwareInfo(row++, tr("Model"), lister->DeviceModel(id));
        AddHardwareInfo(row++, tr("Manufacturer"), lister->DeviceManufacturer(id));
        for (const QString& key : info.keys()) {
            AddHardwareInfo(row++, tr(key.toAscii()), info[key].toString());
        }

        ui_->hardware_info->sortItems(0);
    } else {
        ui_->hardware_info_stack->setCurrentWidget(
            ui_->hardware_info_not_connected_page);
    }

    // Size
    quint64 total = index_.data(DeviceManager::Role_Capacity).toLongLong();

    QVariant free_var = index_.data(DeviceManager::Role_FreeSpace);
    if (free_var.isValid()) {
        quint64 free = free_var.toLongLong();

        ui_->free_space_bar->set_total_bytes(total);
        ui_->free_space_bar->set_free_bytes(free);
        ui_->free_space_bar->show();
    } else {
        ui_->free_space_bar->hide();
    }
}