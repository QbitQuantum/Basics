void ManageInterfacesDialog::showLocalInterfaces()
{
    guint i;
    interface_t device;
    gchar *pr_descr = g_strdup("");
    char *comment = NULL;

    ui->localList->clear();
    for (i = 0; i < global_capture_opts.all_ifaces->len; i++) {
        device = g_array_index(global_capture_opts.all_ifaces, interface_t, i);
        if (device.local && device.type != IF_PIPE && device.type != IF_STDIN) {
            QTreeWidgetItem *item = new QTreeWidgetItem(ui->localList);
            item->setFlags(item->flags() | Qt::ItemIsEditable);
            if (prefs.capture_device && strstr(prefs.capture_device, device.name)) {
                // Force the default device to be checked.
                item->setFlags(item->flags() ^ Qt::ItemIsUserCheckable);
                item->setCheckState(col_l_show_, Qt::Checked);
            } else {
                item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
                item->setCheckState(col_l_show_, device.hidden ? Qt::Unchecked : Qt::Checked);
            }
#ifdef _WIN32
            item->setText(col_l_friendly_name_, device.friendly_name);
#endif
            item->setText(col_l_local_name_, device.name);

            comment = capture_dev_user_descr_find(device.name);
            if (comment) {
                item->setText(col_l_comment_, comment);
                g_free(comment);
            } else if (device.if_info.vendor_description) {
                item->setText(col_l_comment_, device.if_info.vendor_description);
            }
        } else {
            continue;
        }
    }
    g_free(pr_descr);
}