//-----------------------------------------------------------------------------
// Function: onTreeItemChanged()
//-----------------------------------------------------------------------------
void NewSystemPage::onTreeItemChanged(QTreeWidgetItem* cur, QTreeWidgetItem*)
{
    if (cur != 0)
    {
        // Check if the item has a VLNV (i.e. is a leaf item).
        QVariant data = cur->data(0, Qt::UserRole);

        if (!data.isNull())
        {
            VLNV compVLNV = data.value<VLNV>();
            VLNV sysVLNV = vlnvEditor_->getVLNV();

            // Auto-fill the VLNV editor information (vendor and library fields).
            vlnvEditor_->setVLNV(VLNV(VLNV::DESIGN, compVLNV.getVendor(), compVLNV.getLibrary(),
                sysVLNV.getName(), sysVLNV.getVersion()));

            // Add all available hierarchical views to the view combo box.
            QSharedPointer<LibraryComponent> libComp = libInterface_->getModel(compVLNV);
            QSharedPointer<Component> comp = libComp.staticCast<Component>();

            viewComboBox_->clear();

            foreach (QString const& viewName, comp->getHierViews())
            {
                viewComboBox_->addItem(viewName);
            }
        }