//-----------------------------------------------------------------------------
// Function: validate()
//-----------------------------------------------------------------------------
bool NewDesignPage::validate()
{
    VLNV vlnv = vlnvEditor_->getVLNV();
    bool validVLNV = NewPage::validate();

    VLNV designVLNV(VLNV::DESIGN, vlnv.getVendor(), vlnv.getLibrary(),
        vlnv.getName().remove(".comp") + ".design", vlnv.getVersion());
    VLNV desConfVLNV(VLNV::DESIGNCONFIGURATION, vlnv.getVendor(), vlnv.getLibrary(),
        vlnv.getName().remove(".comp") + ".designcfg", vlnv.getVersion());

    // Check if any of the VLNVs already exists.
    if (!validVLNV)
    {
        showErrorForReservedVLVN(vlnv);
        return false;
    }

    if (!isUnusedVLNV(designVLNV))
    {
        showErrorForReservedVLVN(designVLNV);
        return false;
    }

    if (!isUnusedVLNV(desConfVLNV))
    {
        showErrorForReservedVLVN(desConfVLNV);
        return false;
    }    

    return true;
}