//-----------------------------------------------------------------------------
// Function: saveAs()
//-----------------------------------------------------------------------------
bool ApiDefinitionEditor::saveAs()
{
    // Ask the user for a new VLNV and directory.
    VLNV vlnv;
    QString directory;

    if (!NewObjectDialog::saveAsDialog(parentWidget(), libHandler_, *apiDef_->getVlnv(), vlnv, directory))
    {
        return false;
    }

    // Create a copy of the object and update its VLNV.
    apiDef_ = QSharedPointer<ApiDefinition>(new ApiDefinition(*apiDef_));

    vlnv.setType(VLNV::APIDEFINITION);
    apiDef_->setVlnv(vlnv);

    // Apply changes to the copy.
    applyChanges();

    if (libHandler_->writeModelToFile(directory, apiDef_))
    {
        setDocumentName(vlnv.getName() + " (" + vlnv.getVersion() + ")");
        return TabDocument::saveAs();
    }
    else
    {
        return false;
    }
}