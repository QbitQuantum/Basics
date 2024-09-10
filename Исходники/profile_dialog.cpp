void ProfileDialog::on_newToolButton_clicked()
{
    QTreeWidgetItem *item = new QTreeWidgetItem();
    profile_def *profile;
    const gchar *name = "New profile";
    GList *fl_entry = add_to_profile_list(name, "", PROF_STAT_NEW, FALSE, FALSE);

    profile = (profile_def *) fl_entry->data;
    item->setText(0, profile->name);
    item->setData(0, Qt::UserRole, qVariantFromValue(fl_entry));
    item->setFlags(item->flags() | Qt::ItemIsEditable);
    pd_ui_->profileTreeWidget->addTopLevelItem(item);
    pd_ui_->profileTreeWidget->setCurrentItem(item);
    pd_ui_->profileTreeWidget->editItem(item, 0);
}